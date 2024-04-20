#ifndef WINDOW_HPP
#define WINDOW_HPP
#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>
#include <iostream>

namespace SPN 
{    
    class Window final
    {
        private:
            unsigned int _width{ 0 };
            unsigned int _height{ 0 };
            std::string _name;
            GLFWwindow* _context = nullptr;
        public:
            Window(const std::string name);
            ~Window();

            bool Active();
            void Update();
            void Close();

            inline GLFWwindow* getContext() { return this->_context; }
            inline unsigned int getWidth() { return this->_width; }
            inline unsigned int getHeight() { return this->_height; }
    };
}

#endif