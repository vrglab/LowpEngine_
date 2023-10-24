/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once
#include <mono/metadata/metadata.h>
#include <mono/metadata/object.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <EngineCommons/LowpCommons.h>

LP_Export class MonoBehaviour
{
public:
	MonoClass* classType;
	MonoMethod* awakeMethod;
	MonoMethod* startMethod;
	MonoMethod* updateMethod;
	MonoMethod* onEnableMethod;
	MonoMethod* onDisableMethod;
	MonoMethod* onDestroyMethod;
	MonoObject* CreateInstance(ScriptingEngine* engine);
};