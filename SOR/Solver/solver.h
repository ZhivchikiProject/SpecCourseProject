#ifndef __SOL_H__
#define __SOL_H__
#include <windows.h>
#include "..\Core\core.h"
/*  To use this exported function of dll, include this header
 *  in your project.
 */
#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


namespace SOLVER
{
    void DLL_EXPORT dll_load();
    void DLL_EXPORT merge(CORE::Polygons &data1,CORE::Polygons &data2, CORE::Polygons &res);
    void DLL_EXPORT intersect(CORE::Polygons &data1,CORE::Polygons &data2, CORE::Polygons &res);
    void DLL_EXPORT subtract(CORE::Polygons &data1,CORE::Polygons &data2, CORE::Polygons &res);
}





#ifdef __cplusplus
extern "C"
{
#endif

void DLL_EXPORT SomeFunction(const LPCSTR sometext);

#ifdef __cplusplus
}
#endif

#endif // __SOL_H__
