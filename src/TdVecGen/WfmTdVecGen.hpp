// ============================================================================
///
/// \file
///
/// \brief  TODO
///
/// TODO
///
/// \ingroup module_main
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

class WfmTdVecGen : public RecursiveTdVecGen
{
    private:

        // Config

        // Internal functions
        void    ResetRecursiveFilter();
        void    ApplyRecursiveFilter( FFT_RealVector *pw );

    public:

        // Constructors/Destructor
        WfmTdVecGen( size_t TdVecLen, double TickLen, PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, InterpolationConfig_t InterpolConf );
        WfmTdVecGen( const WfmTdVecGen& other );
        ~WfmTdVecGen();

        WfmTdVecGen* Clone() const;  // Virtual constructor (copying)

        // Operators
        WfmTdVecGen&  operator=( const WfmTdVecGen& other );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
