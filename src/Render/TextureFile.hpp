#ifndef TEXTUREFILE_HPP
#define TEXTUREFILE_HPP
#pragma once

#include "Texture.hpp"

namespace SPN 
{
    /**
     * @brief Texture créer à partir d'un fichier
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class TextureFile final : public Texture
    {
        private:
            std::string _filepath;
        public:
            TextureFile(const LoadedTextureFile& loaded_texture);

            void Bind() override;
            void Unbind() override;
            void Delete() override;
    };
}

#endif