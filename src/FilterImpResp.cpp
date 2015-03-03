// =========================================================================
// Includes
// =========================================================================

#include <FilterImpResp.hpp>

#include <stdexcept>
#include <algorithm>

#include "NumericTricks.hpp"
#include "FFT.hpp"

// Debug only
#include "VectorOutput.hpp"

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

FilterImpResp::FilterImpResp()
    :h_( 0 )
{
    this->FilterLen     = 0;
    this->ResponseLen   = 0;
}

FilterImpResp::FilterImpResp( size_t FilterLen )
    :h_( FilterLen )
{
    this->FilterLen     = FilterLen;
    this->ResponseLen   = FilterLen;
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

    FilterLen     = (FilterLen-1) * Cnt;

    size_t  FFT_RealSize    = NumericTricks::nextPowerOf2( this->FilterLen );
    size_t  FFT_CompSize    = FFT::MinFftComplexVectorSize( FFT_RealSize );

    ResponseLen   = FFT_RealSize;

    h_.resize( ResponseLen );

    FFT_ComplexVector   H( FFT_CompSize );

    FFT::RealFFT( h_, H );

    for( size_t i = 1; i < Cnt; i++ )
    {
        std::transform( H.begin(), H.end(),
                        H.begin(), H.begin(),
                        std::multiplies< std::complex< double > >() );
    }

    FFT::ComplexFFT( H, h_ );

    double Scale = 1.0L / (double) FFT_RealSize;

    std::transform( h_.begin(), h_.end(), h_.begin(),
                   std::bind1st(std::multiplies< double>(), Scale));
}
