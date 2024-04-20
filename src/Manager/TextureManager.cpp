#include "TextureManager.hpp"

namespace SPN
{
    TextureManager::TextureManager()
    {}

    std::shared_ptr<Texture> TextureManager::GetElement(const std::string& index) 
    {
        if(this->_element_map.contains(index))
            return std::shared_ptr<Texture>(this->_element_map.at(index));
        
        return nullptr;
    };
    
    void TextureManager::DeleteElement(const std::string& index)
    {
        std::scoped_lock<std::mutex> lock(_mutex_manager);
        if(this->_element_map.contains(index))
            this->_element_map.erase(index);
    }

    void TextureManager::CreateTextureFile(const std::pair<std::string, LoadedTextureFile>& data)
    {
        if(this->_element_map.contains(data.first))
            return;
        
        std::scoped_lock<std::mutex> lock(_mutex_manager);
        this->_element_map.insert({data.first, std::make_shared<TextureFile>(data.second)});

        // Supprimer l'image chargé de la mémoire une fois créée en texture
        stbi_image_free(data.second.image_data.data);
    }

    void TextureManager::CreateTextureCubemap(const std::pair<std::string, LoadedTextureCubemap>& data)
    {
        
        if(this->_element_map.contains(data.first))
            return;
        
        std::scoped_lock<std::mutex> lock(_mutex_manager);
        this->_element_map.insert({data.first, std::make_shared<TextureCubemap>(data.second)});

        for(unsigned int i = 0; i < 6; i++)
        {
            if(data.second.image_datas.at(i).data == NULL)
            {
                throw std::runtime_error(std::string("Impossible de libérer l'image : " + data.second.filepaths.at(i)));
            }
            stbi_image_free(data.second.image_datas.at(i).data);
        }
    }
}