// =========================================================================
// Includes
// =========================================================================

#include <iostream>
#include <fstream>
#include <ctime>

#include "libPLN.hpp"
#include "TdOracle_20MHz_Paper.hpp"

using namespace std;

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef struct
{
    double  t_now;
    double  t_req;
    double  dt_req;
    size_t  cnt;
}
TdBench;

// =========================================================================
// Global variables
// =========================================================================

TdBench TdBenches[] =
{
    { 3.2,    3.2,   0.1, 5 },
    { 15,     16.0,  0.1, 1 },
    { 16.05,  16.1,  0.1, 1 },
    { 16.1,   16.2,  0.1, 1 },
    { 16.1,   16.15, 0.1, 1 },
    { 16.1,   3.35,  0.1, 1 },
};

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================
void
TestBench()
{
    TdEstimatorConfig Conf;

    Conf.SampleConf.f_s              = 1E3;
    Conf.SampleConf.f_s              = 1E1;
    Conf.SampleConf.TdVecLen         = 1000;

    Conf.KwImplOption                = USE_SHORTCUTS;
//    Conf.KwImplOption                = FORCE_GENERIC;

//    Conf.KwFilterConf.Qd             = 1E-24;
    Conf.KwConf.Qd             = 1E-18 * sqrt(100);
    Conf.KwConf.alpha          = 2.0;
    Conf.KwConf.FilterLen      = 100;
    Conf.KwConf.Seed           = 1234;

    Conf.HpConf.Type           = BLACKMAN;
//    Conf.HpConf.Type           = NO_FILTER;
    Conf.HpConf.f_c_nom        = 0.05;
    Conf.HpConf.FilterLen      = 501;
    Conf.HpConf.Cnt            = 1;

    Conf.InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;
    Conf.InterpolConf.Type           = LINEAR_INTERPOLATION;

    Conf.TimeConf.T_val              = Conf.KwConf.FilterLen * (1.0L/Conf.SampleConf.f_s);
    Conf.TimeConf.ForgetTh1          = 200 * Conf.TimeConf.T_val;
    Conf.TimeConf.ForgetTh2          = 2 * Conf.TimeConf.T_val;

    TdEstimator e( Conf );

    double  t_now   = 0.0;
    double  t_req   = 0.0;

    for( size_t i = 0; i < sizeof(TdBenches)/sizeof(TdBenches[0]); i ++ )
    {
        t_now   = TdBenches[ i ].t_now;
        t_req   = TdBenches[ i ].t_req;

        TdEstimate  est;
        for( size_t j = 0; j < TdBenches[ i ].cnt; j ++ )
        {
            est = e.EstimateTd( t_now, t_req );

            cout << "TD[" << t_now << "/" << t_req << "]: " << est.TD << endl;

            t_req += TdBenches[ i ].dt_req;
        }
    }
}

void
FileBench()
{
    TdEstimatorConfig Conf;

    Conf.SampleConf.f_s              = 1E3;
//    Conf.SampleConf.f_s              = 1E1;
    Conf.SampleConf.TdVecLen         = 1000;

    Conf.KwImplOption                = USE_SHORTCUTS;
//    Conf.KwImplOption                = FORCE_GENERIC;

//    Conf.KwFilterConf.Qd             = 1E-24;
    Conf.KwConf.Qd             = 1E-18 * sqrt(100);
    Conf.KwConf.alpha          = 0.0;
    Conf.KwConf.FilterLen      = 100;
    Conf.KwConf.Seed           = 1234;

    Conf.HpConf.Type           = BLACKMAN;
    Conf.HpConf.Type           = NO_FILTER;
    Conf.HpConf.f_c_nom        = 0.05;
    Conf.HpConf.FilterLen      = 501;
    Conf.HpConf.Cnt            = 1;

    Conf.InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;
//    Conf.InterpolConf.Type           = LINEAR_INTERPOLATION;

    Conf.TimeConf.T_val              = Conf.KwConf.FilterLen * (1.0L/Conf.SampleConf.f_s);
    Conf.TimeConf.ForgetTh1          = 200 * Conf.TimeConf.T_val;
    Conf.TimeConf.ForgetTh2          = 2 * Conf.TimeConf.T_val;

    TdEstimator e( Conf );

    double  dt;
    size_t  MaxCnt;

    dt = 1E-3;
    //dt = 1E-1;

    MaxCnt  = 100000;
//    MaxCnt  = 30;
//    MaxCnt  = 3000;

    size_t CntThStep    = MaxCnt / 10;
    size_t NextTh       = CntThStep;
    bool PrintTh;

    PrintTh = true;
//    PrintTh = false;

    ofstream    TdFile;

    TdFile.open( "/main/td.txt" );

    TdFile.precision( 30 );

    double  t = 0.0;
    TdEstimate  est;
    for( size_t i = 0; i < MaxCnt; i ++ )
    {
        est = e.EstimateTd( t, t );

        TdFile << est.TD << endl;

        if( PrintTh )
        {
            if( i >= NextTh )
            {
                cout << "Calculated " << i << " samples (t = " << t << ")." << endl;
                NextTh += CntThStep;
            }
        }

        t   += dt;
    }

    TdFile.close();
}

