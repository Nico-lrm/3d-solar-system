#include "VertexBuffer.hpp"

namespace SPN
{
    void VertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, this->_id);
    }

    void VertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Delete()
    {
        if(_id != 0)
            glDeleteBuffers(1, &this->_id);
    }
}