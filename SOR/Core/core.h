#ifndef __CORE_H__
#define __CORE_H__
#include <windows.h>
#include <vector>
#include <assert.h>
#include "..\Logger\logger.h"
using namespace std;
/*  To use this exported function of dll, include this header
 *  in your project.
 */
#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif



namespace CORE
{
    void DLL_EXPORT dll_load();

    class Polygon
    {
    private:
        vector<pair<int,int> > pol;
    public:
        int size() const
        {
            return pol.size();
        }
        void add(pair<int,int> &x)
        {
            pol.push_back(x);
        }
        const pair<int,int> & get(int i) const
        {
            if (i>=(int)size()||i<0)
            {
                assert(0);
            }
            return pol[i];
        }
        const pair<int,int> & operator [](int i) const
        {
            if (i>=(int)size()||i<0)
            {
                assert(0);
            }
            return pol[i];
        }
    };
    class Polygons
    {
    private:
        vector<Polygon> pol;
    public:
        int size() const
        {
            return pol.size();
        }
        void add(Polygon &x)
        {
            pol.push_back(x);
        }
        const Polygon &get(int i)
        {
            if (i>=(int)size()||i<0)
            {
                assert(0);
            }
            return pol[i];
        }
        const Polygon & operator [](int i) const
        {
            if (i>=(int)size()||i<0)
            {
                assert(0);
            }
            return pol[i];
        }
    };
}



#ifdef __cplusplus
extern "C"
{
#endif

void DLL_EXPORT SomeFunction(const LPCSTR sometext);

#ifdef __cplusplus
}
#endif

#endif // __CORE_H__
