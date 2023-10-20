/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once

#ifndef lpEngine_Commons
#define lpEngine_Commons
#include "Macros.h"

enum LowpResultCodes {
	Success = 0,
	UnknowError = 1,
	SystemFailure = 2
};

LP_Export char* ReadBytes(const std::string& filepath, uint32_t* outSize);
#endif