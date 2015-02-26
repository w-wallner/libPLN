// =========================================================================
// Includes
// =========================================================================

#include "FilterKernel.hpp"

#include <algorithm>

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

FilterKernel::FilterKernel( size_t MaxDataLen, FilterImpResp &h )
{
    size_t  FFT_Size    = NumericTricks::nextPowerOf2( MaxDataLen + h.GetFilterLen() - 1 );

    h.IncreaseResponse( FFT_Size );

    H.resize( FFT::MinFftResultSize( FFT_Size ) );

    FFT::RealFFT( h.h(), H );
}

FilterKernel::FilterKernel( size_t MaxDataLen, FilterImpResp &h1, FilterImpResp &h2 )
{
    size_t  FFT_Size    = NumericTricks::nextPowerOf2( MaxDataLen + h1.GetFilterLen() + h2.GetFilterLen() - 2 );

    cout << "h1.FilterLen(): " << h1.GetFilterLen() << endl;
    cout << "h2.FilterLen(): " << h2.GetFilterLen() << endl;

    cout << "FFT Size: " << FFT_Size << endl;

    h1.IncreaseResponse( FFT_Size );
    h2.IncreaseResponse( FFT_Size );

    cout << "h1.ResponseLen(): " << h1.GetResponseLen() << endl;
    cout << "h2.ResponseLen(): " << h2.GetResponseLen() << endl;

    for( size_t i = 0; i < h1.h().size(); i ++ )
    {
        cout << "h1[" << i << "]: " << h1.h()[ i ] << endl;
    }
    cout << endl;

    for( size_t i = 0; i < h2.h().size(); i ++ )
    {
        cout << "h2[" << i << "]: " << h2.h()[ i ] << endl;
    }
    cout << endl;

    H.resize( FFT::MinFftResultSize( FFT_Size ) );

    FFT_ComplexVector   H1( FFT::MinFftResultSize( FFT_Size ) );
    FFT_ComplexVector   H2( FFT::MinFftResultSize( FFT_Size ) );

    FFT::RealFFT( h1.h(), H1 );
    FFT::RealFFT( h1.h(), H2 );

    for( size_t i = 0; i < H1.size(); i ++ )
    {
        cout << "H1[" << i << "]: " << H1[ i ] << endl;
    }
    cout << endl;

    for( size_t i = 0; i < H1.size(); i ++ )
    {
        cout << "H2[" << i << "]: " << H2[ i ] << endl;
    }
    cout << endl;


    std::transform( H1.begin(), H1.end(),
                    H2.begin(), H.begin(),
                    std::multiplies< std::complex<double> >() );

    for( size_t i = 0; i < H.size(); i ++ )
    {
        cout << "H[" << i << "]: " << H[ i ] << endl;
    }
}
