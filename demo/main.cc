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
    SampleConfig            SampleConf;
    KW_ImplOption           KwImplOption;
    KW_FilterConfig         KwFilterConf;
    HP_FilterConfig         HpFilterConf;
    InterpolationConfig     InterpolConf;

    SampleConf.f_s              = 1E6;
    SampleConf.T_val            = 1E-3;
    SampleConf.TdVecLen         = 10;

    KwImplOption                = USE_SHORTCUTS;

    KwFilterConf.alpha          = -1.0;
    KwFilterConf.Qd             = 1E-6;
    KwFilterConf.FilterLen      = 1000;

    HpFilterConf.Type           = BLACKMAN;
    HpFilterConf.f_c_nom        = 1E-3;
    HpFilterConf.FilterLen      = 1000;
    HpFilterConf.Cnt            = 2;

    InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;

    TdEstimator e( SampleConf, KwImplOption, KwFilterConf, HpFilterConf, InterpolConf );

    e.EstimateTd( 0.1, 1.0, 1.0 );

    cout << "Finished" << endl;

    return 0;
}
