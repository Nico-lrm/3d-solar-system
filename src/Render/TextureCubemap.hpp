#ifndef TEXTURECUBEMAP_HPP
#define TEXTURECUBEMAP_HPP
#pragma once

#include "Texture.hpp"

#include <vector>

namespace SPN
{
    /**
     * @brief Texture cubemap, utilisé par la Skybox pour représenter le ciel
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class TextureCubemap : public Texture
    {
        private:
            std::array<std::string, 6> _filepaths;
        public:
            TextureCubemap(const LoadedTextureCubemap& loaded_texture);
            TextureCubemap(const std::array<std::string, 6>& filepaths, const bool& srgb = true);

            void Bind() override;
            void Unbind() override;
            void Delete() override;
    };
}

#endif