void
ChainBench_FPM()
{
    double f_s;
    double dt;
    double t        = 0.0L;
    size_t cnt      = 0;
    size_t MaxCnt   = 1000000;

    f_s = 1E3;
    f_s = 5E1;

    dt  = 1.0L / f_s;

    TdEstChain c;

    TdEstimatorConfig Conf_1kHz;

    Conf_1kHz.SampleConf.f_s              = 2E3;
    Conf_1kHz.SampleConf.TdVecLen         = 5100;

    Conf_1kHz.KwImplOption                = USE_SHORTCUTS;

    Conf_1kHz.KwConf.Qd             = 1E-18;
    Conf_1kHz.KwConf.alpha          = 1.0;
    Conf_1kHz.KwConf.FilterLen      = 10;
//    Conf_1kHz.KwConf.FilterLen      = 20;
//    Conf_1kHz.KwConf.FilterLen      = 40;
    Conf_1kHz.KwConf.Seed           = 1234;

    Conf_1kHz.HpConf.Type           = BLACKMAN;
//    Conf_1kHz.HpConf.Type           = NO_FILTER;
    Conf_1kHz.HpConf.f_c_nom        = 0.05;
    Conf_1kHz.HpConf.f_c_nom        = 0.045;
    Conf_1kHz.HpConf.f_c_nom        = 0.04;
//    Conf_1kHz.HpConf.f_c_nom        = 0.02;
    Conf_1kHz.HpConf.FilterLen      = 101;
    Conf_1kHz.HpConf.Cnt            = 1;

    Conf_1kHz.InterpolConf.Type           = LINEAR_INTERPOLATION;

    Conf_1kHz.TimeConf.T_val              = Conf_1kHz.KwConf.FilterLen * (1.0L/Conf_1kHz.SampleConf.f_s);
    Conf_1kHz.TimeConf.ForgetTh1          = 200 * Conf_1kHz.TimeConf.T_val;
    Conf_1kHz.TimeConf.ForgetTh2          = 2 * Conf_1kHz.TimeConf.T_val;

    TdEstimatorConfig Conf_100Hz;

    Conf_100Hz.SampleConf.f_s              = 2E2;
    Conf_100Hz.SampleConf.TdVecLen         = 1000;

    Conf_100Hz.KwImplOption                = USE_SHORTCUTS;

    Conf_100Hz.KwConf.Qd             = 1E-18 * 100;
    Conf_100Hz.KwConf.alpha          = 1.0;
    Conf_100Hz.KwConf.FilterLen      = 1000;
    Conf_100Hz.KwConf.Seed           = 1235;

    Conf_100Hz.HpConf.Type           = NO_FILTER;
    Conf_100Hz.HpConf.f_c_nom        = 0.05;
    Conf_100Hz.HpConf.FilterLen      = 501;
    Conf_100Hz.HpConf.Cnt            = 1;

    Conf_100Hz.InterpolConf.Type           = LINEAR_INTERPOLATION;
    Conf_100Hz.InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;

    Conf_100Hz.TimeConf.T_val              = Conf_100Hz.KwConf.FilterLen * (1.0L/Conf_100Hz.SampleConf.f_s);
    Conf_100Hz.TimeConf.ForgetTh1          = 200 * Conf_100Hz.TimeConf.T_val;
    Conf_100Hz.TimeConf.ForgetTh2          = 2 * Conf_100Hz.TimeConf.T_val;


    c.AddTdEstimator( Conf_1kHz, 1.0L );
    c.AddTdEstimator( Conf_100Hz, sqrt(2.0544L) );

    ofstream    TdFile;

    TdFile.open( "/main/td.txt" );

    TdFile.precision( 30 );
    for( cnt = 0; cnt < MaxCnt; cnt ++ )
    {
        TdFile << c.EstimateTd( t, t ) << endl;

        t += dt;
    }
    TdFile.close();

}

