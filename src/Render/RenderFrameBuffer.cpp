#include "RenderFrameBuffer.hpp"

namespace SPN
{
    RenderFrameBuffer::RenderFrameBuffer(const unsigned int& width, const unsigned int& height, const GLuint& renderbuffer_id)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, this->_id);

        this->_texture = std::make_unique<TextureBlank>(width, height, true);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getID(), 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer_id); 

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("Le framebuffer n'est pas complet !");

        unsigned int attachments[1]{ GL_COLOR_ATTACHMENT0 };
	    glDrawBuffers(1, attachments);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}