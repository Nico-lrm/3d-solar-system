#include "Model.hpp"

namespace SPN
{
    Model::Model(const std::pair<std::string, LoadedModel>& data, const std::unique_ptr<TextureManager>& texture_manager)
    {
        // On parcourt l'ensemble des LoadedMesh
        for(auto& loaded_mesh : data.second.meshes)
        {
            std::vector<std::shared_ptr<Texture>> textures;

            // S'il y a des textures, on les finalises puis on les ajoute à un vector pour notre maille
            for(auto& loaded_texture : loaded_mesh.textures)
            {
                texture_manager->CreateTextureFile(loaded_texture);
                textures.push_back(texture_manager->GetElement(loaded_texture.first));
            }

            // On ajoute notre maille à notre vector de maille
            _meshes.push_back(std::make_unique<Mesh>(loaded_mesh.vertices, loaded_mesh.indices, loaded_mesh.vbl, textures, loaded_mesh.opacity, loaded_mesh.transform));            
        }

        this->_directory = data.second.directory;
        this->_filename = data.second.filename;
    }

    void Model::DrawUnique(const std::shared_ptr<Shader>& shader, const glm::dmat4& model, const glm::dmat4& view, const glm::dmat4& proj)
    {
        for(auto& mesh : _meshes)
        {
            mesh->prepareMesh(shader, proj);
            mesh->DrawUnique(shader, model, view);
        }
    }
    void Model::DrawInstanced(const std::shared_ptr<Shader>& shader, const glm::dmat4& view, const glm::dmat4& proj, const unsigned int& count, const std::unique_ptr<ShaderStorage>& ssbo)
    {
        for(auto& mesh : _meshes)
        {
            mesh->prepareMesh(shader, proj);
            mesh->DrawInstanced(shader, count, ssbo, view);
        }
    }
}