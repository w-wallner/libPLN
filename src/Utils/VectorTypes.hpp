// ============================================================================
///
/// \file
///
/// \brief  Vector types
///
/// \ingroup module_vector_types
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

#ifndef LIBPLN_SRC_UTILS_VECTOR_TYPES_HPP_
#define LIBPLN_SRC_UTILS_VECTOR_TYPES_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "FFT_Types.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Vector for real data using the FFTW allocator
typedef std::vector<double, FFTW_Allocator<double> > FFT_RealVector;

/// Vector for complex data using the FFTW allocator
typedef std::vector<std::complex<double>, FFTW_Allocator< std::complex<double> > > FFT_ComplexVector;

/// Vector for real data using the FFTW allocator
typedef std::vector<double> RealVector;

/// Vector for complex data using the FFTW allocator
typedef std::vector< std::complex<double> > ComplexVector;

// =========================================================================
// Function declarations
// =========================================================================

std::ostream& operator<<(std::ostream& os, const RealVector& o);
std::ostream& operator<<(std::ostream& os, const ComplexVector& o);

std::ostream& operator<<(std::ostream& os, const FFT_RealVector& o);
std::ostream& operator<<(std::ostream& os, const FFT_ComplexVector& o);

#endif
