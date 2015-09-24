// ============================================================================
///
/// \file
///
/// \brief
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

// =========================================================================
// Includes
// =========================================================================

#include "TdVecGenFactory.hpp"

#include "GenericTdVecGen.hpp"
#include "WpmTdVecGen.hpp"
#include "WfmTdVecGen.hpp"
#include "RwTdVecGen.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Global variables
// =========================================================================

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

TdVecGen*
TdVecGenFactory::CreateTdVecGen( PLN_FilterImpl_t PLN_FilterImpl, size_t TdVecLen, double TickLen, PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, InterpolationConfig_t InterpolConf )
{
    TdVecGen*   pTdVecGen = NULL;

    switch( PLN_FilterImpl )
    {
        case RECURSIVE_FILTER:
        {
            if( PLN_FilterConf.alpha == 2.0L )
            {
                pTdVecGen    = new WpmTdVecGen( TdVecLen, TickLen, PLN_FilterConf, HP_FilterConf, InterpolConf );
            }
            else if( PLN_FilterConf.alpha == 0.0L )
            {
                pTdVecGen    = new WfmTdVecGen( TdVecLen, TickLen, PLN_FilterConf, HP_FilterConf, InterpolConf );
            }
            else if( PLN_FilterConf.alpha == -2.0L )
            {
                pTdVecGen    = new RwTdVecGen( TdVecLen, TickLen, PLN_FilterConf, HP_FilterConf, InterpolConf );
            }
            else
            {
                pTdVecGen    = new GenericTdVecGen( TdVecLen, TickLen, PLN_FilterConf, HP_FilterConf, InterpolConf );
            }
            break;
        }

        default:
        case KASDIN_WALTER_FILTER:
        {
            pTdVecGen    = new GenericTdVecGen( TdVecLen, TickLen, PLN_FilterConf, HP_FilterConf, InterpolConf );
            break;
        }
    }

    return pTdVecGen;
}
