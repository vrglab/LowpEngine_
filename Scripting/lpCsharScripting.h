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
#include <Macros.h>

struct Assembly
{
	MonoAssembly* assembly;
	MonoDomain* domain;
	MonoImage* image;
	~Assembly()
	{
		mono_jit_cleanup(domain);
		delete assembly;
		delete domain;
		delete image;
	}
};

LP_Export Assembly* LoadAssembly();
LP_Export void InitializeAssembly(Assembly* assembly);
LP_Export void CleanAssembly(Assembly* assembly);

#endif