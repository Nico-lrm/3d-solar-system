#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#pragma once

#include <memory>
#include <future>
#include <execution>
#include <glm/glm.hpp>
#include <mutex>
#include <optional>

#include "../../../Render/Model.hpp"
#include "../../../Render/DepthFramebuffer.hpp"
#include "../../../Render/ShaderStorage.hpp"
#include "../Entity/Entity.hpp"

namespace SPN
{
    struct TransformComponent
    {
        glm::dvec3 position;
        double rotation_angle;
        glm::dvec3 rotation_vec;
        glm::dvec3 scale;
        glm::dvec3 velocity = glm::dvec3(0.0, 0.0, 0.0);
    };

    struct GravityComponent
    {
        double diametre;
        double masse;
        std::shared_ptr<Entity> entity_reference; // On calcule la vitesse initiale grâce à une "référence" d'une autre entité (ex: la Lune tourne autour de la Terre, qui tourne autour du Soleil)
    };

    struct MaterialComponent
    {
        std::shared_ptr<Model> model;
        std::shared_ptr<Shader> shader;
    };

    struct LightComponent
    {
        glm::vec3 color;
        std::vector<glm::dmat4> shadow_transforms;
    };

    struct AtmosphereComponent
    {
        glm::vec3 atmosphere_color;
        float atmosphere_intensity;
        float atmosphere_radius;
        glm::vec3 atmosphere_scattering;
        glm::vec3 mie_coeff;
        float planet_radius;
        glm::vec3 rayleigh_coeff;
    };

    struct OrbitComponent
    {
        float initial_x_position;
        glm::vec3 line_color;
    };

    enum class RingDirection
    {
        HORIZONTAL,
        VERTICAL
    };

    struct RingComponent
    {
        glm::vec3 previous_position;
        unsigned int count;
        std::unique_ptr<ShaderStorage> shader_storage;
        std::vector<ModelData> data;
        std::shared_ptr<Model> model;
        std::shared_ptr<Shader> shader;

        RingComponent(const unsigned int& count, const float& radius, const float& offset, const float& divider, const float& varia, const RingDirection& direction, const std::shared_ptr<Model> model, const std::shared_ptr<Shader> shader)
        {
            // Attribuer les valeurs pour le dessin
            this->count = count;
            this->model = model;
            this->shader = shader;
            this->previous_position = glm::vec3(0.0);

            // Valeur utilisées pour calculer les positions des éléments
            unsigned int j{ 0 };
            std::mutex mutex;

            // Initialiser en premier les différents ModelData dans le vecteur
            for(unsigned int i = 0; i < count; i++)
            {
                this->data.push_back(ModelData());
            }

            // Calculer les positions de chaque éléments et les sauvegarder
            auto prepare = std::async(std::launch::async, [&]() {
                std::for_each(std::execution::par, data.begin(), data.end(), [&](ModelData& model_data) {
                    double angle{ 0. };
                    {
                        std::scoped_lock<std::mutex> lock(mutex);
                        angle = (double)j++ / (double)count * 360.;
                    }
                    double displacement = 0.0;
                    double x = 0.0;
                    double y = 0.0;
                    if(direction == RingDirection::HORIZONTAL)
                    {
                        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
                        x = sin(glm::radians(angle)) * radius + displacement;
                        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
                        y = displacement * 0.1f;
                    }
                    else
                    {
                        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
                        x = displacement * 0.1f;
                        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
                        y = sin(glm::radians(angle)) * radius + displacement;
                    }
                    displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
                    float z = cos(glm::radians(angle)) * radius + displacement;

                    model_data.displacement = glm::dvec3(x, y, z);
                    //model_data->scale = glm::vec3(static_cast<float>((rand() % 3) / 5));
                    model_data.scale = glm::dvec3(static_cast<float>((rand() % 3) / divider + varia));
                    model_data.rotation_vec = glm::vec3(glm::vec3(((rand() % 20 - 10) / 100.), ((rand() % 20 - 10) / 100.), ((rand() % 20 - 10) / 100.)));
                    model_data.rotation_angle = static_cast<float>(rand() % 360);
                });
            });
            prepare.wait();     

            this->shader_storage = std::make_unique<ShaderStorage>(count, data);
        }
    };

    struct DescriptorComponent
    {
        std::string nom;
        std::string type;
        std::vector<std::tuple<std::string, std::string, std::optional<std::string>>> _infos;
        std::vector<std::pair<std::string, std::string>> _compositions_atmo;
    };
}

#endif