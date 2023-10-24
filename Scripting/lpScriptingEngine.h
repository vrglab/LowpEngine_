/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once

#ifndef _lpEngine_Scripting_Engine
#define _lpEngine_Scripting_Engine

#include <mono/jit/jit.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/object.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <filesystem>
#include <LowpCommons.h>
#include "core_class.h"
#include "MonoBehaviour.h"

static std::list<MonoBehaviour*> loadedBehaviours;
static ScriptingEngine* activeScriptingEngine;
#endif