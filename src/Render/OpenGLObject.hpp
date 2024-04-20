#ifndef OPENGLOBJECT_HPP
#define OPENGLOBJECT_HPP
#pragma once

#include <GL/glew.h>

namespace SPN 
{
    /**
     * @brief Interface utilisé par l'ensemble des éléments OpenGL
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class OpenGLObject
    {
        protected:
            GLuint _id = 0;
        public:            
            virtual void Bind() = 0;
            virtual void Unbind() = 0;
            virtual void Delete() = 0;

            inline GLuint getID() { return this->_id; };
    };
}

#endif