#ifndef ISYSTEM_HPP
#define ISYSTEM_HPP
#pragma once

#include "../Entity/EntityManager.hpp"
#include "../Component/ComponentManager.hpp"
#include "../../Camera/Camera.hpp"

namespace SPN 
{
    class ISystem
    {
        public:
            virtual void Update(const std::unique_ptr<EntityManager>& entity_manager, const std::unique_ptr<ComponentManager>& component_manager, const float& deltatime, const float& lastframe, const std::unique_ptr<Camera>& camera) = 0;
    };
}

#endif