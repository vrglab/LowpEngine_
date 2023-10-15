#pragma once

#include <sstream>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#ifdef _WIN32
#include <Windows.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <dxgi1_4.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#endif

#ifdef min
#undef min
#endif

#include <gl/GL.h>
#include <vulkan/vulkan.h>

#ifdef __APPLE__ 
#include <metal/Foundation/Foundation.hpp>
#include <metal/Metal/Metal.hpp>
#include <metal/MetalFX/MetalFX.hpp>
#include <metal/QuartzCore/QuartzCore.hpp>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_vulkan.h>
#include<stb_image.h>

#include "RenderingEngine.h"