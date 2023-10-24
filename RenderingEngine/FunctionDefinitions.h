/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once

int LP_Export GetRendererType();

std::string LP_Export GetRendereTypeName(int renderer);

LP_Export RenderingFramework* InitializeRendering(RenderingEngineCreateInfo* createInfo);

LP_Export int SwapBuffers(RenderingFramework* renderer);

LP_Export int ClearScreen(RenderingFramework* renderer, float clearColor[4]);