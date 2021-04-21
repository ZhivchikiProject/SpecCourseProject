#ifndef __CORE_H__
#define __CORE_H__
#include <windows.h>
#include <vector>
#include <set>
#include <assert.h>
#include <iostream>
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
        pair<int,int> get(int i) const
        {
            if (i>=(int)size()||i<0)
            {
                LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error,"Incorrect index (get)");
            }
            return pol[i];
        }
        const pair<int,int> & operator [](int i) const
        {
            if (i>=(int)size()||i<0)
            {
                LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error,"Incorrect index ([])");
            }
            return pol[i];
        }
        void normalize();
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
        const Polygon& get(int i) const
        {
            if (i>=(int)size()||i<0)
            {
                LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error,"Incorrect index (get)");
            }
            return pol[i];
        }
        const Polygon & operator [](int i) const
        {
            if (i>=(int)size()||i<0)
            {
                LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error,"Incorrect index ([])");
            }
            return pol[i];
        }
        void normalize();
    };
    bool operator !=(const Polygon &x,const Polygon &y)
    {
        if (x.size()!=y.size()) return 1;
        for(int i=0;i<x.size();i++)
        {
            if (x[i]!=y[i]) return 1;
        }
        return 0;
    }
    bool operator !=(const Polygons &x,const Polygons &y)
    {
        if (x.size()!=y.size()) return 1;
        for(int i=0;i<x.size();i++)
        {
            if (x[i]!=y[i]) return 1;
        }
        return 0;
    }
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
