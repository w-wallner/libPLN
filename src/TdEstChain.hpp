// ============================================================================
///
/// \file
///
/// \brief  Chain of time deviation estimators
///
/// \ingroup module_td_estimator
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

#ifndef TDESTCHAIN_HPP_
#define TDESTCHAIN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEst/TdEstimator.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

/// Chain of time deviation estimators.
///
/// When several time deviation estimators are responsible for different
/// intervals of the frequency spectrum, they may be combined to cover the
/// full spectrum. This is the job of a time deviation estimator chain.
class TdEstChain
{
    private:

        // -----------------------------------------------------------------
        // Types
        // -----------------------------------------------------------------

        /// Entry in the time deviation estimator chain
        typedef struct
        {
            TdEstimator     *pEst;      ///< Pointer to a time deviation estimator
        }
        ChainEntry;

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------
        double              alpha;      ///< Alpha value for the type of powerlaw noise that the
                                        ///< time deviviation values from this chain correspond to.

        // -----------------------------------------------------------------
        // Housekeeping
        // -----------------------------------------------------------------

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------
        std::vector<ChainEntry>     Chain;      ///< Internal data structure to store the individual
                                                ///< time deviation estimators.

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------
        void    ClearChain();                   ///< Helper function to remove all time deviation
                                                ///< estimators stored in this chain.

    public:

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------

        /// Constructor
        ///
        /// Creates an empty chain.
        TdEstChain();

        /// Copy constructor
        ///
        /// \param other    The instance that should be copied
        TdEstChain( const TdEstChain& other );

        /// Destructor
        ~TdEstChain();

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------

        /// Assignment operator
        ///
        /// \param other    The instance that should be assigned
        ///
        /// \return         An assigned instance
        TdEstChain& operator= (const TdEstChain& other);

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------

        /// Enable the individual estimators of this chain to skip intervals for
        /// requests in the distant future.
        void    EnableIntervalSkipping();

        /// Disable interval skipping in the individual estimators of this chain.
        ///
        /// \remark This will greatly increase CPU and memory requirements.
        void    DisableIntervalSkipping();

        /// Set the seed for the random number generators
        ///
        /// \param  Seed    The new seed for the random number generators.
        ///                 The seed for each estimator will be increased by one
        ///                 compared to its predecessor.
        void    SetSeed( unsigned int Seed );

        /// Add a new estimator the estimator chain
        ///
        /// \param Conf     Configuration for the new estimator
        void    AddTdEstimator( TdEstimatorConfig Conf );

        /// Request an estimate for the time deviation at a given point in time
        ///
        /// The resulting time deviation will be the sum of the individual results from
        /// the estimator entries in this chain.
        ///
        /// \param t_now    The current time (in seconds)
        /// \param t_req    The time (in seconds) for which the time deviation is requested
        ///
        /// \return         Estimated time deviation (in seconds) at the requested time
        double  EstimateTD( double t_now, double t_req );
};

#endif
