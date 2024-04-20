#ifndef ORBITRENDERER_HPP
#define ORBITRENDERER_HPP
#pragma once

#include "VertexArray.hpp"
#include "VertexBufferDouble.hpp"
#include "Shader.hpp"

#include "../Scene/Scene.hpp"

#include <memory>

#define M_PI           3.14159265358979323846

namespace SPN
{
    /**
     * @brief Classe permettant de calculer et d'afficher les orbites circulaires des objets
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class OrbitRenderer
    {
        private:
            std::unique_ptr<VertexArray> _vao;
            std::unique_ptr<VertexBuffer> _vbo;
            std::unique_ptr<Shader> _shader;
            std::vector<float> _orbit_vertex;
            void CalcModelTranslate(glm::dmat4& model, std::shared_ptr<Entity>& entity, const std::unique_ptr<Scene>& scene);
        public:
            OrbitRenderer();
            void DrawOrbit(const std::unique_ptr<Scene>& scene, const float& deltatime, const float& lastframe);
    };
}

#endif