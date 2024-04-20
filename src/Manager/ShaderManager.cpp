#include "ShaderManager.hpp"

namespace SPN 
{
    ShaderManager::ShaderManager()
    {}

    std::shared_ptr<Shader> ShaderManager::GetElement(const std::string& index) 
    {
        if(this->_element_map.contains(index))
            return std::shared_ptr<Shader>(this->_element_map.at(index));
        
        return nullptr;
    };

    void ShaderManager::DeleteElement(const std::string& index)
    {
        std::scoped_lock<std::mutex> lock(_mutex_manager);
        if(this->_element_map.contains(index))
            this->_element_map.erase(index);
    };

    void ShaderManager::CreateShader(const std::pair<std::string, LoadedShader>& data)
    {
        if(this->_element_map.contains(data.first))
            return;
        
        std::scoped_lock<std::mutex> lock(_mutex_manager);
        this->_element_map.insert({data.first, std::make_shared<Shader>(data.second)});
    }
}