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
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
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
cAvgOsc20MHz::TdEstChain_RW::GetConfig_100Hz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.TdVecGenConf.SampleConf.f_s                  = 200;
    config.TdVecGenConf.SampleConf.TdVecLen             = 510;

    config.TdVecGenConf.WhiteNoiseConf.Qd               = 2.8455E-21;
    config.TdVecGenConf.WhiteNoiseConf.Seed             = Seed;

    config.TdVecGenConf.PLN_FilterConf.Implementation   = RECURSIVE_FILTER;
    config.TdVecGenConf.PLN_FilterConf.alpha            = FSA::ALPHA_RW;
    config.TdVecGenConf.PLN_FilterConf.FilterLen        = 0;

    config.TdVecGenConf.HP_FilterConf.FilterType        = BLACKMAN;
    config.TdVecGenConf.HP_FilterConf.f_c_nom           = 0.005;
    config.TdVecGenConf.HP_FilterConf.FilterLen         = 501;
    config.TdVecGenConf.HP_FilterConf.Cnt               = 1;

    config.TdVecGenConf.InterpolConf.InterPolType       = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                               = 0;
    config.TimeConf.EnableIntervalSkipping              = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh                     = 0;

    return config;
}

TdEstimatorConfig
cAvgOsc20MHz::TdEstChain_RW::GetConfig_1Hz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.TdVecGenConf.SampleConf.f_s                  = 2;
    config.TdVecGenConf.SampleConf.TdVecLen             = 510;

    config.TdVecGenConf.WhiteNoiseConf.Qd               = 2.8455e-19;
    config.TdVecGenConf.WhiteNoiseConf.Seed             = Seed;

    config.TdVecGenConf.PLN_FilterConf.Implementation   = RECURSIVE_FILTER;
    config.TdVecGenConf.PLN_FilterConf.alpha            = FSA::ALPHA_RW;
    config.TdVecGenConf.PLN_FilterConf.FilterLen        = 0;

    config.TdVecGenConf.HP_FilterConf.FilterType        = BLACKMAN;
    config.TdVecGenConf.HP_FilterConf.f_c_nom           = 0.005;
    config.TdVecGenConf.HP_FilterConf.FilterLen         = 501;
    config.TdVecGenConf.HP_FilterConf.Cnt               = 1;

    config.TdVecGenConf.InterpolConf.InterPolType       = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                               = 0;
    config.TimeConf.EnableIntervalSkipping              = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh                     = 0;

    return config;
}

TdEstimatorConfig
cAvgOsc20MHz::TdEstChain_RW::GetConfig_10mHz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.TdVecGenConf.SampleConf.f_s                  = 20E-3;
    config.TdVecGenConf.SampleConf.TdVecLen             = 510;

    config.TdVecGenConf.WhiteNoiseConf.Qd               = 2.8455e-17;
    config.TdVecGenConf.WhiteNoiseConf.Seed             = Seed;

    config.TdVecGenConf.PLN_FilterConf.Implementation   = RECURSIVE_FILTER;
    config.TdVecGenConf.PLN_FilterConf.alpha            = FSA::ALPHA_RW;
    config.TdVecGenConf.PLN_FilterConf.FilterLen        = 0;

    config.TdVecGenConf.HP_FilterConf.FilterType        = NO_FILTER;
    config.TdVecGenConf.HP_FilterConf.f_c_nom           = 0;
    config.TdVecGenConf.HP_FilterConf.FilterLen         = 0;
    config.TdVecGenConf.HP_FilterConf.Cnt               = 0;

    config.TdVecGenConf.InterpolConf.InterPolType       = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                               = 20E3;
    config.TimeConf.EnableIntervalSkipping              = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh                     = 0;

    return config;
}

cAvgOsc20MHz::TdEstChain_RW::TdEstChain_RW( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping )
    : TdEstChain( FSA::ALPHA_RW, SeedOffset )
{
    AddTdEstimator( GetConfig_100Hz(Seed + SeedOffset + 0, EnableIntervalSkipping) );
    AddTdEstimator( GetConfig_1Hz  (Seed + SeedOffset + 1, EnableIntervalSkipping) );
    AddTdEstimator( GetConfig_10mHz(Seed + SeedOffset + 2, EnableIntervalSkipping) );
}

}