void
ChainBench_WPM()
{
    double f_s;
    double dt;
    double t        = 0.0L;
    size_t cnt      = 0;
    size_t MaxCnt   = 1000000;

    f_s = 1E3;
//    f_s = 5E1;

    dt  = 1.0L / f_s;

    TdEstChain c;

    TdEstimatorConfig Conf_1kHz;

    Conf_1kHz.SampleConf.f_s              = 2E3;
    Conf_1kHz.SampleConf.TdVecLen         = 5100;

    Conf_1kHz.KwImplOption                = USE_SHORTCUTS;

    Conf_1kHz.KwConf.Qd             = 1E-18;
    Conf_1kHz.KwConf.alpha          = 2.0;
    Conf_1kHz.KwConf.FilterLen      = 10;
//    Conf_1kHz.KwConf.FilterLen      = 20;
//    Conf_1kHz.KwConf.FilterLen      = 40;
    Conf_1kHz.KwConf.Seed           = 1234;

    Conf_1kHz.HpConf.Type           = BLACKMAN;
//    Conf_1kHz.HpConf.Type           = NO_FILTER;
    Conf_1kHz.HpConf.f_c_nom        = 0.05;
    Conf_1kHz.HpConf.f_c_nom        = 0.045;
    Conf_1kHz.HpConf.f_c_nom        = 0.04;
//    Conf_1kHz.HpConf.f_c_nom        = 0.02;
    Conf_1kHz.HpConf.FilterLen      = 101;
    Conf_1kHz.HpConf.Cnt            = 1;

    Conf_1kHz.InterpolConf.Type           = LINEAR_INTERPOLATION;

    Conf_1kHz.TimeConf.T_val              = Conf_1kHz.KwConf.FilterLen * (1.0L/Conf_1kHz.SampleConf.f_s);
    Conf_1kHz.TimeConf.ForgetTh1          = 200 * Conf_1kHz.TimeConf.T_val;
    Conf_1kHz.TimeConf.ForgetTh2          = 2 * Conf_1kHz.TimeConf.T_val;

    TdEstimatorConfig Conf_100Hz;

    Conf_100Hz.SampleConf.f_s              = 2E2;
    Conf_100Hz.SampleConf.TdVecLen         = 1000;

    Conf_100Hz.KwImplOption                = USE_SHORTCUTS;

    Conf_100Hz.KwConf.Qd             = 1E-18 * 15;
    Conf_100Hz.KwConf.alpha          = 2.0;
    Conf_100Hz.KwConf.FilterLen      = 1000;
    Conf_100Hz.KwConf.Seed           = 1235;

    Conf_100Hz.HpConf.Type           = NO_FILTER;
    Conf_100Hz.HpConf.f_c_nom        = 0.05;
    Conf_100Hz.HpConf.FilterLen      = 501;
    Conf_100Hz.HpConf.Cnt            = 1;

    Conf_100Hz.InterpolConf.Type           = LINEAR_INTERPOLATION;
    Conf_100Hz.InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;

    Conf_100Hz.TimeConf.T_val              = Conf_100Hz.KwConf.FilterLen * (1.0L/Conf_100Hz.SampleConf.f_s);
    Conf_100Hz.TimeConf.ForgetTh1          = 200 * Conf_100Hz.TimeConf.T_val;
    Conf_100Hz.TimeConf.ForgetTh2          = 2 * Conf_100Hz.TimeConf.T_val;


    c.AddTdEstimator( Conf_1kHz, 1.0L );
//    c.AddTdEstimator( Conf_100Hz, sqrt(10L) );
    c.AddTdEstimator( Conf_100Hz, sqrt(8L) );

    ofstream    TdFile;

    TdFile.open( "/main/td.txt" );

    TdFile.precision( 30 );
    for( cnt = 0; cnt < MaxCnt; cnt ++ )
    {
        TdFile << c.EstimateTd( t, t ) << endl;

        t += dt;
    }
    TdFile.close();
}

