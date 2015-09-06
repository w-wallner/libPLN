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

#include "WpmTdVecGen.hpp"

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

void
WpmTdVecGen::ResetRecursiveFilter()
{
    // For WPM there is nothing to do here
}

void
WpmTdVecGen::ApplyRecursiveFilter( FFT_RealVector *pw )
{
    // For WPM there is nothing to do here
}

WpmTdVecGen::WpmTdVecGen( size_t TdVecLen, double TickLen, PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, InterpolationConfig_t InterpolConf )
    : RecursiveTdVecGen( TdVecLen, TickLen, PLN_FilterConf, HP_FilterConf, InterpolConf )
{
    DataType    = TdVector::TD_DATA;
}

WpmTdVecGen::WpmTdVecGen( const WpmTdVecGen& other )
    : RecursiveTdVecGen( other )
{
}

WpmTdVecGen::~WpmTdVecGen()
{
}

WpmTdVecGen*
WpmTdVecGen::Clone() const
{
    return new WpmTdVecGen(*this);
}

WpmTdVecGen&
WpmTdVecGen::operator=( const WpmTdVecGen& other )
{
    RecursiveTdVecGen::operator=( other );

    // By convention, always return *this
    return *this;
}
