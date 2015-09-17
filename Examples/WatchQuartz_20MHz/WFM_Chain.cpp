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

#include "WatchQuartz_20MHz.hpp"

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
cWatchQuartz_20MHz::TdEstChain_WFM::GetConfig_20MHz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.SampleConf.f_s                   = 40E6;
    config.SampleConf.TdVecLen              = 5100;

    config.PLN_FilterImpl                   = RECURSIVE_FILTER;

    config.PLN_FilterConf.Qd                = 5.5360E-5;
    config.PLN_FilterConf.alpha             = FSA::ALPHA_WFM;
    config.PLN_FilterConf.FilterLen         = 10;
    config.PLN_FilterConf.Seed              = Seed;

    config.HP_FilterConf.FilterType         = BLACKMAN;
    config.HP_FilterConf.f_c_nom            = 0.024;
    config.HP_FilterConf.FilterLen          = 5001;
    config.HP_FilterConf.Cnt                = 1;

    config.InterpolConf.InterPolType        = LINEAR_INTERPOLATION;

    config.TimeConf.T_val                   = 2E-6;
    config.TimeConf.EnableIntervalSkipping  = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh         = 0;

    return config;
}

TdEstimatorConfig
cWatchQuartz_20MHz::TdEstChain_WFM::GetConfig_1MHz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.SampleConf.f_s                   = 22E5;
    config.SampleConf.TdVecLen              = 5100;

    config.PLN_FilterImpl                   = RECURSIVE_FILTER;

    config.PLN_FilterConf.Qd                = 9.2105E-09;
    config.PLN_FilterConf.alpha             = FSA::ALPHA_WFM;
    config.PLN_FilterConf.FilterLen         = 10;
    config.PLN_FilterConf.Seed              = Seed;

    config.HP_FilterConf.FilterType         = BLACKMAN;
    config.HP_FilterConf.f_c_nom            = 0.004;
    config.HP_FilterConf.FilterLen          = 1001;
    config.HP_FilterConf.Cnt                = 1;

    config.InterpolConf.InterPolType        = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                   = 200E-6;
    config.TimeConf.EnableIntervalSkipping  = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh         = 0;

    return config;
}

TdEstimatorConfig
cWatchQuartz_20MHz::TdEstChain_WFM::GetConfig_10kHz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.SampleConf.f_s                   = 20E3;
    config.SampleConf.TdVecLen              = 5100;

    config.PLN_FilterImpl                   = RECURSIVE_FILTER;

    config.PLN_FilterConf.Qd                = 6.9200E-15;
    config.PLN_FilterConf.alpha             = FSA::ALPHA_WFM;
    config.PLN_FilterConf.FilterLen         = 10;
    config.PLN_FilterConf.Seed              = Seed;

    config.HP_FilterConf.FilterType         = BLACKMAN;
    config.HP_FilterConf.f_c_nom            = 0.0035;
    config.HP_FilterConf.FilterLen          = 501;
    config.HP_FilterConf.Cnt                = 1;

    config.InterpolConf.InterPolType        = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                   = 20E-3;
    config.TimeConf.EnableIntervalSkipping  = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh         = 0;

    return config;
}

TdEstimatorConfig
cWatchQuartz_20MHz::TdEstChain_WFM::GetConfig_100Hz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.SampleConf.f_s                   = 200;
    config.SampleConf.TdVecLen              = 5100;

    config.PLN_FilterImpl                   = RECURSIVE_FILTER;

    config.PLN_FilterConf.Qd                = 6.9200E-21;
    config.PLN_FilterConf.alpha             = FSA::ALPHA_WFM;
    config.PLN_FilterConf.FilterLen         = 10;
    config.PLN_FilterConf.Seed              = Seed;

    config.HP_FilterConf.FilterType         = NO_FILTER;
    config.HP_FilterConf.f_c_nom            = 0.01;
    config.HP_FilterConf.FilterLen          = 5001;
    config.HP_FilterConf.Cnt                = 1;

    config.InterpolConf.InterPolType        = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val                   = 20;
    config.TimeConf.EnableIntervalSkipping  = EnableIntervalSkipping;

    config.PerformanceConf.ForgetTh         = 0;

    return config;
}

cWatchQuartz_20MHz::TdEstChain_WFM::TdEstChain_WFM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping )
    : TdEstChain( FSA::ALPHA_WFM, SeedOffset )
{
    AddTdEstimator( GetConfig_20MHz( Seed + SeedOffset + 0, EnableIntervalSkipping ) );
//    AddTdEstimator( GetConfig_1MHz ( Seed + SeedOffset + 1, EnableIntervalSkipping ) );
//    AddTdEstimator( GetConfig_10kHz( Seed + SeedOffset + 2, EnableIntervalSkipping ) );
//    AddTdEstimator( GetConfig_100Hz( Seed + SeedOffset + 3, EnableIntervalSkipping ) );
}

}
