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

TdOracle_AvgOsc20MHz::TdEstChain_RW::TdEstChain_RW( unsigned int Seed )
{
    TdEstimatorConfig   Conf_100Hz;

    // -------------------------------------------------------------------------------------------
    // Configure 100 Hz
    // -------------------------------------------------------------------------------------------
    Conf_100Hz.SampleConf.f_s               = 200;
    Conf_100Hz.SampleConf.TdVecLen          = 5100;

    Conf_100Hz.KwImplOption                 = USE_SHORTCUTS;

    Conf_100Hz.KwConf.Qd                    = 175E-32;
    Conf_100Hz.KwConf.alpha                 = -2.0;
    Conf_100Hz.KwConf.FilterLen             = 10;
    Conf_100Hz.KwConf.Seed                  = Seed + 0;

    Conf_100Hz.HpConf.Type                  = NO_FILTER;
    Conf_100Hz.HpConf.f_c_nom               = 0.01;
    Conf_100Hz.HpConf.FilterLen             = 5001;
    Conf_100Hz.HpConf.Cnt                   = 1;

    Conf_100Hz.InterpolConf.Type            = CUBIC_SPLINE_INTERPOLATION;

    Conf_100Hz.TimeConf.T_val               = 2000;

    Conf_100Hz.PerformanceConf.ForgetTh     = 0;

    // -------------------------------------------------------------------------------------------
    // Combine
    // -------------------------------------------------------------------------------------------
    AddTdEstimator( Conf_100Hz, 1.0L );
}

TdOracle_AvgOsc20MHz::TdEstChain_RW::TdEstChain_RW( const TdEstChain_RW& other )
    : TdEstChain( other )
{
}

TdOracle_AvgOsc20MHz::TdEstChain_RW::~TdEstChain_RW()
{
}

TdOracle_AvgOsc20MHz::TdEstChain_RW&
TdOracle_AvgOsc20MHz::TdEstChain_RW::operator= (const TdEstChain_RW& other)
{
    TdEstChain::operator=( other );

    // By convention, always return *this
    return *this;
}

}
