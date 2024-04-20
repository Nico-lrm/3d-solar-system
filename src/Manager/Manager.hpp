#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <unordered_map>
#include <mutex>
#include <memory>

namespace SPN
{
    /**
     * @brief Template pour gestion de divers éléments de l'application (ressource dans cette exemple)
     * @author Nicolas LORMIER
     * @date 14/01/2023
    */
    template<typename T, class C>
    class Manager
    {
        protected:
            std::unordered_map <T, std::shared_ptr<C>> _element_map;            
            std::mutex _mutex_manager;
        public:
            virtual std::shared_ptr<C> GetElement(const T& index) = 0;
            virtual void DeleteElement(const T& index) = 0;
    };
}

#endif