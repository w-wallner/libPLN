// ============================================================================
///
/// \file
///
/// \brief
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

#ifndef LIBPLN_SRC_TDVECGEN_TDVECGENFACTORY_HPP_
#define LIBPLN_SRC_TDVECGEN_TDVECGENFACTORY_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVecGen.hpp"
#include "TdEst/TdEstConfig.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Generator for TdVectors
class TdVecGenFactory
{
    public:

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------

        static TdVecGen*   CreateTdVecGen( TdVecGenConfig_t Conf );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