void
ChainBench_WFM()
{
    double f_s;
    double dt;
    double t        = 0.0L;
    size_t cnt      = 0;
    size_t MaxCnt   = 1000000;

    f_s = 1E3;
    f_s = 1E1;

    dt  = 1.0L / f_s;

    TdEstChain c;

    TdEstimatorConfig Conf_1kHz;

    Conf_1kHz.SampleConf.f_s              = 2E3;
    Conf_1kHz.SampleConf.TdVecLen         = 5100;

    Conf_1kHz.KwImplOption                = USE_SHORTCUTS;

    Conf_1kHz.KwConf.Qd             = 1E-18;
    Conf_1kHz.KwConf.alpha          = 0.0;
    Conf_1kHz.KwConf.FilterLen      = 10;
//    Conf_1kHz.KwConf.FilterLen      = 20;
//    Conf_1kHz.KwConf.FilterLen      = 40;
    Conf_1kHz.KwConf.Seed           = 1234;

    Conf_1kHz.HpConf.Type           = BLACKMAN;
//    Conf_1kHz.HpConf.Type           = NO_FILTER;
    Conf_1kHz.HpConf.f_c_nom        = 0.05;
    Conf_1kHz.HpConf.f_c_nom        = 0.045;
    Conf_1kHz.HpConf.f_c_nom        = 0.04;
//    Conf_1kHz.HpConf.f_c_nom        = 0.02;
    Conf_1kHz.HpConf.FilterLen      = 101;
    Conf_1kHz.HpConf.Cnt            = 1;

    Conf_1kHz.InterpolConf.Type           = LINEAR_INTERPOLATION;

    Conf_1kHz.TimeConf.T_val              = Conf_1kHz.KwConf.FilterLen * (1.0L/Conf_1kHz.SampleConf.f_s);
    Conf_1kHz.TimeConf.ForgetTh1          = 200 * Conf_1kHz.TimeConf.T_val;
    Conf_1kHz.TimeConf.ForgetTh2          = 2 * Conf_1kHz.TimeConf.T_val;

    TdEstimatorConfig Conf_100Hz;

    Conf_100Hz.SampleConf.f_s              = 2E2;
    Conf_100Hz.SampleConf.TdVecLen         = 1000;

    Conf_100Hz.KwImplOption                = USE_SHORTCUTS;

    Conf_100Hz.KwConf.Qd             = 1E-18 * 1000;
    Conf_100Hz.KwConf.alpha          = 0.0;
    Conf_100Hz.KwConf.FilterLen      = 1000;
    Conf_100Hz.KwConf.Seed           = 1235;

    Conf_100Hz.HpConf.Type           = NO_FILTER;
    Conf_100Hz.HpConf.f_c_nom        = 0.05;
    Conf_100Hz.HpConf.FilterLen      = 501;
    Conf_100Hz.HpConf.Cnt            = 1;

    Conf_100Hz.InterpolConf.Type           = LINEAR_INTERPOLATION;
    Conf_100Hz.InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;

    Conf_100Hz.TimeConf.T_val              = Conf_100Hz.KwConf.FilterLen * (1.0L/Conf_100Hz.SampleConf.f_s);
    Conf_100Hz.TimeConf.ForgetTh1          = 200 * Conf_100Hz.TimeConf.T_val;
    Conf_100Hz.TimeConf.ForgetTh2          = 2 * Conf_100Hz.TimeConf.T_val;


    c.AddTdEstimator( Conf_1kHz, 1.0L );
    c.AddTdEstimator( Conf_100Hz, 1.0L );

    ofstream    TdFile;

    TdFile.open( "/main/td.txt" );

    TdFile.precision( 30 );
    for( cnt = 0; cnt < MaxCnt; cnt ++ )
    {
        TdFile << c.EstimateTd( t, t ) << endl;

        t += dt;
    }
    TdFile.close();
}

