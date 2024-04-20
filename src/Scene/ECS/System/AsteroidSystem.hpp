#ifndef ASTEROIDSYSTEM_HPP 
#define ASTEROIDSYSTEM_HPP
#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <mutex>
#include <vector>
#include <future>
#include <execution>

#include "ISystem.hpp"
#include "../../../Render/Frustum.hpp"

namespace SPN
{
    class AsteroidSystem : public ISystem
    {
        private:
            std::mutex _mutex;
        public:
            AsteroidSystem() {}
            void Update(const std::unique_ptr<EntityManager>& entity_manager, const std::unique_ptr<ComponentManager>& component_manager, const float& deltatime, const float& lastframe, const std::unique_ptr<Camera>& camera) override
            {
                // Récupérer l'ensemble des entités
                auto entities{ entity_manager->getEntities() };

                for(auto& entity : entities)
                {
                    if(!component_manager->HasComponent<TransformComponent>(entity) || !component_manager->HasComponent<RingComponent>(entity))
                        continue;
                    
                    // On récupère les composants de notre entité
                    auto tc{ component_manager->GetComponent<TransformComponent>(entity) };
                    auto rc{ component_manager->GetComponent<RingComponent>(entity) };

                    // On initialise le vecteur de models qui sera utilisé par le SSBO et le mutex pour bloquer lors de l'ajout
                    std::vector<glm::mat4> models;
                    std::mutex mutex;

                    // On récupère le frustum et la position de la camera
                    auto frustum{ createFrustumFromCamera(camera) };
                    auto camera_pos{ glm::vec3(camera->getPosition()) };

                    // Pour chaque asteroides, on lance l'execution de cette partie en asynchrone
                    std::for_each(std::execution::par_unseq, rc->data.begin(), rc->data.end(), [&](ModelData& model_data) {

                        // Si l'astéroide actuel est dans le frustum, alors on le mets à jour et on l'ajoute pour le prochain rendu
                        if(isOnFrustum(frustum, glm::vec3(tc->position) - camera_pos + model_data.displacement, model_data.scale))
                        {
                            // Matrice de modèle
                            auto model{ glm::mat4(1.0) };

                            // On déplace d'abord le model à la position de son astre
                            model = glm::translate(model, glm::vec3(tc->position - camera->getPosition()));

                            // On effectue les différentes transformations
                            model = glm::translate(model, model_data.displacement);
                            model = glm::rotate(model, glm::radians(model_data.rotation_angle) * lastframe * 0.1f, model_data.rotation_vec);
                            model = glm::scale(model, model_data.scale);

                            // On ajoute à la liste des modèles
                            std::lock_guard<std::mutex> lock(mutex);
                            models.push_back(model);
                        }   
                    });
                    
                    // On mets à jour le SSBO pour le prochain rendu
                    rc->shader_storage->setModels(models);
                    rc->previous_position = tc->position;
                    rc->shader_storage->AttachData();    
                }
            };
    };
}

#endif