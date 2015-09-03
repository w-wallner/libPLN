// ============================================================================
///
/// \file
///
/// \brief  TODO
///
/// TODO
///
/// \ingroup module_main
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

#ifndef FILTERKERNEL_HPP_
#define FILTERKERNEL_HPP_

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

class FilterKernel
{
    private:

        // Config
        size_t  MaxDataLen;
        size_t  FilterLen;
        size_t  FFT_RealSize;
        size_t  FFT_ComplexSize;

        // Resources
        FFT_ComplexVector   H;
        FFT                 fft;

    public:

        FilterKernel();
        FilterKernel( size_t MaxDataLen, FilterImpResp &h );
        FilterKernel( size_t MaxDataLen, FilterImpResp &h1, FilterImpResp &h2 );

        FFT_RealVector  *ApplyToSignal( FFT_RealVector *pw );

        size_t  GetMaxDataLen();
        size_t  GetFilterLen();
        size_t  GetFFT_RealSize();

        // Debug functions
        void    Print( std::string Name );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
