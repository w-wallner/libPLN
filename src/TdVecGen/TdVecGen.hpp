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

#ifndef TDVECGEN_HPP_
#define TDVECGEN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEst/TdEstConfig.hpp"
#include "TdVector/TdVector.hpp"
#include "TdEst/TdFixPoint.hpp"
#include "Filter/FilterKernel.hpp"
#include "TdVecGen/WhiteNoiseGenerator/WhiteNoiseGenerator.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Generator for TdVectors
class TdVecGen
{
    protected:

        // -----------------------------------------------------------------
        // Types
        // -----------------------------------------------------------------


        /// Enumeration to encode the state of internal convolution
        ///
        /// The time deviation vector generator works by overlapping convolution.
        /// Thus, each new vector depends on the last one.
        /// This means we need to know if we have already generated a vector
        /// before or not.
        typedef enum
        {
            UNINITIALIZED,                          ///< Uninitialized: We can't base the vector on an existing one.
            INITIALIZED,                            ///< Initialized    We already have data from an existing old vector.
        }
        ConvState_t;

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------
        double              TickLen;                ///< Time (in seconds) between two simulated TD values
        InterpolationType   IntpolType;             ///< Interpolation type for the generated TD vectors
        size_t              TdVecLen;               ///< Length of the generated TD vectors

        // -----------------------------------------------------------------
        // House keeping
        // -----------------------------------------------------------------
        ConvState_t         ConvState;              ///< Current state of the convolution
        double              Last_t_end;             ///< Time (in seconds) at the end of the last generated TD vector
        double              LastRelativeTD;         ///< Time deviation (in seconds) at the end of the last generated vector
        size_t              FfdVecLen;              ///< Length of the Fractional Frequency Deviation vectors that are used to generate Time Deviation vectors

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------
        WhiteNoiseGenerator     WhiteNoiseGen;      ///< White noise generator
        FilterKernel            H;                  ///< Filter kernel to shape the white noise
        FFT_RealVector          *pLastFFD;          ///< Pointer to the last generated Fractional Frequency Deviation vector

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------

        /// Initialize the convolution filter
        void        InitConvFilter();

        /// Apply the convolution filter to a data vector
        ///
        /// \param pw   Data vector that should be filtered
        void        ApplyConvFilter( FFT_RealVector *pw );

        /// Reset the convoultion filter
        void        ResetConvFilter();

        /// Construct a Time Deviation vector from given input data
        ///
        /// Depending on the type of input data different operations are performed:
        /// - FFD data: FFD -> TD conversion is done
        /// - TD data:  no conversion needed
        /// \param
        TdVector    *ConstructTdVector( FFT_RealVector *pData, TdVector::TdVecDataType DataType );

        // -----------------------------------------------------------------
        // Constructors
        // -----------------------------------------------------------------

        /// Constructor
        ///
        /// \param
        TdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, InterpolationConfig InterpolConf );
        TdVecGen( const TdVecGen& other );

    public:

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------
        virtual ~TdVecGen();
        virtual TdVecGen* Clone() const = 0;  // Virtual constructor (copying)

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------
        TdVecGen&  operator=( const TdVecGen& other );

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------
        virtual void        ResetToFixPoint( TdFixPoint fp );
        virtual void        SetSeed( unsigned int Seed );
        virtual TdVector    *GetNextVector() = 0;
                double      GetEstimatedValue();
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
