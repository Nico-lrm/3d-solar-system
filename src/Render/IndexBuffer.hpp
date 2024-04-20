#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP
#pragma once

#include <vector>

#include "Buffer.hpp"

namespace SPN 
{
    /**
     * @brief Classe représentant les indices des sommets, utilisés de pair avec un VertexArray et un VertexBuffer
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class IndexBuffer final : public Buffer
    {
        private:
            std::vector<unsigned int> _indices;
        public:
            IndexBuffer(const std::vector<unsigned int>& indices);
            
            void Bind() override;
            void Unbind() override;
            void Delete() override;

            void AttachData();
            inline unsigned int getNbElements() { return static_cast<unsigned int>(this->_indices.size()); }
    };
}

#endif