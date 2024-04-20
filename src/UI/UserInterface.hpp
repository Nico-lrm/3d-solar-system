#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP
#pragma once

#include <memory>
#include <vector>
#include <tuple>
#include <string>

#include "../Scene/Scene.hpp"
#include "../Window/Window.hpp"
#include "../../vendor/imgui/imgui.hpp"
#include "../../vendor/imgui/imgui_impl_glfw.hpp"
#include "../../vendor/imgui/imgui_impl_opengl3.hpp"

namespace SPN
{
    class UserInterface
    {
        private:
            bool _descriptor;
            bool _scene_graph;
            bool _atmo_params;

            unsigned int _width;
            unsigned int _height;

            std::pair<std::shared_ptr<DescriptorComponent>, std::shared_ptr<TransformComponent>> _data_actual;
            std::vector<std::pair<std::shared_ptr<DescriptorComponent>, std::shared_ptr<TransformComponent>>> _data_pointers;

            void SetStyle();
            void RenderDescriptor(const std::unique_ptr<Scene>& scene);
            void RenderSceneGraphe();
            void RenderAtmosphereParams();

        public:

            // Atmosphère params
            static float color[4];
            static float scattering[4];
            static float rayleigh[4];
            static float mie[4];

            UserInterface(const std::unique_ptr<Window>& window);
            ~UserInterface();

            void AttachSceneToUI(const std::unique_ptr<Scene>& scene);
            void Update();
            void DrawElements(const std::unique_ptr<Scene>& scene);
            void Render();

            bool hasWindowActive() { return ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow); }
    };
}

#endif