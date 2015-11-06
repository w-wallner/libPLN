// ============================================================================
///
/// \file
///
/// \brief  Implementation of a filter impulse response
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

#ifndef LIBPLN_SRC_FILTER_FILTERIMPRESP_HPP_
#define LIBPLN_SRC_FILTER_FILTERIMPRESP_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "Utils/VectorTypes.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Filter impulse response
///
/// This class stores the impulse response of a filter. It is intended to
/// be inherited by specialized classes that fill the filter impulse response
/// according to a defined function. This can than in turn be used to
/// calculate the filter kernel, and to apply the filter to a signal.
///
class FilterImpResp
{
    protected:

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------
        size_t  FilterLen;              ///< Length of the filter
        size_t  ResponseLen;            ///< Length of the filter response

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------
        FFT_RealVector h_;              ///< Filter impulse response

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------

        /// Default constructor
        ///
        /// This constructor only allocates resources. The filter impulse response
        /// is initialized to all zeroes. It is the job of inheriting classes to
        /// fill it with more meaningful data.
        ///
        /// \param FilterLen    Length of the filter impulse response
        FilterImpResp( size_t FilterLen );

        /// Virtual destructor
        ///
        /// This is declared to ensure that this class can't be instantiated.
        virtual ~FilterImpResp() = 0;

    public:

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------

        /// Access function to the filter impulse response
        FFT_RealVector &h();

        /// Getter for the length of the filter that corresponds to this
        /// filter impulse response
        size_t  GetFilterLen();

        /// Getter for the length fo this filter impulse response
        size_t  GetResponseLen();

        /// Increase the length of the filter response
        ///
        /// This is usefule, if the filter impuls response is used in an FFT.
        /// The end of the filter impulse response is padded with zeroes.
        void    IncreaseResponse( size_t ResponseLen );

        /// The filter impulse response gets convoluted with itself
        /// multiple times.
        ///
        /// This can be used to achive a much steeper filter curve.
        ///
        /// \param Cnt  Number of times the filter gets convoluted with itself
        void    Augment( size_t Cnt );
};


// =========================================================================
// Function declarations
// =========================================================================

#endif
