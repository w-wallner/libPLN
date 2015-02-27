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
    size_t  FFT_Size    = NumericTricks::nextPowerOf2( MaxDataLen + h.GetFilterLen() - 1 );

    h.IncreaseResponse( FFT_Size );

    H.resize( FFT::MinFftComplexVectorSize( FFT_Size ) );

    FFT::RealFFT( h.h(), H );

    this->MaxDataLen    = MaxDataLen;
    this->ResponseLen   = FFT_Size;
}

FilterKernel::FilterKernel( size_t MaxDataLen, FilterImpResp &h1, FilterImpResp &h2 )
{
    size_t  FFT_Size    = NumericTricks::nextPowerOf2( MaxDataLen + h1.GetFilterLen() + h2.GetFilterLen() - 2 );

    h1.IncreaseResponse( FFT_Size );
    h2.IncreaseResponse( FFT_Size );

    H.resize( FFT::MinFftComplexVectorSize( FFT_Size ) );

    FFT_ComplexVector   H1( FFT::MinFftComplexVectorSize( FFT_Size ) );
    FFT_ComplexVector   H2( FFT::MinFftComplexVectorSize( FFT_Size ) );

    FFT::RealFFT( h1.h(), H1 );
    FFT::RealFFT( h2.h(), H2 );

    // Merge both filters
    std::transform( H1.begin(), H1.end(),
                    H2.begin(), H.begin(),
                    std::multiplies< std::complex< double > >() );

    // Scale filter to include FFT scaling
    double  Scale = 1.0L / ((double) FFT_Size);

    std::transform(H.begin(), H.end(), H.begin(),
                   std::bind1st(std::multiplies< std::complex<double> >(), Scale));

    this->MaxDataLen    = MaxDataLen;
    this->ResponseLen   = FFT_Size;
}

FFT_RealVector  *
FilterKernel::ApplyToSignal( FFT_RealVector *pw )
{
    cout << "w.size: " << pw->size() << endl;
    cout << "w = [ ";
    for( size_t i = 0; i < pw->size(); i ++ )
    {
        cout << (*pw)[i];

        if( i < pw->size() )
        {
            cout << ", ";
        }
    }
    cout << " ];" << endl;
    cout << endl;

    FFT_ComplexVector *pW = fft.GetFrequencyDomain( pw );

    cout << "w.size: " << pw->size() << endl;
    cout << "w = [ ";
    for( size_t i = 0; i < pw->size(); i ++ )
    {
        cout << (*pw)[i];

        if( i < pw->size() )
        {
            cout << ", ";
        }
    }
    cout << " ];" << endl;
    cout << endl;

    // Check size of W
    if( pW->size() != H.size() )
    {
        throw std::logic_error( "FFT(ImpResp) does not match size of FilterKernel." );
    }

    cout << "W.size: " << pW->size() << endl;
    cout << "W = [ ";
    for( size_t i = 0; i < pW->size(); i ++ )
    {
        cout << (*pW)[i];

        if( i < pW->size() )
        {
            cout << ", ";
        }
    }
    cout << " ];" << endl;

    // Apply filter
    /*
    for( size_t i = 0; i < pW->size(); i ++ )
    {
        (*pW)[i] *= H[ i ];
    }
    */

//    std::transform( pW->begin(), pW->end(), H.begin(), pW->begin(), std::multiplies< std::complex< std::complex<double> >());

    std::transform( pW->begin(), pW->end(),
                    H.begin(), pW->begin(),
                    std::multiplies< std::complex< double > >() );

    // Scale
    for( size_t i = 0; i < pW->size(); i ++ )
    {
//        (*pW) *= H[ i ];
    }

    FFT_RealVector  w2( pw->size() );

    fft.ConvertToTimeDomain( pW, &w2 );

    cout << "w2.size: " << w2.size() << endl;
    cout << "w2 = [ ";
    for( size_t i = 0; i < w2.size(); i ++ )
    {
        cout << w2[i];

        if( i < w2.size() )
        {
            cout << ", ";
        }
    }
    cout << " ];" << endl;
    cout << endl;

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
