// ============================================================================
///
/// \file
///
/// \brief  TODO
///
/// TODO
///
/// \ingroup module_main
///
// ============================================================================

// ============================================================================
//
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
//
// This file is part of libPLN.
//
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License.com as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License.com for more details.
//
// You should have received a copy of the GNU General Public License.com
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================

// =========================================================================
// Includes
// =========================================================================

#include "AverageOscillator_20MHz.hpp"

namespace LibPLN_Examples
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
cAvgOsc20MHz::TdEstChain_FPM::GetConfig_20MHz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.TdVecGenConf.SampleConf.f_s                  = 40E6;
    config.TdVecGenConf.SampleConf.TdVecLen             = 5100;

    config.TdVecGenConf.WhiteNoiseConf.Qd               = 1.77743983746859E-5;
    config.TdVecGenConf.WhiteNoiseConf.Seed             = Seed;

    config.TdVecGenConf.PLN_FilterConf.Implementation   = KASDIN_WALTER_FILTER;
    config.TdVecGenConf.PLN_FilterConf.alpha            = FSA::ALPHA_FPM;
    config.TdVecGenConf.PLN_FilterConf.FilterLen        = 10;

    config.TdVecGenConf.HP_FilterConf.FilterType        = BLACKMAN;
    config.TdVecGenConf.HP_FilterConf.f_c_nom           = 0.024;
    config.TdVecGenConf.HP_FilterConf.FilterLen         = 5001;
    config.TdVecGenConf.HP_FilterConf.Cnt               = 1;

    config.TdVecGenConf.InterpolConf.InterPolType       = LINEAR_INTERPOLATION;

    config.TimeConf.T_val                               = 2E-6;
    config.TimeConf.EnableIntervalSkipping              = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh                     = 0;

    return config;
}

TdEstimatorConfig
cAvgOsc20MHz::TdEstChain_FPM::GetConfig_1MHz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.TdVecGenConf.SampleConf.f_s                  = 22E5;
    config.TdVecGenConf.SampleConf.TdVecLen             = 1100;

    config.TdVecGenConf.WhiteNoiseConf.Qd               = 5.37675550834249E-8;
    config.TdVecGenConf.WhiteNoiseConf.Seed             = Seed;

    config.TdVecGenConf.PLN_FilterConf.Implementation   = KASDIN_WALTER_FILTER;
    config.TdVecGenConf.PLN_FilterConf.alpha            = FSA::ALPHA_FPM;
    config.TdVecGenConf.PLN_FilterConf.FilterLen        = 10;

    config.TdVecGenConf.HP_FilterConf.FilterType        = BLACKMAN;
    config.TdVecGenConf.HP_FilterConf.f_c_nom           = 0.004;
    config.TdVecGenConf.HP_FilterConf.FilterLen         = 1001;
    config.TdVecGenConf.HP_FilterConf.Cnt               = 1;

    config.TdVecGenConf.InterpolConf.InterPolType       = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                               = 200E-6;
    config.TimeConf.EnableIntervalSkipping              = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh                     = 0;

    return config;
}

TdEstimatorConfig
cAvgOsc20MHz::TdEstChain_FPM::GetConfig_10kHz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.TdVecGenConf.SampleConf.f_s                  = 20E3;
    config.TdVecGenConf.SampleConf.TdVecLen             = 520;

    config.TdVecGenConf.WhiteNoiseConf.Qd               = 4.44359959367147E-12;
    config.TdVecGenConf.WhiteNoiseConf.Seed             = Seed;

    config.TdVecGenConf.PLN_FilterConf.Implementation   = KASDIN_WALTER_FILTER;
    config.TdVecGenConf.PLN_FilterConf.alpha            = FSA::ALPHA_FPM;
    config.TdVecGenConf.PLN_FilterConf.FilterLen        = 10;

    config.TdVecGenConf.HP_FilterConf.FilterType        = BLACKMAN;
    config.TdVecGenConf.HP_FilterConf.f_c_nom           = 0.0035;
    config.TdVecGenConf.HP_FilterConf.FilterLen         = 501;
    config.TdVecGenConf.HP_FilterConf.Cnt               = 1;

    config.TdVecGenConf.InterpolConf.InterPolType       = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                               = 20E-3;
    config.TimeConf.EnableIntervalSkipping              = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh                     = 0;

    return config;
}

TdEstimatorConfig
cAvgOsc20MHz::TdEstChain_FPM::GetConfig_100Hz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.TdVecGenConf.SampleConf.f_s                  = 200;
    config.TdVecGenConf.SampleConf.TdVecLen             = 500;

    config.TdVecGenConf.WhiteNoiseConf.Qd               = 4.44359959367147E-16;
    config.TdVecGenConf.WhiteNoiseConf.Seed             = Seed;

    config.TdVecGenConf.PLN_FilterConf.Implementation   = KASDIN_WALTER_FILTER;
    config.TdVecGenConf.PLN_FilterConf.alpha            = FSA::ALPHA_FPM;
    config.TdVecGenConf.PLN_FilterConf.FilterLen        = 10;

    config.TdVecGenConf.HP_FilterConf.FilterType        = NO_FILTER;
    config.TdVecGenConf.HP_FilterConf.f_c_nom           = 0;
    config.TdVecGenConf.HP_FilterConf.FilterLen         = 0;
    config.TdVecGenConf.HP_FilterConf.Cnt               = 0;

    config.TdVecGenConf.InterpolConf.InterPolType       = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                               = 20;
    config.TimeConf.EnableIntervalSkipping              = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh                     = 0;

    return config;
}

cAvgOsc20MHz::TdEstChain_FPM::TdEstChain_FPM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping )
    : TdEstChain( FSA::ALPHA_FPM, SeedOffset )
{
    AddTdEstimator( GetConfig_20MHz( Seed + SeedOffset + 0, EnableIntervalSkipping ) );
    AddTdEstimator( GetConfig_1MHz ( Seed + SeedOffset + 1, EnableIntervalSkipping ) );
    AddTdEstimator( GetConfig_10kHz( Seed + SeedOffset + 2, EnableIntervalSkipping ) );
    AddTdEstimator( GetConfig_100Hz( Seed + SeedOffset + 3, EnableIntervalSkipping ) );
}

}
