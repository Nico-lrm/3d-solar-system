#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP
#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace SPN 
{
    /**
     * @brief Element utilisé par le VertexBufferLayout
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    struct VertexBufferElement
    {
        unsigned int count;
        std::string name;
    };
    /**
     * @brief Permet de définir le modèle du VertexBuffer - Ne fonctionne qu'avec des float
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class VertexBufferLayout
    {
        private:
            std::vector<VertexBufferElement> _elementArray;
            unsigned int _stride;
            unsigned int _number_per_row;

        public:
            VertexBufferLayout();

            void Push(const unsigned int count, const std::string& name);

            inline const std::vector<VertexBufferElement> getElements() {  return this->_elementArray; };
            inline unsigned int getStride() { return this->_stride; };
            inline unsigned int getNumberPerRow() { return this->_number_per_row; };
    };
}

#endif