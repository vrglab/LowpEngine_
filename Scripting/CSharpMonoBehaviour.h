/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */

#pragma once
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
