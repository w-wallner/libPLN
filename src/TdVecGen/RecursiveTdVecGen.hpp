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

class RecursiveTdVecGen : public TdVecGen
{
    protected:

        // Config
        bool                        EnableHpFilter;
        TdVector::TdVecDataType     DataType;

        // Internal functions
        virtual void    ResetRecursiveFilter() = 0;
        virtual void    ApplyRecursiveFilter( FFT_RealVector *pw ) = 0;

    public:

        // Constructors/Destructor
        RecursiveTdVecGen( size_t TdVecLen, double TickLen, PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, InterpolationConfig_t InterpolConf );
        RecursiveTdVecGen( const RecursiveTdVecGen& other );
        virtual ~RecursiveTdVecGen();

        virtual RecursiveTdVecGen* Clone() const = 0;  // Virtual constructor (copying)

        // Operators
        RecursiveTdVecGen&  operator=( const RecursiveTdVecGen& other );

        // API
        TdVector        *GetNextVector();
        virtual void    ResetToFixPoint( TdFixPoint fp );
};

#endif
