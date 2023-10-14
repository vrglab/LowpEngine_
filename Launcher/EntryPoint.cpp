#include "lplupch.h"
#include <iostream>

#undef main

#ifdef _WIN32
// Windows-specific headers and entry point
#include <Windows.h>

int WINAPI main(int argc, char* argv[]) {
    GameInfo* info = new GameInfo();
    info->resHeight = 400;
    info->resWidth = 600;

    Application* app = new Application(info);

    app->Initialize();

    app->Run({
    });

    return 0;
}

#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
int main(int argc, char* argv[]) {
    std::cout << "Running on a non-Windows platform!" << std::endl;
    return 0;
}

#else
#error "Unsupported platform"
#endif