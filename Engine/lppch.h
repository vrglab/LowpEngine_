#pragma once

#include<SDL2/SDL.h>
#include<vulkan/vulkan.h>
#include<stb_image.h>

#ifndef _lpEngine_assimp
#define _lpEngine_assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif

#include <glm/glm.hpp>
#include <vector>

#ifndef _lpEngine_bgfx
#define _lpEngine_bgfx
#include<bx/bx.h>
#include<bimg/bimg.h>
#include<bgfx/bgfx.h>
#include<bgfx/platform.h>
#include<bgfx/defines.h>
#include<bgfx/embedded_shader.h>
#include<bgfx/c99/bgfx.h>
using namespace bgfx;
#endif _lpEngine_bgfx
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

#include "LowpEngine.h"