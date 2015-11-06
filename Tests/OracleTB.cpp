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
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================

// =========================================================================
// Includes
// =========================================================================

#include "OracleTB.hpp"

#include "libPLN.hpp"
#include "Examples/AverageOscillator_20MHz/AverageOscillator_20MHz.hpp"
#include "Examples/WatchQuartz_20MHz/WatchQuartz_20MHz.hpp"
#include "Utils/NumericTricks.hpp"
#include "TestLib.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;
using namespace LibPLN_Examples;

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef struct
{
    double          f_s;
    size_t          NumSamples;
}
BurstBench;

// =========================================================================
// Global variables
// =========================================================================

BurstBench  BurstBenchMarks[] =
{
        {   1E2,    500    },
        {   1E0,    10     },
        {   1E2,    500    },
        {   1E0,    10     },
        {   1E2,    500    },
        {   1E0,    10     },
};

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

void SimpleOracleBench()
{
    cout << "Running " << __func__ << "()" << endl;

    double  f_s;
    size_t  NumSamples;
    double  t;

    NumSamples   = 1000;      // 10^3
    NumSamples   = 10000;      // 10^4
//    NumSamples   = 100000;      // 10^5
    NumSamples   = 1000000;     // 10^6
//    NumSamples   = 10000000;    // 10^7
//    NumSamples   = 100000000;   // 10^8     Max @ Matlab

    f_s = 40E6;
    f_s =5E6;
//    f_s = 1E5;
//    f_s = 1E4;
//    f_s = 1E3;
//    f_s = 1E1;
    f_s = 2E-3;
    f_s = 1E-2;

    t = 0.0;

    cAvgOsc20MHz ao( 123, true );
    cWatchQuartz_20MHz w( 123, true );
    TdOracle o;

    o = ao;
    o = w;

    SampleOracle( o, t, f_s, NumSamples, true, true, "/main/td.txt" );
}

void DetailedBench_AvgOsc()
{
    cout << "Running " << __func__ << "()" << endl;

    double   FrequList[]    =
    {
        50E6,    20E6,   10E6,
        5E6,     2E6,    1E6,
        500E3,   200E3,  100E3,
        50E3,    20E3,   10E3,
        5E3,     2E3,    1E3,
        500E0,   200E0,  100E0,
        50E0,    20E0,   10E0,
        5E0,     2E0,    1E0,
        500E-3,  200E-3, 100E-3,
        50E-3,   200E-3, 10E-3,
        5E-3,    2E-3,   1E-3,
    };

    size_t          NumSamples;
    std::string     OutputPath;

    // Resources
    cAvgOsc20MHz    o( 54321, true );

    // Config
    OutputPath = "/main/Tmp/Benchmarks/AvgOsc/";

    NumSamples   = 100000;      // 10^5
//    NumSamples   = 1000000;     // 10^6
    NumSamples   = 10000000;    // 10^7
//    NumSamples   = 100000000;   // 10^8     Max @ Matlab

    std::vector<double> f_s( FrequList, FrequList + NumElements(FrequList) );

    BenchmarkTdOracle( o, f_s, NumSamples, OutputPath );
}

void DetailedBench_WatchQuartz()
{
    cout << "Running " << __func__ << "()" << endl;

    double   FrequList[]    =
    {
        50E6,   20E6,   10E6,
        5E6,    2E6,    1E6,
        500E3,  200E3,  100E3,
        50E3,   20E3,   10E3,
        5E3,    2E3,    1E3,
        500E0,  200E0,  100E0,
        50E0,   20E0,   10E0,
        5E0,    2E0,    1E0,
        500E-3, 200E-3,  100E-3,
        50E-3,  20E-3,   10E-3,
        5E-3,   2E-3,    1E-3,
        500E-6, 200E-6,  100E-6,
        50E-6,  20E-6,   10E-6,
        5E-6,   2E-6,    1E-6,
    };

    size_t          NumSamples;
    std::string     OutputPath;

    // Resources
    cWatchQuartz_20MHz    o( 123, true );

    // Config
    OutputPath = "/main/Tmp/Benchmarks/WatchQuartz/";

    NumSamples   = 100000;      // 10^5
    NumSamples   = 1000000;     // 10^6
    NumSamples   = 10000000;    // 10^7
//    NumSamples   = 100000000;   // 10^8     Max @ Matlab

    std::vector<double> f_s( FrequList, FrequList + NumElements(FrequList) );

    BenchmarkTdOracle( o, f_s, NumSamples, OutputPath );
}

