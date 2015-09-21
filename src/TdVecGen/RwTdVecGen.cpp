// ============================================================================
///
/// \file
///
/// \brief  Implementation of time deviation generator for RW noise using
///         recursive filters.
///
/// \ingroup module_td_vec_gen
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

#include "RwTdVecGen.hpp"

#include <algorithm>
#include <numeric>

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
RwTdVecGen::ResetRecursiveFilter()
{
}

void
RwTdVecGen::ApplyRecursiveFilter( FFT_RealVector *pw )
{
    std::partial_sum( pw->begin(), pw->end(), pw->begin() );
}

RwTdVecGen::RwTdVecGen( size_t TdVecLen, double TickLen, PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, InterpolationConfig_t InterpolConf )
    : RecursiveTdVecGen( TdVecLen, TickLen, PLN_FilterConf, HP_FilterConf, InterpolConf )
{
    DataType    = TdVector::FFD_DATA;
}

RwTdVecGen::RwTdVecGen( const RwTdVecGen& other )
    : RecursiveTdVecGen( other )
{
}

RwTdVecGen::~RwTdVecGen()
{
}

RwTdVecGen*
RwTdVecGen::Clone() const
{
    return new RwTdVecGen(*this);
}

RwTdVecGen&
RwTdVecGen::operator=( const RwTdVecGen& other )
{
    RecursiveTdVecGen::operator=( other );

    // By convention, always return *this
    return *this;
}
