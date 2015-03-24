// =========================================================================
// Includes
// =========================================================================

#include <iostream>
#include <ctime>

#include "libPLN.hpp"

#include "DummyTB.hpp"
#include "OracleTB.hpp"
#include "BasicTests.hpp"

using namespace std;

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Global variables
// =========================================================================

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

int main()
{
    cout << "Starting";
    #ifdef _DEBUG
        cout << " (Debug mode)";
    #else
        cout << " (Release mode)";
    #endif
    cout << endl;

    time_t  start;
    time_t  end;

    time(&start);

    //EstiamtorTestBench();
    //FileBench();
    //ChainBench_WPM();
    //ChainBench_FPM();
    //ChainBench_WFM();
    //ChainBench_FFM();

    //SimpleOracleBench();
    //DetailedOracleBench();
    //SpeedOracleBench();
    //BurstOracleBench();

    BasicTest1();

    time(&end);

    cout << "Finished, took " << difftime( end, start ) << " seconds" << endl;

    return 0;
}
