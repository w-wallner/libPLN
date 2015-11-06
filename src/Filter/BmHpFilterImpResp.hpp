// ============================================================================
///
/// \file
///
/// \brief  Blackman window high pass filter
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

#ifndef LIBPLN_SRC_FILTER_BMHPFILTERIMPRESP_HPP_
#define LIBPLN_SRC_FILTER_BMHPFILTERIMPRESP_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "FilterImpResp.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Implementation of a Blackman window high pass filter impulse response
///
/// This class implements a Blackman window high pass filter.
/// For more information, see either the wikipedia article on the Blackman
/// window function [1] or have a look in your signal processing book
/// of choice (recommendation: [2]).
///
/// [1] https://en.wikipedia.org/wiki/Window_function#Blackman_windows
/// [2] The Scientist and Engineer's Guide to Digital Signal Processing
class BmHpFilterImpResp  : public FilterImpResp
{
    public:

        /// Constructor
        ///
        /// Initializes the filter impulse response with the coefficients
        /// as given by the Blackman window function (for a high pass filter).
        ///
        /// \param FilterLen    Length of the filter impulse response
        /// \param f_c_nom      Nominal cut frequency
        BmHpFilterImpResp( size_t FilterLen, double f_c_nom );
};

// =========================================================================
// Function declarations
// =========================================================================


#endif
