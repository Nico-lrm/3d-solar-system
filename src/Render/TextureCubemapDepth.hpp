#ifndef TEXTURECUBEMAPDEPTH_HPP
#define TEXTURECUBEMAPDEPTH_HPP
#pragma once

#include "Texture.hpp"

namespace SPN
{
    /**
     * @brief Texture cubemap pour la profondeur, utilisé pour calculer les ombres (shadowmapping)
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
	class TextureCubemapDepth : public Texture
	{
		public:
			TextureCubemapDepth(const unsigned int resolution);

            void Bind() override;
            void Unbind() override;
            void Delete() override;
	};
}

#endif