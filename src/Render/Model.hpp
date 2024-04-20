#ifndef MODEL_HPP
#define MODEL_HPP
#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Mesh.hpp"
#include "../Manager/TextureManager.hpp"


namespace SPN
{
    /**
     * @brief Structure contenant l'ensemble de données chargés pour créer un modèle 3D, utilisé pour le chargement asynchrone
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    struct LoadedModel
    {
        std::vector<LoadedMesh> meshes;
        std::string directory;
        std::string filename;
    };

    /**
     * @brief Classe représentant un modèle 3D
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class Model final
    {
        private:
            std::vector<std::unique_ptr<Mesh>> _meshes;
            std::string _directory;
            std::string _filename;

        public:
            Model(const std::pair<std::string, LoadedModel>& data, const std::unique_ptr<TextureManager>& texture_manager);
            void DrawUnique(const std::shared_ptr<Shader>& shader, const glm::dmat4& model, const glm::dmat4& view, const glm::dmat4& proj);
            void DrawInstanced(const std::shared_ptr<Shader>& shader, const glm::dmat4& view, const glm::dmat4& proj, const unsigned int& count, const std::unique_ptr<ShaderStorage>& ssbo);
    };
}


#endif