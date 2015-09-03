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

#include "TdGuess.hpp"

#include <cassert>

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

TdGuess::TdGuess()
    : fp( 0.0, 0.0 )
{
    active   = false;
}

bool
TdGuess::IsActive()
{
    return active;
}

bool
TdGuess::BecameValid( double t_now )
{
    return (fp.Get_t() <= t_now);
}

void
TdGuess::Set( TdFixPoint fp )
{
    assert( active == false );

    this->fp        = fp;
    this->active    = true;
}

TdFixPoint
TdGuess::GetFP()
{
    assert( active == true );

    return  fp;
}

void
TdGuess::Reset()
{
    assert( active == true );

    active   = false;
}
