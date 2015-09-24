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

#include "Utils/FrequencyStabilityAnalysis.hpp"

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
TdVecGenFactory::CreateTdVecGen( SampleConfig_t SampleConf, WhiteNoiseConfig_t WhiteNoiseConf, PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, InterpolationConfig_t InterpolConf )
{
    TdVecGen*   pTdVecGen = NULL;

    switch( PLN_FilterConf.Implementation )
    {
        case RECURSIVE_FILTER:
        {
            if( PLN_FilterConf.alpha == FSA::ALPHA_WPM )
            {
                pTdVecGen    = new WpmTdVecGen( SampleConf, WhiteNoiseConf, HP_FilterConf, InterpolConf );
            }
            else if( PLN_FilterConf.alpha == FSA::ALPHA_WFM )
            {
                pTdVecGen    = new WfmTdVecGen( SampleConf, WhiteNoiseConf, HP_FilterConf, InterpolConf );
            }
            else if( PLN_FilterConf.alpha == FSA::ALPHA_RW )
            {
                pTdVecGen    = new RwTdVecGen( SampleConf, WhiteNoiseConf, HP_FilterConf, InterpolConf );
            }
            else
            {
                pTdVecGen    = new GenericTdVecGen( SampleConf, WhiteNoiseConf, PLN_FilterConf, HP_FilterConf, InterpolConf );
            }
            break;
        }

        default:
        case KASDIN_WALTER_FILTER:
        {
            pTdVecGen    = new GenericTdVecGen( SampleConf, WhiteNoiseConf, PLN_FilterConf, HP_FilterConf, InterpolConf );
            break;
        }
    }

    return pTdVecGen;
}
