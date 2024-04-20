#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP
#pragma once

#include <memory>

#include "OpenGLObject.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace SPN 
{
    /**
     * @brief Contient l'ensemble des informations (quelle donnée est placé où, comment lire les données...) permettant de dessiner un objet, doit être utilisé avec au minimum
     * un VertexBuffer, et en option un IndexBuffer
     * @author Nicolas LORMIER
     * @date 18/03/2023
    */
    class VertexArray final : public OpenGLObject
    {
        public:
            VertexArray();
            ~VertexArray();

            void Bind() override;
            void Unbind() override;
            void Delete() override;

            void AddBufferAndLayout(const std::unique_ptr<VertexBuffer>& vb, const std::unique_ptr<VertexBufferLayout>& layout);
            void AddBufferAndLayout(const std::unique_ptr<VertexBuffer>& vb, const std::unique_ptr<IndexBuffer>& ib, const std::unique_ptr<VertexBufferLayout>& layout);
    };
}

#endif