#include <iostream>
#include <fstream>
#include "..\Core\Core.h"
#include "..\Parser\Parser.h"
#include "..\Logger\Logger.h"
#include "..\Solver\Solver.h"
using namespace std;
int main(int argc,char *argv[])
{
    LOGGER::Logger* logger = LOGGER::Logger::GetInstance();
    CORE::Polygons in_1,in_2,out_1;
    string path;
    if (argc<5)
    {
        logger->WriteLog(LOGGER::LogLevel::Error,"Not enough input data");
    }
    path=argv[1];
    ifstream temp1(path.c_str());
    if (temp1.fail())
    {
        logger->WriteLog(LOGGER::LogLevel::Error,"Incorrect path to first file");
    }
    temp1.close();
    logger->WriteLog(LOGGER::LogLevel::Info,"Read first file");
    PARSER::read_input(path,in_1);
    path=argv[2];
    ifstream temp2(path.c_str());
    if (temp2.fail())
    {
        logger->WriteLog(LOGGER::LogLevel::Error,"Incorrect path to second file");
    }
    temp2.close();
    logger->WriteLog(LOGGER::LogLevel::Info,"Read second file");
    PARSER::read_input(path,in_2);
    int op=0;
    if (strlen(argv[3])!=1)
    {
        logger->WriteLog(LOGGER::LogLevel::Error,"Incorrect operation");
    }
    op=argv[3][0]-'0';
    switch(op)
    {
    case 0:
        logger->WriteLog(LOGGER::LogLevel::Info,"Merge");
        SOLVER::merge(in_1,in_2,out_1);
        break;
    case 1:
        logger->WriteLog(LOGGER::LogLevel::Info,"Intersect");
        SOLVER::intersect(in_1,in_2,out_1);
        break;
    case 2:
        logger->WriteLog(LOGGER::LogLevel::Info,"Subtract");
        SOLVER::subtract(in_1,in_2,out_1);
        break;
    default:
        logger->WriteLog(LOGGER::LogLevel::Error,"Incorrect operation");
    }
    if (argc==6)
    {
        CORE::Polygons valid;
        path=argv[5];
        ifstream temp(path.c_str());
        if (temp.fail())
        {
            logger->WriteLog(LOGGER::LogLevel::Error,"Incorrect path to file with answer");
        }
        temp.close();
        logger->WriteLog(LOGGER::LogLevel::Info,"Read file with answer");
        PARSER::read_input(path,in_2);
        if (valid!=out_1)
        {
            logger->WriteLog(LOGGER::LogLevel::Error,"Wrong Answer");
        }
        else
        {
            logger->WriteLog(LOGGER::LogLevel::Info,"Accepted");
        }
    }
    path=argv[4];
    logger->WriteLog(LOGGER::LogLevel::Info,"Write answer");
    PARSER::write_output(path,out_1);
    return 0;
}
