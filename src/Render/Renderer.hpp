#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <stdexcept>
#include <memory>

#include "../Window/Window.hpp"
#include "../Scene/Scene.hpp"
#include "Skybox.hpp"
#include "RenderTarget.hpp"
#include "OrbitRenderer.hpp"
#include "DepthFramebuffer.hpp"
#include "Frustum.hpp"

namespace SPN
{
   
   class Renderer final
   {
      private:
         std::unique_ptr<Skybox> _skybox;
         std::unique_ptr<RenderTarget> _render_target;
         std::unique_ptr<OrbitRenderer> _orbit_renderer;
         std::unique_ptr<DepthFramebuffer> _depth_fbo;

         unsigned int _width{ 0 };
         unsigned int _height{ 0 };
         
      public:
         Renderer(const std::unique_ptr<Window>& window);
         
         void Clear();
         void SetClearColor(const glm::vec4 &color);
         void SetClearColor(const float& x, const float& y, const float& z);
         void SetViewport(unsigned width, unsigned height);

         void ApplyLights(const std::unique_ptr<Scene>& scene, const std::shared_ptr<Shader>& shader);
         void DrawScene(const std::unique_ptr<Scene>& scene, const std::unique_ptr<UserInterface>& user_interface, const float& deltatime, const float& lastframe);
         void DrawShadow(const std::unique_ptr<Scene>& scene, const float& deltatime, const float& lastframe);
   };
}

#endif