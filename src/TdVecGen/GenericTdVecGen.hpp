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

class GenericTdVecGen : public TdVecGen
{
    private:

        // Config

        // Resources

        // Internal functions
        void        SetUpKwHpConvFilter( PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, size_t TdVecLen );

    public:

        // Constructors/Destructor
        GenericTdVecGen( size_t TdVecLen, double TickLen, PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, InterpolationConfig_t InterpolConf );
        GenericTdVecGen( const GenericTdVecGen& other );
        ~GenericTdVecGen();

        GenericTdVecGen*    Clone() const;  // Virtual constructor (copying)

        // Operators
        GenericTdVecGen&    operator=( const GenericTdVecGen& other );

        // API
        TdVector    *GetNextVector();
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
