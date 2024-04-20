#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#pragma once

#include <future>
#include <chrono>
#include <string>
#include <algorithm>
#include <iostream>
#include <memory>

#include "../Manager/AssetsManager.hpp"
#include "../Loader/AssetsLoader.hpp"
#include "../Render/Renderer.hpp"
#include "../Render/Mesh.hpp"
#include "../Window/Window.hpp"
#include "../Debug/ConsoleLog.hpp"
#include "../Input/InputHandler.hpp"
#include "../Scene/Scene.hpp"
#include "../UI/UserInterface.hpp"
#include "Timestep.hpp"

namespace SPN
{
    /**
     * @brief Classe servant de chef d'orchestre du programme
     * @author Nicolas LORMIER
     * @date 13/01/2023
    */
    class Application
    {
        private:
            std::unique_ptr<Window> _window;
            std::unique_ptr<Renderer> _renderer;
            std::unique_ptr<UserInterface> _user_interface;
            std::unique_ptr<Scene> _scene;
            std::unique_ptr<Log> _log;
            
            std::unique_ptr<InputHandler> _input_handler;
            std::unique_ptr<Timestep> _timestep;
            std::unique_ptr<AssetsManager> _assets_manager;
            std::unique_ptr<AssetsLoader> _assets_loader;

        public:
            /**
             * @brief Construit l'objet Application et initialise l'ensemble des objets qui le compose.
             * 
            */
            Application();

            /**
             * @brief Initialiser la scène que lancera l'application.
             * 
            */
            void InitScene();

            /**
             * @brief Charger les différentes ressources qui seront utilisées
             * 
            */
            void LoadRessources();

            /**
             * @brief Boucle de fonctionnement de l'application.
             * 
            */
            void Run();
    };
} 


#endif