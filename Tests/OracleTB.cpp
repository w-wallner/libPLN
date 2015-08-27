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

#include "OracleTB.hpp"

#include "libPLN.hpp"
#include "Examples/AverageOscillator_20MHz/AverageOscillator_20MHz.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;
using namespace AverageOscillator_20MHz;

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

    double f_s;
    double dt;
    double t        = 0.0L;
    size_t cnt      = 0;
    size_t MaxCnt;

    MaxCnt   = 1000;      // 10^3
//    MaxCnt   = 10000;      // 10^4
//    MaxCnt   = 100000;      // 10^5
//    MaxCnt   = 1000000;     // 10^6
//    MaxCnt   = 10000000;    // 10^7
//    MaxCnt   = 100000000;   // 10^8     Max @ Matlab

    f_s = 40E6;
    f_s =5E6;
//    f_s = 1E5;
//    f_s = 1E4;
//    f_s = 1E3;
//    f_s = 1E1;

//    f_s = 250000;

    dt  = 1.0L / f_s;

    size_t CntThStep    = MaxCnt / 100;
    size_t NextTh       = CntThStep;
    bool PrintTh;

    PrintTh = true;
//    PrintTh = false;

    ofstream    TdFile;
    TdFile.open( "/main/td.txt" );

    TdOracle_AvgOsc20MHz o( 123 );

//    o.SetSeed( 1000 );
//    o.SetSeed( 0 );

    TdFile.precision( 30 );
    for( cnt = 0; cnt < MaxCnt; cnt ++ )
    {
        double TD;

        TD = o.EstimateTD( t, t );

        TdFile << TD << endl;

        t += dt;

        if( PrintTh )
        {
            if( cnt >= NextTh )
            {
                cout << "Calculated " << (double)cnt / (double) MaxCnt * 100 << "% (t = " << t << ")." << endl;
                NextTh += CntThStep;
            }
        }
    }
    TdFile.close();
}

void DetailedOracleBench()
{
    cout << "Running " << __func__ << "()" << endl;

    double          f_s;
    double          dt;
    double          t;
    size_t          i;
    size_t          Cnt;
    size_t          MaxCnt;

    size_t          NextPrintTh;
    bool            EnablePrint;

    std::string     OutputPath;
    std::string     Name;
    std::string     Filename;

    // Resources
    TdOracle_AvgOsc20MHz    o( 54321 );
    ofstream                TdFile;

    // Config
    OutputPath = "/main/Tmp/Benchmarks/";

    EnablePrint     = true;

    MaxCnt   = 100000;      // 10^5
    MaxCnt   = 1000000;     // 10^6
//    MaxCnt   = 10000000;    // 10^7
//    MaxCnt   = 100000000;   // 10^8     Max @ Matlab

    cout << OutputPath << endl;

    t               = 0.0L;

    // Benchmark Oscillator
    for( i = 0; i < sizeof(DetailedBenchMarks) / sizeof(DetailedBenchMarks[0]); i ++ )
    {
        // Read config
        f_s     = DetailedBenchMarks[ i ].f_s;
        Name    = DetailedBenchMarks[ i ].Name;

        // Init
        NextPrintTh     = 0;
        dt              = 1.0L / f_s;
        Filename        = OutputPath + "td_" + Name + ".txt";

        cout << endl;
        cout << "Starting benchmark for " << Name << endl;
        cout << "t = " << t << endl;

        TdFile.open( Filename.c_str() );
        TdFile.precision( 30 );

        for( Cnt = 0; Cnt < MaxCnt; Cnt ++ )
        {
            double TD;

            TD = o.EstimateTD( t, t );

            TdFile << TD << endl;

            t   += dt;

            if( EnablePrint )
            {
                if( Cnt >= NextPrintTh )
                {
                    cout << "Calculated " << (double)Cnt / (double) MaxCnt * 100 << "% (t = " << t << ")." << endl;
                    NextPrintTh += (MaxCnt/10);
                }
            }
        }
        TdFile.close();
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
    TdOracle_AvgOsc20MHz    o( 54321 );
    ofstream                ResultFile;

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
    for( i = 0; i < sizeof(DetailedBenchMarks) / sizeof(DetailedBenchMarks[0]); i ++ )
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

    TdOracle_AvgOsc20MHz    o( 2222 );
    double                  f_s;
    double                  dt;
    double                  t;
    size_t                  Cnt;

    ofstream                ResultFile;
    std::string             ResultFilename;

    size_t                  i;

    ResultFilename = "/main/burst_bench.txt";
    ResultFile.open( ResultFilename.c_str() );
    ResultFile.precision( 30 );

    t = 0.0L;
    for( i = 0; i < sizeof(BurstBenchMarks) / sizeof(BurstBenchMarks[0]); i ++ )
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

    TdOracle_AvgOsc20MHz    o( 0 );
    ifstream                ResultFile;
    std::string             ResultFilename = "/main/CallLog.txt";
    ofstream                TdTraceFile;
    std::string             TdTraceFilename = "/main/TdTrace.txt";
    double                  T_Now;
    double                  T_Now_Latch;
    double                  T_Req;
    double                  TD;
    size_t                  MaxLineCnt = 1000000;

    MaxLineCnt = 100000;

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
