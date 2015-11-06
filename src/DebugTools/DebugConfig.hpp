// ============================================================================
///
/// \file
///
/// \brief
///
/// \ingroup
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

#ifndef LIBPLN_SRC_DEBUGTOOLS_DEBUGCONFIG_HPP_
#define LIBPLN_SRC_DEBUGTOOLS_DEBUGCONFIG_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <string>

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef struct
{
    bool            VerboseTdVecGen;
}
DebugConfig_t;

// =========================================================================
// Global variables
// =========================================================================

extern  const   DebugConfig_t   AllDisabledDebugConfig;
extern  const   DebugConfig_t   AllEnabledDebugConfig;

extern DebugConfig_t   DebugConfig;

// =========================================================================
// Function declarations
// =========================================================================

#endif
