/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once
#include <LowpCommons.h>
#include "SoundSystemInitInfo.h"

LP_Export struct SoundSystem {
public:
	void* system;
	int type;
	LP_Export int Init(SoundSystemInitInfo initInfo);
	LP_Export int Update();
	LP_Export int Close();
};