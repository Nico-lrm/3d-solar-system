#include "InputHandler.hpp"

namespace SPN
{
    InputHandler::InputHandler()
    {}

    void InputHandler::HandleInput(const std::unique_ptr<Window>& window, const std::unique_ptr<Scene>& scene, const std::unique_ptr<UserInterface>& user_interface, const float& deltatime)
    {
        // La fenêtre doit être fonctionnel pour que la gestion des inputs fonctionne
        if(window->getContext() != NULL)
        {
            auto context{ window->getContext() };

            // Fermeture de la fenêtre
            if(glfwGetKey(context, GLFW_KEY_ESCAPE))
                window->Close();

            // Déplacement de la caméra
            if(glfwGetKey(context, GLFW_KEY_W))
                scene->MoveCamera(CameraDirection::FORWARD, deltatime);
            if(glfwGetKey(context, GLFW_KEY_A))
                scene->MoveCamera(CameraDirection::LEFT, deltatime);
            if(glfwGetKey(context, GLFW_KEY_S))
                scene->MoveCamera(CameraDirection::BACKWARD, deltatime);
            if(glfwGetKey(context, GLFW_KEY_D))
                scene->MoveCamera(CameraDirection::RIGHT, deltatime);
            if(glfwGetKey(context, GLFW_KEY_R))
                scene->MoveCamera(CameraDirection::UP, deltatime);
            if(glfwGetKey(context, GLFW_KEY_F))
                scene->MoveCamera(CameraDirection::DOWN, deltatime);

            // Changer l'orientation de la caméra
            if(glfwGetMouseButton(context, GLFW_MOUSE_BUTTON_LEFT))
            {
                if (!user_interface->hasWindowActive())
                {
                    double x_actual, y_actual;
                    glfwGetCursorPos(context, &x_actual, &y_actual);

                    if(firstmouse)
                    {
                        last_x = static_cast<float>(x_actual);
                        last_y = static_cast<float>(y_actual);
                        firstmouse = false;
                    }

                    double x_offset{ x_actual - last_x };
                    double y_offset{ last_y - y_actual };
                    last_x = static_cast<float>(x_actual);
                    last_y = static_cast<float>(y_actual);
                
                    scene->LookCamera(x_offset, y_offset);
                }
            }

            if(glfwGetMouseButton(context, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
            {
                firstmouse = true;
            }
        }
    }
}