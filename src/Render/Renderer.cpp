#include "Renderer.hpp"

/**
 * @brief Fonction de débug pour OpenGL.
 * Doit être activée avec la fonction glDebugMessageCallback().
*/
void OpenGLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,const void *userParam) {
    std::string sourceName;
    std::string typeName;
    std::string severityName;

    // Récupérer au format texte les sources, type et sévérité des erreurs OpenGL
    switch(source)
    {
        case 0x8248:
            sourceName = "GL_DEBUG_SOURCE_SHADER_COMPILER_ARB";
        break;
        case 0x8246:
            sourceName = "GL_DEBUG_SOURCE_API_ARB";
        break;
        default:
            sourceName = "GL_DEBUG_SOURCE_UNKNOWN";
        break;
    }

    switch(type)
    {
        case 0x824c:
            typeName = "GL_DEBUG_TYPE_ERROR_ARB";
        break;
        case 0x8250:
            typeName = "GL_DEBUG_TYPE_PERFORMANCE_ARB";
        break;
        default:
            typeName = "GL_DEBUG_TYPE_UNKNOWN";
        break;
    }

    switch(severity)
    {
        case 0x9146:
            severityName = "GL_DEBUG_SEVERITY_HIGH_AMD";
        break;
        case 0x9147:
            severityName = "GL_DEBUG_SEVERITY_MEDIUM_AMD";
        break;
        case 0x9148:
            severityName = "GL_DEBUG_SEVERITY_LOW_AMD";
        break;
        case 0x826b:
            severityName = "GL_DEBUG_SEVERITY_NOTIFICATION";
        break;
        default:
            sourceName = "GL_DEBUG_SEVERITY_UNKNOWN";
        break;
    }

    // Créer la chaîne finale
    std::string finalString = "source : " + sourceName 
                              + "\ntype : " + typeName
                              + "\nseverity : " + severityName
                              + "\nmessage : " + message;

    // Renvoyer l'exception
    throw std::runtime_error(finalString.c_str());
}

namespace SPN
{
    Renderer::Renderer(const std::unique_ptr<Window>& window)
    {
        // Initialisation de GLEW
        GLenum err{ glewInit() };
        if (GLEW_OK != err)
            throw std::runtime_error("Impossible d'initialiser le rendu.");
        
        // Gestion du debug
        //glEnable(GL_DEBUG_OUTPUT);
        //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        //glDebugMessageCallback(OpenGLMessageCallback, NULL);
        
        // Gérer les notifications OpenGL - Désactiver les notifications
        //glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
        //glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, NULL, GL_FALSE);

        // Activer le sRGB
        glEnable(GL_FRAMEBUFFER_SRGB);

        // Profondeur
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // Transparence
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // N'afficher que les éléménts qui sont devant la caméra
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // Afficher des lignes 
        glEnable(GL_LINE_SMOOTH);

        glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);

        // Range du depth Buffer
        glDepthRange(.00001, 46000.0);
        //glPolygonOffset(4.0, 4.0);
        
        // Couleur utilisé lors du nettoyage de la fenêtre
        glClearColor(0.05, 0.05, 0.05, 1.0);

        this->_width = window->getWidth();
        this->_height = window->getHeight();

        // Initialiser les éléments de base du renderer
        this->_skybox = std::make_unique<Skybox>();
        this->_render_target = std::make_unique<RenderTarget>(window);
        this->_orbit_renderer = std::make_unique<OrbitRenderer>();
        this->_depth_fbo = std::make_unique<DepthFramebuffer>(8192);
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SetClearColor(const glm::vec4 &color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
    }

    void Renderer::SetClearColor(const float& x, const float& y, const float& z)
    {
        glClearColor(x, y, z, 1.0f);
    }
    
    void Renderer::SetViewport(unsigned width, unsigned height)
    {
        glViewport(0, 0, width, height);
    }

