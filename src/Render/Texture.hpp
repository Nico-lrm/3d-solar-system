#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#pragma once

#include <string>
#include <array>
#include <stdexcept>
#include <iostream>

#include "OpenGLObject.hpp"

#include "stb/stb_image.h"

namespace SPN 
{
    /**
     * @brief Les différents types de texture de l'application
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    enum TextureType
    {
        Texture_DIFFUSE,
        Texture_SPECULAR,
        Texture_NORMAL,
        Texture_HEIGHT,
        Texture_EMISSIVE,
        Texture_AMBIENT,
        Texture_SKYBOX
    };
    /**
     * @brief Les données d'une image chargée avec stbi, utile pour l'asynchrone
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    struct ImageData
    {
        int width;
        int height;
        int nb_channel;
        unsigned char* data;
    };

    /**
     * @brief Structure qui contient l'ensemble des infos pour créer une texture, utilisé pour l'asynchrone
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    struct LoadedTextureFile
    {
        std::string filepath;
        TextureType texture_type;
        bool srgb;
        ImageData image_data;
    };

    /**
     * @brief Structure qui contient l'ensemble des infos pour créer une texture cubemap, utilisé pour l'asynchrone
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    struct LoadedTextureCubemap
    {
        std::array<std::string, 6> filepaths;
        std::array<ImageData, 6> image_datas;
        bool srgb;
    };

    /**
     * @brief Classe qui doit être hérité pour être utilisé, contient les infos mini. pour créer une texture OpenGL
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class Texture : public OpenGLObject
    {
        protected:
            TextureType _type;
        public:
            Texture()
            {
                glGenTextures(1, &this->_id);
            }
            ~Texture()
            {
                if(this->_id != 0)
                    glDeleteTextures(1, &this->_id);
            }

            inline TextureType getTextureType() { return this->_type; }
    };
}

#endif