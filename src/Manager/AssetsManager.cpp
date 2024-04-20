#include "AssetsManager.hpp"

namespace SPN
{
    AssetsManager::AssetsManager()
    {
        this->_model_manager = std::make_unique<ModelManager>();
        this->_shader_manager = std::make_unique<ShaderManager>();
        this->_texture_manager = std::make_unique<TextureManager>();
    }

    // ShaderManager
    std::shared_ptr<Shader> AssetsManager::GetShader(const std::string& index)
    {
        return this->_shader_manager->GetElement(index);
    }

    void AssetsManager::DeleteShader(const std::string& index)
    {
        this->_shader_manager->DeleteElement(index);
    }

    void AssetsManager::CreateShader(const std::pair<std::string, LoadedShader>& data)
    {
        this->_shader_manager->CreateShader(data);
    }

    // TextureManager
    std::shared_ptr<Texture> AssetsManager::GetTexture(const std::string& index)
    {
        return this->_texture_manager->GetElement(index);
    }

    void AssetsManager::DeleteTexture(const std::string& index)
    {
        this->_texture_manager->DeleteElement(index);
    }
    
    void AssetsManager::CreateTextureFile(const std::pair<std::string, LoadedTextureFile>& data)
    {
        this->_texture_manager->CreateTextureFile(data);
    }

    void AssetsManager::CreateTextureCubemap(const std::pair<std::string, LoadedTextureCubemap>& data)
    {
        this->_texture_manager->CreateTextureCubemap(data);
    }

    // MeshManager
    std::shared_ptr<Model> AssetsManager::GetModel(const std::string& index)
    {
        return this->_model_manager->GetElement(index);
    }
    
    void AssetsManager::DeleteElement(const std::string& index)
    {
        this->_model_manager->DeleteElement(index);
    }

    void AssetsManager::CreateModel(const std::pair<std::string, LoadedModel>& data)
    {
        this->_model_manager->CreateModel(data, this->_texture_manager);
    }
}