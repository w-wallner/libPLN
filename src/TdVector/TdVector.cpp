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

#include "TdVector.hpp"

#include <cassert>
#include <numeric>

#include <iostream>

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

TdVector::TdVector( double t_beg, double LastRelativeTD, double f_s, FFT_RealVector *pData, size_t ValidLen )
    : TD( ValidLen + 1 )
{
    assert( pData->size() >= ValidLen );

    this->f_s       = f_s;
    this->TickLen   = 1.0L / f_s;
    this->t_beg     = t_beg;
    this->t_end     = t_beg + TickLen * ValidLen;

    TD[0]       = LastRelativeTD;
    (*pData)[0] = (*pData)[0]  + LastRelativeTD;

    std::partial_sum( pData->begin(), pData->begin() + ValidLen, TD.begin()+1 );
}

TdVector::TdVector( const TdVector& other )
    : f_s    ( other.f_s     ),
      TickLen( other.TickLen ),
      t_beg  ( other.t_beg   ),
      t_end  ( other.t_end   ),
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
    this->TD        = other.TD;

    // By convention, always return *this
    return *this;
}

std::ostream& operator<<(std::ostream& os, const TdVector& o)
{
    for( size_t i = 0; i < o.TD.size(); i++ )
    {
        os << o.TD[i] * o.TickLen;

        if( i + 1 < o.TD.size() )
        {
            os << ", ";
        }
    }

    return os;
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
TdVector::GetBeginRelTD()
{
    return *TD.begin();
}

double
TdVector::GetEndRelTD()
{
    return *TD.rbegin();
}

double
TdVector::GetBeginTD()
{
    return GetBeginRelTD() * TickLen;
}


double
TdVector::GetEndTD()
{
    return GetEndRelTD() * TickLen;
}

double
TdVector::GetRelativeTD( double t_req )
{
    assert( t_req >= t_beg );
    assert( t_req <= t_end );

    return InterpolateRelTD( t_req );
}

double
TdVector::GetTD( double t_req )
{
    return GetRelativeTD( t_req ) * TickLen;
}
