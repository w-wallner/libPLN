// ============================================================================
///
/// \file
///
/// \brief  FFT implementation
///
/// \ingroup module_fft
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

/// Class that implements the FFT algorithm
///
/// The class supports static operations for on-the-fly FFT operation,
/// which is useful for one time calculations, and instanced operations
/// that are useful for reoccurring calculations.
///
/// \remark This class is intended to convert real time domain data to the
/// frequency domain (where it will be complex) and vice versa.
/// Thus:
/// - _real data_ here means time domain data
/// - _complex data_ here means frequency domain data
///
class FFT
{
    private:

        // -----------------------------------------------------------------
        // Types
        // -----------------------------------------------------------------

        /// Current state of the FFT instance
        typedef enum
        {
            UNINITIALIZED,      ///< Uninitialized: before an FFT operation can be carried out, an execution plan needs to be created.
            INITIALIZED,        ///< Initialized:   an execution plan already exists, ready to carry out FFT operations
        }
        FFT_State;

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------
        size_t  R2C_RealSize;           ///< Size of the real data in real-to-complex FFT operation
        size_t  R2C_ComplexSize;        ///< Size of the complex data in real-to-complex FFT operation

        size_t  C2R_RealSize;           ///< Size of the real data in complex-to-real FFT operation
        size_t  C2R_ComplexSize;        ///< Size of the complex data in complex-to-real FFT operation

        // -----------------------------------------------------------------
        // House keeping
        // -----------------------------------------------------------------
        FFT_State   R2C_State;          ///< Current state of the real-to-complex FFT
        FFT_State   C2R_State;          ///< Current state of the complex-to-real FFT

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------
        typename FFTW_C_API::plan   *pR2C_Plan;     ///< Execution plan for the real-to-complex FFT
        typename FFTW_C_API::plan   *pC2R_Plan;     ///< Execution plan for the complex-to-real FFT

        // -----------------------------------------------------------------
        // Internal functinos
        // -----------------------------------------------------------------

        /// Initialize the real-to-complex FFT
        ///
        /// \param RealSize     Size of the real data
        void    InitializeR2C( size_t RealSize );

        /// Initialize the complex-to-real FFT
        ///
        /// \param RealSize     Size of the real data
        /// \param ComplexSize  Size of the complex data
        void    InitializeC2R( size_t RealSize, size_t ComplexSize );

    public:

        // -----------------------------------------------------------------
        // Static class interface
        // -----------------------------------------------------------------

        /// Calculates the minimum size of a complex vector
        ///
        /// \param RealVectorSize   Size of the real data
        ///
        /// \return Minimum size of a complex vector
        static  size_t  MinFftComplexVectorSize(const size_t RealVectorSize );

        /// Calculates the minimum size of a real vector
        ///
        /// \param ComplexVectorSize   Size of the complex data
        ///
        /// \return Minimum size of a real vector
        static  size_t  MinFftRealVectorSize( const size_t ComplexVectorSize );

        /// Calculates the frequency domain data for a given real time domain data vector
        ///
        /// An execution plan for the application of the FFT is created on-the-fly.
        /// This function is useful for one-time FFT calculations (e.g. on startup).
        ///
        /// \param r    Real time domain data
        /// \param c    Vector to store the complex frequency domain data
        ///
        /// \return     The function returns the second parameter
        static FFT_ComplexVector &RealFFT   ( FFT_RealVector    &r, FFT_ComplexVector &c );

        /// Calculates the time domain data for a given complex frequency domain data vector
        ///
        /// An execution plan for the application of the FFT is created on-the-fly.
        /// This function is useful for one-time FFT calculations (e.g. on startup).
        ///
        /// \param c    Complex frequency domain data
        /// \param r    Vector to store the real time domain data
        ///
        /// \return     The function returns the second parameter
        static FFT_RealVector    &ComplexFFT( FFT_ComplexVector &c, FFT_RealVector    &r );

        // -----------------------------------------------------------------
        // Individual interface
        // -----------------------------------------------------------------

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------

        FFT();                          ///< Default constructor
        FFT( const FFT& other );        ///< Copy constructor
        ~FFT();                         ///< Destructor

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------
        FFT&  operator=( const FFT& other );        ///< Assignement operator

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------

        /// Converts a real time domain data vector to the frequency domain
        ///
        /// This function uses pre-calculated execution plans.
        /// Multiple calls to this function need to be called with vectors of the same size.
        /// On the first call, an execution plan is created.
        ///
        /// \param pr   Pointer to the vector holding the real time domain data
        ///
        /// \return     Pointer to a vector which stores the calculated complex frequency domain data
        FFT_ComplexVector   *GetFrequencyDomain( FFT_RealVector *pr );

        /// Converts a complex frequency domain data vector to the time domain
        ///
        /// This function uses pre-calculated execution plans.
        /// Multiple calls to this function need to be called with vectors of the same size.
        /// On the first call, an execution plan is created.
        ///
        /// \param pc   Pointer to the vector holding the complex frequency domain data
        /// \param pr   Pointer to the vector where the real time domain data should be stored
        void                ConvertToTimeDomain( FFT_ComplexVector *pc, FFT_RealVector *pr );
};

#endif
