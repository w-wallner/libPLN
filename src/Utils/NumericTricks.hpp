// ============================================================================
///
/// \file
///
/// \brief  Various numerical tricks
///
/// \ingroup module_numeric_tricks
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

#ifndef LIBPLN_SRC_UTILS_NUMERICTRICKS_HPP_
#define LIBPLN_SRC_UTILS_NUMERICTRICKS_HPP_

// =========================================================================
// Includes
// =========================================================================

/// Namespace with function to solve numerical problems
namespace NumericTricks
{

// =========================================================================
// Defines
// =========================================================================

/// Macro to calculate the number of elements in a standard C array
#define NumElements(A) (sizeof(A)/sizeof(A[0]))

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

    /// Round up to the next power of 2
    ///
    /// Accepts an integer n, and rounds it up to the next strictly
    /// positive power of 2. If n itself is already a power of 2,
    /// it is not changed.
    ///
    /// Credits:
    /// This function is based on public domain code from
    /// https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
    ///
    /// \param n    Integer that should be rounded up
    ///
    /// \return     Rounded value
    unsigned int nextPowerOf2(unsigned int n);
}

#endif
