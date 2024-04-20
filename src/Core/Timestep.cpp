#include "Timestep.hpp"

namespace SPN
{
    Timestep::Timestep()
    {
        this->_deltatime = 0.0;
        this->_lastframe = 0.0;
    }

    void Timestep::UpdateTime()
    {
        float current_frame{ static_cast<float>(glfwGetTime()) };
        this->_deltatime = current_frame - this->_lastframe;
        this->_lastframe = current_frame;
    }
}