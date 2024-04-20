#ifndef SKYBOX_HPP 
#define SKYBOX_HPP
#pragma once

#include "TextureCubemap.hpp"
#include "VertexArray.hpp"
#include "VertexBufferDouble.hpp"
#include "Shader.hpp"

#include <memory>
#include <glm/glm.hpp>

namespace SPN
{
    /**
     * @brief Classe représentant le "ciel" de notre rendu, ici, l'espace
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class Skybox
    {
        private:
            // Ne pas modifier, valeur par défaut
            std::unique_ptr<VertexArray> _vao;
            std::unique_ptr<VertexBuffer> _vbo;
            std::unique_ptr<Shader> _shader;

            // Peut être modifié, on attache une texture pour que la skybox change
            std::unique_ptr<Texture> _texture_skybox;
        public:
            Skybox();
            void Draw(const glm::mat4& view, const glm::mat4& proj);
    };
}

#endif