#include "DepthFramebuffer.hpp"

namespace SPN
{
	DepthFramebuffer::DepthFramebuffer(const unsigned int& resolution)
	{
		std::string main_dir{ "C:/Users/lormi/Documents/PROJET_LORMIER_21502501/" };
		//std::string main_dir{ "" };

		this->_shadow_resolution = resolution;
		this->m_TexturePtr = std::make_shared<TextureCubemapDepth>(resolution);
		this->m_ShaderPtr = std::make_shared<Shader>(main_dir + "assets/shader/depthshadow.vert", main_dir + "assets/shader/depthshadow.frag", main_dir + "assets/shader/depthshadow.geom");

		this->Bind();
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->m_TexturePtr->getID(), 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("Le BloomFramebuffert n'est pas complet !");

		this->Unbind();
	}
}