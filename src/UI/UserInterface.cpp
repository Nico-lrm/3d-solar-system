#include "UserInterface.hpp"

namespace SPN
{
    float UserInterface::color[4] = { 0.2078f, 0.1961f, 1.0f, 0.44f };
    float UserInterface::scattering[4] = { 0.004f, 0.0003f, 0.0003f, 0.44f };
    float UserInterface::rayleigh[4] = { 0.00011f, 0.0000245f, 0.0000605f, 0.44f };
    float UserInterface::mie[4] = { 0.0001f, 0.0, 0.0001f, 0.44f };

    UserInterface::UserInterface(const std::unique_ptr<Window>& window)
    {
        // Initialisation de ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        SetStyle();

        ImGui_ImplGlfw_InitForOpenGL(window->getContext(), true);
        ImGui_ImplOpenGL3_Init("#version 430 core");

        this->_descriptor = true;
        this->_scene_graph = true;
        this->_atmo_params = true;
        this->_width = window->getWidth();
        this->_height = window->getHeight();
    }

    void UserInterface::SetStyle()
    {
        std::string main_dir{ "C:/Users/lormi/Documents/PROJET_LORMIER_21502501/" };
        //std::string main_dir{ "" };

        ImGuiIO& io{ ImGui::GetIO() };
        ImGuiStyle& style = ImGui::GetStyle();
        io.Fonts->AddFontFromFileTTF(std::string(main_dir + "assets/font/SourceSansPro-Regular.ttf").c_str(), 18.0f);

        style.WindowRounding = 10.f;
        style.PopupRounding = 10.f;
        style.FrameRounding = 3.f;
        style.PopupBorderSize = 0.f;
        style.WindowBorderSize = 0.f;
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.95f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.95f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.03f, 0.03f, 0.03f, 1.f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.26f, 0.26f, 0.26f, 1.f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.05f, 0.05f, 1.f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.03f, 0.03f, 0.03f, 1.f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.43f, 0.43f, 0.43f, 1.f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.69f, 0.69f, 0.69f, 1.f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.87f, 0.87f, 0.87f, 1.f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.57f, 0.57f, 0.57f, 1.f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.57f, 0.57f, 0.57f, 1.f);
        style.Colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.20f, 0.20f, 1.f);
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.f);
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.57f, 0.57f, 0.57f, 1.f);
    }

    void UserInterface::AttachSceneToUI(const std::unique_ptr<Scene>& scene)
    {
        auto entities{ scene->getEntities() };

        if(entities.size() <= 0)
            return;

        for(auto& ett : entities)
        {
            if(!scene->HasComponent<DescriptorComponent>(ett) ||  !scene->HasComponent<TransformComponent>(ett))
                continue;

            // On récupère les composants nécessaires à l'affichage
            auto d_ett{ scene->GetComponent<DescriptorComponent>(ett) };
            auto t_ett{ scene->GetComponent<TransformComponent>(ett) };

            this->_data_pointers.push_back(std::make_pair(d_ett, t_ett));
        }

        // Passer la Terre comme cible de base de l'application
        for(auto desc : this->_data_pointers)
        {
            if(desc.first->nom == "Terre")
            {
                this->_data_actual = desc;
                break;
            }
        }
    }

    void UserInterface::RenderDescriptor(const std::unique_ptr<Scene>& scene)
    {
        if(this->_descriptor)
        {
            ImGui::SetNextWindowSize(ImVec2(360, 460), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowPos(ImVec2(this->_width - 360.f, 0), ImGuiCond_FirstUseEver);

            // Création de la fenêtre avec ImGui
            ImGui::Begin("Description", &(this->_descriptor));
                // Section Titre et Sous-titre
                ImGui::SetWindowFontScale(1.5f);
                ImGui::TextWrapped(this->_data_actual.first->nom.c_str());
                ImGui::SetWindowFontScale(1.1f);
                ImGui::TextDisabled(this->_data_actual.first->type.c_str());
                ImGui::SetWindowFontScale(1.0f);
                if(ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
                {
                    if(ImGui::BeginTabItem("Infos"))
                    {
                        // On utilise un tableau pour afficher les informations
                        ImGui::BeginTable("##infos", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner);
                        for(auto& data : this->_data_actual.first->_infos)
                        {
                            // La première colonne comporte les légendes
                            ImGui::TableNextColumn();
                            ImGui::TextWrapped(std::get<0>(data).c_str());

                            // Si un tooltip à été saisie pour la colonne, on l'affiche sur la même ligne que la légende
                            if(std::get<2>(data).has_value())
                            {
                                ImGui::SameLine();
                                ImGui::TextDisabled("(?)");
                                if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
                                {
                                    ImGui::BeginTooltip();
                                    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                                    ImGui::TextUnformatted(std::get<2>(data).value().c_str());
                                    ImGui::PopTextWrapPos();
                                    ImGui::EndTooltip();
                                }
                            }

                            // La deuxième colonne comporte les données
                            ImGui::TableNextColumn();
                            ImGui::TextWrapped(std::get<1>(data).c_str());
                        }

                        ImGui::EndTable();
                        ImGui::EndTabItem();
                    }
                    if(ImGui::BeginTabItem("Composition"))
                    {
                        // On utilise un tableau pour afficher les informations
                        ImGui::BeginTable("##compo", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner);
                        for(auto& data : this->_data_actual.first->_compositions_atmo)
                        {
                            // La première colonne comporte les légendes
                            ImGui::TableNextColumn();
                            ImGui::TextWrapped(data.first.c_str());

                            // La deuxième colonne comporte les données
                            ImGui::TableNextColumn();
                            ImGui::TextWrapped(data.second.c_str());
                        }

                        ImGui::EndTable();
                        ImGui::EndTabItem();
                    }

                    if(ImGui::Button("Se déplacer", ImVec2(-FLT_MIN, 3 * ImGui::GetTextLineHeightWithSpacing())))
                    {            
                        auto new_pos{ this->_data_actual.second->position };
                        new_pos.z += (this->_data_actual.second->scale.x * 5);          
                        scene->MoveCamera(new_pos);
                    }
                    
                    ImGui::EndTabBar();

                }
            ImGui::End();
        }
    }

    void UserInterface::RenderSceneGraphe()
    {
        if(this->_scene_graph)
        {
            ImGui::SetNextWindowSize(ImVec2(190, 240), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
            ImGui::Begin("Scène", &(this->_scene_graph));
            for(auto data : this->_data_pointers)
            {
                if(ImGui::Selectable(data.first->nom.c_str()))
                {
                    this->_data_actual = data;
                }
            }
            ImGui::End();
        }
    }

    void UserInterface::RenderAtmosphereParams()
    {
        if (this->_atmo_params)
        {
            ImGui::SetNextWindowSize(ImVec2(190, 240), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
            ImGui::Begin("Atmosphère", &(this->_atmo_params));
                ImGui::InputFloat3("Color", UserInterface::color, "%.7f");
                ImGui::InputFloat3("Scattering", UserInterface::scattering, "%.7f");
                ImGui::InputFloat3("Rayleigh", UserInterface::rayleigh, "%.7f");
                ImGui::InputFloat3("Mie", UserInterface::mie, "%.7f");
            ImGui::End();
        }
    }

    UserInterface::~UserInterface()
    {
        // Fermeture de ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void UserInterface::Update()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void UserInterface::DrawElements(const std::unique_ptr<Scene>& scene)
    {
        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::MenuItem("Description"))
            {
                this->_descriptor = !_descriptor;
            }

            if(ImGui::MenuItem("Scène"))
            {
                this->_scene_graph = !_scene_graph;
            }

            if (ImGui::MenuItem("Atmosphère"))
            {
                this->_atmo_params = !_atmo_params;
            }

            ImGui::EndMainMenuBar();
        }
        RenderDescriptor(scene);
        RenderAtmosphereParams();
        RenderSceneGraphe();
    }

    void UserInterface::Render()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}