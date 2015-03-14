// =========================================================================
// Includes
// =========================================================================

#include "OracleTB.hpp"

#include "libPLN.hpp"
#include "AverageOscillator_20MHz.hpp"

#include <fstream>
#include <iostream>
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

// =========================================================================
// Global variables
// =========================================================================

DetailedBench   DetailedBenchMarks[]    =
{
        {   50E6,   "50MHz"  },
        {   20E6,   "20MHz"  },
        {   10E6,   "10MHz"  },

        {   5E6,    "5MHz"  },
        {   2E6,    "2MHz"  },
        {   1E6,    "1MHz"  },

        {   500E3,  "500kHz"  },
        {   200E3,  "200kHz"  },
        {   100E3,  "100kHz"  },

        {   50E3,   "50kHz"  },
        {   20E3,   "20kHz"  },
        {   10E3,   "10kHz"  },

        {   5E3,    "5kHz"  },
        {   2E3,    "2kHz"  },
        {   1E3,    "1kHz"  },

        {   500E0,  "500Hz"  },
        {   200E0,  "200Hz"  },
        {   100E0,  "100Hz"  },

        {   50E0,   "50Hz"  },
        {   20E0,   "20Hz"  },
        {   10E0,   "10Hz"  },

        {   5E0,    "5Hz"  },
        {   2E0,    "2Hz"  },
        {   1E0,    "1Hz"  },
};

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

void SimpleOracleBench()
{
    double f_s;
    double dt;
    double t        = 0.0L;
    size_t cnt      = 0;
    size_t MaxCnt;

    MaxCnt   = 100000;      // 10^5
    MaxCnt   = 1000000;     // 10^6
//    MaxCnt   = 10000000;    // 10^7
    MaxCnt   = 100000000;   // 10^8     Max @ Matlab

    f_s = 40E6;
//    f_s =3E6;
    f_s = 1E5;
//    f_s = 1E4;
    f_s = 1E3;
//    f_s = 1E1;

//    f_s = 250000;

    dt  = 1.0L / f_s;

    size_t CntThStep    = MaxCnt / 100;
    size_t NextTh       = CntThStep;
    bool PrintTh;

    PrintTh = true;
    PrintTh = false;

    ofstream    TdFile;
    TdFile.open( "/main/td.txt" );

    TdOracle_AvgOsc20MHz o( 123 );

    TdFile.precision( 30 );
    for( cnt = 0; cnt < MaxCnt; cnt ++ )
    {
        double TD;

        TD = o.EstimateTd( t, t );

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
    MaxCnt   = 100000000;   // 10^8     Max @ Matlab

    cout << OutputPath << endl;

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
        t               = 0.0L;

        cout << endl;
        cout << "Starting benchmark for " << Name << endl;

        TdFile.open( Filename.c_str() );
        TdFile.precision( 30 );

        for( Cnt = 0; Cnt < MaxCnt; Cnt ++ )
        {
            double TD;

            TD = o.EstimateTd( t, t );

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
        TdFile.close( );
        cout << "Finished benchmark for " << Name << endl;
    }
}

