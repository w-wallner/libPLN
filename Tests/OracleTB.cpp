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

#include "OracleTB.hpp"

#include "libPLN.hpp"
#include "Examples/AverageOscillator_20MHz/AverageOscillator_20MHz.hpp"
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
    std::string     Name;
}
DetailedBench;

typedef struct
{
    double          f_s;
    size_t          NumSamples;
}
BurstBench;

// =========================================================================
// Global variables
// =========================================================================

DetailedBench   DetailedBenchMarks[]    =
{
        {   5E6,    "5MHz"  },
        {   2E6,    "2MHz"  },
        {   1E6,    "1MHz"  },

        {   50E0,   "50Hz"  },
        {   20E0,   "20Hz"  },
        {   10E0,   "10Hz"  },

        {   500E3,  "500kHz"  },
        {   200E3,  "200kHz"  },
        {   100E3,  "100kHz"  },

        {   50E6,   "50MHz"  },
        {   20E6,   "20MHz"  },
        {   10E6,   "10MHz"  },

        {   50E3,   "50kHz"  },
        {   20E3,   "20kHz"  },
        {   10E3,   "10kHz"  },

        {   5E3,    "5kHz"  },
        {   2E3,    "2kHz"  },
        {   1E3,    "1kHz"  },

        {   500E0,  "500Hz"  },
        {   200E0,  "200Hz"  },
        {   100E0,  "100Hz"  },

        {   5E0,    "5Hz"  },
        {   2E0,    "2Hz"  },
        {   1E0,    "1Hz"  },
};

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
//    NumSamples   = 10000;      // 10^4
    NumSamples   = 100000;      // 10^5
//    NumSamples   = 1000000;     // 10^6
//    NumSamples   = 10000000;    // 10^7
//    NumSamples   = 100000000;   // 10^8     Max @ Matlab

    f_s = 40E6;
    f_s =5E6;
//    f_s = 1E5;
//    f_s = 1E4;
//    f_s = 1E3;
//    f_s = 1E1;

//    f_s = 250000;

    t = 0.0;

    cAvgOsc20MHz o( 123, true );

    SampleOracle( o, t, f_s, NumSamples, true, true, "/main/td.txt" );
}

void DetailedOracleBench()
{
    cout << "Running " << __func__ << "()" << endl;

    double          f_s;
    double          t;
    size_t          i;
    size_t          NumSamples;

    std::string     OutputPath;
    std::string     Name;
    std::string     Filename;

    // Resources
    cAvgOsc20MHz    o( 54321, true );
    ofstream        TdFile;

    // Config
    OutputPath = "/main/Tmp/Benchmarks/";

    NumSamples   = 100000;      // 10^5
//    NumSamples   = 1000000;     // 10^6
//    NumSamples   = 10000000;    // 10^7
//    NumSamples   = 100000000;   // 10^8     Max @ Matlab

    cout << OutputPath << endl;

    t   = 0.0L;

    // Benchmark Oscillator
    for( i = 0; i < NumElements(DetailedBenchMarks); i ++ )
    {
        // Read config
        f_s     = DetailedBenchMarks[ i ].f_s;
        Name    = DetailedBenchMarks[ i ].Name;

        // Init
        Filename        = OutputPath + "td_" + Name + ".txt";

        cout << endl;
        cout << "Starting benchmark " << i + 1 << "/" << NumElements(DetailedBenchMarks) << " for " << Name << endl;
        cout << "t = " << t << endl;

        SampleOracle( o, t, f_s, NumSamples, true, true, Filename );

        cout << "Finished benchmark for " << Name << endl;
    }
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

    t               = 0.0L;

    MinDuration     = 180;

    ResultFile.open( ResultFilename.c_str() );
    ResultFile.precision( 30 );

    // Benchmark Oscillator
    for( i = 0; i < NumElements(DetailedBenchMarks); i ++ )
    {
        // Read config
        f_s     = DetailedBenchMarks[ i ].f_s;
        Name    = DetailedBenchMarks[ i ].Name;

        // Init
        dt              = 1.0L / f_s;

        cout << endl;
        cout << "Starting benchmark for " << Name << endl;
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

        ResultFile << Name << ", " << f_s << ", " << Duration << ", " << SimDuration << endl;
        cout << "Finished benchmark for " << Name << endl;
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
