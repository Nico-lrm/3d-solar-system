#ifndef GRAVITYSYSTEM_HPP 
#define GRAVITYSYSTEM_HPP
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
    // Constante gravitationnelle
    constexpr double GRAV_CONST{ 6.674e-9 };

    class GravitySystem : public ISystem
    {
        private:
            std::mutex _mutex;

            float CalculVelociteInitiale(std::shared_ptr<Entity>& entity, const std::unique_ptr<ComponentManager>& component_manager, const float& deltatime)
            {
                if(!component_manager->HasComponent<GravityComponent>(entity) || !component_manager->HasComponent<TransformComponent>(entity))
                    return 0.0;
                
                auto gc{ component_manager->GetComponent<GravityComponent>(entity) };
                auto tc{ component_manager->GetComponent<TransformComponent>(entity) }; 

                if(gc->entity_reference != nullptr)
                {
                    auto tc_2{ component_manager->GetComponent<TransformComponent>(gc->entity_reference) };
                    auto gc_2{ component_manager->GetComponent<GravityComponent>(gc->entity_reference) };
                    
                    double velocity_z { std::sqrt(GRAV_CONST * gc_2->masse / glm::distance(tc->position, tc_2->position)) };

                    if(gc_2->entity_reference != nullptr)
                    {
                        auto tc_3{ component_manager->GetComponent<TransformComponent>(gc_2->entity_reference) };
                        auto gc_3{ component_manager->GetComponent<GravityComponent>(gc_2->entity_reference) }; 

                        velocity_z += std::sqrt(GRAV_CONST * gc_3->masse / glm::distance(tc_2->position, tc_3->position));
                    }

                    return static_cast<float>(velocity_z);
                }
                else
                {
                    return 0.0;
                }
            };

        public:
            GravitySystem() {}
            void Update(const std::unique_ptr<EntityManager>& entity_manager, const std::unique_ptr<ComponentManager>& component_manager, const float& deltatime, const float& lastframe, const std::unique_ptr<Camera>& camera) override
            {
                auto entities{ entity_manager->getEntities() };
                for(auto i = 0; i < entities.size(); i++)
                {
                    auto& ett{ entities.at(i) };
                    if(component_manager->HasComponent<GravityComponent>(ett) && component_manager->HasComponent<TransformComponent>(ett))
                    {
                        auto gc{ component_manager->GetComponent<GravityComponent>(ett) };
                        auto tc{ component_manager->GetComponent<TransformComponent>(ett) };

                        if(tc->velocity.z == 0.0)
                        {
                            tc->velocity.z = CalculVelociteInitiale(ett, component_manager, deltatime);
                        }
                        else
                        {
                            // On initialise un total des forces gravitationnelle qui jouent sur le deplacement de notre objet a 0;
                            glm::dvec3 totalForceGravitationnelle = glm::dvec3(0.0f, 0.0f, 0.0f);

                            for(auto j = 0; j < entities.size(); j++)
                            {
                                auto ett_2 = entities.at(j);
                                if(component_manager->HasComponent<GravityComponent>(ett_2) && component_manager->HasComponent<TransformComponent>(ett_2))
                                {
                                    auto gc_2{ component_manager->GetComponent<GravityComponent>(ett_2) };
                                    auto tc_2{ component_manager->GetComponent<TransformComponent>(ett_2) };

                                    // Si les deux objets sont différents, alors on peut calculer leur attraction
                                    if(tc->position != tc_2->position)
                                    {
                                        double force{ -GRAV_CONST * gc->masse * gc_2->masse / std::pow(glm::distance(tc->position, tc_2->position), 2) };
                                        glm::dvec3 forceDirection{ glm::normalize(tc->position - tc_2->position) };
                                        totalForceGravitationnelle += forceDirection * force;
                                    }
                                }
                            }
                            tc->velocity += totalForceGravitationnelle / gc->masse * static_cast<double>(deltatime);
                        }
                    }
                }

                for(auto& ett : entities)
                {
                    if(component_manager->HasComponent<GravityComponent>(ett) && component_manager->HasComponent<TransformComponent>(ett))
                    {
                        auto tc{ component_manager->GetComponent<TransformComponent>(ett) };
                        tc->position += tc->velocity * static_cast<double>(deltatime);
                    }
                }
            }
    };
}

#endif