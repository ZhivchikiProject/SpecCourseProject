#include <iostream>
#include "gtest.h"
#include "..\Core\Core.h"
#include "..\Logger\Logger.h"
#include "..\Parser\Parser.h"
#include "..\Solver\Solver.h"
#include "gtest/core_polygon_size.h"
using namespace std;

GTEST_API_ int main(int argc, char **argv)
{
    PARSER::dll_load();
    CORE::dll_load();
    LOGGER::dll_load();
    SOLVER::dll_load();
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
