#ifndef ASSETSMANAGER_HPP
#define ASSETSMANAGER_HPP
#pragma once

#include "ShaderManager.hpp"
#include "TextureManager.hpp"
#include "ModelManager.hpp"

namespace SPN
{
    /**
     * @brief Gestion des diverses ressources utilisées dans l'application
     * @author Nicolas LORMIER
     * @date 14/01/2023
    */
    class AssetsManager
    {
        private:
            std::unique_ptr<ShaderManager> _shader_manager;
            std::unique_ptr<TextureManager> _texture_manager;
            std::unique_ptr<ModelManager> _model_manager;
            
        public:
            AssetsManager();

            // ShaderManager
            std::shared_ptr<Shader> GetShader(const std::string& index);
            void DeleteShader(const std::string& index);
            void CreateShader(const std::pair<std::string, LoadedShader>& data);

            // TextureManager
            std::shared_ptr<Texture> GetTexture(const std::string& index);
            void DeleteTexture(const std::string& index);
            void CreateTextureFile(const std::pair<std::string, LoadedTextureFile>& data);
            void CreateTextureCubemap(const std::pair<std::string, LoadedTextureCubemap>& data);

            // ModelManager
            std::shared_ptr<Model> GetModel(const std::string& index);
            void DeleteElement(const std::string& index);
            void CreateModel(const std::pair<std::string, LoadedModel>& data);
    };
}


#endif