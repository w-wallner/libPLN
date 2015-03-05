// =========================================================================
// Includes
// =========================================================================

#include <iostream>
#include <fstream>
#include <ctime>

#include "libPLN.hpp"

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
    double  Scale;
    double  dt_req;
    size_t  cnt;
}
TdBench;

// =========================================================================
// Global variables
// =========================================================================

TdBench TdBenches[] =
{
    { 3.2,    3.2,   1.0, 0.1, 5 },
    { 15,     16.0,  1.0, 0.1, 1 },
    { 16.05,  16.1,  1.0, 0.1, 1 },
    { 16.1,   16.2,  1.0, 0.1, 1 },
    { 16.1,   16.15, 1.0, 0.1, 1 },
    { 16.1,   3.35,  1.0, 0.1, 1 },
};

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================
void
TestBench( TdEstimator &e )
{
    double  t_now   = 0.0;
    double  t_req   = 0.0;
    double  Scale   = 1.0;

    for( size_t i = 0; i < sizeof(TdBenches)/sizeof(TdBenches[0]); i ++ )
    {
        t_now   = TdBenches[ i ].t_now;
        t_req   = TdBenches[ i ].t_req;
        Scale   = TdBenches[ i ].Scale;

        TdEstimate  est;
        for( size_t j = 0; j < TdBenches[ i ].cnt; j ++ )
        {
            est = e.EstimateTd( t_now, t_req, Scale );

            cout << "TD[" << t_now << "/" << t_req << "]: " << est.TD << endl;

            t_req += TdBenches[ i ].dt_req;
        }
    }
}

void
FileBench( TdEstimator &e )
{
    double  dt      = 1E-5;
    size_t  MaxCnt  = 1000000;
//    MaxCnt  = 30;
//    MaxCnt  = 3000;

    ofstream    TdFile;

    TdFile.open( "/main/td.txt" );

    TdFile.precision( 30 );

    double  t = 0.0;
    TdEstimate  est;
    for( size_t i = 0; i < MaxCnt; i ++ )
    {
        est = e.EstimateTd( t, t, 1.0 );

        TdFile << est.TD << endl;

        t   += dt;
    }

    TdFile.close();
}

int main()
{
    TdEstimatorConfig Conf;

    Conf.SampleConf.f_s              = 1E3;
    Conf.SampleConf.TdVecLen         = 1000000;

    Conf.KwImplOption                = USE_SHORTCUTS;
//    Conf.KwImplOption                = FORCE_GENERIC;

//    Conf.KwFilterConf.Qd             = 1E-24;
    Conf.KwConf.Qd             = 1E-18;
    Conf.KwConf.alpha          = 0.0;
    Conf.KwConf.FilterLen      = 1000000;
    Conf.KwConf.Seed           = 123;

    Conf.HpConf.Type           = BLACKMAN;
    Conf.HpConf.Type           = NO_FILTER;
    Conf.HpConf.f_c_nom        = 0.01;
    Conf.HpConf.FilterLen      = 1001;
    Conf.HpConf.Cnt            = 1;

    Conf.InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;
//    Conf.InterpolConf.Type           = LINEAR_INTERPOLATION;

    Conf.TimeConf.T_val              = 2E-3;
    Conf.TimeConf.ForgetTh1          = 5E-3;
    Conf.TimeConf.ForgetTh2          = 1E-3;

    TdEstimator e( Conf );


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

    //TestBench( e );
    FileBench( e );

    time(&end);

    cout << "Finished, took " << difftime( end, start ) << " seconds" << endl;

    return 0;
}
