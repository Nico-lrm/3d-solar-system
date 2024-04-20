#include "TextureFile.hpp"

namespace SPN
{
    TextureFile::TextureFile(const LoadedTextureFile& loaded_texture)
    {
        glBindTexture(GL_TEXTURE_2D, this->_id);
        
        this->_type = loaded_texture.texture_type;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);

        if (loaded_texture.srgb) 
		{
			//S'il y a bien eu recuperation de donnees, on verifie le nombre de canaux disponibles sur l'image
			if (loaded_texture.image_data.nb_channel == 4)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, loaded_texture.image_data.width, loaded_texture.image_data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, loaded_texture.image_data.data);
			else if (loaded_texture.image_data.nb_channel == 3)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, loaded_texture.image_data.width, loaded_texture.image_data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, loaded_texture.image_data.data);
			else if (loaded_texture.image_data.nb_channel == 1)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, loaded_texture.image_data.width, loaded_texture.image_data.height, 0, GL_RED, GL_UNSIGNED_BYTE, loaded_texture.image_data.data);
			else
				throw std::invalid_argument("Erreur : Impossible de detecter automatiquement le nombre de canaux de l'image\n");
		}
		else
		{
			if (loaded_texture.image_data.nb_channel == 4)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loaded_texture.image_data.width, loaded_texture.image_data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, loaded_texture.image_data.data);
			else if (loaded_texture.image_data.nb_channel == 3)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loaded_texture.image_data.width, loaded_texture.image_data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, loaded_texture.image_data.data);
			else if (loaded_texture.image_data.nb_channel == 1)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loaded_texture.image_data.width, loaded_texture.image_data.height, 0, GL_RED, GL_UNSIGNED_BYTE, loaded_texture.image_data.data);
			else
				throw std::invalid_argument("Erreur : Impossible de detecter automatiquement le nombre de canaux de l'image\n");
		}
        
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureFile::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, this->_id);
    }

    void TextureFile::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureFile::Delete()
    {
        if(_id != 0)
            glDeleteTextures(1, &this->_id);
    }
}