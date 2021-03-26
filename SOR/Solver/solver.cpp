#include "solver.h"
#include <iostream>
using namespace std;

void DLL_EXPORT SOLVER::dll_load()
{
    cout<<"SOLVER_LOAD\n";
}
void DLL_EXPORT SOLVER::merge(CORE::Polygons &data1,CORE::Polygons &data2, CORE::Polygons &res)
{

}
void DLL_EXPORT SOLVER::intersect(CORE::Polygons &data1,CORE::Polygons &data2, CORE::Polygons &res)
{

}
void DLL_EXPORT SOLVER::subtract(CORE::Polygons &data1,CORE::Polygons &data2, CORE::Polygons &res)
{

}









// a sample exported function
void DLL_EXPORT SomeFunction(const LPCSTR sometext)
{
    MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
