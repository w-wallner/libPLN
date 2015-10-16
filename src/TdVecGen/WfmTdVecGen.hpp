// ============================================================================
///
/// \file
///
/// \brief  Implementation of time deviation generator for WFM noise using
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

#ifndef TDVECGEN_WFMTDGEN_CPP_
#define TDVECGEN_WFMTDGEN_CPP_

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

/// Time deviation vector generator for WFM noise using a recursive filter.
class WfmTdVecGen : public RecursiveTdVecGen
{
    private:

        // -----------------------------------------------------------------
        // Config
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
        /// \param Conf     Configuration
        WfmTdVecGen( TdVecGenConfig_t Conf );

        /// Copy constructor
        ///
        /// \param other    The instance from which we want to copy
        WfmTdVecGen( const WfmTdVecGen& other );

        /// Destructor
        ~WfmTdVecGen();

        /// Clone method
        ///
        /// \return         Returns a cloned instance
        WfmTdVecGen* Clone() const;  // Virtual constructor (copying)

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------

        /// Assignment operator
        ///
        /// \param other    The instance from which we want to copy
        WfmTdVecGen&  operator=( const WfmTdVecGen& other );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
