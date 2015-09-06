// ============================================================================
///
/// \file
///
/// \brief  Time deviation oracle, a combination of multiple time deviation
///         estimator chains.
///
/// \ingroup module_td_oracle
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

#ifndef TDORACLE_HPP_
#define TDORACLE_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEstChain.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

/// Time deviation oracle, a combination of multiple time deviation
/// estimator chains.
class TdOracle
{
    private:

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------

    protected:

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------

        /// Constructor
        TdOracle();

        /// Copy constructor
        ///
        /// \param other    The instance that should be copied
        TdOracle( const TdOracle& other );

        /// Destructor
        virtual ~TdOracle() = 0;

    public:

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------

        /// Assignment operator
        ///
        /// \param other    The instance that should be assigned
        ///
        /// \return         An assigned instance
        TdOracle&  operator=( const TdOracle& other );

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------

        /// Enable the individual time deviation estimator to skip time intervals
        /// for requests in the distant future.
        virtual void    EnableIntervalSkipping() = 0;

        /// Disable the skipping of time intervals in the individual time deviation
        /// estimator.
        virtual void    DisableIntervalSkipping() = 0;

        /// Set a new seed for the random number generators
        ///
        /// \param Seed     The new seed for the random number generators
        virtual void    SetSeed( unsigned int Seed ) = 0;

        /// Request an estimate for the time deviation at a given point in time
        ///
        /// The resulting time deviation will be the sum of the individual results from
        /// all estimator chains in this oracle.
        ///
        /// \param t_now    The current time (in seconds)
        /// \param t_req    The time (in seconds) for which the time deviation is requested
        ///
        /// \return         Estimated time deviation (in seconds) at the requested time
        virtual double  EstimateTD( double t_now, double t_req ) = 0;
};

#endif
