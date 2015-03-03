// =========================================================================
// Includes
// =========================================================================

#include <iostream>
#include <fstream>

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

        for( size_t j = 0; j < TdBenches[ i ].cnt; j ++ )
        {
            cout << "TD[" << t_now << "/" << t_req << "]: " << e.EstimateTd( t_now, t_req, Scale ) << endl;

            t_req += TdBenches[ i ].dt_req;
        }
    }
}

void
FileBench( TdEstimator &e )
{
    double  dt      = 1E-3;
    size_t  MaxCnt  = 1000000;
//    MaxCnt  = 10;
//    MaxCnt  = 3000;

    ofstream    TdFile;

    TdFile.open( "/main/td.txt" );

    double  t = 0.0;
    for( size_t i = 0; i < MaxCnt; i ++ )
    {
        TdFile << e.EstimateTd( t, t, 1.0 ) << endl;

        t   += dt;
    }

    TdFile.close();
}

int main()
{
    SampleConfig            SampleConf;
    KW_ImplOption           KwImplOption;
    KW_FilterConfig         KwFilterConf;
    HP_FilterConfig         HpFilterConf;
    InterpolationConfig     InterpolConf;

    SampleConf.f_s              = 1E3;
    SampleConf.T_val            = 2;
    SampleConf.TdVecLen         = 1000;

    KwImplOption                = USE_SHORTCUTS;

    KwFilterConf.Qd             = 1E-24;
    KwFilterConf.alpha          = 0.0;
    KwFilterConf.FilterLen      = 1000;
    KwFilterConf.Seed           = 123;

    HpFilterConf.Type           = BLACKMAN;
//    HpFilterConf.Type           = NO_FILTER;
    HpFilterConf.f_c_nom        = 0.01;
    HpFilterConf.FilterLen      = 1001;
    HpFilterConf.Cnt            = 2;

    InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;

    TdEstimator e( SampleConf, KwImplOption, KwFilterConf, HpFilterConf, InterpolConf );


    cout << "Starting" << endl;
    //TestBench( e );
    FileBench( e );

    cout << "Finished" << endl;

    return 0;
}
