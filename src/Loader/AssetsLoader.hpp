#ifndef ASSETSLOADER_HPP
#define ASSETSLOADER_HPP
#pragma once

#include <mutex>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Render/Shader.hpp"
#include "../Render/Texture.hpp"
#include "../Render/Model.hpp"

namespace SPN
{
    /**
     * @brief Charge les différentes ressources, avant de les finaliser dans les managers (pour qu'elles soient utilisables)
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class AssetsLoader
    {
        private:
            void processNodeModel(aiNode* node, const aiScene* scene, const std::string& directory, LoadedModel& loaded_model, const bool& flipUV);
            LoadedMesh processMeshModel(aiMesh* mesh, const aiScene* scene, const std::string& directory, const bool& flipUV);
            void processTextureMeshModel(aiMaterial* mat, aiTextureType type, const bool& flipUV, const std::string& directory, std::vector<std::pair<std::string, LoadedTextureFile>>& textures, std::vector<std::pair<std::string, LoadedTextureFile>>& textures_loaded);
            glm::dmat4 AiMatrix4x4ToGlm(const aiMatrix4x4* from);

            std::mutex _mutex;
        public:
            AssetsLoader();

            // Texture
            std::pair<std::string, LoadedTextureFile> LoadTextureFile(const std::string& name, const std::string& filepath, const TextureType type, const bool& flipUV, const bool& SRGB);
            std::pair<std::string, LoadedTextureCubemap> LoadTextureCubemap(const std::string& name, const std::array<std::string, 6>& filepaths, const bool& SRGB);

            // Shader
            std::pair<std::string, LoadedShader> LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);

            // 3D Model
            std::pair<std::string, LoadedModel> LoadModel(const std::string& name, const std::string& filepath, const bool flipUV);
    };
}


#endif