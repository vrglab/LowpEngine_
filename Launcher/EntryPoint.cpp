#include "lplupch.h"
#include <iostream>

#ifdef _WIN32
// Windows-specific headers and entry point
#include <Windows.h>

int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::cout << "Running on Windows!" << std::endl;
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