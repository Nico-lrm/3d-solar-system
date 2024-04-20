#include "Core/Application.hpp"
#define STB_RECT_PACK_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STBI_THREAD_LOCAL thread_local
#include "stb/stb_image.h"

int main(int argc, char const *argv[])
{
    SPN::Application app;
    app.LoadRessources();
    app.InitScene();
    app.Run();

    return 0;
}