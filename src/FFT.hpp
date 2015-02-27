
#ifndef FFT_HPP_
#define FFT_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "FFT_Types.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

class FFT
{
    private:

        // Types
        typedef enum
        {
            UNINITIALIZED,
            INITIALIZED,
        }
        FFT_State;

        // Config
        size_t  R2C_RealSize;
        size_t  R2C_ComplexSize;

        size_t  C2R_RealSize;
        size_t  C2R_ComplexSize;

        // House keeping
        FFT_State   R2C_State;
        FFT_State   C2R_State;

        // Resources
        typename FFTW_C_API::plan   *pR2C_Plan;
        typename FFTW_C_API::plan   *pC2R_Plan;

        // Internal functinos
        void    InitializeR2C( size_t RealSize );
        void    InitializeC2R( size_t RealSize, size_t ComplexSize );

    public:

        // -------------------------------------------------------------
        // Static class interface
        // -------------------------------------------------------------
        static  size_t  MinFftComplexVectorSize(const size_t RealVectorSize );
        static  size_t  MinFftRealVectorSize( size_t ComplexVectorSize );

        static FFT_ComplexVector &RealFFT( FFT_RealVector &r, FFT_ComplexVector &c );

        // -------------------------------------------------------------
        // Individual interface
        // -------------------------------------------------------------
        FFT();
        ~FFT();

        FFT_ComplexVector   *GetFrequencyDomain( FFT_RealVector *pr );
        void                ConvertToTimeDomain( FFT_ComplexVector *pc, FFT_RealVector *pr );
};

#endif
