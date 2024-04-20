#ifndef BUFFER_HPP
#define BUFFER_HPP
#pragma once

#include "OpenGLObject.hpp"

namespace SPN 
{
    /**
     * @brief Classe devant être hérité pour les différents buffers OpenGL (hormis Framebuffer)
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class Buffer : public OpenGLObject
    {
        public:
            Buffer()
            {
                glGenBuffers(1, &(this->_id));
            }
            ~Buffer()
            {
                if(_id != 0)
                    glDeleteBuffers(1, &this->_id);
            }
    };
}

#endif