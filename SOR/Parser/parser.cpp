#include "parser.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

bool is_number(string& s)
{
    if ((s[s.size()-1] == ',') || (s[s.size()-1] == '.') || (s[s.size()-1] == ';') || (s[s.size()-1] == ':'))
        s.resize(s.size() - 1);
    string::const_iterator it = s.begin();
    if (s[0] == '-') it++;
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void DLL_EXPORT PARSER::read_input(string &path, CORE::Polygons &res)
{
    string x, y;

    ifstream fin(path);
    int PolygonsCount, PointsCount;

    fin>>x;

    if (x != "Count")
        LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error, "\"Count\" needed in file: " + path);

    fin>>y;

     if (!is_number(y))
                LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error, "The number of boundaries needed in file: " + path);

    PolygonsCount = stoi(y);

    for (int i=0;i<PolygonsCount;i++)
    {

        int minX, minY, minPos = 0;
        vector<pair<int,int> > vect;

        CORE::Polygon pol;

        fin>>x;

        if (x != "Boundary")
            LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error, "\"Boundary\" needed in file: " + path);

        fin>>y;

        if (!is_number(y))
                LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error, "The number of points needed in "
                                                    + to_string(i+2)+ " line in file: " + path);

        PointsCount = stoi(y);

        if (PointsCount < 5 || PointsCount%2 == 0)
            LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error, "Wrong number of points in "
                                                    + to_string(i+2)+ " line in file: " + path);


        for (int j=0;j<PointsCount;j++)
        {

            fin>>x;

            if (fin.eof())
                LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error, "Sudden EOF: " + path);

            fin>>y;

            if (!is_number(x) || !is_number(y))
                LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error, "Error in coordinates in "
                                                    + to_string(i+2)+ " line in file: " + path);

            pair<int,int> p(stoi(x), stoi(y));
            vect.push_back(p);
        }

        if ((vect[0].first != vect.back().first)||(vect[0].second != vect.back().second))
            LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error, "The first and last point of boundary in"
                                                    + to_string(i+2)+ " line are not the same in file: " + path);

        minX = vect[0].first;
        minY = vect[0].second;

        for (int j=0; j<PointsCount; j++)
        {
            if ((vect[j].first < minX)||((vect[j].first == minX)&&(vect[j].second < minY)))
            {
                minX = vect[j].first;
                minY = vect[j].second;
                minPos = j;
            }
        }

        if ((minX != vect[0].first)||(minY != vect[0].second))
        {
            vect.erase(vect.begin());
            rotate(vect.begin(),vect.begin()+minPos -1,vect.end());
            vect.push_back(vect[0]);
        }

        if (vect[0].second < vect[1].second)
        {
            for (int j=0; j<PointsCount; j++)
                pol.add(vect[j]);
        }
        else
        {
            for (int j=PointsCount-1; j>=0; j--)
                pol.add(vect[j]);
        }

        res.add(pol);
    }

     fin.close();
}

void DLL_EXPORT PARSER::write_output(string &path, CORE::Polygons &res)
{
    ofstream fout(path);

    fout << "Count  " << res.size() << endl;

    for(int i=0;i<res.size();i++)
    {
        fout << "Boundary " << res.get(i).size() << " ";

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
