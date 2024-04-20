#include "Window.hpp"

namespace SPN
{
    Window::Window(const std::string name)
    {
        // Initialisation de GLFW
        glfwInit();

        // Paramètres OpenGL
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Paramètres fenêtre
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

        // Synchro verticale
        glfwSwapInterval(0);

        auto videomode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        //this->_width = 1920;
        this->_width = videomode->width - 160;
        //this->_height = 1080;
        this->_height = videomode->height - 90;
        this->_name = name;

        // Création de la fenêtre
        //this->_context = glfwCreateWindow(this->_width, this->_height, name.c_str(), glfwGetPrimaryMonitor(), NULL);
        this->_context = glfwCreateWindow(this->_width, this->_height, name.c_str(), NULL, NULL);
        if(this->_context == nullptr)
            throw std::runtime_error("Impossible d'initialiser la fenêtre.");

        glfwMakeContextCurrent(this->_context);
    }
    
    Window::~Window() 
    {
        if(this->_context != NULL)
            glfwDestroyWindow(this->_context);
        glfwTerminate();
    }

    bool Window::Active()
    {
        return !glfwWindowShouldClose(this->_context);
    }

    void Window::Close()
    {
        glfwSetWindowShouldClose(this->_context, GLFW_TRUE);
    }

    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(this->_context);
    }
}