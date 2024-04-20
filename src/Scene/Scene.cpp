#include "Scene.hpp"

namespace SPN
{
	Scene::Scene(const unsigned int& width, const unsigned int& height, const unsigned int& max_entities) : ECS(max_entities)
	{
		this->_camera = std::make_unique<StandardCamera>(width, height, glm::vec3(1500.0, 0., 3.5));
	}

	void Scene::Update(const float& deltatime, const float& lastframe)
	{
		this->_camera->Update(deltatime);
		this->_system_manager->Update(this->_entity_manager, this->_component_manager, deltatime, lastframe, this->_camera);
	}

	void Scene::MoveCamera(const CameraDirection& cam_dir, const float& deltatime)
	{
		this->_camera->Move(cam_dir, deltatime);
	}

	void Scene::LookCamera(float xoffset, float yoffset)
	{
		this->_camera->Look(xoffset, yoffset);
	}
}