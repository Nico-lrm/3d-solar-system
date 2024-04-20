#include "ModelManager.hpp"

namespace SPN
{
    ModelManager::ModelManager()
    {}

    std::shared_ptr<Model> ModelManager::GetElement(const std::string& index)
    {
        if(this->_element_map.contains(index))
            return std::shared_ptr<Model>(this->_element_map.at(index));
        
        return nullptr;
    }

    void ModelManager::DeleteElement(const std::string& index)
    {
        if(this->_element_map.contains(index))
            this->_element_map.erase(index);
    }

    void ModelManager::CreateModel(const std::pair<std::string, LoadedModel>& data, const std::unique_ptr<TextureManager>& texture_manager)
    {
        if(this->_element_map.contains(data.first))
            return;

        std::scoped_lock<std::mutex> lock(this->_mutex_manager);
        this->_element_map.insert({data.first, std::make_shared<Model>(data, texture_manager)});
    }
}