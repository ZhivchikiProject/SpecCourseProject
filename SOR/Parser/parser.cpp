#include "parser.h"
#include "..\Core\Core.h"
#include <iostream>
#include <fstream>
using namespace std;

void DLL_EXPORT PARSER::read_input(string &path, CORE::Polygons &res)
{
    string x, y;

    ifstream fin(path);
    int PolygonsCount, PointsCount;

    fin>>PolygonsCount;

    for (int i=0;i<PolygonsCount;i++)
    {

        CORE::Polygon pol;

        fin>>x;
        fin>>PointsCount;

        for (int j=0;j<PointsCount;j++)
        {
            fin>>x;
            fin>>y;
            pair<int,int> p(stoi(x), stoi(y));
            pol.add(p);
        }
        res.add(pol);
    }

     fin.close();
}

void DLL_EXPORT PARSER::write_output(string &path, CORE::Polygons &res)
{
    ofstream fout(path);

    fout << res.size() << endl;

    for(int i=0;i<res.size();i++)
    {
        fout << "Box    " << res.get(i).size() << " ";

        for (int j=0; j<res.get(i).size(); j++)
        {
            fout << res.get(i).get(j).first << ", " << res.get(i).get(j).second << "; ";
        }

        fout << endl;
    }


     fout.close();
}

void DLL_EXPORT PARSER::dll_load()
{
    cout << "PARSER_LOAD" << endl;
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
