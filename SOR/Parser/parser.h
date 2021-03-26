#ifndef __PARS_H__
#define __PARS_H__
#include <windows.h>
#include "..\Core\Core.h"
#include "..\Logger\Logger.h"

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
    void DLL_EXPORT read_input(string &path, Polygons &res);
    void DLL_EXPORT write_output(string &path, Polygons &res);
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
