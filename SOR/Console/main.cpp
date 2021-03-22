#include <iostream>
#include "..\Core\Core.h"
#include "..\Parser\Parser.h"
#include "..\Logger\Logger.h"
#include "..\Solver\Solver.h"
using namespace std;

int main()
{
    CORE::dll_load();
    PARSER::dll_load();
    LOGGER::dll_load();
    SOLVER::dll_load();
    return 0;
}
