// ============================================================================
///
/// \file
///
/// \brief  Generic implementation of a time deviation generator based
///         on the powerlaw noise simulation approach proposed by Kasdin
///         and Walter.
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

#ifndef TDVECGEN_GENERICTDVECGEN_HPP_
#define TDVECGEN_GENERICTDVECGEN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEst/TdEstConfig.hpp"
#include "TdVecGen/TdVecGen.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Generic generator for TdVectors
///
/// This kind of time deviation vector generator is suitable for all values
/// of alpha between -2 and 2, including non-integer values.
///
/// The method that is used is based on the one described in [1].
///
/// [1] Discrete simulation of power law noise
///     N.J. Kasdin, T. Walter
///     Frequency Control Symposium, 1992
class GenericTdVecGen : public TdVecGen
{
    private:

        //------------------------------------------------------------------
        // Config
        //------------------------------------------------------------------

        //------------------------------------------------------------------
        // Resources
        //------------------------------------------------------------------

        //------------------------------------------------------------------
        // Internal functions
        //------------------------------------------------------------------

        /// Setup the PLN convolution filter
        ///
        /// Sets up a filter kernel that corresponds to a combination of a
        /// Kasdin/Walter filter followed by a specified number of high pass
        /// filters.
        void        SetUpPLNConvFilter( PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, size_t TdVecLen );

    public:

        //------------------------------------------------------------------
        // Constructors/Destructor
        //------------------------------------------------------------------

        /// Construtor
        ///
        /// Creates a new instance of generic time deviation generator,
        /// based on the Kasdin/Walter powerlaw noise simulation approach.
        ///
        /// \param TdVecLen             Length of the simulated time deviation vectors
        /// \param TickLen              Time (in seconds) between two simulated samples
        /// \param PLN_FilterConf       Configuration for the powerlaw noise filter
        /// \param HP_FilterConf        Configuration for the high pass filter
        /// \param InterpolConf         Interpolation configuration
        GenericTdVecGen( size_t TdVecLen, double TickLen, PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, InterpolationConfig_t InterpolConf );

        /// Copy constructor
        ///
        /// \param other    The instance that should be copied
        GenericTdVecGen( const GenericTdVecGen& other );

        /// Destructor
        ~GenericTdVecGen();

        /// Clone method
        ///
        /// \return         Returns a cloned instance
        GenericTdVecGen*    Clone() const;  // Virtual constructor (copying)

        //------------------------------------------------------------------
        // Operators
        //------------------------------------------------------------------

        /// Assignment operator
        ///
        /// \param other    The instance that should be copied
        ///
        /// \return         Assigned instance
        GenericTdVecGen&    operator=( const GenericTdVecGen& other );

        //------------------------------------------------------------------
        // API
        //------------------------------------------------------------------

        /// Get a new time deviation vector
        ///
        /// This creates a new time deviation vector, that continuous either
        /// either from the last generated time deviation vector, or from the
        /// last configured fixpoint.
        ///
        /// \return     A new simulated time deviation vector
        TdVector    *GetNextVector();
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
