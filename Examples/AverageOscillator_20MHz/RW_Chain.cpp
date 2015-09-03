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
TdOracle_AvgOsc20MHz::TdEstChain_RW::GetConfig_RW_100Hz(unsigned int Seed)
{
    TdEstimatorConfig   config;

    config.SampleConf.f_s               = 200;
    config.SampleConf.TdVecLen          = 5100;

    config.KwImplOption                 = USE_SHORTCUTS;

    config.KwConf.Qd                    = 175E-32;
    config.KwConf.alpha                 = -2.0;
    config.KwConf.FilterLen             = 10;
    config.KwConf.Seed                  = Seed + 0;

    config.HpConf.Type                  = NO_FILTER;
    config.HpConf.f_c_nom               = 0.01;
    config.HpConf.FilterLen             = 5001;
    config.HpConf.Cnt                   = 1;

    config.InterpolConf.Type            = CUBIC_SPLINE_INTERPOLATION;

    config.TimeConf.T_val               = 2000;

    config.PerformanceConf.ForgetTh     = 0;

    return config;
}

TdOracle_AvgOsc20MHz::TdEstChain_RW::TdEstChain_RW( unsigned int Seed )
{
    AddTdEstimator( GetConfig_RW_100Hz(Seed + 0) );
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
