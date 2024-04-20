#ifndef VERTEXBUFFERDOUBLE_HPP
#define VERTEXBUFFERDOUBLE_HPP
#pragma once

#include "VertexBuffer.hpp"

namespace SPN 
{
    /**
     * @brief Buffer pour les objets où l'on peut récupérer les infos sans la structure Vertex
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class VertexBufferDouble : public VertexBuffer
    {
        private:
            std::vector<float> _vertices;
        public:
            VertexBufferDouble(const std::vector<float> vertices) 
            {
                this->_vertices = vertices;
            }

            void AttachData() override
            {
                glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(float), this->_vertices.data(), GL_STATIC_DRAW);
            }

            unsigned int getNumberElement() override 
            {
                return static_cast<unsigned int>(this->_vertices.size());
            }
    };
}

#endif