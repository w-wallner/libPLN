// ============================================================================
///
/// \file
///
/// \brief  Guess of a future time deviation value
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

#ifndef TDGUESS_HPP_
#define TDGUESS_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdFixPoint.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Guess of a future time deviation value
///
/// If a request for a time deviation estimator lies in the distant future,
/// it won't calculate a continuous series of time deviation vectors, but
/// might just guess what a suitable time deviation value might be. This
/// class stores such guesses.
class  TdGuess
{
    private:

        // -----------------------------------------------------------------
        // House keeping
        // -----------------------------------------------------------------
        bool        active;     ///< Encodes whether or not the current
                                ///< instance is active.

        // -----------------------------------------------------------------
        // Resources
        // -------------------------------------------- ---------------------
        TdFixPoint  fp;         ///< The guessed future value

    public:

        // -----------------------------------------------------------------
        // Constructor
        // -----------------------------------------------------------------

        /// Constructor
        TdGuess();

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------

        /// Check whether this instance is currently active
        ///
        /// \return     Returns whether or not this instance is currently active
        bool        IsActive();

        /// Checks whether the current guess became already valid
        ///
        /// A guess becomes valid when the requested time (that was initially
        /// in the future) is now either in the presence or past.
        ///
        /// \param t_now    The current time (in seconds)
        ///
        /// \return     Returns wheter or not the guess became already valid
        bool        BecameValid( double t_now );

        /// Sets the current guess to the provided fixpoint
        ///
        /// \param fp   The new guess
        void        Set( TdFixPoint fp );

        /// Getter for the current saved guess value
        TdFixPoint  GetFP();

        /// Deactivates this guess instance
        void        Reset();
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
