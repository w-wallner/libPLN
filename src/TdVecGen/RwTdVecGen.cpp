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
    FFD_0       = 0.0L;
}

void
RwTdVecGen::ApplyRecursiveFilter( FFT_RealVector *pw )
{
    (*pw)[0] = (*pw)[0] + FFD_0;

    std::partial_sum( pw->begin(), pw->begin() + TdVecLen, pw->begin() );

    // Save last FFD value for the next iteration
    FFD_0 = (*pw)[TdVecLen-1];
}

RwTdVecGen::RwTdVecGen( TdVecGenConfig_t Conf )
    : RecursiveTdVecGen( Conf )
{
    FFD_0       = 0.0L;
}

RwTdVecGen::RwTdVecGen( const RwTdVecGen& other )
    : RecursiveTdVecGen( other )
{
    this->FFD_0 = other.FFD_0;
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

    this->FFD_0 = other.FFD_0;

    // By convention, always return *this
    return *this;
}
