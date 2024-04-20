#ifndef SCENE_HPP
#define SCENE_HPP
#pragma once

#include <future>

#include "ECS/ECS.hpp"
#include "Camera/StandardCamera.hpp"

namespace SPN
{
    class Scene : public ECS
    {
        private:
            std::unique_ptr<Camera> _camera = nullptr;
        public:
            Scene(const unsigned int& width, const unsigned int& height, const unsigned int& max_entities = 100);
            void Update(const float& deltatime, const float& lastframe) override;

            // Caméra
            void MoveCamera(const CameraDirection& cam_dir, const float& deltatime);
            void LookCamera(float xoffset, float yoffset);
            const std::unique_ptr<Camera>& getCamera() { return this->_camera; };
            void MoveCamera(glm::vec3 new_pos) { this->_camera->MoveCamera(new_pos); };

            // Getter
            inline glm::dmat4 getViewMatrix(){ return this->_camera->getViewMatrix(); };
            inline glm::dmat4 getProjMatrix(){ return this->_camera->getProjMatrix(); };
            inline glm::dmat4 getViewProjMatrix(){ return this->_camera->getViewProjMatrix(); };
            inline glm::dvec3 getCameraPosition() { return this->_camera->getPosition(); }
            inline glm::dvec3 getCameraRight() { return this->_camera->getRight(); }
            inline glm::dvec3 getCameraUp() { return this->_camera->getUp(); }
            inline glm::dvec3 getCameraOrientation() { return this->_camera->getOrientation(); }
            inline double getCameraNear() { return this->_camera->getNear(); }
            inline double getCameraFar() { return this->_camera->getFar(); }
            inline double getCameraAspect() { return this->_camera->getAspect(); }
            inline double getCameraFovY() { return this->_camera->getFovY(); }
    };
};

#endif