#include "Mesh.hpp"

namespace SPN
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices,const VertexBufferLayout& vbl, const std::vector<std::shared_ptr<Texture>>& textures, const float& opacity, const glm::dmat4& transform)
    {
        this->_opacity = opacity;
        this->_textures = textures;
        this->_transform = transform;

        this->_vao = std::make_unique<VertexArray>();
        this->_vbo = std::make_unique<VertexBufferVertex>(vertices);
        this->_vbl = std::make_unique<VertexBufferLayout>(vbl);
        this->_ibo = std::make_unique<IndexBuffer>(indices);

        _vbo->AttachData();
        _ibo->AttachData();
        _vao->AddBufferAndLayout(_vbo, _ibo, _vbl);
    }

    Mesh::Mesh(const std::vector<float>& vertices, const VertexBufferLayout& vbl, const std::vector<std::shared_ptr<Texture>> textures)
    {
        this->_opacity = 1.f;
        this->_textures = textures;
        this->_transform = glm::dmat4(1.f);

        this->_vao = std::make_unique<VertexArray>();
        this->_vbo = std::make_unique<VertexBufferDouble>(vertices);
        this->_vbl = std::make_unique<VertexBufferLayout>(vbl);
        this->_ibo = nullptr;

        _vbo->AttachData();
        _vao->AddBufferAndLayout(_vbo, _vbl);
    }
    void Mesh::prepareMesh(const std::shared_ptr<Shader>& shader, const glm::dmat4& proj)
    {
        shader->setFloat("mat.opacity", _opacity);
        shader->setMat4("proj", proj);
        
        // Attacher la bonne texture au shader
        unsigned int diffuseNr{ 1 };
        unsigned int specularNr{ 1 };
        unsigned int normalNr{ 1 };
        unsigned int heightNr{ 1 };
        unsigned int emissiveNr{ 1 };
        unsigned int ambientNr{ 1 };

        // Attacher chaque texture
        for (unsigned int i = 0; i < this->_textures.size(); i++)
        {
            auto texture{ this->_textures.at(i) };
            // On active le textureUnit avant d'attacher notre texture
            glActiveTexture(GL_TEXTURE0 + i + 1);

            std::string number;
            std::string name;
            TextureType texType{ texture->getTextureType() };

            switch (texType)
            {
                case TextureType::Texture_DIFFUSE:
                    name = "texture_diffuse";
                    number = std::to_string(diffuseNr++);
                    break;
                case TextureType::Texture_SPECULAR:
                    name = "texture_specular";
                    number = std::to_string(specularNr++);
                    break;
                case TextureType::Texture_NORMAL:
                    name = "texture_normal";
                    number = std::to_string(normalNr++);
                    break;
                case TextureType::Texture_HEIGHT:
                    name = "texture_height";
                    number = std::to_string(heightNr++);
                    break;
                case TextureType::Texture_EMISSIVE:
                    name = "texture_emissive";
                    number = std::to_string(emissiveNr++);
                    break;
                case TextureType::Texture_AMBIENT:
                    name = "texture_ambient";
                    number = std::to_string(ambientNr++);
                    break;
            }

            // On applique maintenant l'uniform de la texture (type + nombre) et on l'envoie sur le bon textureUnit
            shader->setInt(std::string("mat." + name + number), i + 1);
            
            // Enfin, on attache notre texture une fois que tout est active.
            texture->Bind();
        }
    }

    void Mesh::DrawUnique(const std::shared_ptr<Shader>& shader, const glm::dmat4& model, const glm::dmat4& view)
    {
        // Finalisation de la matrice de modèle, pour représenter l'objet dans l'espace de vue
        auto model_final{ model * this->_transform };
        shader->setMat4("modelview", view * model_final);
        shader->setMat4("model", model_final);
        shader->setMat3("normals", glm::transpose(glm::inverse(glm::dmat3(model_final))));

        // Dessin de la maille
        _vao->Bind();
        if(_ibo != nullptr)
            glDrawElements(GL_TRIANGLES, _ibo->getNbElements(), GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, this->_vbo->getNumberElement() / this->_vbl->getNumberPerRow());
        _vao->Unbind();
    }

    void Mesh::DrawInstanced(const std::shared_ptr<Shader>& shader, const unsigned int& count, const std::unique_ptr<ShaderStorage>& ssbo, const glm::dmat4& view)
    {
        // Les matrices de modèles sont dans un ShaderStorageBuffer, afin de n'effectué qu'un seul draw call pour l'ensemble des objets
        ssbo->AttachBuffer(shader, "bufferModelMatrices");
        shader->setMat4("view", view);
        _vao->Bind();
        if(_ibo != nullptr)
            glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLuint>(_ibo->getNbElements()), GL_UNSIGNED_INT, 0, count);
        else
            glDrawArraysInstanced(GL_TRIANGLES, 0, this->_vbo->getNumberElement() / this->_vbl->getNumberPerRow(), count);
        _vao->Unbind();
    }
}