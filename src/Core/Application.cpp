#include "Application.hpp"

namespace SPN
{
    Application::Application()
    {
        this->_log = std::make_unique<ConsoleLog>();

        try
        {
            // Initialiser les différents objets utilisés par l'application
            this->_window = std::make_unique<Window>("Système Solaire en 3D - Nicolas LORMIER");
            this->_renderer = std::make_unique<Renderer>(_window);
            this->_scene = std::make_unique<Scene>(_window->getWidth(), _window->getHeight());
            this->_user_interface = std::make_unique<UserInterface>(_window);
            this->_input_handler = std::make_unique<InputHandler>();
            this->_timestep = std::make_unique<Timestep>();
            this->_assets_manager = std::make_unique<AssetsManager>();
            this->_assets_loader = std::make_unique<AssetsLoader>();

            // Initialiser la seed de l'aléatoire en fonction du temps;
            std::srand(std::time(0));
        }
        catch(const std::exception& e)
        {
            this->_log->writeError(e.what());
        }
    }

    void Application::LoadRessources()
    {
        try
        {
            // Debug, pour utiliser avec RenderDoc
            std::string main_dir{ "C:/Users/lormi/Documents/PROJET_LORMIER_21502501/" };
            //std::string main_dir{ "" };

            // Shader
            auto planet_shader_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadShader("planet", main_dir + "assets/shader/planet.vert", main_dir + "assets/shader/planet.frag");
            }) };
            auto asteroid_shader_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadShader("asteroid", main_dir + "assets/shader/asteroid.vert", main_dir + "assets/shader/planet.frag");
            }) };

            // Soleil
            auto model_sun_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("sun", main_dir + "assets/model/sun/sun.gltf", false);
            }) };

            // Mercure
            auto model_mercury_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("mercury", main_dir + "assets/model/mercury/mercury.gltf", false);
            }) };

            // Venus
            auto model_venus_async{ std::async(std::launch::async, [&]() {
               return _assets_loader->LoadModel("venus", main_dir + "assets/model/venus/venus.gltf", false);
            }) };

            // Terre 
            auto model_earth_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("earth", main_dir + "assets/model/earth/earth.gltf", true);
            }) };
            auto model_moon_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("moon", main_dir + "assets/model/moon/moon.gltf", true);
            }) };

            // Mars
            auto model_mars_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("mars", main_dir + "assets/model/mars/mars.gltf", false);
            }) };
            auto model_deimos_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("deimos", main_dir + "assets/model/deimos/deimos.gltf", false);
            }) };
            auto model_phobos_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("phobos", main_dir + "assets/model/phobos/phobos.gltf", false);
            }) };

            // Jupiter 
            auto model_jupiter_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("jupiter", main_dir + "assets/model/jupiter/jupiter.gltf", false);
            }) };
            auto model_io_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("io", main_dir + "assets/model/io/io.gltf", false);
            }) };
            auto model_ganymede_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("ganymede", main_dir + "assets/model/ganymede/ganymede.gltf", false);
            }) };
            auto model_callisto_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("callisto", main_dir + "assets/model/callisto/callisto.gltf", false);
            }) };
            auto model_europa_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("europa", main_dir + "assets/model/europa/europa.gltf", false);
            }) };

            // Saturne
            auto model_saturn_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("saturn", main_dir + "assets/model/saturn/saturn.gltf", false);
            }) };
            auto model_mimas_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("mimas", main_dir + "assets/model/mimas/mimas.gltf", false);
            }) };
            auto model_encelade_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("encelade", main_dir + "assets/model/encelade/encelade.gltf", false);
            }) };
            auto model_tethys_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("tethys", main_dir + "assets/model/tethys/tethys.gltf", false);
            }) };
            auto model_dione_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("dione", main_dir + "assets/model/dione/dione.gltf", false);
            }) };
            auto model_rhea_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("rhea", main_dir + "assets/model/rhea/rhea.gltf", false);
            }) };
            auto model_titan_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("titan", main_dir + "assets/model/titan/titan.gltf", false);
            }) };
            auto model_japet_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("japet", main_dir + "assets/model/iapetus/iapetus.gltf", false);
            }) };

            // Uranus
            auto model_uranus_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("uranus", main_dir + "assets/model/uranus/uranus.gltf", false);
            }) };
            auto model_miranda_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("miranda", main_dir + "assets/model/miranda/miranda.gltf", false);
            }) };
            auto model_ariel_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("ariel", main_dir + "assets/model/ariel/ariel.gltf", false);
            }) };
            auto model_umbriel_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("umbriel", main_dir + "assets/model/umbriel/umbriel.gltf", false);
            }) };
            auto model_titania_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("titania", main_dir + "assets/model/titania/titania.gltf", false);
            }) };
            auto model_oberon_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("oberon", main_dir + "assets/model/oberon/oberon.gltf", false);
            }) };

            // Neptune
            auto model_neptune_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("neptune", main_dir + "assets/model/neptune/neptune.gltf", false);
            }) };
            auto model_triton_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("triton", main_dir + "assets/model/triton/triton.gltf", false);
            }) };

            // Astéroide
            auto model_asteroid_async{ std::async(std::launch::async, [&]() {
                return _assets_loader->LoadModel("asteroid", main_dir + "assets/model/asteroid/asteroid.gltf", false);
            }) };

            // Finalisation des ressources & Ajout dans le gestionnaire de ressource
            _assets_manager->CreateShader(planet_shader_async.get());
            _assets_manager->CreateShader(asteroid_shader_async.get());
            _assets_manager->CreateModel(model_sun_async.get());
            _assets_manager->CreateModel(model_mercury_async.get());
            _assets_manager->CreateModel(model_venus_async.get());
            _assets_manager->CreateModel(model_earth_async.get());
            _assets_manager->CreateModel(model_moon_async.get());
            _assets_manager->CreateModel(model_mars_async.get());
            _assets_manager->CreateModel(model_deimos_async.get());
            _assets_manager->CreateModel(model_phobos_async.get());
            _assets_manager->CreateModel(model_jupiter_async.get());
            _assets_manager->CreateModel(model_io_async.get());
            _assets_manager->CreateModel(model_ganymede_async.get());
            _assets_manager->CreateModel(model_callisto_async.get());
            _assets_manager->CreateModel(model_europa_async.get());
            _assets_manager->CreateModel(model_saturn_async.get());
            _assets_manager->CreateModel(model_mimas_async.get());
            _assets_manager->CreateModel(model_encelade_async.get());
            _assets_manager->CreateModel(model_tethys_async.get());
            _assets_manager->CreateModel(model_dione_async.get());
            _assets_manager->CreateModel(model_rhea_async.get());
            _assets_manager->CreateModel(model_titan_async.get());
            _assets_manager->CreateModel(model_japet_async.get());
            _assets_manager->CreateModel(model_uranus_async.get());
            _assets_manager->CreateModel(model_miranda_async.get());
            _assets_manager->CreateModel(model_ariel_async.get());
            _assets_manager->CreateModel(model_umbriel_async.get());
            _assets_manager->CreateModel(model_titania_async.get());
            _assets_manager->CreateModel(model_oberon_async.get());
            _assets_manager->CreateModel(model_neptune_async.get());
            _assets_manager->CreateModel(model_triton_async.get());
            _assets_manager->CreateModel(model_asteroid_async.get());
        }
        catch(const std::exception& e)
        {
            this->_log->writeError(e.what());
        }
    }

    void Application::InitScene()
    {
        try
        {
            // Ajout des types de composant à la scène
            _scene->AddComponentType<LightComponent>();
            _scene->AddComponentType<GravityComponent>();
            _scene->AddComponentType<TransformComponent>();
            _scene->AddComponentType<MaterialComponent>();
            _scene->AddComponentType<RingComponent>();
            _scene->AddComponentType<AtmosphereComponent>();
            _scene->AddComponentType<OrbitComponent>();
            _scene->AddComponentType<DescriptorComponent>();

            // Soleil
            auto ett_sun{ _scene->CreateEntity() };
            auto mc_sun{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("sun"), _assets_manager->GetShader("planet")) };
            auto tc_sun{ std::make_shared<TransformComponent>(glm::dvec3(0.0, 0., 0.), 0., glm::dvec3(1.), glm::dvec3(14.)) };
            auto lc_sun{ std::make_shared<LightComponent>(glm::dvec3(1.)) };
            auto gc_sun{ std::make_shared<GravityComponent>(1392700.0, 1988900) };
            auto dc_sun{ std::make_shared<DescriptorComponent>() };
            gc_sun->entity_reference = nullptr;
            dc_sun->nom = "Soleil";
            dc_sun->type = "Etoile de classe G2V";
            dc_sun->_infos.push_back(std::make_tuple("Masse","1988500.0 * 10^24 kg", std::optional<std::string>()));
            dc_sun->_infos.push_back(std::make_tuple("Gravité","274.0 m/s^2", "Il s'agit de l'accélération gravitationnelle à la surface de la planète, au niveau de l'équateur, elle est exprimée en mètres par second. Elle inclut l'effet de rotation de la planète. Pour les géantes gazeuses, elle est donné à 1 bar de pression dans l'atmosphère."));
            dc_sun->_infos.push_back(std::make_tuple("Vitesse d'échappement","617.6 km/s", "Il s'agit de la vitesse nécessaire pour sortir de l'orbite gravitationnelle."));
            dc_sun->_infos.push_back(std::make_tuple("Luminosité","382.8 * 10^24 J/s", std::optional<std::string>()));
            dc_sun->_infos.push_back(std::make_tuple("Emission à la surface","92.94 * 10^6 J/m^2 *s", std::optional<std::string>()));
            dc_sun->_infos.push_back(std::make_tuple("Température effective","5772 K", std::optional<std::string>()));
            dc_sun->_compositions_atmo.push_back(std::make_pair("Hydrogène", "91.0%%"));
            dc_sun->_compositions_atmo.push_back(std::make_pair("Hélium", "8.9%%"));
            _scene->AddComponent<LightComponent>(ett_sun, lc_sun);
            _scene->AddComponent<TransformComponent>(ett_sun, tc_sun);
            _scene->AddComponent<MaterialComponent>(ett_sun, mc_sun);
            _scene->AddComponent<GravityComponent>(ett_sun, gc_sun);
            _scene->AddComponent<DescriptorComponent>(ett_sun, dc_sun);
            
            // Mercure
            auto ett_mercury{ _scene->CreateEntity() };
            auto mc_mercury{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("mercury"), _assets_manager->GetShader("planet")) };
            auto tc_mercury{ std::make_shared<TransformComponent>(glm::dvec3(580.,0.,0.), 0.03, glm::dvec3(0., 1., 0.), glm::dvec3(0.05)) };
            auto gc_mercury{ std::make_shared<GravityComponent>(4879.4, 0.33018) };
            auto oc_mercury{ std::make_shared<OrbitComponent>(tc_mercury->position.x, glm::dvec3(1.0)) };
            auto dc_mercury{ std::make_shared<DescriptorComponent>() };
            gc_mercury->entity_reference = ett_sun;
            dc_mercury->nom = "Mercure";
            dc_mercury->type = "Planète tellurique";
            dc_mercury->_infos.push_back(std::make_tuple("Masse", "0.330 * 10^24 kg", std::optional<std::string>()));
            dc_mercury->_infos.push_back(std::make_tuple("Diamètre", "4879 km", std::optional<std::string>()));
            dc_mercury->_infos.push_back(std::make_tuple("Gravité", "3.7 m/s^2", "Il s'agit de l'accélération gravitationnelle à la surface de la planète, au niveau de l'équateur, elle est exprimée en mètres par second. Elle inclut l'effet de rotation de la planète. Pour les géantes gazeuses, elle est donné à 1 bar de pression dans l'atmosphère."));
            dc_mercury->_infos.push_back(std::make_tuple("Vitesse d'échappement", "4.3 km/s", "Il s'agit de la vitesse nécessaire pour sortir de l'orbite gravitationnelle."));
            dc_mercury->_infos.push_back(std::make_tuple("Période de rotation", "1407.6 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport à un ciel étoilé au niveau de l'équateur. Un nombre négatif indique une rotation anti-horaire."));
            dc_mercury->_infos.push_back(std::make_tuple("Durée d'une journée", "4222.6 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport au Soleil, au niveau de l'équateur."));
            dc_mercury->_infos.push_back(std::make_tuple("Distance du Soleil", " 57.9 * 10^6 km", std::optional<std::string>()));
            dc_mercury->_infos.push_back(std::make_tuple("Période orbitale", "88.0 j", "Temps nécessaire pour effectuer une rotation autour du Soleil."));
            dc_mercury->_infos.push_back(std::make_tuple("Vitesse Orbitale", "47.4 km/s", std::optional<std::string>()));
            dc_mercury->_infos.push_back(std::make_tuple("Moyenne - Température de surface", "167 °C", std::optional<std::string>()));
            dc_mercury->_infos.push_back(std::make_tuple("Nombre de Satellites", "0", std::optional<std::string>()));
            dc_mercury->_compositions_atmo.push_back(std::make_pair("Métaux", "70.0%%"));
            dc_mercury->_compositions_atmo.push_back(std::make_pair("Silicate", "30.0%%"));
            _scene->AddComponent<MaterialComponent>(ett_mercury, mc_mercury);
            _scene->AddComponent<TransformComponent>(ett_mercury, tc_mercury);
            _scene->AddComponent<GravityComponent>(ett_mercury, gc_mercury);
            _scene->AddComponent<OrbitComponent>(ett_mercury, oc_mercury);
            _scene->AddComponent<DescriptorComponent>(ett_mercury, dc_mercury);

            // Venus
            auto ett_venus{ _scene->CreateEntity() };
            auto mc_venus{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("venus"), _assets_manager->GetShader("planet")) };
            auto tc_venus{ std::make_shared<TransformComponent>(glm::dvec3(1080.,0.,0.), 177.4, glm::dvec3(1., 0., 0.), glm::dvec3(0.1)) };
            auto ac_venus{ std::make_shared<AtmosphereComponent>(glm::dvec3(0.6, 0.3, 0.1), 0.05, 6301.8, glm::dvec3(0.25, 0.0025, 0.00095), glm::dvec3(4.0e-4, 4.0e-4, 4.0e-4), 6051.8, glm::dvec3(5.8e-5, 1.2e-4, 2.7e-4)) };
            auto gc_venus{ std::make_shared<GravityComponent>(12104.0, 4.8685) };
            auto oc_venus{ std::make_shared<OrbitComponent>(tc_venus->position.x, ac_venus->atmosphere_color) };
            auto dc_venus{ std::make_shared<DescriptorComponent>() };
            gc_venus->entity_reference = ett_sun;
            dc_venus->nom = "Vénus";
            dc_venus->type = "Planète tellurique";
            dc_venus->_infos.push_back(std::make_tuple("Masse", "4.87 * 10^24 kg", std::optional<std::string>()));
            dc_venus->_infos.push_back(std::make_tuple("Diamètre", "12104 km", std::optional<std::string>()));
            dc_venus->_infos.push_back(std::make_tuple("Gravité", "8.9 m/s^2", "Il s'agit de l'accélération gravitationnelle à la surface de la planète, au niveau de l'équateur, elle est exprimée en mètres par second. Elle inclut l'effet de rotation de la planète. Pour les géantes gazeuses, elle est donné à 1 bar de pression dans l'atmosphère."));
            dc_venus->_infos.push_back(std::make_tuple("Vitesse d'échappement", "10.4 km/s", "Il s'agit de la vitesse nécessaire pour sortir de l'orbite gravitationnelle."));
            dc_venus->_infos.push_back(std::make_tuple("Période de rotation", "-5832.5 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport à un ciel étoilé au niveau de l'équateur. Un nombre négatif indique une rotation anti-horaire."));
            dc_venus->_infos.push_back(std::make_tuple("Durée d'une journée", "2802.0 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport au Soleil, au niveau de l'équateur."));
            dc_venus->_infos.push_back(std::make_tuple("Distance du Soleil", "108.2 * 10^6 km", std::optional<std::string>()));
            dc_venus->_infos.push_back(std::make_tuple("Période orbitale", "224.7 j", "Temps nécessaire pour effectuer une rotation autour du Soleil."));
            dc_venus->_infos.push_back(std::make_tuple("Vitesse Orbitale", "35.0 km/s", std::optional<std::string>()));
            dc_venus->_infos.push_back(std::make_tuple("Moyenne - Température de surface", "464 °C", std::optional<std::string>()));
            dc_venus->_infos.push_back(std::make_tuple("Nombre de Satellites", "0", std::optional<std::string>()));
            dc_venus->_compositions_atmo.push_back(std::make_pair("Dioxyde de carbone", "96.5%%"));
            dc_venus->_compositions_atmo.push_back(std::make_pair("Diazote", "3.5%%"));
            dc_venus->_compositions_atmo.push_back(std::make_pair("Dioxyde de souffre", "Traces"));
            dc_venus->_compositions_atmo.push_back(std::make_pair("Argon", "Traces"));
            dc_venus->_compositions_atmo.push_back(std::make_pair("Vapeur d'eau", "Traces"));
            dc_venus->_compositions_atmo.push_back(std::make_pair("Monoxyde de carbone", "Traces"));
            dc_venus->_compositions_atmo.push_back(std::make_pair("Hélium", "Traces"));
            dc_venus->_compositions_atmo.push_back(std::make_pair("Néon", "Traces"));
            _scene->AddComponent<MaterialComponent>(ett_venus, mc_venus);
            _scene->AddComponent<TransformComponent>(ett_venus, tc_venus);
            _scene->AddComponent<AtmosphereComponent>(ett_venus, ac_venus);
            _scene->AddComponent<GravityComponent>(ett_venus, gc_venus);
            _scene->AddComponent<OrbitComponent>(ett_venus, oc_venus);
            _scene->AddComponent<DescriptorComponent>(ett_venus, dc_venus);

            // Terre
            auto ett_earth{ _scene->CreateEntity() };
            // x = Impact la couleur sur le centre de la planète (); y = hauteur de l'atmo pour les bords (plus la valeur est petite, plus gros sera la zone); z = "Densité" del'atmosphère -> Sens de diffusion de la lumière de l'atmo
            auto mc_earth{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("earth"), _assets_manager->GetShader("planet")) };
            auto tc_earth{ std::make_shared<TransformComponent>(glm::dvec3(1500.,0.,0.), 23.4, glm::dvec3(0., 1., 0.), glm::dvec3(0.12)) };
            //auto ac_earth{ std::make_shared<AtmosphereComponent>(glm::dvec3(0.20, 0.35, 1.0), 0.05, 6471.0, glm::dvec3(0.00005, 0.00013, 0.00003), glm::dvec3(2.0e-4), 6371.0, glm::dvec3(5.8e-5, 1.35e-4, 3.31e-4)) };
            auto ac_earth{ std::make_shared<AtmosphereComponent>(glm::dvec3(0.0650, 0.0815, .25), 0.15, 6471.0, glm::dvec3(1.25e-4, 1.5e-5, 5.0e-6), glm::dvec3(2.0e-5), 6371.0, glm::dvec3(5.8e-6, 1.35e-5, 3.31e-5)) };
            auto gc_earth{ std::make_shared<GravityComponent>(12742.0, 5.9736) };
            auto oc_earth{ std::make_shared<OrbitComponent>(tc_earth->position.x, glm::dvec3(0.20, 0.35, 1.0)) };
            auto dc_earth{ std::make_shared<DescriptorComponent>() };
            gc_earth->entity_reference = ett_sun;
            dc_earth->nom = "Terre";
            dc_earth->type = "Planète tellurique";
            dc_earth->_infos.push_back(std::make_tuple("Masse", "5.97 * 10^24 kg", std::optional<std::string>()));
            dc_earth->_infos.push_back(std::make_tuple("Diamètre", "12756 km", std::optional<std::string>()));
            dc_earth->_infos.push_back(std::make_tuple("Gravité", "9.8 m/s^2", "Il s'agit de l'accélération gravitationnelle à la surface de la planète, au niveau de l'équateur, elle est exprimée en mètres par second. Elle inclut l'effet de rotation de la planète. Pour les géantes gazeuses, elle est donné à 1 bar de pression dans l'atmosphère."));
            dc_earth->_infos.push_back(std::make_tuple("Vitesse d'échappement", "11.2 km/s", "Il s'agit de la vitesse nécessaire pour sortir de l'orbite gravitationnelle."));
            dc_earth->_infos.push_back(std::make_tuple("Période de rotation", "23.9 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport à un ciel étoilé au niveau de l'équateur. Un nombre négatif indique une rotation anti-horaire."));
            dc_earth->_infos.push_back(std::make_tuple("Durée d'une journée", "24.0 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport au Soleil, au niveau de l'équateur."));
            dc_earth->_infos.push_back(std::make_tuple("Distance du Soleil", "149.6 * 10^6 km", std::optional<std::string>()));
            dc_earth->_infos.push_back(std::make_tuple("Période orbitale", "365.2 j", "Temps nécessaire pour effectuer une rotation autour du Soleil."));
            dc_earth->_infos.push_back(std::make_tuple("Vitesse Orbitale", "29.8 km/s", std::optional<std::string>()));
            dc_earth->_infos.push_back(std::make_tuple("Moyenne - Température de surface", "15 °C", std::optional<std::string>()));
            dc_earth->_infos.push_back(std::make_tuple("Nombre de Satellites", "1", std::optional<std::string>()));
            dc_earth->_compositions_atmo.push_back(std::make_pair("Fer", "32.1%%"));
            dc_earth->_compositions_atmo.push_back(std::make_pair("Oxygène", "30.1%%"));
            dc_earth->_compositions_atmo.push_back(std::make_pair("Silicium", "15.1%%"));
            dc_earth->_compositions_atmo.push_back(std::make_pair("Magnésium", "13.9%%"));
            dc_earth->_compositions_atmo.push_back(std::make_pair("Soufre", "2.9%%"));
            dc_earth->_compositions_atmo.push_back(std::make_pair("Nickel", "1.8%%"));
            dc_earth->_compositions_atmo.push_back(std::make_pair("Calcium", "1.5%%"));
            dc_earth->_compositions_atmo.push_back(std::make_pair("Aluminium", "1.4%%"));
            dc_earth->_compositions_atmo.push_back(std::make_pair("Divers", "1.2%%"));
            _scene->AddComponent<MaterialComponent>(ett_earth, mc_earth);
            _scene->AddComponent<TransformComponent>(ett_earth, tc_earth);
            _scene->AddComponent<AtmosphereComponent>(ett_earth, ac_earth);
            _scene->AddComponent<GravityComponent>(ett_earth, gc_earth);
            _scene->AddComponent<OrbitComponent>(ett_earth, oc_earth);
            _scene->AddComponent<DescriptorComponent>(ett_earth, dc_earth);

            // Lune
            auto ett_moon{ _scene->CreateEntity() };
            auto mc_moon{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("moon"), _assets_manager->GetShader("planet")) };
            auto tc_moon{ std::make_shared<TransformComponent>(glm::dvec3(1503.84,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.03)) };
            auto gc_moon{ std::make_shared<GravityComponent>(3474.8, 0.0735) };
            auto oc_moon{ std::make_shared<OrbitComponent>(tc_moon->position.x, glm::dvec3(1.0f)) };
            gc_moon->entity_reference = ett_earth;
            _scene->AddComponent<MaterialComponent>(ett_moon, mc_moon);
            _scene->AddComponent<TransformComponent>(ett_moon, tc_moon);
            _scene->AddComponent<GravityComponent>(ett_moon, gc_moon);
            _scene->AddComponent<OrbitComponent>(ett_moon, oc_moon);

            // Mars
            auto ett_mars{ _scene->CreateEntity() };
            auto mc_mars{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("mars"), _assets_manager->GetShader("planet")) };
            auto tc_mars{ std::make_shared<TransformComponent>(glm::dvec3(2200.,0.,0.), 25.2, glm::dvec3(0., 1., 0.), glm::dvec3(0.06)) };
            //auto ac_mars{ std::make_shared<AtmosphereComponent>(glm::dvec3(1.0, 0.6, 0.3), 0.025, 379.0, glm::dvec3(0.25, 0.0025, 0.00095)) };
            auto ac_mars{ std::make_shared<AtmosphereComponent>(glm::dvec3(0.7, 0.2, 0.05), 0.025, 3489.5, glm::dvec3(0.25, 0.0025, 0.00095), glm::dvec3(4.0e-5), 3389.5, glm::dvec3(2.5e-5, 5.5e-5, 13.0e-5)) };
            auto gc_mars{ std::make_shared<GravityComponent>(6779.0, 0.64185) };
            auto oc_mars{ std::make_shared<OrbitComponent>(tc_mars->position.x, ac_mars->atmosphere_color) };
            auto dc_mars{ std::make_shared<DescriptorComponent>() };
            gc_mars->entity_reference = ett_sun;
            dc_mars->nom = "Mars";
            dc_mars->type = "Planète tellurique";
            dc_mars->_infos.push_back(std::make_tuple("Masse", "0.642 * 10^24 kg", std::optional<std::string>()));
            dc_mars->_infos.push_back(std::make_tuple("Diamètre", "6792 km", std::optional<std::string>()));
            dc_mars->_infos.push_back(std::make_tuple("Gravité", "3.7 m/s^2", "Il s'agit de l'accélération gravitationnelle à la surface de la planète, au niveau de l'équateur, elle est exprimée en mètres par second. Elle inclut l'effet de rotation de la planète. Pour les géantes gazeuses, elle est donné à 1 bar de pression dans l'atmosphère."));
            dc_mars->_infos.push_back(std::make_tuple("Vitesse d'échappement", "5.0 km/s", "Il s'agit de la vitesse nécessaire pour sortir de l'orbite gravitationnelle."));
            dc_mars->_infos.push_back(std::make_tuple("Période de rotation", "24.6 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport à un ciel étoilé au niveau de l'équateur. Un nombre négatif indique une rotation anti-horaire."));
            dc_mars->_infos.push_back(std::make_tuple("Durée d'une journée", "24.7 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport au Soleil, au niveau de l'équateur."));
            dc_mars->_infos.push_back(std::make_tuple("Distance du Soleil", "228.0 * 10^6 km", std::optional<std::string>()));
            dc_mars->_infos.push_back(std::make_tuple("Période orbitale", "687.0 j", "Temps nécessaire pour effectuer une rotation autour du Soleil."));
            dc_mars->_infos.push_back(std::make_tuple("Vitesse Orbitale", "24.1 km/s", std::optional<std::string>()));
            dc_mars->_infos.push_back(std::make_tuple("Moyenne - Température de surface", "-65 °C", std::optional<std::string>()));
            dc_mars->_infos.push_back(std::make_tuple("Nombre de Satellites", "2", std::optional<std::string>()));
            dc_mars->_compositions_atmo.push_back(std::make_pair("Fer", "Valeur inconnue"));
            dc_mars->_compositions_atmo.push_back(std::make_pair("Silicium", "Valeur inconnue"));
            dc_mars->_compositions_atmo.push_back(std::make_pair("Magnésium", "Valeur inconnue"));
            dc_mars->_compositions_atmo.push_back(std::make_pair("Soufre", "Valeur inconnue"));
            dc_mars->_compositions_atmo.push_back(std::make_pair("Potassium", "Valeur inconnue"));
            dc_mars->_compositions_atmo.push_back(std::make_pair("Strontium", "Valeur inconnue"));
            dc_mars->_compositions_atmo.push_back(std::make_pair("Yttrium", "Valeur inconnue"));
            dc_mars->_compositions_atmo.push_back(std::make_pair("Titane", "Valeur inconnue"));
            dc_mars->_compositions_atmo.push_back(std::make_pair("Chlore", "Valeur inconnue"));
            dc_mars->_compositions_atmo.push_back(std::make_pair("Calcium", "Valeur inconnue"));
            dc_mars->_compositions_atmo.push_back(std::make_pair("Aluminium", "Valeur inconnue"));
            _scene->AddComponent<MaterialComponent>(ett_mars, mc_mars);
            _scene->AddComponent<TransformComponent>(ett_mars, tc_mars);
            _scene->AddComponent<AtmosphereComponent>(ett_mars, ac_mars);
            _scene->AddComponent<GravityComponent>(ett_mars, gc_mars);
            _scene->AddComponent<OrbitComponent>(ett_mars, oc_mars);
            _scene->AddComponent<DescriptorComponent>(ett_mars, dc_mars);

            // Deimos
            auto ett_deimos{ _scene->CreateEntity() };
            auto mc_deimos{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("deimos"), _assets_manager->GetShader("planet")) };
            auto tc_deimos{ std::make_shared<TransformComponent>(glm::dvec3(2200.23,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.00124)) };
            auto gc_deimos{ std::make_shared<GravityComponent>(12.4, 1.48e-9) };
            auto oc_deimos{ std::make_shared<OrbitComponent>(tc_deimos->position.x, glm::dvec3(1.0f)) };
            gc_deimos->entity_reference = ett_mars;
            _scene->AddComponent<MaterialComponent>(ett_deimos, mc_deimos);
            _scene->AddComponent<TransformComponent>(ett_deimos, tc_deimos);
            _scene->AddComponent<GravityComponent>(ett_deimos, gc_deimos);
            _scene->AddComponent<OrbitComponent>(ett_deimos, oc_deimos);

            // Phobos
            auto ett_phobos{ _scene->CreateEntity() };
            auto mc_phobos{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("phobos"), _assets_manager->GetShader("planet")) };
            auto tc_phobos{ std::make_shared<TransformComponent>(glm::dvec3(2200.09,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.0022533)) };
            auto gc_phobos{ std::make_shared<GravityComponent>(22.533, 1.072e-8) };
            auto oc_phobos{ std::make_shared<OrbitComponent>(tc_phobos->position.x, glm::dvec3(1.0f)) };
            gc_phobos->entity_reference = ett_mars;
            _scene->AddComponent<MaterialComponent>(ett_phobos, mc_phobos);
            _scene->AddComponent<TransformComponent>(ett_phobos, tc_phobos);
            _scene->AddComponent<GravityComponent>(ett_phobos, gc_phobos);
            _scene->AddComponent<OrbitComponent>(ett_phobos, oc_phobos);

            // Ceinture d'astéroide
            auto ett_rb{ _scene->CreateEntity() };
            auto tc_rb{ std::make_shared<TransformComponent>(glm::dvec3(0.,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.01)) };
            auto rc_rb{ std::make_shared<RingComponent>(42500, 2350.f, 100.4f, 40.f, 0.25, RingDirection::HORIZONTAL, _assets_manager->GetModel("asteroid"), _assets_manager->GetShader("asteroid")) };
            _scene->AddComponent<TransformComponent>(ett_rb, tc_rb);
            _scene->AddComponent<RingComponent>(ett_rb, rc_rb);

            // Jupiter
            auto ett_jupiter{ _scene->CreateEntity() };
            auto mc_jupiter{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("jupiter"), _assets_manager->GetShader("planet")) };
            auto tc_jupiter{ std::make_shared<TransformComponent>(glm::dvec3(7500., 0., 0.), 3.1, glm::dvec3(0., 1., 0.), glm::dvec3(1.4)) };
            //auto tc_jupiter{ std::make_shared<TransformComponent>(glm::dvec3(7500., 0., 0.), 3.1, glm::dvec3(0., 1., 0.), glm::dvec3(0.12)) };
            //auto ac_jupiter{ std::make_shared<AtmosphereComponent>(glm::dvec3(1.0, 0.8, 0.5), 0.5, 6992.1, glm::dvec3(15.0, 5.0, 0.0)) };
            auto ac_jupiter{ std::make_shared<AtmosphereComponent>(glm::dvec3(0.8, 0.6, 0.2), 0.5, 84911.0, glm::dvec3(1.9e-5, 4.1e-5, 4.4e-5), glm::dvec3(4.0e-3), 69911.0, glm::dvec3(1.5e-2, 3.3e-2, 8.0e-2)) };
            auto gc_jupiter{ std::make_shared<GravityComponent>(139820.0, 1898.6) };
            auto rc_jupiter{ std::make_shared<RingComponent>(2000, 2.5f, 0.1f, 50000.0f, 0.0009, RingDirection::HORIZONTAL, _assets_manager->GetModel("asteroid"), _assets_manager->GetShader("asteroid")) };
            auto oc_jupiter{ std::make_shared<OrbitComponent>(tc_jupiter->position.x, ac_jupiter->atmosphere_color) };
            auto dc_jupiter{ std::make_shared<DescriptorComponent>() };
            gc_jupiter->entity_reference = ett_sun;
            dc_jupiter->nom = "Jupiter";
            dc_jupiter->type = "Géante gazeuse";
            dc_jupiter->_infos.push_back(std::make_tuple("Masse", "1898.0 * 10^24 kg", std::optional<std::string>()));
            dc_jupiter->_infos.push_back(std::make_tuple("Diamètre", "142984 km", std::optional<std::string>()));
            dc_jupiter->_infos.push_back(std::make_tuple("Gravité", "23.1 m/s^2", "Il s'agit de l'accélération gravitationnelle à la surface de la planète, au niveau de l'équateur, elle est exprimée en mètres par second. Elle inclut l'effet de rotation de la planète. Pour les géantes gazeuses, elle est donné à 1 bar de pression dans l'atmosphère."));
            dc_jupiter->_infos.push_back(std::make_tuple("Vitesse d'échappement", "59.5 km/s", "Il s'agit de la vitesse nécessaire pour sortir de l'orbite gravitationnelle."));
            dc_jupiter->_infos.push_back(std::make_tuple("Période de rotation", "9.9 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport à un ciel étoilé au niveau de l'équateur. Un nombre négatif indique une rotation anti-horaire."));
            dc_jupiter->_infos.push_back(std::make_tuple("Durée d'une journée", "9.9 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport au Soleil, au niveau de l'équateur."));
            dc_jupiter->_infos.push_back(std::make_tuple("Distance du Soleil", "778.5 * 10^6 km", std::optional<std::string>()));
            dc_jupiter->_infos.push_back(std::make_tuple("Période orbitale", "4331 j", "Temps nécessaire pour effectuer une rotation autour du Soleil."));
            dc_jupiter->_infos.push_back(std::make_tuple("Vitesse Orbitale", "13.1 km/s", std::optional<std::string>()));
            dc_jupiter->_infos.push_back(std::make_tuple("Moyenne - Température de surface", "-110 °C", std::optional<std::string>()));
            dc_jupiter->_infos.push_back(std::make_tuple("Nombre de Satellites", "92", std::optional<std::string>()));
            dc_jupiter->_compositions_atmo.push_back(std::make_pair("Hydrogène", "75%%"));
            dc_jupiter->_compositions_atmo.push_back(std::make_pair("Hélium", "24%%"));
            dc_jupiter->_compositions_atmo.push_back(std::make_pair("Méthane", "< 0.1%%"));
            dc_jupiter->_compositions_atmo.push_back(std::make_pair("Ammoniac", "< 0.1%%"));
            dc_jupiter->_compositions_atmo.push_back(std::make_pair("Carbone", "< 0.1%%"));
            dc_jupiter->_compositions_atmo.push_back(std::make_pair("Ethane", "< 0.1%%"));
            dc_jupiter->_compositions_atmo.push_back(std::make_pair("Oxygène", "< 0.1%%"));
            dc_jupiter->_compositions_atmo.push_back(std::make_pair("Soufre", "< 0.1%%"));
            dc_jupiter->_compositions_atmo.push_back(std::make_pair("Divers", "< 0.1%%"));
            _scene->AddComponent<MaterialComponent>(ett_jupiter, mc_jupiter);
            _scene->AddComponent<TransformComponent>(ett_jupiter, tc_jupiter);
            _scene->AddComponent<AtmosphereComponent>(ett_jupiter, ac_jupiter);
            _scene->AddComponent<GravityComponent>(ett_jupiter, gc_jupiter);
            _scene->AddComponent<OrbitComponent>(ett_jupiter, oc_jupiter);
            _scene->AddComponent<RingComponent>(ett_jupiter, rc_jupiter);
            _scene->AddComponent<DescriptorComponent>(ett_jupiter, dc_jupiter);

            // Io
            auto ett_io{ _scene->CreateEntity() };
            auto mc_io{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("io"), _assets_manager->GetShader("planet")) };
            auto tc_io{ std::make_shared<TransformComponent>(glm::dvec3(7504.218,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.03)) };
            auto gc_io{ std::make_shared<GravityComponent>(3643.0, 0.089319) };
            auto oc_io{ std::make_shared<OrbitComponent>(tc_io->position.x, glm::dvec3(1.0f)) };
            gc_io->entity_reference = ett_jupiter;
            _scene->AddComponent<MaterialComponent>(ett_io, mc_io);
            _scene->AddComponent<TransformComponent>(ett_io, tc_io);
            _scene->AddComponent<GravityComponent>(ett_io, gc_io);
            _scene->AddComponent<OrbitComponent>(ett_io, oc_io);

            // Europa
            auto ett_europa{ _scene->CreateEntity() };
            auto mc_europa{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("europa"), _assets_manager->GetShader("planet")) };
            auto tc_europa{ std::make_shared<TransformComponent>(glm::dvec3(7506.711,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.03)) };
            auto gc_europa{ std::make_shared<GravityComponent>(3122.0, 0.048) };
            auto oc_europa{ std::make_shared<OrbitComponent>(tc_europa->position.x, glm::dvec3(1.0f)) };
            gc_europa->entity_reference = ett_jupiter;
            _scene->AddComponent<MaterialComponent>(ett_europa, mc_europa);
            _scene->AddComponent<TransformComponent>(ett_europa, tc_europa);
            _scene->AddComponent<GravityComponent>(ett_europa, gc_europa);
            _scene->AddComponent<OrbitComponent>(ett_europa, oc_europa);

            // Ganymede
            auto ett_ganymede{ _scene->CreateEntity() };
            auto mc_ganymede{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("ganymede"), _assets_manager->GetShader("planet")) };
            auto tc_ganymede{ std::make_shared<TransformComponent>(glm::dvec3(7510.74,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.052)) };
            auto gc_ganymede{ std::make_shared<GravityComponent>(5262.0, 0.1481) };
            auto oc_ganymede{ std::make_shared<OrbitComponent>(tc_ganymede->position.x, glm::dvec3(1.0f)) };
            gc_ganymede->entity_reference = ett_jupiter;
            _scene->AddComponent<MaterialComponent>(ett_ganymede, mc_ganymede);
            _scene->AddComponent<TransformComponent>(ett_ganymede, tc_ganymede);
            _scene->AddComponent<GravityComponent>(ett_ganymede, gc_ganymede);
            _scene->AddComponent<OrbitComponent>(ett_ganymede, oc_ganymede);

            // Callisto
            auto ett_callisto{ _scene->CreateEntity() };
            auto mc_callisto{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("callisto"), _assets_manager->GetShader("planet")) };
            auto tc_callisto{ std::make_shared<TransformComponent>(glm::dvec3(7518.827,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.048)) };
            auto gc_callisto{ std::make_shared<GravityComponent>(2410.0, 0.1075) };
            auto oc_callisto{ std::make_shared<OrbitComponent>(tc_callisto->position.x, glm::dvec3(1.0f)) };
            gc_callisto->entity_reference = ett_jupiter;
            _scene->AddComponent<MaterialComponent>(ett_callisto, mc_callisto);
            _scene->AddComponent<TransformComponent>(ett_callisto, tc_callisto);
            _scene->AddComponent<GravityComponent>(ett_callisto, gc_callisto);
            _scene->AddComponent<OrbitComponent>(ett_callisto, oc_callisto);

            // Saturne
            auto ett_saturn{ _scene->CreateEntity() };
            auto mc_saturn{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("saturn"), _assets_manager->GetShader("planet")) };
            auto tc_saturn{ std::make_shared<TransformComponent>(glm::dvec3(14000.,0.,0.), 26.7, glm::dvec3(0., 1., 0.), glm::dvec3(1.2)) };
            auto rc_saturn{ std::make_shared<RingComponent>(25000, 1.55f, 0.2f, 20000.0f, 0.0008, RingDirection::HORIZONTAL, _assets_manager->GetModel("asteroid"), _assets_manager->GetShader("asteroid")) };
            //auto ac_saturn{ std::make_shared<AtmosphereComponent>(glm::dvec3(1.0, 0.6, 0.3), 0.5, 6038.0, glm::dvec3(15.0, 0.1, 1.25)) };
            auto ac_saturn{ std::make_shared<AtmosphereComponent>(glm::dvec3(0.8, 0.6, 0.4), 0.5, 61232.0, glm::dvec3(2.8e-5, 5.2e-5, 6.4e-5), glm::dvec3(2.5e-3), 58232.0, glm::dvec3(1.2e-2, 2.7e-2, 6.5e-2)) };
            auto gc_saturn{ std::make_shared<GravityComponent>(116460.0, 568.46) };
            auto oc_saturn{ std::make_shared<OrbitComponent>(tc_saturn->position.x, ac_saturn->atmosphere_color) };
            auto dc_saturn{ std::make_shared<DescriptorComponent>() };
            gc_saturn->entity_reference = ett_sun;
            dc_saturn->nom = "Saturne";
            dc_saturn->type = "Géante gazeuse";
            dc_saturn->_infos.push_back(std::make_tuple("Masse", "568 * 10^24 kg", std::optional<std::string>()));
            dc_saturn->_infos.push_back(std::make_tuple("Diamètre", "120536 km", std::optional<std::string>()));
            dc_saturn->_infos.push_back(std::make_tuple("Gravité", "9.0 m/s^2", "Il s'agit de l'accélération gravitationnelle à la surface de la planète, au niveau de l'équateur, elle est exprimée en mètres par second. Elle inclut l'effet de rotation de la planète. Pour les géantes gazeuses, elle est donné à 1 bar de pression dans l'atmosphère."));
            dc_saturn->_infos.push_back(std::make_tuple("Vitesse d'échappement", "35.5 km/s", "Il s'agit de la vitesse nécessaire pour sortir de l'orbite gravitationnelle."));
            dc_saturn->_infos.push_back(std::make_tuple("Période de rotation", "10.7 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport à un ciel étoilé au niveau de l'équateur. Un nombre négatif indique une rotation anti-horaire."));
            dc_saturn->_infos.push_back(std::make_tuple("Durée d'une journée", "10.7 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport au Soleil, au niveau de l'équateur."));
            dc_saturn->_infos.push_back(std::make_tuple("Distance du Soleil", "1432 * 10^6 km", std::optional<std::string>()));
            dc_saturn->_infos.push_back(std::make_tuple("Période orbitale", "10747 j", "Temps nécessaire pour effectuer une rotation autour du Soleil."));
            dc_saturn->_infos.push_back(std::make_tuple("Vitesse Orbitale", "9.7 km/s", std::optional<std::string>()));
            dc_saturn->_infos.push_back(std::make_tuple("Moyenne - Température de surface", "-140 °C", std::optional<std::string>()));
            dc_saturn->_infos.push_back(std::make_tuple("Nombre de Satellites", "83", std::optional<std::string>()));
            dc_saturn->_compositions_atmo.push_back(std::make_pair("Hydrogène", "96.3%%"));
            dc_saturn->_compositions_atmo.push_back(std::make_pair("Hélium", "3.25%%"));
            dc_saturn->_compositions_atmo.push_back(std::make_pair("Méthane", "Traces"));
            dc_saturn->_compositions_atmo.push_back(std::make_pair("Ammoniac", "Traces"));
            dc_saturn->_compositions_atmo.push_back(std::make_pair("Acétylène", "Traces"));
            dc_saturn->_compositions_atmo.push_back(std::make_pair("Phosphine", "Traces"));
            _scene->AddComponent<MaterialComponent>(ett_saturn, mc_saturn);
            _scene->AddComponent<TransformComponent>(ett_saturn, tc_saturn);
            _scene->AddComponent<RingComponent>(ett_saturn, rc_saturn);
            _scene->AddComponent<AtmosphereComponent>(ett_saturn, ac_saturn);
            _scene->AddComponent<GravityComponent>(ett_saturn, gc_saturn);
            _scene->AddComponent<OrbitComponent>(ett_saturn, oc_saturn);
            _scene->AddComponent<DescriptorComponent>(ett_saturn, dc_saturn);

            // Mimas
            auto ett_mimas{ _scene->CreateEntity() };
            auto mc_mimas{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("mimas"), _assets_manager->GetShader("planet")) };
            auto tc_mimas{ std::make_shared<TransformComponent>(glm::dvec3(14001.85,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.00418)) };
            auto gc_mimas{ std::make_shared<GravityComponent>(418.0, 3.84e-5) };
            auto oc_mimas{ std::make_shared<OrbitComponent>(tc_mimas->position.x, glm::dvec3(1.0f)) };
            gc_mimas->entity_reference = ett_saturn;
            _scene->AddComponent<MaterialComponent>(ett_mimas, mc_mimas);
            _scene->AddComponent<TransformComponent>(ett_mimas, tc_mimas);
            _scene->AddComponent<GravityComponent>(ett_mimas, gc_mimas);
            _scene->AddComponent<OrbitComponent>(ett_mimas, oc_mimas);

            // Encelade
            auto ett_encelade{ _scene->CreateEntity() };
            auto mc_encelade{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("encelade"), _assets_manager->GetShader("planet")) };
            auto tc_encelade{ std::make_shared<TransformComponent>(glm::dvec3(14002.38,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.00510)) };
            auto gc_encelade{ std::make_shared<GravityComponent>(510.0, 8.6e-5) };
            auto oc_encelade{ std::make_shared<OrbitComponent>(tc_encelade->position.x, glm::dvec3(1.0f)) };
            gc_encelade->entity_reference = ett_saturn;
            _scene->AddComponent<MaterialComponent>(ett_encelade, mc_encelade);
            _scene->AddComponent<TransformComponent>(ett_encelade, tc_encelade);
            _scene->AddComponent<GravityComponent>(ett_encelade, gc_encelade);
            _scene->AddComponent<OrbitComponent>(ett_encelade, oc_encelade);

            // Tethys
            auto ett_tethys{ _scene->CreateEntity() };
            auto mc_tethys{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("tethys"), _assets_manager->GetShader("planet")) };
            auto tc_tethys{ std::make_shared<TransformComponent>(glm::dvec3(14002.94,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.01060)) };
            auto gc_tethys{ std::make_shared<GravityComponent>(1060.0, 6.176e-4) };
            auto oc_tethys{ std::make_shared<OrbitComponent>(tc_tethys->position.x, glm::dvec3(1.0f)) };
            gc_tethys->entity_reference = ett_saturn;
            _scene->AddComponent<MaterialComponent>(ett_tethys, mc_tethys);
            _scene->AddComponent<TransformComponent>(ett_tethys, tc_tethys);
            _scene->AddComponent<GravityComponent>(ett_tethys, gc_tethys);
            _scene->AddComponent<OrbitComponent>(ett_tethys, oc_tethys);

            // Dione
            auto ett_dione{ _scene->CreateEntity() };
            auto mc_dione{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("dione"), _assets_manager->GetShader("planet")) };
            auto tc_dione{ std::make_shared<TransformComponent>(glm::dvec3(14003.7742,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.01118)) };
            auto gc_dione{ std::make_shared<GravityComponent>(1118.0, 1.096e-3) };
            auto oc_dione{ std::make_shared<OrbitComponent>(tc_dione->position.x, glm::dvec3(1.0f)) };
            gc_dione->entity_reference = ett_saturn;
            _scene->AddComponent<MaterialComponent>(ett_dione, mc_dione);
            _scene->AddComponent<TransformComponent>(ett_dione, tc_dione);
            _scene->AddComponent<GravityComponent>(ett_dione, gc_dione);
            _scene->AddComponent<OrbitComponent>(ett_dione, oc_dione);

            // Rhea
            auto ett_rhea{ _scene->CreateEntity() };
            auto mc_rhea{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("rhea"), _assets_manager->GetShader("planet")) };
            auto tc_rhea{ std::make_shared<TransformComponent>(glm::dvec3(14005.27,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.01529)) };
            auto gc_rhea{ std::make_shared<GravityComponent>(1529.0, 2.307e-3) };
            auto oc_rhea{ std::make_shared<OrbitComponent>(tc_rhea->position.x, glm::dvec3(1.0f)) };
            gc_rhea->entity_reference = ett_saturn;
            _scene->AddComponent<MaterialComponent>(ett_rhea, mc_rhea);
            _scene->AddComponent<TransformComponent>(ett_rhea, tc_rhea);
            _scene->AddComponent<GravityComponent>(ett_rhea, gc_rhea);
            _scene->AddComponent<OrbitComponent>(ett_rhea, oc_rhea);

            // Titan
            auto ett_titan{ _scene->CreateEntity() };
            auto mc_titan{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("titan"), _assets_manager->GetShader("planet")) };
            auto tc_titan{ std::make_shared<TransformComponent>(glm::dvec3(14012.22,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.05)) };
            auto gc_titan{ std::make_shared<GravityComponent>(5151.0, 1.3456e-1) };
            auto oc_titan{ std::make_shared<OrbitComponent>(tc_titan->position.x, glm::dvec3(1.0f)) };
            auto ac_titan{ std::make_shared<AtmosphereComponent>(glm::dvec3(0.6, 0.4, 0.1), 0.025, 3174.7, glm::dvec3(1.1e-4, 2.2e-4, 3.3e-4), glm::dvec3(5.33e-5), 2574.7, glm::dvec3(1.14e-4, 3.84e-4, 6.80e-4)) };
            gc_titan->entity_reference = ett_saturn;
            _scene->AddComponent<MaterialComponent>(ett_titan, mc_titan);
            _scene->AddComponent<TransformComponent>(ett_titan, tc_titan);
            _scene->AddComponent<GravityComponent>(ett_titan, gc_titan);
            _scene->AddComponent<OrbitComponent>(ett_titan, oc_titan);
            _scene->AddComponent<AtmosphereComponent>(ett_titan, ac_titan);

            // Japet
            auto ett_japet{ _scene->CreateEntity() };
            auto mc_japet{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("japet"), _assets_manager->GetShader("planet")) };
            auto tc_japet{ std::make_shared<TransformComponent>(glm::dvec3(14035.60,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.0145)) };
            auto gc_japet{ std::make_shared<GravityComponent>(1450.0, 1.805e-3) };
            auto oc_japet{ std::make_shared<OrbitComponent>(tc_japet->position.x, glm::dvec3(1.0f)) };
            gc_japet->entity_reference = ett_saturn;
            _scene->AddComponent<MaterialComponent>(ett_japet, mc_japet);
            _scene->AddComponent<TransformComponent>(ett_japet, tc_japet);
            _scene->AddComponent<GravityComponent>(ett_japet, gc_japet);
            _scene->AddComponent<OrbitComponent>(ett_japet, oc_japet);

            // Uranus
            auto ett_uranus{ _scene->CreateEntity() };
            auto mc_uranus{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("uranus"), _assets_manager->GetShader("planet")) };
            auto tc_uranus{ std::make_shared<TransformComponent>(glm::dvec3(28700.,0.,0.), 97.8, glm::dvec3(0., 1., 0.), glm::dvec3(0.49)) };
            //auto ac_uranus{ std::make_shared<AtmosphereComponent>(glm::dvec3(0.5, 1.0, 0.7), 0.05, 2559.9, glm::dvec3(15, 0.5, 0.000175)) };
            auto ac_uranus{ std::make_shared<AtmosphereComponent>(glm::dvec3(0.4, 0.8, 0.9), 0.05, 30362.0, glm::dvec3(4.2e-5, 8.4e-5, 13.6e-5), glm::dvec3(4.0e-3), 25362.0, glm::dvec3(4.0e-3, 8.0e-3, 1.8e-2)) };
            auto gc_uranus{ std::make_shared<GravityComponent>(50724.0, 86.831) };
            auto rc_uranus{ std::make_shared<RingComponent>(7500, .8f, 0.05f, 10000.0f, 0.00025, RingDirection::HORIZONTAL, _assets_manager->GetModel("asteroid"), _assets_manager->GetShader("asteroid")) };
            auto oc_uranus{ std::make_shared<OrbitComponent>(tc_uranus->position.x, ac_uranus->atmosphere_color) };
            auto dc_uranus{ std::make_shared<DescriptorComponent>() };
            gc_uranus->entity_reference = ett_sun;
            dc_uranus->nom = "Uranus";
            dc_uranus->type = "Géante de glace";
            dc_uranus->_infos.push_back(std::make_tuple("Masse", "86.8 * 10^24 kg", std::optional<std::string>()));
            dc_uranus->_infos.push_back(std::make_tuple("Diamètre", "51118 km", std::optional<std::string>()));
            dc_uranus->_infos.push_back(std::make_tuple("Gravité", "11.0 m/s^2", "Il s'agit de l'accélération gravitationnelle à la surface de la planète, au niveau de l'équateur, elle est exprimée en mètres par second. Elle inclut l'effet de rotation de la planète. Pour les géantes gazeuses, elle est donné à 1 bar de pression dans l'atmosphère."));
            dc_uranus->_infos.push_back(std::make_tuple("Vitesse d'échappement", "21.3 km/s", "Il s'agit de la vitesse nécessaire pour sortir de l'orbite gravitationnelle."));
            dc_uranus->_infos.push_back(std::make_tuple("Période de rotation", "-17.2 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport à un ciel étoilé au niveau de l'équateur. Un nombre négatif indique une rotation anti-horaire."));
            dc_uranus->_infos.push_back(std::make_tuple("Durée d'une journée", "17.2 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport au Soleil, au niveau de l'équateur."));
            dc_uranus->_infos.push_back(std::make_tuple("Distance du Soleil", "2867.0 * 10^6 km", std::optional<std::string>()));
            dc_uranus->_infos.push_back(std::make_tuple("Période orbitale", "30589 j", "Temps nécessaire pour effectuer une rotation autour du Soleil."));
            dc_uranus->_infos.push_back(std::make_tuple("Vitesse Orbitale", "6.8 km/s", std::optional<std::string>()));
            dc_uranus->_infos.push_back(std::make_tuple("Moyenne - Température de surface", "-195 °C", std::optional<std::string>()));
            dc_uranus->_infos.push_back(std::make_tuple("Nombre de Satellites", "27", std::optional<std::string>()));
            dc_uranus->_compositions_atmo.push_back(std::make_pair("Hydrogène", "Valeur inconnue"));
            dc_uranus->_compositions_atmo.push_back(std::make_pair("Hélium", "Valeur inconnue"));
            dc_uranus->_compositions_atmo.push_back(std::make_pair("Méthane", "Valeur inconnue"));
            dc_uranus->_compositions_atmo.push_back(std::make_pair("Ammoniac", "Valeur inconnue"));
            dc_uranus->_compositions_atmo.push_back(std::make_pair("Eau", "Valeur inconnue"));
            _scene->AddComponent<MaterialComponent>(ett_uranus, mc_uranus);
            _scene->AddComponent<TransformComponent>(ett_uranus, tc_uranus);
            _scene->AddComponent<AtmosphereComponent>(ett_uranus, ac_uranus);
            _scene->AddComponent<GravityComponent>(ett_uranus, gc_uranus);
            _scene->AddComponent<RingComponent>(ett_uranus, rc_uranus);
            _scene->AddComponent<OrbitComponent>(ett_uranus, oc_uranus);
            _scene->AddComponent<DescriptorComponent>(ett_uranus, dc_uranus);

            // Miranda
            auto ett_miranda{ _scene->CreateEntity() };
            auto mc_miranda{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("miranda"), _assets_manager->GetShader("planet")) };
            auto tc_miranda{ std::make_shared<TransformComponent>(glm::dvec3(28701.29,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.004716)) };
            auto gc_miranda{ std::make_shared<GravityComponent>(471.6, 6.59e-5) };
            auto oc_miranda{ std::make_shared<OrbitComponent>(tc_miranda->position.x, glm::dvec3(1.0f)) };
            gc_miranda->entity_reference = ett_uranus;
            _scene->AddComponent<MaterialComponent>(ett_miranda, mc_miranda);
            _scene->AddComponent<TransformComponent>(ett_miranda, tc_miranda);
            _scene->AddComponent<GravityComponent>(ett_miranda, gc_miranda);
            _scene->AddComponent<OrbitComponent>(ett_miranda, oc_miranda);

            // Titania
            auto ett_titania{ _scene->CreateEntity() };
            auto mc_titania{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("titania"), _assets_manager->GetShader("planet")) };
            auto tc_titania{ std::make_shared<TransformComponent>(glm::dvec3(28704.36,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.015768)) };
            auto gc_titania{ std::make_shared<GravityComponent>(1576.8, 3.527e-3) };
            auto oc_titania{ std::make_shared<OrbitComponent>(tc_titania->position.x, glm::dvec3(1.0f)) };
            gc_titania->entity_reference = ett_uranus;
            _scene->AddComponent<MaterialComponent>(ett_titania, mc_titania);
            _scene->AddComponent<TransformComponent>(ett_titania, tc_titania);
            _scene->AddComponent<GravityComponent>(ett_titania, gc_titania);
            _scene->AddComponent<OrbitComponent>(ett_titania, oc_titania);

            // Umbriel
            auto ett_umbriel{ _scene->CreateEntity() };
            auto mc_umbriel{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("umbriel"), _assets_manager->GetShader("planet")) };
            auto tc_umbriel{ std::make_shared<TransformComponent>(glm::dvec3(28702.66,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.01169)) };
            auto gc_umbriel{ std::make_shared<GravityComponent>(1169.0, 1.172e-3) };
            auto oc_umbriel{ std::make_shared<OrbitComponent>(tc_umbriel->position.x, glm::dvec3(1.0f)) };
            gc_umbriel->entity_reference = ett_uranus;
            _scene->AddComponent<MaterialComponent>(ett_umbriel, mc_umbriel);
            _scene->AddComponent<TransformComponent>(ett_umbriel, tc_umbriel);
            _scene->AddComponent<GravityComponent>(ett_umbriel, gc_umbriel);
            _scene->AddComponent<OrbitComponent>(ett_umbriel, oc_umbriel);

            // Ariel
            auto ett_ariel{ _scene->CreateEntity() };
            auto mc_ariel{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("ariel"), _assets_manager->GetShader("planet")) };
            auto tc_ariel{ std::make_shared<TransformComponent>(glm::dvec3(28701.9,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.01150)) };
            auto gc_ariel{ std::make_shared<GravityComponent>(1150.0, 1.4e-3) };
            auto oc_ariel{ std::make_shared<OrbitComponent>(tc_ariel->position.x, glm::dvec3(1.0f)) };
            gc_ariel->entity_reference = ett_uranus;
            _scene->AddComponent<MaterialComponent>(ett_ariel, mc_ariel);
            _scene->AddComponent<TransformComponent>(ett_ariel, tc_ariel);
            _scene->AddComponent<GravityComponent>(ett_ariel, gc_ariel);
            _scene->AddComponent<OrbitComponent>(ett_ariel, oc_ariel);

            // Obéron
            auto ett_oberon{ _scene->CreateEntity() };
            auto mc_oberon{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("oberon"), _assets_manager->GetShader("planet")) };
            auto tc_oberon{ std::make_shared<TransformComponent>(glm::dvec3(28705.8,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.01522)) };
            auto gc_oberon{ std::make_shared<GravityComponent>(1522.8, 5.046e-3) };
            auto oc_oberon{ std::make_shared<OrbitComponent>(tc_oberon->position.x, glm::dvec3(1.0f)) };
            gc_oberon->entity_reference = ett_uranus;
            _scene->AddComponent<MaterialComponent>(ett_oberon, mc_oberon);
            _scene->AddComponent<TransformComponent>(ett_oberon, tc_oberon);
            _scene->AddComponent<GravityComponent>(ett_oberon, gc_oberon);
            _scene->AddComponent<OrbitComponent>(ett_oberon, oc_oberon);

            // Neptune
            auto ett_neptune{ _scene->CreateEntity() };
            auto mc_neptune{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("neptune"), _assets_manager->GetShader("planet")) };
            auto tc_neptune{ std::make_shared<TransformComponent>(glm::dvec3(45000.f, 0.f, 0.f), 28.3f, glm::dvec3(0.f, 1.f, 0.f), glm::dvec3(0.49)) };
            //auto ac_neptune{ std::make_shared<AtmosphereComponent>(glm::dvec3(0.3f, 0.5f, 1.0f), 0.05, 2480.4f, glm::dvec3(7.5, 1.5, 0.00001)) };
            auto ac_neptune{ std::make_shared<AtmosphereComponent>(glm::dvec3(0.1, 0.1, 0.8), 0.05, 29622.0, glm::dvec3(4.0e-5, 7.5e-5, 9.0e-5), glm::dvec3(2.55e-2), 24622.0, glm::dvec3(45.32e-2, 1.86e-1, 3.98e-1)) };
            auto gc_neptune{ std::make_shared<GravityComponent>(49244.0, 102.43) };
            auto rc_neptune{ std::make_shared<RingComponent>(7500, 0.8f, 0.05f, 10000.0f, 0.00025, RingDirection::HORIZONTAL, _assets_manager->GetModel("asteroid"), _assets_manager->GetShader("asteroid")) };
            auto oc_neptune{ std::make_shared<OrbitComponent>(tc_neptune->position.x, ac_neptune->atmosphere_color) };
            auto dc_neptune{ std::make_shared<DescriptorComponent>() };
            gc_neptune->entity_reference = ett_sun;
            dc_neptune->nom = "Neptune";
            dc_neptune->type = "Géante de glace";
            dc_neptune->_infos.push_back(std::make_tuple("Masse", "102.0 * 10^24 kg", std::optional<std::string>()));
            dc_neptune->_infos.push_back(std::make_tuple("Diamètre", "49528 km", std::optional<std::string>()));
            dc_neptune->_infos.push_back(std::make_tuple("Gravité", "11.0 m/s^2", "Il s'agit de l'accélération gravitationnelle à la surface de la planète, au niveau de l'équateur, elle est exprimée en mètres par second. Elle inclut l'effet de rotation de la planète. Pour les géantes gazeuses, elle est donné à 1 bar de pression dans l'atmosphère."));
            dc_neptune->_infos.push_back(std::make_tuple("Vitesse d'échappement", "23.5 km/s", "Il s'agit de la vitesse nécessaire pour sortir de l'orbite gravitationnelle."));
            dc_neptune->_infos.push_back(std::make_tuple("Période de rotation", "16.1 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport à un ciel étoilé au niveau de l'équateur. Un nombre négatif indique une rotation anti-horaire."));
            dc_neptune->_infos.push_back(std::make_tuple("Durée d'une journée", "16.1 h", "Temps nécessaire pour effectuer une rotation complète sur elle-même, par rapport au Soleil, au niveau de l'équateur."));
            dc_neptune->_infos.push_back(std::make_tuple("Distance du Soleil", "4515.0 * 10^6 km", std::optional<std::string>()));
            dc_neptune->_infos.push_back(std::make_tuple("Période orbitale", "59800 j", "Temps nécessaire pour effectuer une rotation autour du Soleil."));
            dc_neptune->_infos.push_back(std::make_tuple("Vitesse Orbitale", "5.4 km/s", std::optional<std::string>()));
            dc_neptune->_infos.push_back(std::make_tuple("Moyenne - Température de surface", "-200 °C", std::optional<std::string>()));
            dc_neptune->_infos.push_back(std::make_tuple("Nombre de Satellites", "14", std::optional<std::string>()));
            dc_neptune->_compositions_atmo.push_back(std::make_pair("Hydrogène", "Valeur inconnue"));
            dc_neptune->_compositions_atmo.push_back(std::make_pair("Hélium", "Valeur inconnue"));
            dc_neptune->_compositions_atmo.push_back(std::make_pair("Méthane", "Valeur inconnue"));
            dc_neptune->_compositions_atmo.push_back(std::make_pair("Ammoniac", "Valeur inconnue"));
            dc_neptune->_compositions_atmo.push_back(std::make_pair("Eau", "Valeur inconnue"));
            _scene->AddComponent<MaterialComponent>(ett_neptune, mc_neptune);
            _scene->AddComponent<TransformComponent>(ett_neptune, tc_neptune);
            _scene->AddComponent<AtmosphereComponent>(ett_neptune, ac_neptune);
            _scene->AddComponent<GravityComponent>(ett_neptune, gc_neptune);
            _scene->AddComponent<RingComponent>(ett_neptune, rc_neptune);
            _scene->AddComponent<OrbitComponent>(ett_neptune, oc_neptune);
            _scene->AddComponent<DescriptorComponent>(ett_neptune, dc_neptune);

            // Triton
            auto ett_triton{ _scene->CreateEntity() };
            auto mc_triton{ std::make_shared<MaterialComponent>(_assets_manager->GetModel("triton"), _assets_manager->GetShader("planet")) };
            auto tc_triton{ std::make_shared<TransformComponent>(glm::dvec3(45003.54,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.027)) };
            auto gc_triton{ std::make_shared<GravityComponent>(2706.8, 2.14e-2) };
            auto oc_triton{ std::make_shared<OrbitComponent>(tc_triton->position.x, glm::dvec3(1.0f)) };
            gc_triton->entity_reference = ett_neptune;
            _scene->AddComponent<MaterialComponent>(ett_triton, mc_triton);
            _scene->AddComponent<TransformComponent>(ett_triton, tc_triton);
            _scene->AddComponent<GravityComponent>(ett_triton, gc_triton);
            _scene->AddComponent<OrbitComponent>(ett_triton, oc_triton);

            // Ceinture de Kuiper
            auto ett_kb{ _scene->CreateEntity() };
            auto tc_kb{ std::make_shared<TransformComponent>(glm::dvec3(0.,0.,0.), 0, glm::dvec3(0., 0.01, 0.), glm::dvec3(0.01)) };
            auto rc_kb{ std::make_shared<RingComponent>(105000, 45200.f, 100.f, 2.f, 1., RingDirection::HORIZONTAL, _assets_manager->GetModel("asteroid"), _assets_manager->GetShader("asteroid")) };
            _scene->AddComponent<TransformComponent>(ett_kb, tc_kb);
            _scene->AddComponent<RingComponent>(ett_kb, rc_kb);

            // On attache la scène qui vient d'être créée à l'UI
            this->_user_interface->AttachSceneToUI(this->_scene);
        }

        catch(const std::exception& e)
        {
            this->_log->writeError(e.what());
        }
    }
    
    void Application::Run()
    {
        try
        {
            while(this->_window->Active())
            {
                // Mise à jour du Timestep
                this->_timestep->UpdateTime();

                // Entrée
                this->_input_handler->HandleInput(this->_window, this->_scene, this->_user_interface, this->_timestep->getDeltatime());

                // Mise à jour de la scène
                this->_scene->Update(this->_timestep->getDeltatime(), this->_timestep->getLastFrame());

                // Afficher l'image actuel
                this->_renderer->DrawScene(this->_scene, this->_user_interface, this->_timestep->getDeltatime(), this->_timestep->getLastFrame());

                // Récupérer les évènements et swap les buffers
                this->_window->Update();
            }
        }
        catch(const std::exception& e)
        {
            this->_log->writeError(e.what());
        }
    }
}