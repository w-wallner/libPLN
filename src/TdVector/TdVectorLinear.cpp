// ============================================================================
///
/// \file
///
/// \brief  Implementation of a TD vector that is linearly interpolated
///
/// \ingroup module_td_vector
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

#include "TdVectorLinear.hpp"

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

double
TdVectorLinear::InterpolateAt( double t_req )
{
    double  t   = t_req - t_beg;

    size_t  idxl = std::floor( t / TickLen );
    size_t  idxr = std::ceil ( t / TickLen );

    double  x  = t - (idxl * TickLen);
    double  dx = TickLen;
    double  dy = (TD[idxr] - TD[idxl]);

    return TD[idxl] + dy / dx * x;
}

TdVectorLinear::TdVectorLinear( double t_beg, double LastRelativeTD, double TickLen, FFT_RealVector *pData, size_t ValidLen )
    : TdVector( t_beg, LastRelativeTD, TickLen, pData, ValidLen )
{
}

TdVectorLinear::TdVectorLinear( const TdVectorLinear& other )
    : TdVector( other )
{
}

TdVectorLinear::~TdVectorLinear()
{
}

TdVectorLinear*
TdVectorLinear::Clone() const
{
    return new TdVectorLinear(*this);
}

TdVectorLinear&
TdVectorLinear::operator=( const TdVectorLinear& other )
{
    TdVector::operator=( other );

    // By convention, always return *this
    return *this;
}
