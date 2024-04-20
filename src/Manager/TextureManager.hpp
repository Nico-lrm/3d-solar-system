#ifndef TEXTUREMANAGERMANAGER_HPP
#define TEXTUREMANAGERMANAGER_HPP
#pragma once

#include <stb/stb_image.h>

#include "Manager.hpp"

#include "../Render/TextureFile.hpp"
#include "../Render/TextureCubemap.hpp"

namespace SPN 
{
    /**
     * @brief Gestion des textures
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class TextureManager : public Manager<std::string, Texture>
    {
        public:
            TextureManager();

            // Get & Delete
            std::shared_ptr<Texture> GetElement(const std::string& index) override;
            void DeleteElement(const std::string& index) override;
            
            // Création
            void CreateTextureFile(const std::pair<std::string, LoadedTextureFile>& data);
            void CreateTextureCubemap(const std::pair<std::string, LoadedTextureCubemap>& data);
    };
}


#endif