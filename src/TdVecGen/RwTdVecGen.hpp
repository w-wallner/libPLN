// ============================================================================
///
/// \file
///
/// \brief  Implementation of time deviation generator for RW noise using
///         recursive filters.
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

#ifndef TDVECGEN_RWTDVECGEN_HPP_
#define TDVECGEN_RWTDVECGEN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "RecursiveTdVecGen.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

/// Time deviation vector generator for RW noise using a recursive filter.
///
/// The white noise vectors are filtered using a cumulative sum filter to
/// get RW shaped FFD data. Each new generated vector needs to continue
/// where the last vector ended, thus the last FFD value is stored.
class RwTdVecGen : public RecursiveTdVecGen
{
    private:

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------

        // -----------------------------------------------------------------
        // House keeping
        // -----------------------------------------------------------------

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------

        /// Reset the internal data structures of the recursive filter
        void    ResetRecursiveFilter();

        /// Apply the recursive filter on the generated random white noise data
        void    ApplyRecursiveFilter( FFT_RealVector *pw );

    public:

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------

        /// Constructor
        ///
        /// \param SampleConf       Sampling configuration
        /// \param WhiteNoiseConf   White noise configuration
        /// \param PLN_FilterConf   Configuration for the PLN filtering process
        /// \param InterpolConfig   Interpolation configuration
        RwTdVecGen( SampleConfig_t SampleConf, WhiteNoiseConfig_t WhiteNoiseConf, PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, InterpolationConfig_t InterpolConf );

        /// Copy constructor
        ///
        /// \param other    The instance from which we want to copy
        RwTdVecGen( const RwTdVecGen& other );

        /// Destructor
        ~RwTdVecGen();

        /// Clone method
        ///
        /// \return         Returns a cloned instance
        RwTdVecGen* Clone() const;  // Virtual constructor (copying)

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------

        /// Assignment operator
        ///
        /// \param other    The instance from which we want to copy
        RwTdVecGen&  operator=( const RwTdVecGen& other );
};

#endif
