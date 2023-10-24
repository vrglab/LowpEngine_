/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once

#ifndef _lpEngine_Scene_Engine
#define _lpEngine_Scene_Engine
#include <EngineCommons/LowpCommons.h>
#include <yaml-cpp/yaml.h>
#include "../Scripting/lpScriptingEngine.h"

#include "Scene.h"

static Scene* activeScene;

#include "SceneManager.h"

#endif