#include "parser.h"
#include "..\Core\Core.h"
#include <iostream>
#include <fstream>
using namespace std;

void DLL_EXPORT PARSER::read_input(string &path, CORE::Polygons &res)
{
    string s, s1;

    ifstream fin(path);
    int x, y;

    fin>>s;

    for(;;)
    {
        CORE::Polygon pol;

        fin>>s;
        fin>>s1;

        while (s != "EndBox")
        {
            x = stoi(s);
            y= stoi(s1);
            pair<int,int> p(x, y);
            pol.add(p);

            fin>>s;
            fin>>s1;
        }
        res.add(pol);

        if (fin.eof())
            break;
    }

     fin.close();
}

void DLL_EXPORT PARSER::write_output(string &path, CORE::Polygons &res)
{
    ofstream fout(path);

    for(int i=0;i<res.size();i++)
    {
        fout << "Box    ";

        for (int j=0; j<res.get(i).size(); j++)
        {
            fout << res.get(i).get(j).first << ", " << res.get(i).get(j).second << "; ";
        }

        fout << endl << "   EndBox" << endl;
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
