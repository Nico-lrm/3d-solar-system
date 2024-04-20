#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP
#pragma once

#include "OpenGLObject.hpp"
#include <stdexcept>

namespace SPN
{
    /**
     * @brief Classe devant être hérité pour les différents Framebuffers OpenGL (hormis Buffer standard)
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class FrameBuffer : public OpenGLObject
    {
        public:
            FrameBuffer()
            {
                glGenFramebuffers(1, &this->_id);
            }

            ~FrameBuffer()
            {
                if(this->_id != 0)
                    glDeleteFramebuffers(1, &this->_id);
            }

            void Bind() override
            {
                glBindFramebuffer(GL_FRAMEBUFFER, this->_id);

            }

            void Unbind() override
            {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }

            void Delete() override
            {
                if(this->_id != 0)
                    glDeleteFramebuffers(1, &this->_id);
            }
    };
}

#endif