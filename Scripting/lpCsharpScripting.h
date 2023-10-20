/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */


#ifndef _LpEngine_Sharp_Scripting
#define _LpEngine_Sharp_Scripting

#include <mono/jit/jit.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <LowpCommons.h>

class CSharpMonoBehaviour
{
public:
	MonoObject* LoadedClass;
	MonoMethod* Update;
	MonoMethod* Start;
	MonoMethod* Awake;
	MonoMethod* OnDestroy;
	MonoMethod* OnEnable;
	MonoMethod* OnDisable;
	~CSharpMonoBehaviour()
	{
		delete LoadedClass;
		delete Update;
		delete Start;
		delete Awake;
		delete OnDestroy;
		delete OnEnable;
		delete OnDisable;
	}
};

struct LoadedMonoBehaviours {
	std::list<CSharpMonoBehaviour*> behaviours;
	~LoadedMonoBehaviours()
	{
		for (CSharpMonoBehaviour* behaviour : behaviours) {
			delete behaviour;
		}
		behaviours.clear();
	}
};

struct Assembly
{
	MonoAssembly* assembly;
	MonoDomain* domain;
	MonoImage* image;
	MonoClass* BehaviourRegistery;
	LoadedMonoBehaviours* behaviours;
	~Assembly()
	{
		mono_jit_cleanup(domain);
		delete assembly;
		delete domain;
		delete image;
		delete BehaviourRegistery;
	}
};

LP_Export Assembly* LoadAssembly();
LP_Export int InitializeAssembly(Assembly* assembly);
LP_Export void CleanAssembly(Assembly* assembly);

#endif