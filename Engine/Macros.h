#pragma once

#ifdef  _lpEngine_
#ifdef _WIN32
  #define LP_Export __declspec(dllexport)
#else
  #define LP_Export
#endif
#define LP_Extern extern "C"
#endif //  _lpEngine_
