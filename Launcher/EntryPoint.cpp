#include "lplupch.h"
#include <LowpEngineCore.h>
#include <iostream>

#undef main

#ifdef _WIN32
// Windows-specific headers and entry point
#include <Windows.h>

int WINAPI main(int argc, char* argv[]) {
    GameInfo* info = new GameInfo();
    info->name = "Test";
    info->resolution = new Resolution();
    info->resolution->width = 600;
    info->resolution->height = 400;
    info->soundSystemInfo = {};
    info->soundSystemInfo.be_Type = SoundSystemBackendType::OpenAL;
    info->renderer_type = RendererType::OpenGL;

    Game* game = new Game();

    InitGame(info, game);
    StartGame(game);
    CleanupGame(game);
    return 0;
}

#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
int main(int argc, char* argv[]) {
    GameInfo* info = new GameInfo();
    info->name = "Test";
    info->resolution = new Resolution();
    info->resolution->width = 600;
    info->resolution->height = 400;
    info->soundSystemInfo = {};
    info->soundSystemInfo.be_Type = SoundSystemBackendType::OpenAL;
    info->renderer_type = RendererType::OpenGL;

    Game* game = new Game();

    InitGame(info, game);
    StartGame(game);
    CleanupGame(game);
    return 0;
}

#else
#error "Unsupported platform"
#endif