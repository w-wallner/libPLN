// 
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
// 
// This file is part of libPLN.
// 
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//

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

    SimpleOracleBench();
    //DetailedOracleBench();
    //SpeedOracleBench();
    //BurstOracleBench();

    //BasicTest1();

    time(&end);

    cout << "Finished, took " << difftime( end, start ) << " seconds" << endl;

    return 0;
}
