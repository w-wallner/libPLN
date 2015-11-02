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

#ifndef LIBPLN_SRC_FILTER_KWFILTERIMPRESP_HPP_
#define LIBPLN_SRC_FILTER_KWFILTERIMPRESP_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <cstddef>

#include "FilterImpResp.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

/// Implementation of a powerlaw noise filter as proposed by Kasdin and Walter.
///
/// This class implements the filter impulse response for an FIR filter that
/// can be used to generate PowerLaw Noise that fulfills
/// S_y(f) ~ f^alpha
/// where S_y(f) is the power spectral density of the powerlaw noise.
///
/// The method is described in [1].
///
/// [1] Discrete simulation of power law noise
///     N.J. Kasdin, T. Walter
///     Frequency Control Symposium, 1992
class KwFilterImpResp  : public FilterImpResp
{
    public:

        /// Constructor
        ///
        /// Generates a KW filter impulse response for the given value of alpha
        /// of length FilerLen
        ///
        /// \param FilterLen    Length of the filter impulse response
        /// \param alpha        Exponent of the power spectral density
        KwFilterImpResp( size_t FilterLen, double alpha );
};

#endif
