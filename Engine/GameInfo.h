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
#include "Windowing/Resolution.h"

LP_Export struct GameInfo
{
    std::string name;
    std::string developer;
    std::string version;
    int flags;
    int renderer_type;
    SoundSystemInitInfo soundSystemInfo;
    Resolution* resolution;
};