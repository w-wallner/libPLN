// =========================================================================
// Includes
// =========================================================================

#include "TdOracle_20MHz_Paper.hpp"

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


TdOracle_20MHz_Paper::TdEstChain_WPM::TdEstChain_WPM( unsigned int Seed )
{
    TdEstimatorConfig   Conf_20MHz;
    TdEstimatorConfig   Conf_1MHz;
    TdEstimatorConfig   Conf_10kHz;
    TdEstimatorConfig   Conf_100Hz;

    // 20 MHz

    Conf_20MHz.SampleConf.f_s              = 40E6;
    Conf_20MHz.SampleConf.TdVecLen         = 5100;

    Conf_20MHz.KwImplOption                = USE_SHORTCUTS;

    Conf_20MHz.KwConf.Qd             = 25E-36;
    Conf_20MHz.KwConf.alpha          = 2.0;
    Conf_20MHz.KwConf.FilterLen      = 10;
    Conf_20MHz.KwConf.Seed           = Seed + 0;

    Conf_20MHz.HpConf.Type           = BLACKMAN;
//    Conf_20MHz.HpConf.Type           = NO_FILTER;
    Conf_20MHz.HpConf.f_c_nom        = 0.024;
    Conf_20MHz.HpConf.FilterLen      = 5001;
    Conf_20MHz.HpConf.Cnt            = 1;

    Conf_20MHz.InterpolConf.Type           = LINEAR_INTERPOLATION;

    Conf_20MHz.TimeConf.T_val              = 2E-6;
    Conf_20MHz.TimeConf.ForgetTh1          = 200 * Conf_20MHz.TimeConf.T_val;
    Conf_20MHz.TimeConf.ForgetTh2          = 2 * Conf_20MHz.TimeConf.T_val;

    // 1 MHz

    Conf_1MHz.SampleConf.f_s              = 22E5;
    Conf_1MHz.SampleConf.TdVecLen         = 5100;

    Conf_1MHz.KwImplOption                = USE_SHORTCUTS;

    Conf_1MHz.KwConf.Qd             = 6E-34;
    Conf_1MHz.KwConf.alpha          = 2.0;
    Conf_1MHz.KwConf.FilterLen      = 10;
    Conf_1MHz.KwConf.Seed           = Seed + 1;

    Conf_1MHz.HpConf.Type           = BLACKMAN;
//    Conf_1MHz.HpConf.Type           = NO_FILTER;
    Conf_1MHz.HpConf.f_c_nom        = 0.004;
    Conf_1MHz.HpConf.FilterLen      = 1001;
    Conf_1MHz.HpConf.Cnt            = 1;

    Conf_1MHz.InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;

    Conf_1MHz.TimeConf.T_val              = 200E-6;
    Conf_1MHz.TimeConf.ForgetTh1          = 200 * Conf_1MHz.TimeConf.T_val;
    Conf_1MHz.TimeConf.ForgetTh2          = 2 * Conf_1MHz.TimeConf.T_val;

    // 10 kHz

    Conf_10kHz.SampleConf.f_s              = 20E3;
    Conf_10kHz.SampleConf.TdVecLen         = 5100;

    Conf_10kHz.KwImplOption                = USE_SHORTCUTS;

    Conf_10kHz.KwConf.Qd             = 730E-34;
    Conf_10kHz.KwConf.alpha          = 2.0;
    Conf_10kHz.KwConf.FilterLen      = 10;
    Conf_10kHz.KwConf.Seed           = Seed + 2;

    Conf_10kHz.HpConf.Type           = BLACKMAN;
//    Conf_10kHz.HpConf.Type           = NO_FILTER;
    Conf_10kHz.HpConf.f_c_nom        = 0.004;
    Conf_10kHz.HpConf.f_c_nom        = 0.0035;
    Conf_10kHz.HpConf.FilterLen      = 501;
    Conf_10kHz.HpConf.Cnt            = 1;

    Conf_10kHz.InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;

    Conf_10kHz.TimeConf.T_val              = 20E-3;
    Conf_10kHz.TimeConf.ForgetTh1          = 200 * Conf_10kHz.TimeConf.T_val;
    Conf_10kHz.TimeConf.ForgetTh2          = 2 * Conf_10kHz.TimeConf.T_val;

    // 100 Hz
    Conf_100Hz.SampleConf.f_s              = 200;
    Conf_100Hz.SampleConf.TdVecLen         = 5100;

    Conf_100Hz.KwImplOption                = USE_SHORTCUTS;

    Conf_100Hz.KwConf.Qd             = 730E-32;
    Conf_100Hz.KwConf.alpha          = 2.0;
    Conf_100Hz.KwConf.FilterLen      = 10;
    Conf_100Hz.KwConf.Seed           = Seed + 3;

    Conf_100Hz.HpConf.Type           = NO_FILTER;
    Conf_100Hz.HpConf.f_c_nom        = 0.01;
    Conf_100Hz.HpConf.FilterLen      = 5001;
    Conf_100Hz.HpConf.Cnt            = 1;

    Conf_100Hz.InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;

    Conf_100Hz.TimeConf.T_val              = 20;
    Conf_100Hz.TimeConf.ForgetTh1          = 200 * Conf_100Hz.TimeConf.T_val;
    Conf_100Hz.TimeConf.ForgetTh2          = 2 * Conf_100Hz.TimeConf.T_val;


    AddTdEstimator( Conf_20MHz, 1.0L );
    AddTdEstimator( Conf_1MHz,  sqrt(14.0L) );
    AddTdEstimator( Conf_10kHz, sqrt(93.7L) );
    AddTdEstimator( Conf_100Hz, sqrt(95.3L) );
}

TdOracle_20MHz_Paper::TdOracle_20MHz_Paper( unsigned int Seed )
    : WpmChain( Seed )
{
}

double
TdOracle_20MHz_Paper::EstimateTd( double t_now, double t_req )
{
    double  TD = 0.0L;

    TD  += WpmChain.EstimateTd( t_now, t_req );



    return TD;
}

