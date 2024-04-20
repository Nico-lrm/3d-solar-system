#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP
#pragma once

#include "VertexArray.hpp"
#include "VertexBufferDouble.hpp"
#include "TextureBlank.hpp"
#include "Shader.hpp"
#include "RenderBuffer.hpp"
#include "RenderFrameBuffer.hpp"
#include "BloomFrameBuffer.hpp"
#include "../Window/Window.hpp"
#include "../UI/UserInterface.hpp"

#include <memory>

namespace SPN
{
    class RenderTarget
    {
        private:
            std::unique_ptr<VertexArray> _vao;
            std::unique_ptr<VertexBuffer> _vbo;

            std::unique_ptr<BloomFrameBuffer> _bloom_framebuffer;
            std::unique_ptr<Shader> _downscale_shader;
            std::unique_ptr<Shader> _upscale_shader;

            std::unique_ptr<RenderFrameBuffer> _render_framebuffer;
            std::unique_ptr<RenderBuffer> _renderbuffer;
            std::unique_ptr<Shader> _render_shader;

            glm::dvec2 _size;
        public:
            RenderTarget(const std::unique_ptr<Window>& window);

            void Bind();
            void Unbind();
            void Draw(const std::unique_ptr<UserInterface>& user_interface, const std::unique_ptr<Scene>& scene);

            void Blur(const float& radius);
            void Downscale();
            void Upscale(const float& radius);
    };
}

#endif