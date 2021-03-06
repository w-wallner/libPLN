// ============================================================================
///
/// \file
///
/// \brief  Implementation of a generator class for time deviation vectors.
///
/// \ingroup module_td_vec_gen
///
// ============================================================================

// ============================================================================
//
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
//
// This file is part of libPLN.
//
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================

#ifndef LIBPLN_SRC_TDVECGEN_TDVECGEN_HPP_
#define LIBPLN_SRC_TDVECGEN_TDVECGEN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEst/TdEstConfig.hpp"
#include "TdVector/TdVector.hpp"
#include "TdEst/TdFixPoint.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class WhiteNoiseGenerator;
class cFilterKernel;

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
        double                  f_s;                ///< Sampling frequency (in Hertz)
        InterpolationType_t     IntpolType;         ///< Interpolation type for the generated TD vectors
        size_t                  TdVecLen;           ///< Length of the generated TD vectors

        // -----------------------------------------------------------------
        // House keeping
        // -----------------------------------------------------------------
        double                  Last_t_end;         ///< Time (in seconds) at the end of the last generated TD vector
        double                  LastRelativeTD;     ///< Time deviation (in seconds) at the end of the last generated vector
        size_t                  FfdVecLen;          ///< Length of the Fractional Frequency Deviation vectors that are used to generate Time Deviation vectors

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------
        WhiteNoiseGenerator     *pWNG;              ///< White noise generator
        cFilterKernel           *pH;                ///< Filter kernel to shape the white noise
        FFT_RealVector          *pLastFFD;          ///< Pointer to the last generated Fractional Frequency Deviation vector

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------

        /// Apply the convolution filter to a data vector
        ///
        /// \param pw   Data vector that should be filtered
        void        ApplyConvFilter( FFT_RealVector *pw );

        /// Reset the convolution filter
        void        ResetConvFilter();

        /// Construct a Time Deviation vector from given input data
        ///

        /// \param
        TdVector    *ConstructTdVector( FFT_RealVector *pData );

        // -----------------------------------------------------------------
        // Constructors
        // -----------------------------------------------------------------

        /// Constructor
        ///
        /// \param Conf     Configuration
        TdVecGen( TdVecGenConfig_t Conf );

        /// Copy constructor
        ///
        /// \param other    The instance from which we want to copy
        TdVecGen( const TdVecGen& other );

    public:

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------

        /// Destructor
        virtual ~TdVecGen();

        /// Clone method
        ///
        /// This method has to be overloaded by subclasses and needs to return a pointer
        /// to a subclass instance.
        virtual TdVecGen* Clone() const = 0;  // Virtual constructor (copying)

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------
        /// Assignment operator
        ///
        /// \param other    The instance from which we want to copy
        TdVecGen&  operator=( const TdVecGen& other );

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------

        /// Reset to a new fix point
        ///
        /// The new fixpoint will be the starting point for future generated TD vectors.
        ///
        /// \param fp   The new fixpoint we want to configure.
        virtual void        ResetToFixPoint( TdFixPoint fp );

        /// Set a new seed for the generation of random time deviation values.
        ///
        /// \param Seed     The new seed that should be usd for the random number
        ///                 generator.
        virtual void        SetSeed( unsigned int Seed );

        /// Generate a new random time deviation vector.
        ///
        /// The new time deviation vector should start at the end of the last
        /// generated TD vector, or if no such vector is available, at the last
        /// fixpoint.
        ///
        /// This function has to be implemented by subclasses.
        ///
        /// \return     A new time deviation vector.
        virtual TdVector    *GetNextVector() = 0;

        /// Get a single random value.
        ///
        /// \return A single random value.
        double              GetEstimatedValue();
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
