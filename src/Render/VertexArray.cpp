#include "VertexArray.hpp"

namespace SPN 
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &_id);
    }
    
    VertexArray::~VertexArray()
    {
        if(_id != 0)
        {
            glDeleteVertexArrays(1, &_id);
        }    
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(this->_id);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    void VertexArray::Delete()
    {
        if(_id != 0)
        {
            glDeleteVertexArrays(1, &_id);
        }
    }

    void VertexArray::AddBufferAndLayout(const std::unique_ptr<VertexBuffer>& vb, const std::unique_ptr<VertexBufferLayout>& layout)
    {
        // Connecter les buffers
        this->Bind();
        vb->Bind();

        // Appliquer le layout
        GLuint offset = 0;
        GLuint i = 0;
        for(VertexBufferElement vbe : layout->getElements())
        {
            glEnableVertexAttribArray(i);
	        glVertexAttribPointer(i, vbe.count, GL_FLOAT, GL_FALSE, layout->getStride(), (void*)offset); 
            offset += vbe.count * sizeof(float);
            i++;
        }

        // Déconnecter les buffers
        this->Unbind();
        vb->Unbind();
    }

    void VertexArray::AddBufferAndLayout(const std::unique_ptr<VertexBuffer>& vb, const std::unique_ptr<IndexBuffer>& ib, const std::unique_ptr<VertexBufferLayout>& layout)
    {
        // Connecter les buffers
        this->Bind();
        vb->Bind();
        ib->Bind();

        // Appliquer le layout
        GLuint offset = 0;
        GLuint i = 0;
        for(VertexBufferElement vbe : layout->getElements())
        {
            glEnableVertexAttribArray(i);
	        glVertexAttribPointer(i, vbe.count, GL_FLOAT, GL_FALSE, layout->getStride(), (void*)offset); 
            offset += vbe.count * sizeof(float);
            i++;
        }

        // Déconnecter les buffers
        this->Unbind();
        vb->Unbind();
        ib->Unbind();
    }
}