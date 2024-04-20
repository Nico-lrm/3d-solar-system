#include "StandardCamera.hpp"

namespace SPN
{
	StandardCamera::StandardCamera(const unsigned int& width, const unsigned int& height, glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Camera(position, up, yaw, pitch)
	{
		this->_width = width;
		this->_height = height;
	}

	void StandardCamera::Move(const CameraDirection& cam_dir, const float& deltatime)
	{
		double velocity{ _movement_speed * static_cast<double>(deltatime) };
		switch (cam_dir)
		{
			case CameraDirection::FORWARD:
				_target_position += _orientation * velocity;
			break;
			case CameraDirection::BACKWARD:
				_target_position -= _orientation * velocity;
			break;
			case CameraDirection::LEFT:
				_target_position -= _right * velocity;
			break;
			case CameraDirection::RIGHT:
				_target_position += _right * velocity;
			break;
			case CameraDirection::UP:
				_target_position += _up * velocity;
			break;
			case CameraDirection::DOWN:
				_target_position -= _up * velocity;
			break;
		}
	}
	void StandardCamera::Look(float xoffset, float yoffset)
	{
		float x = xoffset;
		float y = yoffset;
		x *= this->_sensitivity;
		y *= this->_sensitivity;

		this->_yaw += x;
		this->_pitch += y;

		if (_pitch > 89.0f)
        	_pitch = 89.0f;
		if (_pitch < -89.0f)
			_pitch = -89.0f;
	}

	void StandardCamera::Update(const float& deltatime)
	{
		_position = glm::lerp(_position, _target_position, 1.0 * static_cast<double>(deltatime));
		_orientation = glm::lerp(_orientation, _target_orientation, 3.0 * static_cast<double>(deltatime));
		updateVector();
	}
}