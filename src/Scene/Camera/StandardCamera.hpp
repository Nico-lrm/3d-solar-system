#ifndef STANDARDCAMERA_HPP
#define	STANDARDCAMERA_HPP
#pragma once

#include <iostream>
#include "Camera.hpp"

namespace SPN
{
	class StandardCamera final : public Camera
	{
		public:
			StandardCamera(const unsigned int& width, const unsigned int& height, glm::vec3 position = glm::vec3(0.0, 0.0, 0.0), glm::vec3 up = glm::vec3(0.0, 1.0, 0.0), float yaw = YAW, float pitch = PITCH);

			void Move(const CameraDirection& cam_dir, const float& deltatime) override;
			void Look(float xoffset, float yoffset) override;
			void Update(const float& deltatime) override;
	};
}

#endif