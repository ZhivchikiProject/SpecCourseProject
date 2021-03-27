#include <iostream>
#include <fstream>
#include "..\Core\Core.h"
#include "..\Parser\Parser.h"
#include "..\Logger\Logger.h"
#include "..\Solver\Solver.h"
using namespace std;
int main(int argc,char *argv[])
{
    CORE::dll_load();
    PARSER::dll_load();
    LOGGER::dll_load();
    SOLVER::dll_load();
    CORE::Polygons in_1,in_2,out_1;
    string path="C:/SOR/Tests/1.txt";
//    if (argc<5)
//    {
//        ///logger
//        assert(0);
//    }
//    string path=argv[1];
    ifstream temp1(path.c_str());
    if (temp1.fail())
    {
        ///logger
        assert(0);
    }
    temp1.close();
            ///logger
    PARSER::read_input(path,in_1);
//    path=argv[2];
    ifstream temp2(path.c_str());
    if (temp2.fail())
    {
            ///logger
        assert(0);
    }
    temp2.close();
            ///logger
    PARSER::read_input(path,in_2);
    int op=0;
//    if (strlen(argv[3])!=1)
//    {
//        ///logger
//        assert(0);
//    }
//    op=argv[3][0]-'0';
    switch(op)
    {
    case 0:
            ///logger
        SOLVER::merge(in_1,in_2,out_1);
        break;
    case 1:
            ///logger
        SOLVER::intersect(in_1,in_2,out_1);
        break;
    case 2:
            ///logger
        SOLVER::subtract(in_1,in_2,out_1);
        break;
    default:
        assert(0);
        break;
    }
    if (argc==6)
    {
        CORE::Polygons valid;
//        path=argv[5];
        ifstream temp(path.c_str());
        if (temp.fail())
        {
            ///logger
            assert(0);
        }
        temp.close();
            ///logger
        PARSER::read_input(path,in_2);
        if (valid!=out_1)
        {
            ///logger
            assert(0);
        }
        else
        {
            ///logger
        }
    }
//    path=argv[4];
    ifstream temp3(path.c_str());
    if (temp3.fail())
    {
        ///logger
        assert(0);
    }
    temp3.close();
            ///logger
    PARSER::write_output(path,out_1);
    return 0;
}
