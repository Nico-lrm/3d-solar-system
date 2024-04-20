#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP
#pragma once

#include "Buffer.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace SPN 
{
    /**
     * @brief Structure qui contient l'ensemble des sommets d'un modèles
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
    };

    /**
     * @brief Stocke l'ensemble des données pour afficher un objet, doit être utilisé par un VertexArray, et doit être hérité pour être utilisé
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class VertexBuffer : public Buffer
    {
        public:
            void Bind() override;
            void Unbind() override;
            void Delete() override;

            virtual void AttachData() = 0;
            virtual unsigned int getNumberElement() = 0;
    };
}

#endif