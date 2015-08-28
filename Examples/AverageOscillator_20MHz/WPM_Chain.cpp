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

TdEstimatorConfig
TdOracle_AvgOsc20MHz::TdEstChain_WPM::GetConfig_WPM_20MHz(unsigned int Seed)
{
    TdEstimatorConfig   config;

    config.SampleConf.f_s               = 40E6;
    config.SampleConf.f_s               = 40E6;
    config.SampleConf.TdVecLen          = 5100;
    config.KwImplOption                 = USE_SHORTCUTS;

    config.KwConf.Qd                    = 25E-36;
    config.KwConf.alpha                 = 2.0;
    config.KwConf.FilterLen             = 10;
    config.KwConf.Seed                  = Seed + 0;

    config.HpConf.Type                  = BLACKMAN;
    config.HpConf.f_c_nom               = 0.024;
    config.HpConf.FilterLen             = 5001;
    config.HpConf.Cnt                   = 1;

    config.InterpolConf.Type            = LINEAR_INTERPOLATION;

    config.TimeConf.T_val               = 2E-6;

    config.PerformanceConf.ForgetTh     = 0;

    return config;
}

TdEstimatorConfig
TdOracle_AvgOsc20MHz::TdEstChain_WPM::GetConfig_WPM_1MHz(unsigned int Seed)
{
    TdEstimatorConfig   config;

    config.SampleConf.f_s                = 22E5;
    config.SampleConf.TdVecLen           = 5100;

    config.KwImplOption                  = USE_SHORTCUTS;

    config.KwConf.Qd                     = 6E-34;
    config.KwConf.alpha                  = 2.0;
    config.KwConf.FilterLen              = 10;
    config.KwConf.Seed                   = Seed;

    config.HpConf.Type                   = BLACKMAN;
    config.HpConf.f_c_nom                = 0.004;
    config.HpConf.FilterLen              = 1001;
    config.HpConf.Cnt                    = 1;

    config.InterpolConf.Type             = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                = 200E-6;

    config.PerformanceConf.ForgetTh      = 0;

    return config;
}

TdEstimatorConfig
TdOracle_AvgOsc20MHz::TdEstChain_WPM::GetConfig_WPM_10kHz(unsigned int Seed)
{
    TdEstimatorConfig   config;

    config.SampleConf.f_s               = 20E3;
    config.SampleConf.TdVecLen          = 5100;

    config.KwImplOption                 = USE_SHORTCUTS;

    config.KwConf.Qd                    = 730E-34;
    config.KwConf.alpha                 = 2.0;
    config.KwConf.FilterLen             = 10;
    config.KwConf.Seed                  = Seed;

    config.HpConf.Type                  = BLACKMAN;
    config.HpConf.f_c_nom               = 0.004;
    config.HpConf.f_c_nom               = 0.0035;
    config.HpConf.FilterLen             = 501;
    config.HpConf.Cnt                   = 1;

    config.InterpolConf.Type            = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val               = 20E-3;

    config.PerformanceConf.ForgetTh     = 0;

    return config;
}

TdEstimatorConfig
TdOracle_AvgOsc20MHz::TdEstChain_WPM::GetConfig_WPM_100Hz(unsigned int Seed)
{
    TdEstimatorConfig   config;

    config.SampleConf.f_s               = 200;
    config.SampleConf.TdVecLen          = 5100;

    config.KwImplOption                 = USE_SHORTCUTS;

    config.KwConf.Qd                    = 730E-32;
    config.KwConf.alpha                 = 2.0;
    config.KwConf.FilterLen             = 10;
    config.KwConf.Seed                  = Seed;

    config.HpConf.Type                  = NO_FILTER;
    config.HpConf.f_c_nom               = 0.01;
    config.HpConf.FilterLen             = 5001;
    config.HpConf.Cnt                   = 1;

    config.InterpolConf.Type            = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val               = 20;

    config.PerformanceConf.ForgetTh     = 0;

    return config;
}

TdOracle_AvgOsc20MHz::TdEstChain_WPM::TdEstChain_WPM( unsigned int Seed )
{
    AddTdEstimator( GetConfig_WPM_20MHz( Seed + 0 ) );
    AddTdEstimator( GetConfig_WPM_1MHz ( Seed + 1 ) );
    AddTdEstimator( GetConfig_WPM_10kHz( Seed + 2 ) );
    AddTdEstimator( GetConfig_WPM_100Hz( Seed + 3 ) );
}

TdOracle_AvgOsc20MHz::TdEstChain_WPM::TdEstChain_WPM( const TdEstChain_WPM& other )
    : TdEstChain( other )
{
}

TdOracle_AvgOsc20MHz::TdEstChain_WPM::~TdEstChain_WPM()
{
}

TdOracle_AvgOsc20MHz::TdEstChain_WPM&
TdOracle_AvgOsc20MHz::TdEstChain_WPM::operator= (const TdEstChain_WPM& other)
{
    TdEstChain::operator=( other );

    // By convention, always return *this
    return *this;
}

}
