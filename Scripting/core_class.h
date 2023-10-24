/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/object.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <EngineCommons/LowpCommons.h>

LP_Export class ScriptingEngine {
public:
	MonoDomain* root_domain;
	MonoDomain* app_domain;
	MonoAssembly* core_assembly;
	MonoAssembly* game_assembly;
	LP_Export MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath);
	LP_Export int Init(std::string gamename);
	LP_Export void Update();
	LP_Export void Cleanup();
};