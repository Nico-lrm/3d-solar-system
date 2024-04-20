#include "RenderBuffer.hpp"

namespace SPN
{
    RenderBuffer::RenderBuffer(const unsigned int& width, const unsigned int& height)
    {
        glGenRenderbuffers(1, &this->_id);
        glBindRenderbuffer(GL_RENDERBUFFER, this->_id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    }

    RenderBuffer::~RenderBuffer()
    {
        if(_id != 0)
            glDeleteRenderbuffers(1, &this->_id);
    }

    void RenderBuffer::Bind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, this->_id);
    }

    void RenderBuffer::Unbind() 
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    void RenderBuffer::Delete() 
    {
        if(_id != 0)
            glDeleteRenderbuffers(1, &this->_id);
    }
}