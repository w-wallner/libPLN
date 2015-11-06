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

// =========================================================================
// Includes
// =========================================================================

#include "FilterKernel.hpp"

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <cassert>

#include "Utils/FFT.hpp"
#include "Utils/NumericTricks.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Global variables
// =========================================================================

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

cFilterKernel::cFilterKernel()
{
    MaxDataLen      = 0;
    FilterLen       = 0;
    FFT_RealSize    = 0;
    FFT_ComplexSize = 0;
}

cFilterKernel::cFilterKernel( size_t MaxDataLen, FilterImpResp &h )
{
    this->MaxDataLen        = MaxDataLen;
    this->FilterLen         = h.GetFilterLen();
    this->FFT_RealSize      = NumericTricks::nextPowerOf2( MaxDataLen + FilterLen - 1 );;
    this->FFT_ComplexSize   = FFT::MinFftComplexVectorSize( FFT_RealSize );

    // Implementation of overlap-add convolution assumes that vectors are longer than filters
    if( MaxDataLen < FilterLen )
    {
        throw std::invalid_argument( "Data length has to be at least as long as the filter." );
    }

    h.IncreaseResponse( FFT_RealSize );

    H.resize( FFT_ComplexSize );

    FFT::RealFFT( h.h(), H );

    // Scale filter to include FFT scaling
    double  Scale = 1.0L / ((double) FFT_RealSize);

    std::transform( H.begin(), H.end(), H.begin(),
                   std::bind1st(std::multiplies< std::complex<double> >(), Scale) );
}

cFilterKernel::cFilterKernel( size_t MaxDataLen, FilterImpResp &h1, FilterImpResp &h2 )
{
    this->MaxDataLen        = MaxDataLen;
    this->FilterLen         = h1.GetFilterLen() + h2.GetFilterLen() - 1;
    this->FFT_RealSize      = NumericTricks::nextPowerOf2( MaxDataLen + FilterLen - 1 );;
    this->FFT_ComplexSize   = FFT::MinFftComplexVectorSize( FFT_RealSize );

    // Implementation of overlap-add convolution assumes that vectors are at least as long as filters
    if( MaxDataLen < FilterLen )
    {
        throw std::invalid_argument( "Data length has to be at least as long as the filter." );
    }

    h1.IncreaseResponse( FFT_RealSize );
    h2.IncreaseResponse( FFT_RealSize );

    H.resize( FFT_ComplexSize );

    FFT_ComplexVector   H1( FFT_ComplexSize );
    FFT_ComplexVector   H2( FFT_ComplexSize );

    FFT::RealFFT( h1.h(), H1 );
    FFT::RealFFT( h2.h(), H2 );

    // Merge both filters
    std::transform( H1.begin(), H1.end(),
                    H2.begin(), H.begin(),
                    std::multiplies< std::complex< double > >() );

    // Scale filter to include FFT scaling
    double  Scale = 1.0L / ((double) FFT_RealSize);

    std::transform( H.begin(), H.end(), H.begin(),
                   std::bind1st(std::multiplies< std::complex<double> >(), Scale) );
}

FFT_RealVector *
cFilterKernel::ApplyToSignal( FFT_RealVector *pw )
{
    FFT_ComplexVector *pW = fft.GetFrequencyDomain( pw );

    // Check size of W
    if( pW->size() != H.size() )
    {
        throw std::logic_error( "FFT(ImpResp) does not match size of FilterKernel." );
    }

    // Apply filter
    std::transform( pW->begin(), pW->end(),
                    H.begin(), pW->begin(),
                    std::multiplies< std::complex< double > >() );

    // Remark: Scaling of 1/N is already contained in the filter kernel

    fft.ConvertToTimeDomain( pW, pw );

    delete pW;

    return pw;
}

size_t
cFilterKernel::GetMaxDataLen()
{
    return MaxDataLen;
}

size_t
cFilterKernel::GetFilterLen()
{
    return FilterLen;
}

size_t
cFilterKernel::GetFFT_RealSize()
{
    return FFT_RealSize;
}

FFT_ComplexVector&
cFilterKernel::GetFilterKernel()
{
    return H;
}
