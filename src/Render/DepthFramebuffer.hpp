#ifndef DEPTHFRAMEBUFFER_HPP
#define DEPTHFRAMEBUFFER_HPP
#pragma once

#include <memory>

#include "TextureCubemapDepth.hpp"
#include "FrameBuffer.hpp"
#include "Shader.hpp"

namespace SPN
{
    /**
     * @brief Framebuffer dessinant la profondeur des objets, utilisé pour dessiner les ombres projetées
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
	class DepthFramebuffer : public FrameBuffer
	{
		private:
			std::shared_ptr<TextureCubemapDepth> m_TexturePtr;
			std::shared_ptr<Shader> m_ShaderPtr;
			unsigned int _shadow_resolution;
		public:
			DepthFramebuffer(const unsigned int& resolution);
			std::shared_ptr<TextureCubemapDepth> getTexture() { return this->m_TexturePtr; }
			std::shared_ptr<Shader> getShader() { return this->m_ShaderPtr; }
			unsigned int getShadowResolution() { return this->_shadow_resolution; }
	};
}


#endif