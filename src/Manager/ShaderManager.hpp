#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP
#pragma once

#include <tuple>

#include "Manager.hpp"

#include "../Render/Shader.hpp"

namespace SPN 
{
    /**
     * @brief Gestion des shaders
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class ShaderManager : public Manager<std::string, Shader>
    {
        public:
            ShaderManager();

            // Get & Delete (Thread-safe)
            std::shared_ptr<Shader> GetElement(const std::string& index) override;
            void DeleteElement(const std::string& index) override;

            // Création du Shader (Thread-unsafe, toujours sur le main thread)
            void CreateShader(const std::pair<std::string, LoadedShader>& data);
    };
}


#endif