    void Renderer::ApplyLights(const std::unique_ptr<Scene>& scene, const std::shared_ptr<Shader>& shader)
    {
        // On récupère l'ensemble des entités
        auto entities{ scene->getEntities() };

        // S'il n'y a pas d'entité, on s'arrête là
        if(entities.size() <= 0)
            return;
        
        for(auto& ett : entities)
        {
            // Si l'entité n'a pas ces deux composants, on passe à la suite
            if(!scene->HasComponent<LightComponent>(ett) ||  !scene->HasComponent<TransformComponent>(ett))
                continue;

            // On récupère les composants nécessaires à l'affichage
            auto light_ett{ scene->GetComponent<LightComponent>(ett) };
            auto transform_ett{ scene->GetComponent<TransformComponent>(ett) };

            // Information de l'ombre
            shader->setVec3("pLight.position", transform_ett->position);
            shader->setVec3("pLight.ambient", light_ett->color * 0.1f);
            shader->setVec3("pLight.diffuse", light_ett->color);
            shader->setVec3("pLight.specular", light_ett->color * 0.5f);
        }
    }

    void Renderer::DrawShadow(const std::unique_ptr<Scene>& scene, const float& deltatime, const float& lastframe)
    {
        // Récupérer l'ensemble des entités
        auto entities{ scene->getEntities() };
        auto view{ scene->getViewMatrix() };
        auto proj{ scene->getProjMatrix() };

        // On définit la taille de l'affiche par rapport a la résolution des ombres
        glViewport(0, 0, this->_depth_fbo->getShadowResolution(), this->_depth_fbo->getShadowResolution());

        // Attacher le depth framebuffer pour dessiner dedans
        this->_depth_fbo->Bind();

        // Nettoyer de l'image précédente
        glClear(GL_DEPTH_BUFFER_BIT);

        // Récupérer le shader pour effectuer le dessin dans la carte de profondeur
        auto shader = this->_depth_fbo->getShader();

        // Parcourir l'ensemble des entités
        for(unsigned int i = 0; i < entities.size(); i++)
        {
            if(!scene->HasComponent<LightComponent>(entities.at(i)) || !scene->HasComponent<TransformComponent>(entities.at(i)))
                continue;

            // Récupérer les composants utiles pour le système
            auto lc{ scene->GetComponent<LightComponent>(entities.at(i)) };
            auto tc{ scene->GetComponent<TransformComponent>(entities.at(i)) };
            
            // Attacher le shader pour dessiner les profondeurs
            shader->Bind();

            // Passer les infos de la lumière et de la caméra pour effectuer le dessin de la profondeur
            shader->setFloat("far_plane", scene->getCameraFar());
            shader->setFloat("near", .00001);
            shader->setFloat("far", 46000.0f);
            shader->setVec3("cameraPos", scene->getCameraPosition());
            shader->setVec3("lightPos", tc->position);
            for (unsigned int k = 0; k < 6; ++k)
		        shader->setMat4("shadowMatrices[" + std::to_string(k) + "]", lc->shadow_transforms[k]);

            for(unsigned int j = 0; j < entities.size(); j++)
            {
                // Si c'est la source de lumière, on ne la dessine pas
                if(i == j)
                    continue;

                // Si l'entité ne possède pas ces composants, on ne la dessine pas
                if(!scene->HasComponent<MaterialComponent>(entities.at(j)) || !scene->HasComponent<TransformComponent>(entities.at(j)))
                    continue;

                auto mc2{ scene->GetComponent<MaterialComponent>(entities.at(j)) };
                auto tc2{ scene->GetComponent<TransformComponent>(entities.at(j)) };

                // Définir la matrice de modèle
                auto model_matrix = glm::dmat4(1.0);
                model_matrix = glm::translate(model_matrix, tc2->position - tc->position);
                //model_matrix = glm::rotate(model_matrix, glm::radians(static_cast<double>(lastframe)), tc2->rotation_vec);
                //model_matrix = glm::rotate(model_matrix, glm::radians(tc2->rotation_angle), glm::dvec3(0.f, 0., 1.f));
                model_matrix = glm::scale(model_matrix, glm::dvec3(tc2->scale));

                // Dessiner l'entité dans le carte de profondeur
                mc2->model->DrawUnique(shader, model_matrix, view, proj);
            }

            // Détacher le shader
            shader->Unbind();
        }

        // Détacher le depth framebuffer
        this->_depth_fbo->Unbind();
        glViewport(0, 0, _width, _height);
    }

