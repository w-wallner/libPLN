// =========================================================================
// Includes
// =========================================================================

#include "FilterKernel.hpp"

#include <algorithm>
#include <functional>
#include <stdexcept>

#include "FFT.hpp"
#include "NumericTricks.hpp"

// Debug only
#include <iostream>
using namespace std;
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

FilterKernel::FilterKernel()
{
    MaxDataLen  = 0;
    ResponseLen = 0;
}

FilterKernel::FilterKernel( size_t MaxDataLen, FilterImpResp &h )
{
    size_t  FFT_RealSize    = NumericTricks::nextPowerOf2( MaxDataLen + h.GetFilterLen() - 1 );
    size_t  FFT_ComplexSize = FFT::MinFftComplexVectorSize( FFT_RealSize );

    h.IncreaseResponse( FFT_RealSize );

    H.resize( FFT_ComplexSize );

    FFT::RealFFT( h.h(), H );

    this->MaxDataLen    = MaxDataLen;
    this->ResponseLen   = FFT_RealSize;
}

FilterKernel::FilterKernel( size_t MaxDataLen, FilterImpResp &h1, FilterImpResp &h2 )
{
    size_t  FFT_RealSize    = NumericTricks::nextPowerOf2( MaxDataLen + h1.GetFilterLen() + h2.GetFilterLen() - 2 );
    size_t  FFT_ComplexSize = FFT::MinFftComplexVectorSize( FFT_RealSize );

    h1.IncreaseResponse( FFT_RealSize );
    h2.IncreaseResponse( FFT_RealSize );

    H.resize( FFT_ComplexSize );

    FFT_ComplexVector   H1( FFT_ComplexSize );
    FFT_ComplexVector   H2( FFT_ComplexSize );

    FFT::RealFFT( h1.h(), H1 );
    FFT::RealFFT( h2.h(), H2 );

    PrintFftCompVector( "H1", H1 );
    PrintFftCompVector( "H2", H2 );

    // Merge both filters
    std::transform( H1.begin(), H1.end(),
                    H2.begin(), H.begin(),
                    std::multiplies< std::complex< double > >() );

    PrintFftCompVector( "H (merge)", H );

    // Scale filter to include FFT scaling
    double  Scale = 1.0L / ((double) FFT_RealSize);

    cout << "Scale: " << Scale << endl;

    std::transform( H.begin(), H.end(), H.begin(),
                   std::bind1st(std::multiplies< std::complex<double> >(), Scale) );

    PrintFftCompVector( "H (scale)", H );

    this->MaxDataLen    = MaxDataLen;
    this->ResponseLen   = FFT_RealSize;
}

FFT_RealVector *
FilterKernel::ApplyToSignal( FFT_RealVector *pw )
{
    PrintFftRealVector( "w", *pw );

    FFT_ComplexVector *pW = fft.GetFrequencyDomain( pw );

    // Check size of W
    if( pW->size() != H.size() )
    {
        throw std::logic_error( "FFT(ImpResp) does not match size of FilterKernel." );
    }

    PrintFftCompVector( "W", *pW );
    PrintFftCompVector( "H", H );

    // Apply filter
    std::transform( pW->begin(), pW->end(),
                    H.begin(), pW->begin(),
                    std::multiplies< std::complex< double > >() );

    PrintFftCompVector( "W (filt)", *pW );

    // Remark: Scaling of 1/N is already containg in the filter kernel

    fft.ConvertToTimeDomain( pW, pw );

    PrintFftRealVector( "w", *pw );

    return pw;
}

size_t
FilterKernel::GetMaxDataLen()
{
    return MaxDataLen;
}

size_t
FilterKernel::GetResponseLen()
{
    return ResponseLen;
}
