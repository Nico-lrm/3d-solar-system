#ifndef MESH_HPP
#define MESH_HPP
#pragma once

#include <vector>
#include <optional>

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferDouble.hpp"
#include "VertexBufferVertex.hpp"
#include "Shader.hpp"
#include "ShaderStorage.hpp"
#include "Texture.hpp"

namespace SPN
{
    /**
     * @brief Structure contenant l'ensemble de données chargés pour créer une maille, utilisé pour le chargement asynchrone
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    struct LoadedMesh
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<std::pair<std::string, LoadedTextureFile>> textures;
        VertexBufferLayout vbl;
        float opacity;
        glm::dmat4 transform;
    };

    /**
     * @brief Classe représentant une maille d'un modèle 3D
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class Mesh final
    {
        private:
            std::unique_ptr<VertexArray> _vao;
            std::unique_ptr<VertexBufferLayout> _vbl;
            std::unique_ptr<VertexBuffer> _vbo;
            std::unique_ptr<IndexBuffer> _ibo;
            std::vector<std::shared_ptr<Texture>> _textures;

            // Transformation de dessin
            float _opacity = 1.f;
            glm::dmat4 _transform;

        public:
            // Maille créée à partir d'un fichier
            Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices,const VertexBufferLayout& vbl, const std::vector<std::shared_ptr<Texture>>& textures, const float& opacity, const glm::dmat4& transform);

            // Maille à partir de données seulement des sommets
            Mesh(const std::vector<float>& vertices, const VertexBufferLayout& vbl, const std::vector<std::shared_ptr<Texture>> textures = std::vector<std::shared_ptr<Texture>>());

            // Dessin d'une maille
            void prepareMesh(const std::shared_ptr<Shader>& shader, const glm::dmat4& proj);
            void DrawUnique(const std::shared_ptr<Shader>& shader, const glm::dmat4& model, const glm::dmat4& view);
            void DrawInstanced(const std::shared_ptr<Shader>& shader, const unsigned int& count, const std::unique_ptr<ShaderStorage>& ssbo, const glm::dmat4& view);
    };
}


#endif