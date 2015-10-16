// ============================================================================
///
/// \file
///
/// \brief  Implementation of time deviation generator using recursive filters.
///         This approach is valid for several classes of powerlaw noise, i.e.
///         those where alpha is an even number (WPM, WFM and RW noise).
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

#ifndef _RECURSIVE_TD_VEC_GEN_HPP_
#define _RECURSIVE_TD_VEC_GEN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVecGen/TdVecGen.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

/// Time deviation vector generator using recursive filters
///
/// Several classes of powerlaw noise can be implemented using recursive
/// filters instead of the generic Kasdin/Walter filter approach:
/// - WFM noise: The white noise generator produces ... white noise. Thus if
///     it is interpreted as fractional frequency deviation data, we don't
///     need any further filtering. In this case, we still need to calculate
///     the cumulative sum of the FFD data to get relative time deviation
///     data.
/// - RW noise: The filter to get RW-shaped powerlaw noise from white noise
///     is a cumulative sum. To get relative time deviation data, we need
///     to calculate again a cumulative sum.
/// - WPM noise: the filter to get WPM-shaped powerlaw noise from white noise
///     is a discrete derivative filter. This cancels with the cumulative sum
///     needed for the FFD->TD step. Thus, the random values from the white
///     noise generator can be directly interpreted as WPM noise.
///
/// These recursive filter options are implemented in the subclasses of this
/// class.
class RecursiveTdVecGen : public TdVecGen
{
    protected:

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------
        bool    EnableHpFilter;     ///< Configuration option to use a high pass filter

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------

        /// Reset the internal data structures of the recursive filter
        virtual void    ResetRecursiveFilter() = 0;

        /// Apply the recursive filter on the generated random white noise data
        virtual void    ApplyRecursiveFilter( FFT_RealVector *pw ) = 0;

    public:

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------

        /// Constructor
        ///
        /// \param Conf     Configuration
        RecursiveTdVecGen( TdVecGenConfig_t Conf );

        /// Copy constructor
        ///
        /// \param other    The instance from which we want to copy
        RecursiveTdVecGen( const RecursiveTdVecGen& other );

        /// Destructor
        virtual ~RecursiveTdVecGen();

        /// Clone method
        ///
        /// This method has to be overloaded by subclasses and needs to return a pointer
        /// to a subclass instance.
        virtual RecursiveTdVecGen* Clone() const = 0;  // Virtual constructor (copying)

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------

        /// Assignment operator
        ///
        /// \param other    The instance from which we want to copy
        RecursiveTdVecGen&  operator=( const RecursiveTdVecGen& other );

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------
        TdVector        *GetNextVector();
        virtual void    ResetToFixPoint( TdFixPoint fp );
};

#endif
