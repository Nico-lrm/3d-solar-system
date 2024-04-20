#ifndef ECS_HPP
#define ECS_HPP
#pragma once

#include <mutex>
#include "Entity/EntityManager.hpp"
#include "Component/ComponentManager.hpp"
#include "System/SystemManager.hpp"

/**
 * @brief Système ECS en headers-only pour gérer les templates
 * 
*/

namespace SPN 
{
    class ECS 
    {
        protected:
            std::unique_ptr<EntityManager> _entity_manager;
            std::unique_ptr<ComponentManager> _component_manager;
            std::unique_ptr<SystemManager> _system_manager;
        public:
            // Initialisation
            ECS(unsigned int max_entity = 100)
            {
                this->_entity_manager = std::make_unique<EntityManager>(max_entity);
                this->_component_manager = std::make_unique<ComponentManager>();
                this->_system_manager = std::make_unique<SystemManager>();
            }

            // Entity
            std::shared_ptr<Entity> CreateEntity()
            {
                return this->_entity_manager->createEntity();
            }

            std::vector<std::shared_ptr<Entity>> getEntities() { return this->_entity_manager->getEntities(); };

            // Component
            template<typename T>
            void AddComponentType()
            {
                this->_component_manager->AddComponentType<T>();
            }

            template<typename T>
            unsigned int GetComponentType()
            {
                return this->_component_manager->GetComponentType<T>();
            }

            template<typename T>
            void AddComponent(const std::shared_ptr<Entity> entity, const std::shared_ptr<T> component)
            {
                this->_component_manager->AddComponent<T>(entity, component);
            }

            template<typename T>
            void RemoveComponent(const std::shared_ptr<Entity> entity)
            {
                this->_component_manager->RemoveComponent<T>(entity);
            }

            template<typename T>
            std::shared_ptr<T> GetComponent(const std::shared_ptr<Entity> entity)
            {
                return this->_component_manager->GetComponent<T>(entity);
            }

            template<typename T>
            bool HasComponent(const std::shared_ptr<Entity> entity)
            {
                return this->_component_manager->HasComponent<T>(entity);
            }

            // System
            virtual void Update(const float& deltatime, const float& lastframe)
            {
                //this->_system_manager->Update(this->_entity_manager, this->_component_manager, deltatime, )
            }
    };
}

#endif