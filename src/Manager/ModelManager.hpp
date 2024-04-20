#ifndef MODELMANAGER_HPP
#define MODELMANAGER_HPP
#pragma once

#include "../Render/Model.hpp"
#include "TextureManager.hpp"

namespace SPN
{
    /**
     * @brief Gestion des modèles 3D
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class ModelManager : public Manager<std::string, Model>
    {
        public:
            ModelManager();

            // Get & Delete
            std::shared_ptr<Model> GetElement(const std::string& index) override;
            void DeleteElement(const std::string& index) override;

            // Créer un modèle à partir d'un chargement
            void CreateModel(const std::pair<std::string, LoadedModel>& data, const std::unique_ptr<TextureManager>& texture_manager);
    };
}



#endif