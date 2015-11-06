// ============================================================================
///
/// \file
///
/// \brief  Implementation of 'fixpoints': ordered pairs of the form
///         (real-time, time deviation).
///
/// \ingroup module_td_estimator
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

#include "TdFixPoint.hpp"

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

TdFixPoint::TdFixPoint( double t, double TD )
{
    this->t     = t;
    this->TD    = TD;
}

TdFixPoint::TdFixPoint( const TdFixPoint& other )
{
    this->t     = other.t;
    this->TD    = other.TD;
}

TdFixPoint&
TdFixPoint::operator= (const TdFixPoint& other)
{
    this->t     = other.t;
    this->TD    = other.TD;

    // By convention, always return *this
    return *this;
}

double
TdFixPoint::Get_t() const
{
    return t;
}

double
TdFixPoint::GetTD() const
{
    return TD;
}

