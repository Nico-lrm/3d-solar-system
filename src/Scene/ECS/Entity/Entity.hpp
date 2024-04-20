#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once

#include <bitset>
#include <unordered_map>
#include <string>

namespace SPN 
{
    constexpr unsigned int MAX_COMPONENT{ 16 };
    
    struct Entity
    {
        // Définir l'identifiant a la création de la structure
        Entity(unsigned int id) : _id(id) {};

        friend bool operator==(const Entity& e1, const Entity& e2)
        {
            return e1._id == e2._id;
        }

        friend bool operator<(const Entity& e1, const Entity& e2)
        {
            return e1._id < e2._id;
        }

        friend bool operator>(const Entity& e1, const Entity& e2)
        {
            return e1._id > e2._id;
        }
        
        unsigned int _id;
        std::bitset<MAX_COMPONENT> _signature;
    };
}

#endif