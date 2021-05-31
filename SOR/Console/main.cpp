#pragma GCC optimize("O3")
#include <iostream>
#include <fstream>
#include "..\Core\Core.h"
#include "..\Parser\Parser.h"
#include "..\Logger\Logger.h"
#include "..\Solver\Solver.h"
using namespace std;
int main(int argc,char *argv[])
{
    CORE::Polygons in_1,in_2,out_1;
    LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Info,"New Launch");
    string path;
    if (argc<5)
    {
        LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error,"Not enough input data");
    }
    path=argv[1];
    ifstream temp1(path.c_str());
    if (temp1.fail())
    {
        LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error,"Incorrect path to first file");
    }
    temp1.close();
    LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Info,"Read first file");
    PARSER::read_input(path,in_1);
    path=argv[2];
    ifstream temp2(path.c_str());
    if (temp2.fail())
    {
        LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error,"Incorrect path to second file");
    }
    temp2.close();
    LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Info,"Read second file");
    PARSER::read_input(path,in_2);
    int op=0;
    if (strlen(argv[3])!=1)
    {
        LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error,"Incorrect operation");
    }
    LOGGER::Logger::GetInstance()->GetTime("Read complete",1);
    op=argv[3][0]-'0';
    switch(op)
    {
    case 0:
        LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Info,"Merge");
        SOLVER::merge(in_1,in_2,out_1);
        break;
    case 1:
        LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Info,"Intersect");
        SOLVER::intersect(in_1,in_2,out_1);
        break;
    case 2:
        LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Info,"Subtract");
        SOLVER::subtract(in_1,in_2,out_1);
        break;
    default:
        LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error,"Incorrect operation");
    }
    LOGGER::Logger::GetInstance()->GetTime("Operation complete",1);
    if (argc==6)
    {
        CORE::Polygons valid;
        path=argv[5];
        ifstream temp(path.c_str());
        if (temp.fail())
        {
            LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error,"Incorrect path to file with standard");
        }
        temp.close();
        LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Info,"Reading file with answer");
        PARSER::read_input(path,valid);
        if (valid!=out_1)
        {
            LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Error,"Program result doesn't match the standard");
        }
        else
        {
            LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Info,"Program result is correct");
        }
    }
    path=argv[4];
    LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Info,"Writing result file");
    PARSER::write_output(path,out_1);
    LOGGER::Logger::GetInstance()->WriteLog(LOGGER::LogLevel::Debug,"Program has finished work");
    LOGGER::Logger::GetInstance()->GetTime("Output complete",1);
    return 0;
}
