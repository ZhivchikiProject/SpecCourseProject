#ifndef __PARS_H__
#define __PARS_H__
#include <windows.h>
/*  To use this exported function of dll, include this header
 *  in your project.
 */
#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


namespace PARSER
{
    void DLL_EXPORT dll_load();
}






#ifdef __cplusplus
extern "C"
{
#endif

void DLL_EXPORT SomeFunction(const LPCSTR sometext);

#ifdef __cplusplus
}
#endif

#endif // __PARS_H__
