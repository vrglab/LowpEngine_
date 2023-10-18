/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*  Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                                     */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once

#ifndef _lpEngine_ 
#define _lpEngine_
#include "Macros.h"
#include "PhysicsEngineCore.h"
#include "RenderingEngine.h"

#ifndef _lpEngine_Physics
#error  Physics engine not initialized
#endif

//Windowing
#include "Windowing/Window.h"

//Meshing
#include "Types/Mesh.h"
#include "Loaders/Assimp.h"

//Rendering
#include "Rendering/Renderer.h"

//Application Handling
#include "Application Handling/Application.h"

#endif // !_lpEngine_ 
