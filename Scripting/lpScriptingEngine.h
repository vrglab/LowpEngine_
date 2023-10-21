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

LP_Export struct MonoBehaviourChild
{
	MonoClass* classType;
	MonoMethod* awakeMethod;
	MonoMethod* startMethod;
	MonoMethod* updateMethod;
	MonoMethod* onEnableMethod;
	MonoMethod* onDisableMethod;
	MonoMethod* onDestroyMethod;
};


LP_Export struct ScriptingEngine {
	MonoDomain* root_domain;
	MonoDomain* app_domain;
	MonoAssembly* core_assembly;
	MonoAssembly* game_assembly;
};


LP_Export MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath);
LP_Export int InitScriptingEngine(std::string GameName, ScriptingEngine* engine);

#endif