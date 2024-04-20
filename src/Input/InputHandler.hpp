#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include "../Scene/Scene.hpp"
#include "../Window/Window.hpp"
#include "../UI/UserInterface.hpp"

namespace SPN
{
    /**
     * @brief Gestion des entrées utilisateurs, menant à des actions
     * @author Nicolas LORMIER
     * @date 13/01/2023
    */
    class InputHandler
    {
        private:
            bool firstmouse{ true };
            float last_x{ 0.f };
            float last_y{ 0.f };
        public:
            InputHandler();
            void HandleInput(const std::unique_ptr<Window>& window, const std::unique_ptr<Scene>& scene, const std::unique_ptr<UserInterface>& user_interface, const float& deltatime);
    };
} 


#endif