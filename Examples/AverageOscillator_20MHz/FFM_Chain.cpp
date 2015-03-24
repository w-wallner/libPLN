// =========================================================================
// Includes
// =========================================================================

#include "AverageOscillator_20MHz.hpp"

namespace AverageOscillator_20MHz
{

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

TdOracle_AvgOsc20MHz::TdEstChain_FFM::TdEstChain_FFM( unsigned int Seed )
{
    TdEstimatorConfig   Conf_100Hz;

    // -------------------------------------------------------------------------------------------
    // Configure 100 Hz
    // -------------------------------------------------------------------------------------------
    Conf_100Hz.SampleConf.f_s               = 20;
    Conf_100Hz.SampleConf.TdVecLen          = 5100;

    Conf_100Hz.KwImplOption                 = USE_SHORTCUTS;

    Conf_100Hz.KwConf.Qd                    = 400E-26;
    Conf_100Hz.KwConf.alpha                 = -1.0;
    Conf_100Hz.KwConf.FilterLen             = 1000;
    Conf_100Hz.KwConf.Seed                  = Seed + 0;

    Conf_100Hz.HpConf.Type                  = NO_FILTER;
    Conf_100Hz.HpConf.f_c_nom               = 0.01;
    Conf_100Hz.HpConf.FilterLen             = 5001;
    Conf_100Hz.HpConf.Cnt                   = 1;

    Conf_100Hz.InterpolConf.Type            = CUBIC_SPLINE_INTERPOLATION;

    Conf_100Hz.TimeConf.T_val               = 20;

    Conf_100Hz.PerformanceConf.ForgetTh     = 0;

    // -------------------------------------------------------------------------------------------
    // Combine
    // -------------------------------------------------------------------------------------------
    AddTdEstimator( Conf_100Hz, 1.0L );
}

TdOracle_AvgOsc20MHz::TdEstChain_FFM::TdEstChain_FFM( const TdEstChain_FFM& other )
    : TdEstChain( other )
{
}

TdOracle_AvgOsc20MHz::TdEstChain_FFM::~TdEstChain_FFM()
{
}

TdOracle_AvgOsc20MHz::TdEstChain_FFM&
TdOracle_AvgOsc20MHz::TdEstChain_FFM::operator= (const TdEstChain_FFM& other)
{
    TdEstChain::operator=( other );

    // By convention, always return *this
    return *this;
}

}
