#include "TextureCubemapDepth.hpp"

namespace SPN
{
	TextureCubemapDepth::TextureCubemapDepth(const unsigned int resolution)
	{
		this->Bind();

	for (unsigned int i = 0; i < 6; ++i)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT32F,resolution, resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		this->Unbind();
	}

    void TextureCubemapDepth::Bind()
    {
	    glBindTexture(GL_TEXTURE_CUBE_MAP, this->_id);
    }

    void TextureCubemapDepth::Unbind()
    {
	    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void TextureCubemapDepth::Delete()
    {
        if(this->_id != 0)
            glDeleteTextures(1, &this->_id);
    }
}
