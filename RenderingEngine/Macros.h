#pragma once


//LP_EXPORT
#ifdef _WIN32
#define LP_Export __declspec(dllexport)
#else
#define LP_Export __attribute__((visibility("default")))
#endif

//LP_EXTERN
#define LP_Extern extern "C"