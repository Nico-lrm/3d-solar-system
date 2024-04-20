#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP
#pragma once

#include <condition_variable>
#include <mutex>
#include <string>
#include <memory>

#include "ComponentArray.hpp"
#include "../Entity/EntityManager.hpp"

namespace SPN
{
    // Pour l'instant, ne sert qu'a ajouter des composants aux entités -> Voir pour qu'il les stock
    class ComponentManager
    {
        private:
            std::unordered_map<std::string, std::shared_ptr<IComponentArray>> _component_array_map;
            std::unordered_map<std::string, unsigned int> _component_mask_map;
            std::mutex _mutex_component_manager;

            // Initialiser à 1 le numéro de type;
            unsigned int _next_type{0};

            template<typename T>
            std::shared_ptr<ComponentArray<T>> getComponentArray()
            {
                std::string type{ typeid(T).name() };

                if(_component_mask_map.find(type) == _component_mask_map.end())
                    throw std::runtime_error("Ce composant n'existe pas.");
                    
                return std::static_pointer_cast<ComponentArray<T>>(_component_array_map[type]);
            };

        public:
            // Partie ComponentArray
            template<typename T>
            void AddComponentType()
            {
                std::scoped_lock<std::mutex> lock(this->_mutex_component_manager);

                // Récupérer le nom de type pour éviter d'ajouter plusieurs fois le même tableau de composant;
                std::string type{ std::string(typeid(T).name()) };

                // Empêcher l'ajout d'un composant déjà existant
                if(this->_component_array_map.find(type) != this->_component_array_map.end())
                    return;
                
                // Ajouter le tableau de composant & mettre à jour la map pour les bitmask
                this->_component_array_map.insert(std::make_pair(type, std::make_shared<ComponentArray<T>>()));
                this->_component_mask_map.insert(std::make_pair(type, this->_next_type));
                this->_next_type += 1;
            }

            template<typename T>
            unsigned int GetComponentType()
            {
                // Récupérer le nom de type pour éviter d'ajouter plusieurs fois le même tableau de composant;
                std::string type { typeid(T).name() };

                if(this->_component_mask_map.find(type) == this->_component_mask_map.end())
                    throw std::runtime_error("Le type de composant spécifié n'est pas encore existant.");

                return this->_component_mask_map.at(type);
            }

            // Partie Component
            template<typename T>
            void AddComponent(const std::shared_ptr<Entity> entity, const std::shared_ptr<T> component)
            {
                // Récupérer le nom du type
                std::string type{ typeid(T).name() };

                // Récupérer le ComponentArray associé au type demandé
                std::shared_ptr<ComponentArray<T>> component_array{ getComponentArray<T>() };

                // Ajouter le composant dans le ComponentArray avec comme clé l'ID de l'entité
                component_array->AddComponent(entity, component);

                // Mettre à jour le bitmask de l'entité
                entity->_signature.set(this->_component_mask_map.at(type));
            }

            template<typename T>
            void RemoveComponent(const std::shared_ptr<Entity> entity)
            {
                // Récupérer le nom du type
                std::string type{ typeid(T).name() };

                // Récupérer le ComponentArray associé au type demandé
                std::shared_ptr<ComponentArray<T>> component_array{ getComponentArray<T>() };

                // Supprimer le composant dans le ComponentArray avec comme clé l'ID de l'entité
                component_array->RemoveComponent(entity);

                // Mettre à jour le bitmask de l'entité
                entity->_signature.reset(this->_component_mask_map.at(type));
            }

            template<typename T>
            std::shared_ptr<T> GetComponent(const std::shared_ptr<Entity> entity)
            {
                // Récupérer le nom du type
                std::string type{ typeid(T).name() };

                // Récupérer le ComponentArray associé au type demandé
                std::shared_ptr<ComponentArray<T>> component_array{ getComponentArray<T>() };

                return component_array->GetComponent(entity);
            }

            template<typename T>
            bool HasComponent(const std::shared_ptr<Entity> entity)
            {
                // Récupérer le nom du type
                std::string type{ typeid(T).name() };

                // Récupérer le ComponentArray associé au type demandé
                std::shared_ptr<ComponentArray<T>> component_array{ getComponentArray<T>() };

                return component_array->HasComponent(entity);
            }
    };
}

#endif