void
ChainBench_FFM()
{
    double f_s;
    double dt;
    double t        = 0.0L;
    size_t cnt      = 0;
    size_t MaxCnt   = 1000000;

    f_s = 1E3;
//    f_s = 1E1;

    dt  = 1.0L / f_s;

    TdEstChain c;

    TdEstimatorConfig Conf_1kHz;

    Conf_1kHz.SampleConf.f_s              = 2E3;
    Conf_1kHz.SampleConf.TdVecLen         = 5100;

    Conf_1kHz.KwImplOption                = USE_SHORTCUTS;

    Conf_1kHz.KwConf.Qd             = 1E-18;
    Conf_1kHz.KwConf.alpha          = -1.0;
    Conf_1kHz.KwConf.FilterLen      = 1000;
//    Conf_1kHz.KwConf.FilterLen      = 20;
//    Conf_1kHz.KwConf.FilterLen      = 40;
    Conf_1kHz.KwConf.Seed           = 1234;

    Conf_1kHz.HpConf.Type           = BLACKMAN;
//    Conf_1kHz.HpConf.Type           = NO_FILTER;
//    Conf_1kHz.HpConf.f_c_nom        = 0.005;
//    Conf_1kHz.HpConf.f_c_nom        = 0.0045;
    Conf_1kHz.HpConf.f_c_nom        = 0.004;
//    Conf_1kHz.HpConf.f_c_nom        = 0.002;
//    Conf_1kHz.HpConf.f_c_nom        = 0.00005;
    Conf_1kHz.HpConf.FilterLen      = 701;
    Conf_1kHz.HpConf.Cnt            = 1;

    Conf_1kHz.InterpolConf.Type           = LINEAR_INTERPOLATION;

    Conf_1kHz.TimeConf.T_val              = Conf_1kHz.KwConf.FilterLen * (1.0L/Conf_1kHz.SampleConf.f_s);
    Conf_1kHz.TimeConf.ForgetTh1          = 200 * Conf_1kHz.TimeConf.T_val;
    Conf_1kHz.TimeConf.ForgetTh2          = 2 * Conf_1kHz.TimeConf.T_val;

    TdEstimatorConfig Conf_100Hz;

    Conf_100Hz.SampleConf.f_s              = 2E1;
    Conf_100Hz.SampleConf.TdVecLen         = 1000;

    Conf_100Hz.KwImplOption                = USE_SHORTCUTS;

    Conf_100Hz.KwConf.Qd             = 1E-18 * 5.0119e+07 * 2;
    Conf_100Hz.KwConf.alpha          = -1.0;
    Conf_100Hz.KwConf.FilterLen      = 100;
    Conf_100Hz.KwConf.Seed           = 1235;

    Conf_100Hz.HpConf.Type           = NO_FILTER;
    Conf_100Hz.HpConf.f_c_nom        = 0.05;
    Conf_100Hz.HpConf.FilterLen      = 501;
    Conf_100Hz.HpConf.Cnt            = 1;

    Conf_100Hz.InterpolConf.Type           = LINEAR_INTERPOLATION;
    Conf_100Hz.InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;

    Conf_100Hz.TimeConf.T_val              = Conf_100Hz.KwConf.FilterLen * (1.0L/Conf_100Hz.SampleConf.f_s);
    Conf_100Hz.TimeConf.ForgetTh1          = 200 * Conf_100Hz.TimeConf.T_val;
    Conf_100Hz.TimeConf.ForgetTh2          = 2 * Conf_100Hz.TimeConf.T_val;


//    c.AddTdEstimator( Conf_1kHz, 1.0L );
    c.AddTdEstimator( Conf_100Hz, 1.0L );

    ofstream    TdFile;

    TdFile.open( "/main/td.txt" );

    TdFile.precision( 30 );
    for( cnt = 0; cnt < MaxCnt; cnt ++ )
    {
        TdFile << c.EstimateTd( t, t ) << endl;

        t += dt;
    }
    TdFile.close();
}

void PaperOracleBench()
{
    double f_s;
    double dt;
    double t        = 0.0L;
    size_t cnt      = 0;
    size_t MaxCnt;

    MaxCnt   = 100000;
    MaxCnt   = 1000000;
    MaxCnt   = 10000000;
    MaxCnt   = 100000000;   // Max @ Matlab

    f_s = 40E6;
//    f_s =3E6;
    f_s = 1E5;
//    f_s = 1E4;
//    f_s = 1E3;
    f_s = 1E1;

    f_s = 250000;

    dt  = 1.0L / f_s;

    size_t CntThStep    = MaxCnt / 10;
    size_t NextTh       = CntThStep;
    bool PrintTh;

    PrintTh = true;
//    PrintTh = false;

    ofstream    TdFile;
    TdFile.open( "/main/td.txt" );

    TdOracle_20MHz_Paper o( 123 );

    TdFile.precision( 30 );
    for( cnt = 0; cnt < MaxCnt; cnt ++ )
    {
        TdFile << o.EstimateTd( t, t ) << endl;

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

    //TestBench();
    //FileBench();
    //ChainBench_WPM();
    //ChainBench_FPM();
    //ChainBench_WFM();
    //ChainBench_FFM();

    PaperOracleBench();

    time(&end);

    cout << "Finished, took " << difftime( end, start ) << " seconds" << endl;

    return 0;
}
