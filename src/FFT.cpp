// =========================================================================
// Includes
// =========================================================================

#include "FFT.hpp"

#include <stdexcept>

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

size_t
FFT::MinFftResultSize( size_t RealVectorSize )
{
  return RealVectorSize / 2 + 1;
}

FFT_ComplexVector &
FFT::RealFFT( FFT_RealVector &r, FFT_ComplexVector &c )
{
    if( c.size() < MinFftResultSize(r.size()) )
    {
         throw std::invalid_argument("fftw::fft(): result must have size v.size() / 2 + 1");
    }

    // the transform is performed out-of-place, hence the const_cast is safe
    typename FFTW_C_API::plan p = FFTW_C_API::plan_dft_r2c_1d(
                r.size(),
                const_cast<typename FFT_RealVector::value_type*>(&r[0]),
                &c[0],
                FFTW_ESTIMATE);

    FFTW_C_API::execute(p);
    FFTW_C_API::destroy_plan(p);

    return c;
}

