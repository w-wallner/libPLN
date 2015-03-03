// =========================================================================
// Includes
// =========================================================================

#include <iostream>

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
};

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================
void Testbench( TdEstimator &e )
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

int main()
{
    SampleConfig            SampleConf;
    KW_ImplOption           KwImplOption;
    KW_FilterConfig         KwFilterConf;
    HP_FilterConfig         HpFilterConf;
    InterpolationConfig     InterpolConf;

    SampleConf.f_s              = 10;
    SampleConf.T_val            = 10;
    SampleConf.TdVecLen         = 10;

    KwImplOption                = USE_SHORTCUTS;

    KwFilterConf.Qd             = 1E-6;
    KwFilterConf.alpha          = -1.0;
    KwFilterConf.FilterLen      = 10;

    HpFilterConf.Type           = BLACKMAN;
    HpFilterConf.Type           = NO_FILTER;
    HpFilterConf.f_c_nom        = 0.1;
    HpFilterConf.FilterLen      = 11;
    HpFilterConf.Cnt            = 1;

    InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;

    TdEstimator e( SampleConf, KwImplOption, KwFilterConf, HpFilterConf, InterpolConf );


    Testbench( e );

    cout << "Finished" << endl;

    return 0;
}
