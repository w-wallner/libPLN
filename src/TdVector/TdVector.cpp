// ============================================================================
///
/// \file
///
/// \brief  Implementation of a Time Deviation vector
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

#include "TdVector.hpp"

#include <cassert>
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

TdVector::TdVector( double t_beg, double TD_0, double TickLen, FFT_RealVector *pData, size_t ValidLen, TdVecDataType DataType )
    : TD( ValidLen + 1 )
{
    assert( pData->size() >= ValidLen );

    this->t_beg     = t_beg;
    this->t_end     = t_beg + TickLen * ValidLen;
    this->TickLen   = TickLen;
    this->TD_0      = TD_0;

    TD[0]   = 0.0L;

    switch( DataType )
    {
        case FFD_DATA:
        {
            std::partial_sum( pData->begin(), pData->begin() + ValidLen, TD.begin()+1 );
            break;
        }
        case TD_DATA:
        {
            std::copy( pData->begin(), pData->begin() + ValidLen, TD.begin() + 1 );
            break;
        }
    }
}

TdVector::TdVector( const TdVector& other )
    : TickLen( other.TickLen ),
      t_beg  ( other.t_beg   ),
      t_end  ( other.t_end   ),
      TD_0   ( other.TD_0    ),
      TD     ( other.TD      )
{
}

TdVector::~TdVector()
{
}

TdVector&
TdVector::operator=( const TdVector& other )
{
    this->TickLen   = other.TickLen;
    this->t_beg     = other.t_beg;
    this->t_end     = other.t_end;
    this->TD_0      = other.TD_0;
    this->TD        = other.TD;

    // By convention, always return *this
    return *this;
}

double
TdVector::GetBeginTime()
{
    return t_beg;
}

double
TdVector::GetEndTime()
{
    return t_end;
}

double
TdVector::GetBeginTD()
{
    return *TD.begin() + TD_0;
}

double
TdVector::GetEndTD()
{
    return *TD.rbegin() + TD_0;
}

double
TdVector::GetRelativeTD( double t_req )
{
    assert( t_req >= t_beg );
    assert( t_req <= t_end );

    return TD_0 + InterpolateAt( t_req );
}
