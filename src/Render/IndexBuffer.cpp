#include "IndexBuffer.hpp"

namespace SPN 
{
    IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices)
    {
        this->_indices = indices;
    }

    void IndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    }

    void IndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::Delete()
    {
        if(_id != 0)
        {
            glDeleteBuffers(1, &_id);
        }
    }
    
    void IndexBuffer::AttachData()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indices.size() * sizeof(GLuint), this->_indices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}