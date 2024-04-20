#ifndef VERTEXBUFFERVERTEX_HPP
#define VERTEXBUFFERVERTEX_HPP
#pragma once

#include "VertexBuffer.hpp"

namespace SPN 
{
    /**
     * @brief Buffer pour les objets où l'on peut récupérer les infos avec la structure Vertex
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class VertexBufferVertex : public VertexBuffer
    {
        private:
            std::vector<Vertex> _vertices;
        public:
            VertexBufferVertex(const std::vector<Vertex>& vertices) 
            {
                this->_vertices = vertices;
            }

            void AttachData() override
            {
                glBindBuffer(GL_ARRAY_BUFFER,_id);
                glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(Vertex), this->_vertices.data(), GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            unsigned int getNumberElement() override 
            {
                return static_cast<unsigned int>(this->_vertices.size());
            }
    };
}

#endif