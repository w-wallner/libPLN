// ============================================================================
///
/// \file
///
/// \brief  White noise generator
///
/// \ingroup module_white_noise_gen
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

#ifndef LIBPLN_SRC_TDVECGEN_WHITENOISEGENERATOR_HPP_
#define LIBPLN_SRC_TDVECGEN_WHITENOISEGENERATOR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <vector>
#include <cstddef>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>

#include "Utils/VectorTypes.hpp"
#include "TdEst/TdEstConfig.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef boost::mt19937                     ENG;    ///< Mersenne Twister
typedef boost::normal_distribution<double> DIST;   ///< Normal Distribution
typedef boost::variate_generator<ENG,DIST> GEN;    ///< Variate generator

// =========================================================================
// Function declarations
// =========================================================================

/// White noise generator using the Gaussian noise implementation of the Boost library
class WhiteNoiseGenerator
{
    private:

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------
        GEN  *pGen;   ///< Variate generator

    public:

        // -----------------------------------------------------------------
        // Constructor/Destructor
        // -----------------------------------------------------------------

        /// Constructor
        ///
        /// \param Seed     The seed for the white noise generator
        /// \param Qd       The standard variance of the generated Gaussian noise
        WhiteNoiseGenerator( WhiteNoiseConfig_t WhiteNoiseConfig );

        /// Copy constructor
        ///
        /// \param other    The instance that should be copied
        WhiteNoiseGenerator( const WhiteNoiseGenerator& other );

        /// Destructor
        ~WhiteNoiseGenerator();

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------

        /// Assignment operator
        ///
        /// \param other    The instance that should be assigned
        ///
        /// \return         An assigned instance
        WhiteNoiseGenerator&  operator=( const WhiteNoiseGenerator& other );

        // -----------------------------------------------------------------
        // Noise generation functions
        // -----------------------------------------------------------------

        /// Generates a white noise vector suitable for FFT calculations
        ///
        /// \param VecLen   Length of the requested vector
        /// \param FillLen  Length of the vector that is filled with random data.
        ///                 The rest of the vector is set to 0.0L.
        ///                 FillLen must be smaller or equal to VecLen
        ///
        /// \return         The requested vector
        FFT_RealVector      *GetFftVector( size_t VecLen, size_t FillLen );

        /// Generates a white noise std::vector
        ///
        /// \param VecLen   Length of the requested vector
        /// \param FillLen  Length of the vector that is filled with random data.
        ///                 The rest of the vector is set to 0.0L.
        ///                 FillLen must be smaller or equal to VecLen
        ///
        /// \return         The requested vector
        RealVector          *GetStdVector( size_t VecLen, size_t FillLen );

        /// Returns a single random value from the configured distribution
        ///
        /// \return     Random value
        double  GetRandomValue();

        // -----------------------------------------------------------------
        // Configuration API
        // -----------------------------------------------------------------

        /// Configures the random number generator with a new seed
        ///
        /// \param Seed     New seed for the random number generator
        void    SetSeed( unsigned int Seed );
};

#endif
