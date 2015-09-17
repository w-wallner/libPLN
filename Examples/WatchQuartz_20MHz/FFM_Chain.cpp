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
cWatchQuartz_20MHz::TdEstChain_FFMa::GetConfig_100Hz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.SampleConf.f_s                   = 20;
    config.SampleConf.TdVecLen              = 5100;

    config.PLN_FilterImpl                   = RECURSIVE_FILTER;

    config.PLN_FilterConf.Qd                = 6.4654117423164914448E-19;
    config.PLN_FilterConf.alpha             = FSA::ALPHA_FFM;
    config.PLN_FilterConf.FilterLen         = 1000;
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

cWatchQuartz_20MHz::TdEstChain_FFMa::TdEstChain_FFMa( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping )
    : TdEstChain( FSA::ALPHA_FFM, SeedOffset )
{
    AddTdEstimator( GetConfig_100Hz( Seed + SeedOffset + 0, EnableIntervalSkipping ) );
}

}
