/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once

#ifndef _lpEngine_Renderer_
#define _lpEngine_Renderer_

//Dependencies
#include<SDL2/SDL.h>
#include<stb_image.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

//The rendering engine headers
#include "Macros.h"
#include "Types/RenderingEngineCreateInfo.h"
#include "RenderingFramework.h"
#include "ResourceFactories/OpenGLResourceFactory.h"
#include "RendererMannager.h"
#endif