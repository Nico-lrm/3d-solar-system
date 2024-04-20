#ifndef RENDERBUFFER_HPP
#define RENDERBUFFER_HPP
#pragma once

#include "OpenGLObject.hpp"

namespace SPN
{
    /**
     * @brief Framebuffer spécialisé dans le calcul de la profondeur, utilisé comme composant d'un Framebuffer
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class RenderBuffer : public OpenGLObject
    {
        public:
            RenderBuffer(const unsigned int& width, const unsigned int& height);
            ~RenderBuffer();

            void Bind() override;
            void Unbind() override;
            void Delete() override;
    };
}

#endif