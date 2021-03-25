#include "parser.h"
#include "..\Core\Core.h"
#include <iostream>
#include <fstream>
using namespace std;

/*void DLL_EXPORT PARSER::read_input()(string &path, Polygons &res)
{
    string s, s1;

    //ifstream fin("file.txt");
    ifstream fin(path);
    int Layer, x, y;

    CORE::Polygons p3;
    CORE::Polygons p4;

    fin>>s;

    for(;;)
    {
        CORE::Polygon pol;

        while(s!="Box"){
            fin>>s;
        }

        while(s!="Layer"){
            fin>>s;
        }

        fin>>s;
        fin>>s;

        if(s=="3")
            Layer = 3;
        else if(s=="4")
            Layer = 4;

        while(s!="XY"){
            fin>>s;
        }

        fin>>s;
        fin>>s;
        fin>>s1;

        while (s != "EndEl")
        {
            x = stoi(s);
            y= stoi(s1);
            pair<int,int> p(x, y);
            pol.add(p);

            fin>>s;
            fin>>s1;
        }

        if(Layer == 3)
            p3.add(pol);
        else
            p4.add(pol);


        while ((s != "EndLib")&&(s!="Box"))
        {
            fin>>s;
        }

        if (s=="EndLib")
            break;

    }


    for (int i =0; i<p3.size(); i++)
    {
        CORE::Polygon ee = p3.get(i);
        for (int j=0; j<ee.size(); j++)
        {
            pair<int,int> r = ee.get(j);
            cout << r.first << "  "<< r.second << endl;
        }

        cout << endl;

    }

    for (int i =0; i<p4.size(); i++)
    {
        CORE::Polygon ee = p4.get(i);
        for (int j=0; j<ee.size(); j++)
        {
            pair<int,int> r = ee.get(j);
            cout << r.first << "  " << r.second << endl;
        }

        cout << endl;

    }


}
*/
void DLL_EXPORT PARSER::dll_load()
{

    cout << "PARSER_LOAD" << endl;
    string s, s1;

    ifstream fin("file.txt");
    int Layer, x, y;

    CORE::Polygons p3;
    CORE::Polygons p4;

    fin>>s;

    for(;;)
    {
        CORE::Polygon pol;

        while(s!="Box"){
            fin>>s;
        }

        while(s!="Layer"){
            fin>>s;
        }

        fin>>s;
        fin>>s;

        if(s=="3")
            Layer = 3;
        else if(s=="4")
            Layer = 4;

        while(s!="XY"){
            fin>>s;
        }

        fin>>s;
        fin>>s;
        fin>>s1;

        while (s != "EndEl")
        {
            x = stoi(s);
            y= stoi(s1);
            pair<int,int> p(x, y);
            pol.add(p);

            fin>>s;
            fin>>s1;
        }

        if(Layer == 3)
            p3.add(pol);
        else
            p4.add(pol);


        while ((s != "EndLib")&&(s!="Box"))
        {
            fin>>s;
        }

        if (s=="EndLib")
            break;

    }

    /*
    for (int i =0; i<p3.size(); i++)
    {
        CORE::Polygon ee = p3.get(i);
        for (int j=0; j<ee.size(); j++)
        {
            pair<int,int> r = ee.get(j);
            cout << r.first << "  "<< r.second << endl;
        }

        cout << endl;

    }

    for (int i =0; i<p4.size(); i++)
    {
        CORE::Polygon ee = p4.get(i);
        for (int j=0; j<ee.size(); j++)
        {
            pair<int,int> r = ee.get(j);
            cout << r.first << "  " << r.second << endl;
        }

        cout << endl;

    }

    */
    fin.close();
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
