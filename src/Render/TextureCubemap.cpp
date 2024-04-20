#include "TextureCubemap.hpp"

namespace SPN
{
    TextureCubemap::TextureCubemap(const LoadedTextureCubemap& loaded_texture)
    {
	    glBindTexture(GL_TEXTURE_CUBE_MAP, this->_id);

        this->_type = TextureType::Texture_SKYBOX;
        this->_filepaths = loaded_texture.filepaths;

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.f);

        for(unsigned int i = 0; i < 6; i++)
        {
            if(loaded_texture.srgb)
            {
                if (loaded_texture.image_datas.at(i).nb_channel == 4)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB_ALPHA, loaded_texture.image_datas.at(i).width, loaded_texture.image_datas.at(i).height, 0, GL_RGBA, GL_UNSIGNED_BYTE, loaded_texture.image_datas.at(i).data);
                else if (loaded_texture.image_datas.at(i).nb_channel == 3)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB_ALPHA, loaded_texture.image_datas.at(i).width, loaded_texture.image_datas.at(i).height, 0, GL_RGB, GL_UNSIGNED_BYTE, loaded_texture.image_datas.at(i).data);
                else if (loaded_texture.image_datas.at(i).nb_channel == 1)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB_ALPHA, loaded_texture.image_datas.at(i).width, loaded_texture.image_datas.at(i).height, 0, GL_RED, GL_UNSIGNED_BYTE, loaded_texture.image_datas.at(i).data);
                else
                    throw std::runtime_error(std::string("Erreur : Impossible de detecter automatiquement le nombre de canaux de l'image " + loaded_texture.filepaths.at(i)).c_str());
            }
            else
            {
                if (loaded_texture.image_datas.at(i).nb_channel == 4)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, loaded_texture.image_datas.at(i).width, loaded_texture.image_datas.at(i).height, 0, GL_RGBA, GL_UNSIGNED_BYTE, loaded_texture.image_datas.at(i).data);
                else if (loaded_texture.image_datas.at(i).nb_channel == 3)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, loaded_texture.image_datas.at(i).width, loaded_texture.image_datas.at(i).height, 0, GL_RGB, GL_UNSIGNED_BYTE, loaded_texture.image_datas.at(i).data);
                else if (loaded_texture.image_datas.at(i).nb_channel == 1)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, loaded_texture.image_datas.at(i).width, loaded_texture.image_datas.at(i).height, 0, GL_RED, GL_UNSIGNED_BYTE, loaded_texture.image_datas.at(i).data);
                else
                    throw std::runtime_error(std::string("Erreur : Impossible de detecter automatiquement le nombre de canaux de l'image " + loaded_texture.filepaths.at(i)).c_str());
            }
        }  

        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);  
    }

    
    TextureCubemap::TextureCubemap(const std::array<std::string, 6>& filepaths, const bool& srgb)
    {
	    glBindTexture(GL_TEXTURE_CUBE_MAP, this->_id);

        this->_type = TextureType::Texture_SKYBOX;
        this->_filepaths = filepaths;

        for(unsigned int i = 0; i < 6; i++)
        {
            int width, height, nb_channel;
            auto data{ stbi_load(filepaths.at(i).c_str(), &width, &height, &nb_channel, 0) };
            if(!data)
                throw std::runtime_error(std::string("Erreur : Impossible de lire l'image " + filepaths.at(i)).c_str());

            if(srgb)
            {
                if (nb_channel == 4)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                else if (nb_channel == 3)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                else if (nb_channel == 1)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB_ALPHA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
                else
                    throw std::runtime_error(std::string("Erreur : Impossible de detecter automatiquement le nombre de canaux de l'image " + filepaths.at(i)).c_str());
            }
            else
            {
                if (nb_channel == 4)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                else if (nb_channel == 3)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                else if (nb_channel == 1)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
                else
                    throw std::runtime_error(std::string("Erreur : Impossible de detecter automatiquement le nombre de canaux de l'image " + filepaths.at(i)).c_str());
            }
        }  

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.f);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);  
    }

    void TextureCubemap::Bind()
    {
	    glBindTexture(GL_TEXTURE_CUBE_MAP, this->_id);
    }

    void TextureCubemap::Unbind()
    {
	    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void TextureCubemap::Delete()
    {
        if(this->_id != 0)
            glDeleteTextures(1, &this->_id);
    }
}