#include "VertexBufferLayout.hpp"

namespace SPN
{
    VertexBufferLayout::VertexBufferLayout() : _stride(0), _number_per_row(0)
    {}

    void VertexBufferLayout::Push(const unsigned int count, const std::string& name) 
    {
        VertexBufferElement vbe = {
            .count = count,
            .name = name
        };

        this->_elementArray.push_back(vbe); 
        this->_stride += sizeof(float) * count;
        this->_number_per_row += count;
    };
}
