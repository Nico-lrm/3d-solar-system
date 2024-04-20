#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP
#pragma once

#include <vector>
#include "ISystem.hpp"
#include "AsteroidSystem.hpp"
#include "GravitySystem.hpp"
#include "LightSystem.hpp"

namespace SPN 
{
    class SystemManager
    {
        private:
            std::vector<std::unique_ptr<ISystem>> _systems;
        public:
            SystemManager()
            {
                // Ajout des différents systèmes
                this->_systems.push_back(std::make_unique<AsteroidSystem>());
                this->_systems.push_back(std::make_unique<GravitySystem>());
                this->_systems.push_back(std::make_unique<LightSystem>());
            }

            void Update(const std::unique_ptr<EntityManager>& entity_manager, const std::unique_ptr<ComponentManager>& component_manager, const float& deltatime, const float& lastframe, const std::unique_ptr<Camera>& camera)
            {
                for(const auto& system : this->_systems)
                {
                    system->Update(entity_manager, component_manager, deltatime, lastframe, camera);
                }
            }
    };
}

#endif