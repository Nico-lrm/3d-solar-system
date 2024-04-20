#ifndef SHADERSTORAGE_HPP
#define SHADERSTORAGE_HPP
#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <memory>

#include "Buffer.hpp"
#include "Shader.hpp"

namespace SPN 
{
    /**
     * @brief Structure utilisé pour calculer les anneaux d'astéroide
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    struct ModelData
    {
        glm::vec3 displacement;
        float rotation_angle;
        glm::vec3 rotation_vec;
        glm::vec3 scale;
    };

    /**
     * @brief Buffer permettant de passer de grande quantité de données aux shaders, utile pour le dessin instancié
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class ShaderStorage final : public Buffer
    {
        private:
            bool _hasData;
            bool _hasPendingUpdate;
            std::vector<glm::mat4> _models;
            GLvoid* pointer;

            GLuint _ssbo_id;
            static GLuint _next_id;
        public:
            ShaderStorage(const unsigned int& count, std::vector<ModelData>& data);
            
            void Bind() override;
            void Unbind() override;
            void Delete() override;

            void AttachData();
            void AttachBuffer(const std::shared_ptr<Shader>& shader, const char* name);

            void setModels(const std::vector<glm::mat4>& models) { this->_models = models; }
            void setPendingUpdate(const bool& value) { this->_hasPendingUpdate = value; }
            bool hasPendingUpdate() { return this->_hasPendingUpdate; }

            unsigned int getSize() { return static_cast<unsigned int>(this->_models.size()); };
    };
}

#endif