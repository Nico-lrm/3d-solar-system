#include "OrbitRenderer.hpp"

namespace SPN
{
    OrbitRenderer::OrbitRenderer()
    {
        std::string main_dir{ "C:/Users/lormi/Documents/PROJET_LORMIER_21502501/" };
        //std::string main_dir{ "" };

        GLfloat xx;
        GLfloat zz;
        float angl;

        for (int i = 0; i < 2000; i++)
        {
            angl = (float)(M_PI / 2 - i * (M_PI / 1000));
            xx = sin(angl) * 100.0f;
            zz = cos(angl) * 100.0f;
            _orbit_vertex.push_back(xx);
            _orbit_vertex.push_back(0.0f);
            _orbit_vertex.push_back(zz);
        }

        this->_vao = std::make_unique<VertexArray>();
        this->_vbo = std::make_unique<VertexBufferDouble>(this->_orbit_vertex);

        this->_vao->Bind();
        this->_vbo->Bind();

        this->_vbo->AttachData();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
        glEnableVertexAttribArray(0);

        this->_vao->Unbind();
        this->_vbo->Unbind();     
        this->_shader = std::make_unique<Shader>(main_dir + "assets/shader/simple.vert", main_dir + "assets/shader/simple.frag");
        glLineWidth(1.0f);
    }

    void OrbitRenderer::DrawOrbit(const std::unique_ptr<Scene>& scene, const float& deltatime, const float& lastframe)
    {
        // Récupérer l'ensemble des entités
        auto entities{ scene->getEntities() };

        // Récupérer les types et variables nécessaires pour le dessin
        auto gravity_type{ scene->GetComponentType<GravityComponent>() };
        auto transform_type{ scene->GetComponentType<TransformComponent>() };
        auto orbit_type{ scene->GetComponentType<OrbitComponent>() };
        auto camera_pos{ scene->getCameraPosition() };

        // Récupérer les matrices de la caméra
        auto view{ scene->getViewMatrix() };
        auto proj{ scene->getProjMatrix() };

        // Attacher le shader pour le dessin d'orbites et passer les matrices au shader
        this->_shader->Bind();
        this->_vao->Bind();
        this->_shader->setMat4("viewProj", proj * view);

        // Pour chaque entités
        for(auto& ett : entities)
        {
            // Si l'entité ne possède pas ces composants, alors on passe a l'entité suivante
            if(!ett->_signature.test(orbit_type) || !ett->_signature.test(transform_type) || !ett->_signature.test(gravity_type))
                continue;

            auto orbit_ett{ scene->GetComponent<OrbitComponent>(ett) };
            auto gc_ett{ scene->GetComponent<GravityComponent>(ett) };
            auto transform_ett{ scene->GetComponent<TransformComponent>(ett) };

            // Matrice de modèle, utilisé pour représenter la ligne de l'orbite dans l'espace
            auto model_matrix{ glm::dmat4(1.) };

            // Déplacer la ligne d'orbite
            if(gc_ett->entity_reference != nullptr)
            {
                auto transform_ett_2{ scene->GetComponent<TransformComponent>(gc_ett->entity_reference) };
                model_matrix = glm::translate(model_matrix, transform_ett_2->position - camera_pos);
            }
            else
            {
                model_matrix = glm::translate(model_matrix, glm::dvec3(0.0) - camera_pos);
            }

            // Mettre à l'échelle la ligne d'orbite
            if(gc_ett->entity_reference != nullptr && scene->HasComponent<OrbitComponent>(gc_ett->entity_reference))
            {
                auto orbit_2{ scene->GetComponent<OrbitComponent>(gc_ett->entity_reference) };
                model_matrix = glm::scale(model_matrix, glm::dvec3((orbit_ett->initial_x_position - orbit_2->initial_x_position) / 100));
            }
            else
            {
                model_matrix = glm::scale(model_matrix, glm::dvec3(orbit_ett->initial_x_position / 100));
            }

            // Attacher au shader la couleur de l'orbite et la matrice de modèle
            this->_shader->setMat4("model", model_matrix);
            this->_shader->setVec3("color", orbit_ett->line_color);
            this->_shader->setFloat("near", .00001);
            this->_shader->setFloat("far", 46000.0f);

            // Dessiner la ligne d'orbite
            glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)_orbit_vertex.size() / 3);
        }
        this->_vao->Unbind();
        this->_shader->Unbind();
    }
}