// ============================================================================
///
/// \file
///
/// \brief  TODO
///
/// TODO
///
/// \ingroup module_main
///
// ============================================================================

// ============================================================================
//
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
//
// This file is part of libPLN.
//
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License.com as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License.com for more details.
//
// You should have received a copy of the GNU General Public License.com
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================

// =========================================================================
// Includes
// =========================================================================

#include "NumericTests.hpp"
#include "BasicTests.hpp"
#include "EstimatorTB.hpp"
#include "OracleTB.hpp"

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef enum
{
    NUMERIC_TEST,
    BASIC_TEST,
    ESTIMATOR_TEST,
    ORACLE_TEST,
}
tTestType;

// =========================================================================
// Global variables
// =========================================================================

std::string ProgName;

// =========================================================================
// Locale function prototypes
// =========================================================================

void PrintUsage();
void ExitOnFailure( std::string ErrMsg );

// =========================================================================
// Function definitions
// =========================================================================

void PrintUsage()
{
    cout << "Usage: " << ProgName << " TestType TestID" << endl;
    cout << "TestTypes: Numeric, Basic, Estimator, Oracle" << endl;
}

void ExitOnFailure( std::string ErrMsg )
{
    cerr << "ERROR: " << ErrMsg << endl;
    cout << endl;
    PrintUsage();

    exit(EXIT_FAILURE);
}

void ExitOnInvalidID()
{
    ExitOnFailure( std::string( "TestID is out of range." ) );
}

void RunNumericTest( int TestID )
{
    switch( TestID )
    {
        case 0:     TestPowerOfTwo();           break;

        default:    ExitOnInvalidID();
                    break;
    }
}

void RunBasicTest( int TestID )
{
    switch( TestID )
    {
        case 0:     TestTdVecStorage();         break;
        case 1:     TestTdVecGen();             break;
        case 2:     TestWpmTdVecGen();          break;
        case 3:     TestTdEst();                break;

        default:    ExitOnInvalidID();
                    break;
    }
}

void RunEstimatorTest( int TestID )
{
    switch( TestID )
    {
        case 0:     EstimatorTestBench();       break;
        case 1:     FileBench();                break;

        default:    ExitOnInvalidID();
                    break;
    }
}

void RunOracleTest( int TestID )
{
    switch( TestID )
    {
        case 0:     SimpleOracleBench();        break;
        case 1:     DetailedOracleBench();      break;
        case 2:     SpeedOracleBench();         break;
        case 3:     BurstOracleBench();         break;
        case 4:     PreRecordedOracleBench();    break;

        default:    ExitOnInvalidID();
                    break;
    }
}

int main( int argc, char *argv[] )
{
    tTestType   TestType;

    ProgName = argv[0];

    cout << "==================================================================================" << endl;
    cout << "libPLN TestBench, built on " << __DATE__ << " at " << __TIME__ << endl;
    cout << "==================================================================================" << endl;

    cout << "Starting";
    #ifdef _DEBUG
        cout << " (Debug mode)";
    #else
        cout << " (Release mode)";
    #endif
    cout << endl;

    // ---------------------------------------------------------------------
    // Parse arguments
    // ---------------------------------------------------------------------
    if( argc < 3 )
    {
        ExitOnFailure( std::string( "Not enough arguments" ) );
    }

    if( 0 == strcmp( "Numeric", argv[1]) )
    {
        TestType = NUMERIC_TEST;
    }
    else if( 0 == strcmp( "Basic", argv[1]) )
    {
        TestType = BASIC_TEST;
    }
    else if( 0 == strcmp( "Estimator", argv[1]) )
    {
        TestType = ESTIMATOR_TEST;
    }
    else if( 0 == strcmp( "Oracle", argv[1]) )
    {
        TestType = ORACLE_TEST;
    }
    else
    {
        ExitOnFailure( std::string( "Invalid TestType" ) );
    }

    int TestID = atoi( argv[2] );

    // ---------------------------------------------------------------------
    // Start test
    // ---------------------------------------------------------------------

    time_t  start;
    time_t  end;

    time(&start);

    switch( TestType )
    {
        case NUMERIC_TEST:      RunNumericTest( TestID );
                                break;

        default:
        case BASIC_TEST:        RunBasicTest( TestID );
                                break;

        case ESTIMATOR_TEST:    RunEstimatorTest( TestID );
                                break;

        case ORACLE_TEST:       RunOracleTest( TestID );
                                break;
    }

    time(&end);

    cout << "Finished, took " << difftime( end, start ) << " seconds" << endl;

    return EXIT_SUCCESS;
}
