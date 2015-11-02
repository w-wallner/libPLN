// ============================================================================
///
/// \file
///
/// \brief  Implementation of 'fixpoints': ordered pairs of the form
///         (real-time, time deviation).
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

#ifndef LIBPLN_SRC_TDEST_TDFIXPOINT_HPP_
#define LIBPLN_SRC_TDEST_TDFIXPOINT_HPP_

// =========================================================================
// Includes
// =========================================================================

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Class to store fixpoints: ordered pairs of the form
/// (real-time, time deviation).
///
/// A fixpoint is an ordered pair consisting of the real time in seconds (t), and the
/// time deviation (TD) that point in time.
class TdFixPoint
{
    private:

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------
        double  t;          ///< Real time (in seconds)
        double  TD;         ///< Time deviation

    public:

        // -----------------------------------------------------------------
        // Constructor
        // -----------------------------------------------------------------

        /// Constructor
        ///
        /// \param t            Real time (in seconds)
        /// \param TD           Time deviation
        TdFixPoint( double t, double TD );

        /// Copy constructor
        ///
        /// \param other        The instance that we want to copy
        TdFixPoint( const TdFixPoint& other );

        /// Assignment operator
        ///
        /// \param other        The instance that we want to assign
        ///
        /// \return     An assigned instance
        TdFixPoint&     operator= (const TdFixPoint& other);

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------

        /// Getter for the real time stored in this fixpoint
        double  Get_t() const;

        /// Getter for the time deviation stored in this fixpoint
        double  GetTD() const;
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
