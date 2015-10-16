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
cAvgOsc20MHz::TdEstChain_WPM::GetConfig_20MHz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.TdVecGenConf.SampleConf.f_s                  = 40E6;
    config.TdVecGenConf.SampleConf.TdVecLen             = 5100;

    config.TdVecGenConf.WhiteNoiseConf.Qd               = 5.5360E-5;
    config.TdVecGenConf.WhiteNoiseConf.Seed             = Seed;

    config.TdVecGenConf.PLN_FilterConf.Implementation   = RECURSIVE_FILTER;
    config.TdVecGenConf.PLN_FilterConf.alpha            = FSA::ALPHA_WPM;
    config.TdVecGenConf.PLN_FilterConf.FilterLen        = 0;

    config.TdVecGenConf.HP_FilterConf.FilterType        = BLACKMAN;
    config.TdVecGenConf.HP_FilterConf.f_c_nom           = 0.024;
    config.TdVecGenConf.HP_FilterConf.FilterLen         = 5001;
    config.TdVecGenConf.HP_FilterConf.Cnt               = 1;

    config.TdVecGenConf.InterpolConf.InterPolType       = LINEAR_INTERPOLATION;

    config.TimeConf.T_val                               = 0;
    config.TimeConf.EnableIntervalSkipping              = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh                     = 0;

    return config;
}

TdEstimatorConfig
cAvgOsc20MHz::TdEstChain_WPM::GetConfig_1MHz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.TdVecGenConf.SampleConf.f_s                  = 22E5;
    config.TdVecGenConf.SampleConf.TdVecLen             = 1100;

    config.TdVecGenConf.WhiteNoiseConf.Qd               = 9.2105E-09;
    config.TdVecGenConf.WhiteNoiseConf.Seed             = Seed;

    config.TdVecGenConf.PLN_FilterConf.Implementation   = RECURSIVE_FILTER;
    config.TdVecGenConf.PLN_FilterConf.alpha            = FSA::ALPHA_WPM;
    config.TdVecGenConf.PLN_FilterConf.FilterLen        = 0;

    config.TdVecGenConf.HP_FilterConf.FilterType        = BLACKMAN;
    config.TdVecGenConf.HP_FilterConf.f_c_nom           = 0.004;
    config.TdVecGenConf.HP_FilterConf.FilterLen         = 1001;
    config.TdVecGenConf.HP_FilterConf.Cnt               = 1;

    config.TdVecGenConf.InterpolConf.InterPolType       = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                               = 0;
    config.TimeConf.EnableIntervalSkipping              = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh                     = 0;

    return config;
}

TdEstimatorConfig
cAvgOsc20MHz::TdEstChain_WPM::GetConfig_10kHz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.TdVecGenConf.SampleConf.f_s                  = 20E3;
    config.TdVecGenConf.SampleConf.TdVecLen             = 510;

    config.TdVecGenConf.WhiteNoiseConf.Qd               = 6.9200E-15;
    config.TdVecGenConf.WhiteNoiseConf.Seed             = Seed;

    config.TdVecGenConf.PLN_FilterConf.Implementation   = RECURSIVE_FILTER;
    config.TdVecGenConf.PLN_FilterConf.alpha            = FSA::ALPHA_WPM;
    config.TdVecGenConf.PLN_FilterConf.FilterLen        = 0;

    config.TdVecGenConf.HP_FilterConf.FilterType        = BLACKMAN;
    config.TdVecGenConf.HP_FilterConf.f_c_nom           = 0.0035;
    config.TdVecGenConf.HP_FilterConf.FilterLen         = 501;
    config.TdVecGenConf.HP_FilterConf.Cnt               = 1;

    config.TdVecGenConf.InterpolConf.InterPolType       = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                               = 0;
    config.TimeConf.EnableIntervalSkipping              = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh                     = 0;

    return config;
}

TdEstimatorConfig
cAvgOsc20MHz::TdEstChain_WPM::GetConfig_100Hz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.TdVecGenConf.SampleConf.f_s                  = 200;
    config.TdVecGenConf.SampleConf.TdVecLen             = 510;

    config.TdVecGenConf.WhiteNoiseConf.Qd               = 6.9200E-21;
    config.TdVecGenConf.WhiteNoiseConf.Seed             = Seed;

    config.TdVecGenConf.PLN_FilterConf.Implementation   = RECURSIVE_FILTER;
    config.TdVecGenConf.PLN_FilterConf.alpha            = FSA::ALPHA_WPM;
    config.TdVecGenConf.PLN_FilterConf.FilterLen        = 0;

    config.TdVecGenConf.HP_FilterConf.FilterType        = NO_FILTER;
    config.TdVecGenConf.HP_FilterConf.f_c_nom           = 0;
    config.TdVecGenConf.HP_FilterConf.FilterLen         = 0;
    config.TdVecGenConf.HP_FilterConf.Cnt               = 0;

    config.TdVecGenConf.InterpolConf.InterPolType       = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                               = 10;
    config.TimeConf.EnableIntervalSkipping              = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh                     = 0;

    return config;
}

cAvgOsc20MHz::TdEstChain_WPM::TdEstChain_WPM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping )
    : TdEstChain( FSA::ALPHA_WPM, SeedOffset )
{
    AddTdEstimator( GetConfig_20MHz( Seed + SeedOffset + 0, EnableIntervalSkipping ) );
    AddTdEstimator( GetConfig_1MHz ( Seed + SeedOffset + 1, EnableIntervalSkipping ) );
    AddTdEstimator( GetConfig_10kHz( Seed + SeedOffset + 2, EnableIntervalSkipping ) );
    AddTdEstimator( GetConfig_100Hz( Seed + SeedOffset + 3, EnableIntervalSkipping ) );
}

}
