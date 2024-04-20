#ifndef RENDERFRAMEBUFFER_HPP
#define RENDERFRAMEBUFFER_HPP
#pragma once

#include <memory>

#include "TextureBlank.hpp"
#include "Shader.hpp"
#include "FrameBuffer.hpp"

namespace SPN
{
    class RenderFrameBuffer : public FrameBuffer
    {
        private:
            std::unique_ptr<TextureBlank> _texture;
        public:
            RenderFrameBuffer(const unsigned int& width, const unsigned int& height, const GLuint& renderbuffer_id);
            std::unique_ptr<TextureBlank>& getRenderTexture() { return this->_texture; }
    };
}

#endif