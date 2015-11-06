// ============================================================================
///
/// \file
///
/// \brief  Implementation of a filter kernel
///
/// The filter kernel can be applied to time domain data, and used to
/// shape this data.
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

#ifndef LIBPLN_SRC_FILTER_FILTERKERNEL_HPP_
#define LIBPLN_SRC_FILTER_FILTERKERNEL_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <complex>
#include <vector>

#include "Filter/FilterImpResp.hpp"
#include "Utils/FFT.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Filter kernel
///
/// This class implements a filter kernel (i.e. the filter impulse response
/// in the frequency domain. The filter kernel can be used to apply the
/// given filter to a signal.
class cFilterKernel
{
    private:

        // Config
        size_t  MaxDataLen;             ///< Maximum length of data that will be filtered
        size_t  FilterLen;              ///< Filter length
        size_t  FFT_RealSize;           ///< Length of the vectors in the time domain (where the data is real)
        size_t  FFT_ComplexSize;        ///< Length of the vectors in the frequency domain (where the data is complex)

        // Resources
        FFT_ComplexVector   H;          ///< Vector to store complex frequency domain data
        FFT                 fft;        ///< FFT instance

    public:

        /// Default constructor, constructs an empty filter kernel.
        cFilterKernel();

        /// Constructor to create a filter kernel from one filter impulse response.
        ///
        /// The given filter impulse response will be converted to the frequency
        /// domain using the FFT algorithm.
        ///
        /// \note The resulting filter kernel will contain the 1/N scaling that is
        /// necessary when going from the time domain to the frequency domain and
        /// back again.
        ///
        /// \param MaxDataLen   The maximum length of the data for which this filter
        ///                     will be used.
        /// \param h            The filter impulse response from which the
        ///                     filter kernel will be created
        cFilterKernel( size_t MaxDataLen, FilterImpResp &h );

        /// Constructor to create a filter kernel from two filter impulse responses.
        ///
        /// The given filter impulse responses will be converted to the frequency
        /// domain using the FFT algorithm and multiplied (as if they would be
        /// connected one after the other).
        ///
        /// \note The resulting filter kernel will contain the 1/N scaling that is
        /// necessary when going from the time domain to the frequency domain and
        /// back again.
        ///
        /// \param MaxDataLen   The maximum length of the data for which this filter
        ///                     will be used.
        /// \param h1           The first filter impulse response from which the
        ///                     filter kernel will be created
        /// \param h2           The second filter impulse response from which the
        ///                     filter kernel will be created
        cFilterKernel( size_t MaxDataLen, FilterImpResp &h1, FilterImpResp &h2 );

        /// Apply the configured filter kernel to a signal
        ///
        /// Applies the configured filter kernel to a time domain signal.
        /// The signal is converted to the frequency domain, multiplied with
        /// filter kernel, and converted back to the time domain.
        ///
        /// \param pw   Time domain signal to which the filter kernel should be applied.
        ///
        /// \return     The time domain signal on which
        FFT_RealVector  *ApplyToSignal( FFT_RealVector *pw );

        /// Getter for the maximum data length
        size_t  GetMaxDataLen();

        /// Getter for the filter length
        ///
        /// \return Filter length
        size_t  GetFilterLen();

        /// Getter for the configured length of the time domain data for the FFT
        ///
        /// \return Length of the time domain data
        size_t  GetFFT_RealSize();

        FFT_ComplexVector   &GetFilterKernel();
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
