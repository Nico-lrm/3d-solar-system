#ifndef TIMESTEP_HPP
#define TIMESTEP_HPP
#pragma once

#include <GLFW/glfw3.h>
#include <memory>

namespace SPN
{
    /**
     * @brief Sert à gérer les variations de framerate dans le rendu, afin d'assurer le même déroulement sur l'ensemble des machines.
     * @author Nicolas LORMIER
     * @date 14/01/2023
    */
	class Timestep
	{
		private:
			float _deltatime;
			float _lastframe;
		public:
			Timestep();
			void UpdateTime();

			inline float getDeltatime() { return this->_deltatime; }
			inline float getLastFrame() { return this->_lastframe; }
	};
}

#endif
