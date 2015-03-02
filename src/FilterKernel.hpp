
#ifndef FILTERKERNEL_HPP_
#define FILTERKERNEL_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <FilterImpResp.hpp>
#include <complex>
#include <vector>

#include "FFT.hpp"

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
        size_t  ResponseLen;

        // Resources
        FFT_ComplexVector   H;
        FFT                 fft;

    public:

        FilterKernel();
        FilterKernel( size_t MaxDataLen, FilterImpResp &h );
        FilterKernel( size_t MaxDataLen, FilterImpResp &h1, FilterImpResp &h2 );

        FFT_RealVector  *ApplyToSignal( FFT_RealVector *pw );

        size_t  GetMaxDataLen();
        size_t  GetResponseLen();

        // Debug functions
        void    Print( std::string Name );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
