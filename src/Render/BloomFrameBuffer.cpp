#include "BloomFrameBuffer.hpp"

namespace SPN
{
    BloomFrameBuffer::BloomFrameBuffer(const unsigned int& width, const unsigned int& height)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, this->_id);

        // Préparation de la chaîne de mipmap, moins gourmand que les regénérer à chaque fois
        glm::vec2 mip_size{ glm::vec2(width, height) };
        for(unsigned int i = 0; i < 6; i++)
        {
            BloomMip mip {
                .size = glm::vec2(0.0),
                .texture = nullptr
            };

            // Sauvegarder la taille de la texture et la générer
            mip_size *= 0.5f;
            mip.size = mip_size;
            mip.texture = std::make_shared<TextureBlank>(static_cast<unsigned int>(mip.size.x), static_cast<unsigned int>(mip.size.y), true);

            // Ajouter la texture à la chaîne
            this->_mip_chain.emplace_back(mip);
        }

        // Ajouter la première texture comme destination de dessin
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _mip_chain.at(0).texture->getID(), 0);

        unsigned int attachments[1]{ GL_COLOR_ATTACHMENT0 };
	    glDrawBuffers(1, attachments);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("Le BloomFramebuffert n'est pas complet !");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}