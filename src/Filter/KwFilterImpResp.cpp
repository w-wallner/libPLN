// ============================================================================
///
/// \file
///
/// \brief  Implementation of the powerlaw noise filter as proposed by Kasdin
///         and Walter.
///
/// \ingroup module_filter
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

#include "KwFilterImpResp.hpp"

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

KwFilterImpResp::KwFilterImpResp( size_t FilterLen, double alpha )
    : FilterImpResp( FilterLen )
{
    double ha = -alpha/2.0;

    h_[0]= 1.0;

    for( size_t i=1; i < FilterLen ; i++ )
    {
        // generate the coefficients h_k
        h_[i] = h_[i-1]* (ha + (double)(i-1))/((double)(i));
    }
}
