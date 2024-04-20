#ifndef COMPONENTARRAY_HPP
#define COMPONENTARRAY_HPP
#pragma once

#include <mutex>
#include "../Entity/Entity.hpp"
#include "Component.hpp"


namespace SPN
{
    // Interface pour le stockage dans le ComponentManager
    class IComponentArray
    {
        public:
            virtual ~IComponentArray() = default;
    };

    template <typename T>
    class ComponentArray : public IComponentArray
    {
        private:
            std::unordered_map<unsigned int, std::shared_ptr<T>> _component_map;
            std::mutex _mutex_component_array;

        public:
            void AddComponent(const std::shared_ptr<Entity>& entity, const std::shared_ptr<T> component)
            {
                std::scoped_lock<std::mutex> lock(this->_mutex_component_array);

                if(this->_component_map.find(entity->_id) != this->_component_map.end())
                    return;
                
                this->_component_map.insert(std::make_pair(entity->_id, component));
            };

            void RemoveComponent(std::shared_ptr<Entity> entity)
            {          
                std::scoped_lock<std::mutex> lock(this->_mutex_component_array);

                if(this->_component_map.find(entity->_id) == this->_component_map.end())
                    return;
                
                this->_component_map.erase(entity->_id);
            };

            std::shared_ptr<T> GetComponent(const std::shared_ptr<Entity> entity)
            {
                if(this->_component_map.find(entity->_id) == this->_component_map.end())
                    throw std::runtime_error("Impossible de trouver le composant pour l'entité.");

                return std::shared_ptr<T>(this->_component_map.at(entity->_id));
            };

            bool HasComponent(const std::shared_ptr<Entity> entity)
            {
                if(this->_component_map.find(entity->_id) == this->_component_map.end())
                    return false;

                return true;
            }
    };
}

#endif