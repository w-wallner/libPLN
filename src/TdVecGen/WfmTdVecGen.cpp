// ============================================================================
///
/// \file
///
/// \brief  Implementation of time deviation generator for WFM noise using
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

#include "WfmTdVecGen.hpp"

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
WfmTdVecGen::ResetRecursiveFilter()
{
    // For WFM there is nothing to do here
}

void
WfmTdVecGen::ApplyRecursiveFilter( FFT_RealVector *pw )
{
    // For WFM there is nothing to do here
}

WfmTdVecGen::WfmTdVecGen( TdVecGenConfig_t Conf )
    : RecursiveTdVecGen( Conf )
{
    DataType    = TdVector::FFD_DATA;
}

WfmTdVecGen::WfmTdVecGen( const WfmTdVecGen& other )
    : RecursiveTdVecGen( other )
{
}

WfmTdVecGen::~WfmTdVecGen()
{
}

WfmTdVecGen*
WfmTdVecGen::Clone() const
{
    return new WfmTdVecGen(*this);
}

WfmTdVecGen&
WfmTdVecGen::operator=( const WfmTdVecGen& other )
{
    RecursiveTdVecGen::operator=( other );

    // By convention, always return *this
    return *this;
}
