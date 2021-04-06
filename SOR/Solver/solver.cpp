#include "solver.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

void DLL_EXPORT SOLVER::dll_load()
{
    cout<<"SOLVER_LOAD\n";
}
void prepare(CORE::Polygons &data1,CORE::Polygons &data2,vector<vector<bool> > &matr1,vector<vector<bool> > &matr2,vector<int> &x,vector<int> &y)
{
    for(int i=0;i<data1.size();i++)
    {
        for(int j=0;j<data1[i].size();j++)
        {
            x.push_back(data1[i][j].first);
            y.push_back(data1[i][j].second);
        }
    }
    for(int i=0;i<data2.size();i++)
    {
        for(int j=0;j<data2[i].size();j++)
        {
            x.push_back(data2[i][j].first);
            y.push_back(data2[i][j].second);
        }
    }
    sort(x.begin(),x.end());
    x.resize(unique(x.begin(),x.end())-x.begin());
    sort(y.begin(),y.end());
    y.resize(unique(y.begin(),y.end())-y.begin());
    map<int,int> szat_x,szat_y;
    for(size_t i=0;i<x.size();i++)
    {
        szat_x[x[i]]=i;
    }
    for(size_t i=0;i<y.size();i++)
    {
        szat_y[y[i]]=i;
    }
    vector<vector<int> > v1,v2;
    v1.resize(y.size()-1);
    v2.resize(y.size()-1);
    set<pair<int,int> > was1,was2;
    for(int i=0;i<data1.size();i++)
    {
        for(int j=0;j<data1[i].size();j++)
        {
            if (data1[i][j].second==y.back()) continue;
            if (was1.count(data1[i][j])) continue;
            v1[szat_y[data1[i][j].second]].push_back(szat_x[data1[i][j].first]);
            was1.insert(data1[i][j]);
        }
    }
    for(int i=0;i<data2.size();i++)
    {
        for(int j=0;j<data2[i].size();j++)
        {
            if (data2[i][j].second==y.back()) continue;
            if (was2.count(data2[i][j])) continue;
            v2[szat_y[data2[i][j].second]].push_back(szat_x[data2[i][j].first]);
            was2.insert(data2[i][j]);
        }
    }
    matr1.resize(x.size()-1);
    matr2.resize(x.size()-1);
    for(size_t i=0;i<x.size()-1;i++)
    {
        matr1[i].resize(y.size()-1);
        matr2[i].resize(y.size()-1);
    }
    vector<bool> color1(x.size()-1,0),color2(x.size()-1,0);
    for(size_t j=0;j<y.size()-1;j++)
    {
        sort(v1[j].begin(),v1[j].end());
        for(size_t i=0;i<v1[j].size();i+=2)
        {
            for(int q=v1[j][i];q<v1[j][i+1];q++)
            {
                color1[q]=!color1[q];
            }
        }
        for(size_t i=0;i<x.size()-1;i++)
        {
            matr1[i][j]=color1[i];
        }
        sort(v2[j].begin(),v2[j].end());
        for(size_t i=0;i<v2[j].size();i+=2)
        {
            for(int q=v2[j][i];q<v2[j][i+1];q++)
            {
                color2[q]=!color2[q];
            }
        }
        for(size_t i=0;i<x.size()-1;i++)
        {
            matr2[i][j]=color2[i];
        }
    }
}
void restore_ans(vector<vector<bool> > &matr,CORE::Polygons &res,vector<int> &x,vector<int> &y)
{
    for(size_t i=0;i<matr.size();i++)
    {
        for(size_t j=0;j<matr[0].size();j++)
        {
            if (matr[i][j])
            {
                CORE::Polygon pol;
                pair<int,int> p={x[i],y[j]};
                pol.add(p);
                p.second=y[j+1];
                pol.add(p);
                p.first=x[i+1];
                pol.add(p);
                p.second=y[j];
                pol.add(p);
                res.add(pol);
            }
        }
    }
}
void DLL_EXPORT SOLVER::merge(CORE::Polygons &data1,CORE::Polygons &data2,CORE::Polygons &res)
{
    vector<vector<bool> > matr1,matr2;
    vector<int> x,y;
    prepare(data1,data2,matr1,matr2,x,y);
    if (matr1.size()!=matr2.size())
    {
        ///logger
        assert(0);
    }
    for(size_t i=0;i<matr1.size();i++)
    {
        if (matr1[i].size()!=matr2[i].size())
        {
            ///logger
            assert(0);
        }
        for(size_t j=0;j<matr1[0].size();j++)
        {
            matr1[i][j]=(matr1[i][j]|matr2[i][j]);
        }
    }
    restore_ans(matr1,res,x,y);
}
void DLL_EXPORT SOLVER::intersect(CORE::Polygons &data1,CORE::Polygons &data2,CORE::Polygons &res)
{
    vector<vector<bool> > matr1,matr2;
    vector<int> x,y;
    prepare(data1,data2,matr1,matr2,x,y);
    if (matr1.size()!=matr2.size())
    {
        ///logger
        assert(0);
    }
    for(size_t i=0;i<matr1.size();i++)
    {
        if (matr1[i].size()!=matr1[0].size())
        {
            ///logger
            assert(0);
        }
        if (matr1[i].size()!=matr2[i].size())
        {
            ///logger
            assert(0);
        }
        for(size_t j=0;j<matr1[0].size();j++)
        {
            matr1[i][j]=(matr1[i][j]&matr2[i][j]);
        }
    }
    restore_ans(matr1,res,x,y);
}
void DLL_EXPORT SOLVER::subtract(CORE::Polygons &data1,CORE::Polygons &data2,CORE::Polygons &res)
{
    vector<vector<bool> > matr1,matr2;
    vector<int> x,y;
    prepare(data1,data2,matr1,matr2,x,y);
    if (matr1.size()!=matr2.size())
    {
        ///logger
        assert(0);
    }
    for(size_t i=0;i<matr1.size();i++)
    {
        if (matr1[i].size()!=matr2[i].size())
        {
            ///logger
            assert(0);
        }
        for(size_t j=0;j<matr1[0].size();j++)
        {
            matr1[i][j]=(matr1[i][j]&(!matr2[i][j]));
        }
    }
    restore_ans(matr1,res,x,y);
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
