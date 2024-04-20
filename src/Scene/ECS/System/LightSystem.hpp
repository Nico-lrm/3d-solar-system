#ifndef LIGHTSYSTEM_HPP 
#define LIGHTSYSTEM_HPP
#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <mutex>
#include <vector>
#include <future>
#include <execution>

#include "ISystem.hpp"

namespace SPN
{
    class LightSystem : public ISystem
    {
        private:
            std::mutex _mutex;
        public:
            LightSystem() {}
            void Update(const std::unique_ptr<EntityManager>& entity_manager, const std::unique_ptr<ComponentManager>& component_manager, const float& deltatime, const float& lastframe, const std::unique_ptr<Camera>& camera) override
            {
                // Récupérer l'ensemble des entités
                auto entities{ entity_manager->getEntities() };

                // Parcourir l'ensemble des entités
                for(unsigned int i = 0; i < entities.size(); i++)
                {
                    if(component_manager->HasComponent<LightComponent>(entities.at(i)) && component_manager->HasComponent<TransformComponent>(entities.at(i)))
                    {
                        // Récupérer les composants utiles pour le système
                        auto lc{ component_manager->GetComponent<LightComponent>(entities.at(i)) };
                        auto tc{ component_manager->GetComponent<TransformComponent>(entities.at(i)) };

                        // On vide le tableau des anciennes valeurs
                        lc->shadow_transforms.clear();

                        // Matrice de projection
                        glm::dmat4 shadowProj = glm::perspective(glm::radians(90.0), 8192.0 / 8192.0, camera->getNear(), camera->getFar());
                        lc->shadow_transforms.push_back(shadowProj * glm::lookAt(tc->position - camera->getPosition(), tc->position - camera->getPosition() + glm::dvec3(1.0f, 0.0f, 0.0f), glm::dvec3(0.0f, -1.0f, 0.0f)));
                        lc->shadow_transforms.push_back(shadowProj * glm::lookAt(tc->position - camera->getPosition(), tc->position - camera->getPosition() + glm::dvec3(-1.0f, 0.0f, 0.0f), glm::dvec3(0.0f, -1.0f, 0.0f)));
                        lc->shadow_transforms.push_back(shadowProj * glm::lookAt(tc->position - camera->getPosition(), tc->position - camera->getPosition() + glm::dvec3(0.0f, 1.0f, 0.0f), glm::dvec3(0.0f, 0.0f, 1.0f)));
                        lc->shadow_transforms.push_back(shadowProj * glm::lookAt(tc->position - camera->getPosition(), tc->position - camera->getPosition() + glm::dvec3(0.0f, -1.0f, 0.0f), glm::dvec3(0.0f, 0.0f, -1.0f)));
                        lc->shadow_transforms.push_back(shadowProj * glm::lookAt(tc->position - camera->getPosition(), tc->position - camera->getPosition() + glm::dvec3(0.0f, 0.0f, 1.0f), glm::dvec3(0.0f, -1.0f, 0.0f)));
                        lc->shadow_transforms.push_back(shadowProj * glm::lookAt(tc->position - camera->getPosition(), tc->position - camera->getPosition() + glm::dvec3(0.0f, 0.0f, -1.0f), glm::dvec3(0.0f, -1.0f, 0.0f)));
                    }
                }
            };
    };
}

#endif