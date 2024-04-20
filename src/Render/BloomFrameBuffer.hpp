#ifndef BLOOMFRAMEBUFFER_HPP
#define BLOOMFRAMEBUFFER_HPP
#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "TextureBlank.hpp"
#include "FrameBuffer.hpp"

namespace SPN
{
    /**
     * @brief Chaîne de mipmap pour créer un bloom
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    struct BloomMip
    {
        glm::vec2 size;
        std::shared_ptr<TextureBlank> texture;
    };

    /**
     * @brief Framebuffer afin de réaliser un effet de bloom sur une texture
     * qui sera utilisé lors du rendu final de la scène
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class BloomFrameBuffer : public FrameBuffer
    {
        private:
            std::vector<BloomMip> _mip_chain;
        public:
            BloomFrameBuffer(const unsigned int& width, const unsigned int& height);

            std::vector<BloomMip>& getMipChain() { return this->_mip_chain; };
            std::shared_ptr<TextureBlank> getBloomTexture() 
            { 
                if(this->_mip_chain.size() > 0)
                {
                    return this->_mip_chain.at(0).texture; 
                }
                return nullptr;
            }
    };
};

#endif