    void Renderer::DrawScene(const std::unique_ptr<Scene>& scene, const std::unique_ptr<UserInterface>& user_interface, const float& deltatime, const float& lastframe)
    {
        // On active le blending pour le dessin des entités
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Récupérer l'ensemble des entités
        auto entities{ scene->getEntities() };

        // Récupérer les types et variables nécessaires pour le dessin
        auto material_type{ scene->GetComponentType<MaterialComponent>() };
        auto transform_type{ scene->GetComponentType<TransformComponent>() };
        auto ring_type{ scene->GetComponentType<RingComponent>() };
        auto camera_pos{ scene->getCameraPosition() };
        auto view{ scene->getViewMatrix() };
        auto proj{ scene->getProjMatrix() };
        auto model_matrix{ glm::dmat4(1.) };

        // Créer le frustum de la caméra pour le rendu actuel
        auto frustum{ createFrustumFromCamera(scene->getCamera()) };

        // On attache le framebuffer de rendu, où l'on va dessiner notre scène et on le nettoie l'image précédente
        this->_render_target->Bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // S'il n'y a pas d'entités, on s'arrête là
        if(entities.size() <= 0)
            return;

        // Pour chaque entité de la liste, on regarde si elle dispose des composants nécessaire pour l'affichage, si oui, on l'affiche
        for(auto& ett : entities)
        {
            if(ett->_signature.test(material_type) && ett->_signature.test(transform_type))
            {
                // On récupère les composants nécessaires à l'affichage
                auto material_ett{ scene->GetComponent<MaterialComponent>(ett) };
                auto transform_ett{ scene->GetComponent<TransformComponent>(ett) };

                // Si l'objet est dans le frustum, alors on l'affiche
                //if(isOnFrustum(frustum, glm::vec3(transform_ett->position - camera_pos), glm::vec3(transform_ett->scale)))
                //{
                    // On attache le shader de l'entité actuelle pour les uniforms
                    material_ett->shader->Bind();
                    material_ett->shader->setVec3("cameraPos", camera_pos);
                    material_ett->shader->setVec3("planetPos", transform_ett->position - camera_pos);

                    // On attache la texture d'ombre
                    glActiveTexture(GL_TEXTURE0);
                    this->_depth_fbo->getTexture()->Bind();
                    material_ett->shader->setInt("shadow_texture", 0);
                    material_ett->shader->setFloat("far_plane", scene->getCameraFar());
                    material_ett->shader->setInt("enable_shadow", 1);
                    material_ett->shader->setFloat("near", .00001);
                    material_ett->shader->setFloat("far", 46000.0f);

                    // Si c'est une source de lumière
                    if(scene->HasComponent<LightComponent>(ett))
                    {
                        material_ett->shader->setInt("isEmissive", 1);
                    }
                    else
                    {
                        this->ApplyLights(scene, material_ett->shader);
                        material_ett->shader->setInt("isEmissive", 0);
                    }

                    // Si notre entité a une atmosphère
                    if(scene->HasComponent<AtmosphereComponent>(ett))
                    {
                        auto atmo_ett{ scene->GetComponent<AtmosphereComponent>(ett) };
                        material_ett->shader->setFloat("planetRadius", atmo_ett->planet_radius);
                        material_ett->shader->setFloat("atmosphereRadius", atmo_ett->atmosphere_radius);
                        //material_ett->shader->setFloat("atmosphereIntensity", atmo_ett->atmosphere_intensity);
                        //material_ett->shader->setVec3("atmosphericScattering", atmo_ett->atmosphere_scattering);
                        //material_ett->shader->setVec3("atmosphereColor", atmo_ett->atmosphere_color);
                        //material_ett->shader->setVec3("rayleighCoefficient", atmo_ett->rayleigh_coeff);
                        //material_ett->shader->setVec3("mieCoefficient", atmo_ett->mie_coeff);
                        material_ett->shader->setVec3("atmosphereColor", UserInterface::color[0], UserInterface::color[1], UserInterface::color[2]);
                        material_ett->shader->setVec3("atmosphericScattering", UserInterface::scattering[0], UserInterface::scattering[1], UserInterface::scattering[2]);
                        material_ett->shader->setVec3("rayleighCoefficient", UserInterface::rayleigh[0], UserInterface::rayleigh[1], UserInterface::rayleigh[2]);
                        material_ett->shader->setVec3("mieCoefficient", UserInterface::mie[0], UserInterface::mie[1], UserInterface::mie[2]);

                        material_ett->shader->setInt("hasAtmosphere", 1);
                    }
                    else
                    {
                        material_ett->shader->setInt("hasAtmosphere", 0);
                    }

                    // Transformation de la matrice de l'entité
                    model_matrix = glm::dmat4(1.0);
                    model_matrix = glm::translate(model_matrix, transform_ett->position - camera_pos);
                    //model_matrix = glm::rotate(model_matrix, 6.283 * static_cast<double>(lastframe), transform_ett->rotation_vec);
                    //model_matrix = glm::rotate(model_matrix, glm::radians(transform_ett->rotation_angle), glm::dvec3(0.f, 0., -1.f));
                    model_matrix = glm::scale(model_matrix, glm::dvec3(transform_ett->scale));

                    // On dessine l'entité
                    material_ett->model->DrawUnique(material_ett->shader, model_matrix, view, proj);

                    this->_depth_fbo->getTexture()->Unbind();
                    material_ett->shader->Unbind();
                //}
            }

            // Si l'entité possède un anneau d'astéroide, on affiche (le frustum s'applique dans la mise à jour des astéroides)
            if(ett->_signature.test(ring_type))
            {
                // Récupérer les composants de l'anneau d'astéroide
                auto ring_ett{ scene->GetComponent<RingComponent>(ett) };

                // Attacher le shader du composants
                ring_ett->shader->Bind();

                // Attacher la texture pour les ombres
                glActiveTexture(GL_TEXTURE0);
                this->_depth_fbo->getTexture()->Bind();
                ring_ett->shader->setInt("shadow_texture", 0);
                ring_ett->shader->setFloat("far_plane", scene->getCameraFar());
                ring_ett->shader->setInt("enable_shadow", 1);

                // Définir les paramètres de bases (Pas d'atmo + pas source de lumière)
                ring_ett->shader->setInt("isEmissive", 0);
                this->ApplyLights(scene, ring_ett->shader);
                ring_ett->shader->setInt("hasAtmosphere", 0);
                ring_ett->shader->setFloat("near", .00001);
                ring_ett->shader->setFloat("far", 46000.0f);

                // Attacher la position de la caméra pour calculer la lumière dans le shader
                ring_ett->shader->setVec3("cameraPos", camera_pos);

                // Effectuer un draw call instancié (un seul appel pour plusieurs objets)
                ring_ett->model->DrawInstanced(ring_ett->shader, view, proj, ring_ett->shader_storage->getSize(), ring_ett->shader_storage);

                // Détacher les ressources
                this->_depth_fbo->getTexture()->Unbind();
                ring_ett->shader->Unbind();
            }
        }
        // Dessiner les orbites
        this->_orbit_renderer->DrawOrbit(scene, deltatime, lastframe);     

        // Dessiner la skybox
        this->_skybox->Draw(view, proj);

        // Dessiner les ombres pour la prochaine chaine
        DrawShadow(scene, deltatime, lastframe);

        // On détache le framebuffer
        this->_render_target->Unbind();

        // On désactive la gestion de la profondeur pour le bloom
        glDisable(GL_BLEND);

        // On dessine notre framebuffer
        this->_render_target->Draw(user_interface, scene);
    }
}