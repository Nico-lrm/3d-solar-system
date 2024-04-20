#include "ShaderStorage.hpp"

namespace SPN
{
    GLuint ShaderStorage::_next_id{ 1 };

    ShaderStorage::ShaderStorage(const unsigned int& count, std::vector<ModelData>& data)
    {
        this->_hasData = false;
        this->_hasPendingUpdate = false;
        this->_ssbo_id = ShaderStorage::_next_id++;

        // Préparer les modèles qui seront utilisés par le SSBO
        for(unsigned int i = 0; i < count; i++)
        {
            auto model{ glm::mat4(1.0) };
            this->_models.push_back(model);
        }
        AttachData();
    }

    void ShaderStorage::Bind()
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->_id);
    }

    void ShaderStorage::Unbind()
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void ShaderStorage::Delete()
    {
        if(this->_id != 0)
            glDeleteBuffers(1, &this->_id);
    }

    void ShaderStorage::AttachData()
    {
        this->Bind();
        if(!_hasData)
        {
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, _id);
            glBufferData(GL_SHADER_STORAGE_BUFFER, _models.size() * sizeof(glm::mat4), _models.data(), GL_DYNAMIC_DRAW);
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
            _hasData = true;
        }
        else
        {
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, _id);
            glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, _models.size() * sizeof(glm::mat4), _models.data());
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        }
        this->Unbind();
    }

    void ShaderStorage::AttachBuffer(const std::shared_ptr<Shader>& shader, const char* name)
    {
        if(!this->_hasData)
            throw std::runtime_error("Impossible d'attacher le ShaderStorage : Il n'y a pas de données dedans.");

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->_id);
        GLuint block_index{ 0 };
        block_index = glGetProgramResourceIndex(shader->getID(), GL_SHADER_STORAGE_BLOCK, name);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, this->_ssbo_id, this->_id);

        // Optionnel
        glShaderStorageBlockBinding(shader->getID(), block_index, this->_ssbo_id);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
}