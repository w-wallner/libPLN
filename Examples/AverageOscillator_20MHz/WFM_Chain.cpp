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
cAvgOsc20MHz::TdEstChain_WFM::GetConfig_100Hz(unsigned int Seed, bool EnableIntervalSkipping)
{
    TdEstimatorConfig   config;

    config.TdVecGenConf.SampleConf.f_s                  = 200;
    config.TdVecGenConf.SampleConf.TdVecLen             = 510;

    config.TdVecGenConf.WhiteNoiseConf.Qd               = 4.5420E-17;
    config.TdVecGenConf.WhiteNoiseConf.Seed             = Seed;

    config.TdVecGenConf.PLN_FilterConf.Implementation   = RECURSIVE_FILTER;
    config.TdVecGenConf.PLN_FilterConf.alpha            = FSA::ALPHA_WFM;
    config.TdVecGenConf.PLN_FilterConf.FilterLen        = 0;

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

cAvgOsc20MHz::TdEstChain_WFM::TdEstChain_WFM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping )
    : TdEstChain( FSA::ALPHA_WFM, SeedOffset )
{
    AddTdEstimator( GetConfig_100Hz( Seed + SeedOffset + 0, EnableIntervalSkipping ) );
}

}
