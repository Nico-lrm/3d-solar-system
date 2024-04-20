#ifndef TEXTUREBLANK_HPP
#define TEXTUREBLANK_HPP
#pragma once

#include "Texture.hpp"

namespace SPN 
{
    /**
     * @brief Texture vide, sert pour dessiner la scène dans la texture grâce aux framebuffers
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class TextureBlank final : public Texture
    {
        public:
            TextureBlank(const unsigned int& width, const unsigned int& height, const bool& is_float_texture, const bool& srgb = true);

            void Bind() override;
            void Unbind() override;
            void Delete() override;
    };
}

#endif