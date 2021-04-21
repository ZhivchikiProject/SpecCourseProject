#include "core.h"
#include <iostream>
using namespace std;


void DLL_EXPORT CORE::dll_load()
{
    cout<<"CORE_LOAD\n";
}
void CORE::Polygon::normalize()
{
    int n=pol.size();
    set<pair<int,pair<int,int> > > s;
    for(int i=0;i<pol.size();i++) s.insert({i,{pol[i]}});
    set<pair<int,int> > was;
    for(set<pair<int,pair<int,int> > >::iterator it=s.begin();it!=s.end();it++)
    {
        if (was.count(it->second))
        {
            auto w=it;
            w++;
            if (w!=s.end())
            {
                if (was.count(w->second))
                {
                    auto j=it;
                    auto q=j;
                    q--;
                    while(q->second!=w->second)
                    {
                        pol[--n]=j->second;
                        was.erase(j->second);
                        s.erase(j);
                        j=q;
                        q--;
                    }
                    pol[--n]=j->second;
                    was.erase(j->second);
                    s.erase(j);
                    s.erase(q);
                    it=w;
                }
            }
        }
        was.insert(it->second);
    }
    int i=0;
    while(s.size())
    {
        pol[i++]=s.begin()->second;
        s.erase(s.begin());
    }
    while(n!=pol.size())
    {
        pol[i++]=pol[n++];
    }
    pol.resize(i);
}

void DLL_EXPORT CORE::Polygons::normalize()
{
    for(auto &j:pol)
    {
        j.normalize();
    }
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
