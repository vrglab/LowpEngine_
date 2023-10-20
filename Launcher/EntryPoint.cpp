#include "lplupch.h"
#include <iostream>

#undef main

#ifdef _WIN32
// Windows-specific headers and entry point
#include <Windows.h>

int WINAPI main(int argc, char* argv[]) {
 
}

#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
int main(int argc, char* argv[]) {
    AppInfo* info = new AppInfo();
    info->resHeight = 400;
    info->resWidth = 600;

    Application* app = new Application(info);

    app->Initialize();

    app->Run();
    return 0;
}

#else
#error "Unsupported platform"
#endif