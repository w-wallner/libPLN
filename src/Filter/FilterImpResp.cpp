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

// =========================================================================
// Includes
// =========================================================================

#include "FilterImpResp.hpp"

#include <stdexcept>
#include <algorithm>

#include "Utils/NumericTricks.hpp"
#include "Utils/FFT.hpp"

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

FilterImpResp::FilterImpResp( size_t FilterLen )
    :h_( FilterLen, 0.0L )
{
    this->FilterLen     = FilterLen;
    this->ResponseLen   = FilterLen;
}

FilterImpResp::~FilterImpResp()
{
}

FFT_RealVector &
FilterImpResp::h()
{
    return h_;
}

size_t
FilterImpResp::GetFilterLen()
{
    return FilterLen;
}

size_t
FilterImpResp::GetResponseLen()
{
    return ResponseLen;
}

void
FilterImpResp::IncreaseResponse( size_t ResponseLen )
{
    if( ResponseLen < this->ResponseLen )
    {
        throw "New ResponseLen is smaller than older ResponseLen";
    }

    h_.resize( ResponseLen, 0.0L );
    this->ResponseLen = ResponseLen;
}

void
FilterImpResp::Augment( size_t Cnt )
{
    if( Cnt < 1 )
    {
        throw std::invalid_argument( "ImpResp: Cnt must be at least 1." );
    }

    if( Cnt == 1 )
    {
        return;
    }

    FilterLen = 1 + (FilterLen-1) * Cnt;

    size_t  FFT_RealSize    = NumericTricks::nextPowerOf2( FilterLen );
    size_t  FFT_CompSize    = FFT::MinFftComplexVectorSize( FFT_RealSize );

    ResponseLen = FFT_RealSize;

    h_.resize( ResponseLen );

    FFT_ComplexVector   H1( FFT_CompSize );
    FFT::RealFFT( h_, H1 );
    FFT_ComplexVector   H2( H1 );

    for( size_t i = 1; i < Cnt; i++ )
    {
        std::transform( H2.begin(), H2.end(),
                        H1.begin(), H2.begin(),
                        std::multiplies< std::complex< double > >() );
    }

    FFT::ComplexFFT( H2, h_ );

    double Scale = 1.0L / (double) FFT_RealSize;

    std::transform( h_.begin(), h_.end(), h_.begin(),
                   std::bind1st(std::multiplies< double>(), Scale));
}
