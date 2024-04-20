#include "TextureBlank.hpp"

namespace SPN
{
    TextureBlank::TextureBlank(const unsigned int& width, const unsigned int& height, const bool& is_float_texture, const bool& srgb)
    {
        glBindTexture(GL_TEXTURE_2D, this->_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.f);

        if(is_float_texture)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
        }
        else
        {
            if(srgb)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            else
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureBlank::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, this->_id);
    }

    void TextureBlank::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureBlank::Delete()
    {
        if(_id != 0)
            glDeleteTextures(1, &this->_id);
    }
}