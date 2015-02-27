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
FFT::MinFftComplexVectorSize( size_t RealVectorSize )
{
  return RealVectorSize / 2 + 1;
}

size_t
FFT::MinFftRealVectorSize( size_t ComplexVectorSize )
{
  return (ComplexVectorSize-1) * 2;
}

FFT_ComplexVector &
FFT::RealFFT( FFT_RealVector &r, FFT_ComplexVector &c )
{
    if( c.size() < MinFftComplexVectorSize(r.size()) )
    {
         throw std::invalid_argument( "FFT: complex vector must have at least a size of real.size() / 2 + 1" );
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

FFT::FFT()
{
    this->R2C_RealSize      = 0;
    this->R2C_ComplexSize   = 0;
    this->C2R_RealSize      = 0;
    this->C2R_ComplexSize   = 0;

    this->R2C_State = UNINITIALIZED;
    this->C2R_State = UNINITIALIZED;

    this->pR2C_Plan = NULL;
    this->pC2R_Plan = NULL;
}

FFT::~FFT()
{
    if( this->pR2C_Plan != NULL )
    {
        FFTW_C_API::destroy_plan( *pR2C_Plan );

        delete pR2C_Plan;
    }
    if( this->pC2R_Plan != NULL )
    {
        FFTW_C_API::destroy_plan( *pC2R_Plan );

        delete pC2R_Plan;
    }
}

void
FFT::InitializeR2C( size_t RealSize )
{
    if( R2C_State == UNINITIALIZED )
    {
        R2C_RealSize    = RealSize;
        R2C_ComplexSize = MinFftComplexVectorSize( RealSize );

        pR2C_Plan   = new FFTW_C_API::plan;

        FFT_RealVector      r( R2C_RealSize     );
        FFT_ComplexVector   c( R2C_ComplexSize  );

        *pR2C_Plan = FFTW_C_API::plan_dft_r2c_1d( R2C_RealSize, &r[0], &c[0], FFTW_MEASURE );

        R2C_State = INITIALIZED;
    }
    else
    {
        // Check input
        if( RealSize != R2C_RealSize )
        {
            throw std::invalid_argument( "FFT: Vector size does not match expected size." );
        }
    }
}

void
FFT::InitializeC2R( size_t ComplexSize, size_t RealSize )
{
    if( C2R_State == UNINITIALIZED )
    {
        C2R_ComplexSize = ComplexSize;
        C2R_RealSize    = RealSize;

        if( RealSize < MinFftRealVectorSize( ComplexSize ) )
        {
            throw std::invalid_argument( "FFT: Vector size does not match expected size." );
        }

        pC2R_Plan   = new FFTW_C_API::plan;

        FFT_ComplexVector   c( C2R_ComplexSize  );
        FFT_RealVector      r( C2R_RealSize     );

        *pC2R_Plan = FFTW_C_API::plan_dft_c2r_1d( C2R_RealSize, &c[0], &r[0], FFTW_MEASURE );

        C2R_State = INITIALIZED;
    }
    else
    {
        // Check input
        if
        (
            ( ComplexSize   != C2R_ComplexSize  ) ||
            ( RealSize      != C2R_RealSize     )
        )
        {
            throw std::invalid_argument( "FFT: Vector size does not match expected size." );
        }
    }
}

FFT_ComplexVector *
FFT::GetFrequencyDomain( FFT_RealVector *pr )
{
    // Initialize
    InitializeR2C( pr->size() );

    FFT_ComplexVector   *pc = new FFT_ComplexVector( R2C_ComplexSize );

    // Convert to frequency domain
    FFTW_C_API::execute_dft_r2c( *pR2C_Plan, &(*pr)[0], &(*pc)[0] );

    return pc;
}

void
FFT::ConvertToTimeDomain( FFT_ComplexVector *pc, FFT_RealVector *pr )
{
    // Initialize
    InitializeC2R( pc->size(), pr->size() );

    // Convert to time domain
    FFTW_C_API::execute_dft_c2r( *pC2R_Plan, &(*pc)[0], &(*pr)[0] );
}

