#ifndef SHADER_HPP
#define SHADER_HPP
#pragma once

#include "OpenGLObject.hpp"
#include <stdexcept>

#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace SPN 
{
    /**
     * @brief Structure contenant l'ensemble de données chargés pour créer un shader, utilisé pour le chargement asynchrone
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    struct LoadedShader
    {
        std::string v_shader_code;
        std::string f_shader_code;
        std::optional<std::string> g_shader_code;
    };

    /**
     * @brief Classe représentant un shader OpenGL
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class Shader final : public OpenGLObject
    {
        public:
            // Génération via asynchrone -> Pour les utilisateurs & différentes scènes
            Shader(const LoadedShader& loaded_shader);

            // Génération pour les composants de l'application
            Shader(const std::string& vertexPath, const std::string& fragmentPath);
            Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);

            void Bind() override;
            void Unbind() override;
            void Delete() override;

            // Fonctions pour les uniforms
            // ---------------------------
            void setBool(const std::string& name, bool value) ;
            // ------------------------------------------------------------------------
            void setInt(const std::string& name, int value) ;
            // ------------------------------------------------------------------------
            void setFloat(const std::string& name, float value) ;
            // ------------------------------------------------------------------------
            void setVec2(const std::string& name, const glm::vec2& value) ;
            void setVec2(const std::string& name, float x, float y) ;
            // ------------------------------------------------------------------------
            void setVec3(const std::string& name, const glm::vec3& value) ;
            void setVec3(const std::string& name, float x, float y, float z) ;
            // ------------------------------------------------------------------------
            void setVec4(const std::string& name, const glm::vec4& value) ;
            void setVec4(const std::string& name, float x, float y, float z, float w) ;
            // ------------------------------------------------------------------------
            void setMat2(const std::string& name, const glm::mat2& mat) ;
            void setMat3(const std::string& name, const glm::mat3& mat) ;
            void setMat4(const std::string& name, const glm::mat4& mat) ;
    };
}


#endif