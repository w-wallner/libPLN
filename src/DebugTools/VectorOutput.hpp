// ============================================================================
///
/// \file
///
/// \brief  Tools that are helpful for debugging
///
/// \ingroup module_debug_tools
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

#ifndef VECTOROUTPUT_HPP_
#define VECTOROUTPUT_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <vector>
#include <iostream>
#include <complex>

#include "Utils/VectorTypes.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

std::ostream& operator<<(std::ostream& os, const RealVector& o);
std::ostream& operator<<(std::ostream& os, const ComplexVector& o);

std::ostream& operator<<(std::ostream& os, const FFT_RealVector& o);
std::ostream& operator<<(std::ostream& os, const FFT_ComplexVector& o);

#endif
