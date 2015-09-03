// ============================================================================
///
/// \file
///
/// \brief  TODO
///
/// TODO
///
/// \ingroup module_main
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
        static  size_t  MinFftRealVectorSize( const size_t ComplexVectorSize );

        static FFT_ComplexVector &RealFFT   ( FFT_RealVector    &r, FFT_ComplexVector &c );
        static FFT_RealVector    &ComplexFFT( FFT_ComplexVector &c, FFT_RealVector    &r );

        // -------------------------------------------------------------
        // Individual interface
        // -------------------------------------------------------------

        // Constructors/Destructor
        FFT();
        FFT( const FFT& other );
        ~FFT();

        // Operators
        FFT&  operator=( const FFT& other );

        // API
        FFT_ComplexVector   *GetFrequencyDomain( FFT_RealVector *pr );
        void                ConvertToTimeDomain( FFT_ComplexVector *pc, FFT_RealVector *pr );
};

#endif
