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

#ifndef GENERIC_TD_ORACLE_HPP_
#define GENERIC_TD_ORACLE_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdOracle.hpp"

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
class GenericTdOracle : public TdOracle
{
    private:

    protected:

        // -----------------------------------------------------------------
        // Types
        // -----------------------------------------------------------------

        /// Entry in the time deviation oracle
        typedef struct
        {
            TdEstChain      *pChain;        ///< Pointer to a time deviation estimator chain
            unsigned int    SeedOffset;     ///< Seed offset to have individual seeds for individual chains
        }
        ChainVecEntry;

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------

        std::vector<ChainVecEntry>  ChainVec;   ///< Storage for the individual time deviation estimator chains.

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------
        void    ClearChainStorage();

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------

        /// Constructor
        GenericTdOracle();

        /// Copy constructor
        ///
        /// \param other    The instance that should be copied
        GenericTdOracle( const GenericTdOracle& other );

        /// Destructor
        virtual ~GenericTdOracle();

    public:

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------

        /// Assignment operator
        ///
        /// \param other    The instance that should be assigned
        ///
        /// \return         An assigned instance
        GenericTdOracle&  operator=( const GenericTdOracle& other );

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------

        /// Enable the individual time deviation estimator to skip time intervals
        /// for requests in the distant future.
        void    EnableIntervalSkipping();

        /// Disable the skipping of time intervals in the individual time deviation
        /// estimator.
        void    DisableIntervalSkipping();

        /// Set a new seed for the random number generators
        ///
        /// \param Seed     The new seed for the random number generators
        void    SetSeed( unsigned int Seed );

        /// Request an estimate for the time deviation at a given point in time
        ///
        /// The resulting time deviation will be the sum of the individual results from
        /// all estimator chains in this oracle.
        ///
        /// \param t_now    The current time (in seconds)
        /// \param t_req    The time (in seconds) for which the time deviation is requested
        ///
        /// \return         Estimated time deviation (in seconds) at the requested time
        double  EstimateTD( double t_now, double t_req );
};

#endif
