// ============================================================================
///
/// \file
///
/// \brief  Implementation of a TD vector that is interpolated using cubic splines
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

#include "TdVectorCubSpline.hpp"

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
TdVectorCubSpline::InterpolateRelTD( double t_req )
{
    if( State == UNINITIALIZED )
    {
        t.resize( TD.size() );

        t[0] = t_beg;
        for( size_t i = 1; i < t.size(); i ++ )
        {
            t[ i ] = t[i-1] + TickLen;
        }

        s.set_points( t, TD );

        State = INITIALIZED;
    }

    return s(t_req);
}

TdVectorCubSpline::TdVectorCubSpline( double t_beg, double LastRelativeTD, double f_s, FFT_RealVector *pData, size_t ValidLen )
    : TdVector( t_beg, LastRelativeTD, f_s, pData, ValidLen )
{
    State   = UNINITIALIZED;
}

TdVectorCubSpline::TdVectorCubSpline( const TdVectorCubSpline& other )
    : TdVector( other )
{
    this->State = other.State;
    this->s     = other.s;
    this->t     = other.t;
}

TdVectorCubSpline::~TdVectorCubSpline()
{
}

TdVectorCubSpline*
TdVectorCubSpline::Clone() const
{
    return new TdVectorCubSpline(*this);
}

TdVectorCubSpline&
TdVectorCubSpline::operator=( const TdVectorCubSpline& other )
{
    TdVector::operator=( other );

    this->State = other.State;
    this->s     = other.s;
    this->t     = other.t;

    // By convention, always return *this
    return *this;
}
