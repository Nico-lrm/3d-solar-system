#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP
#pragma once

#include <queue>
#include <mutex>
#include <list>

#include "Entity.hpp"

namespace SPN 
{
    class EntityManager
    {
        private:
            std::queue<unsigned int> _id_emplace_queue;
            std::vector<std::shared_ptr<Entity>> _entities;
            std::mutex _mutex;
        public:
            EntityManager(unsigned int max_entities)
            {
                for(unsigned int i = 0; i < max_entities; i++)
                    this->_id_emplace_queue.push(i);
            }

            std::shared_ptr<Entity> createEntity()
            {
                std::scoped_lock<std::mutex> lock(_mutex);
                auto id = this->_id_emplace_queue.front();
                this->_id_emplace_queue.pop();
                this->_entities.push_back(std::make_shared<Entity>(id));
                return std::shared_ptr<Entity>(this->_entities.back());
            }

            std::vector<std::shared_ptr<Entity>> getEntities() { return this->_entities; };
    };
}

#endif