void SpeedOracleBench()
{
    cout << "Running " << __func__ << "()" << endl;

    double          f_s;
    double          dt;
    double          t;
    size_t          i;
    size_t          Cnt;
    size_t          MaxCnt;

    double          MinDuration;
    double          StartSimTime;
    double          EndSimTime;
    double          SimDuration;
    double          Duration;

    time_t  start;
    time_t  end;

    std::string     ResultFilename;
    std::string     Name;

    // Resources
    cAvgOsc20MHz    o( 54321, true );
    ofstream        ResultFile;

    // Config
    ResultFilename = "/main/speed_results.txt";


    MaxCnt = 1000;
    MaxCnt   = 100000;      // 10^5
    //MaxCnt   = 1000000;     // 10^6

    double   FrequList[]    =
    {
        50E6,    20E6,   10E6,
        5E6,     2E6,    1E6,
        500E3,   200E3,  100E3,
        50E3,    20E3,   10E3,
        5E3,     2E3,    1E3,
        500E0,   200E0,  100E0,
        50E0,    20E0,   10E0,
        5E0,     2E0,    1E0,
    };

    t               = 0.0L;

    MinDuration     = 180;

    ResultFile.open( ResultFilename.c_str() );
    ResultFile.precision( 30 );

    // Benchmark Oscillator
    for( i = 0; i < NumElements(FrequList); i ++ )
    {
        // Read config
        f_s     = FrequList[ i ];

        // Init
        dt              = 1.0L / f_s;

        cout << endl;
        cout << "Starting benchmark for " << f_s << endl;
        cout << "t = " << t << endl;

        time(&start);
        StartSimTime    = t;
        do
        {
            for( Cnt = 0; Cnt < MaxCnt; Cnt ++ )
            {
                o.EstimateTD( t, t );

                t   += dt;
            }

            time(&end);
        }
        while( difftime( end, start ) < MinDuration );

        EndSimTime  = t;
        SimDuration = EndSimTime - StartSimTime;
        Duration    = difftime( end, start );

        cout << "StartSimTime: " << StartSimTime << endl;
        cout << "EndSimTime: " << EndSimTime << endl;

        cout << "SimDuration: " << SimDuration << endl;
        cout << "Duration: " << Duration << endl;

        ResultFile << f_s << ", " << Duration << ", " << SimDuration << endl;
        cout << "Finished benchmark for " << f_s << endl;
    }

    ResultFile.close();
}

void BurstOracleBench()
{
    cout << "Running " << __func__ << "()" << endl;

    cAvgOsc20MHz    o( 2222, true );
    double          f_s;
    double          dt;
    double          t;
    size_t          Cnt;

    ofstream        ResultFile;
    std::string     ResultFilename;

    size_t          i;

    ResultFilename = "/main/burst_bench.txt";
    ResultFile.open( ResultFilename.c_str() );
    ResultFile.precision( 30 );

    t = 0.0L;
    for( i = 0; i < NumElements(BurstBenchMarks); i ++ )
    {
        f_s = BurstBenchMarks[i].f_s;
        dt  = 1.0L / f_s;

        cout << t << ": Sampling with " << f_s << " Hz for " << BurstBenchMarks[i].NumSamples << " samples now (dt = " << dt << ")." << endl;

        for( Cnt = 0; Cnt < BurstBenchMarks[i].NumSamples; Cnt ++ )
        {
            double  TD;

            TD  = o.EstimateTD( t, t );

            ResultFile << t << ", " << TD << endl;

            t   += dt;
        }
    }
    cout << "Final time: " << t << endl;

    ResultFile.close();
}

void PreRecordedOracleBench()
{
    cout << "Running " << __func__ << "()" << endl;

    cAvgOsc20MHz    o( 0, true );
    ifstream        ResultFile;
    std::string     ResultFilename = "/main/CallLog.txt";
    ofstream        TdTraceFile;
    std::string     TdTraceFilename = "/main/TdTrace.txt";
    double          T_Now;
    double          T_Now_Latch;
    double          T_Req;
    double          TD;
    size_t          MaxLineCnt = 1000000;

//    MaxLineCnt = 100000;

    o.DisableIntervalSkipping();
    o.EnableIntervalSkipping();
//    o.DisableIntervalSkipping();

    ResultFile.open( ResultFilename.c_str(), std::ifstream::in );

    if( !ResultFile )
    {
        cerr << "Error opening result file" << endl;
        return;
    }

    TdTraceFile.open( TdTraceFilename.c_str(), std::ifstream::out );

    if( !TdTraceFile )
    {
        cerr << "Error opening TD trace file" << endl;
        return;
    }

    size_t LineCnt = 0;
    T_Now_Latch = -1.0;
    while( LineCnt <= MaxLineCnt )
    {
        ResultFile >> T_Now;

        if( ResultFile.eof() )
            break;

        ResultFile >> T_Req;

        if( ResultFile.eof() )
            break;

//        cout << std::setprecision( 20 ) << "T_now: " << T_Now << ", T_req: " << T_Req << endl;

        TD = o.EstimateTD( T_Now, T_Req );

        if( T_Now != T_Now_Latch )
        {
            if( T_Now == T_Req )
            {
                TdTraceFile << std::setprecision( 20 ) << T_Now << ", " << TD << endl;

                T_Now_Latch = T_Now;
            }
        }

//        cout << "  Estimated TD: " << TD << endl;

        LineCnt ++;
    }

    ResultFile.close();
    TdTraceFile.close();
}

void
SkipVsNoSkipBench()
{
    cout << "Running " << __func__ << "()" << endl;

    double          f_s;
    size_t          NumSamples;
    double          t;
    unsigned int    Seed;
    std::string     FilenameSkip;
    std::string     FilenameNoSkip;

    Seed            = 54321;
    f_s             = 1E3;
    NumSamples      = 1E5;
    FilenameSkip    = "/main/td_skip.txt";
    FilenameNoSkip  = "/main/td_no_skip.txt";

    cAvgOsc20MHz    SkipOsc  ( Seed, true  );
    cAvgOsc20MHz    NoSkipOsc( Seed, false );

    cout << "Starting test case with skipping enabled ..." << endl;

    t = 0;
    SampleOracle( SkipOsc, t, f_s, NumSamples, true, true, FilenameSkip );

    cout << "Starting test case with skipping disabled ..." << endl;
    t = 0;
    SampleOracle( NoSkipOsc, t, f_s, NumSamples, true, true, FilenameNoSkip );
}
