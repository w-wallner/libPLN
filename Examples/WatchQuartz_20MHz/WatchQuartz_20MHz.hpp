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

#ifndef WATCH_QUARTZ_20MHZ_HPP_
#define WATCH_QUARTZ_20MHZ_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "libPLN.hpp"

namespace LibPLN_Examples
{

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class cWatchQuartz_20MHz : public TdOracle
{
    public:

        // Types
        class TdEstChain_WFM : public TdEstChain
        {
         public:
             // Constructors/Destructor
             TdEstChain_WFM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping );

             // Getters
             static TdEstimatorConfig   GetConfig_20MHz (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_1MHz  (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_10kHz (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_100Hz (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_1Hz   (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_10mHz (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_100uHz(unsigned int Seed, bool EnableIntervalSkipping);
        };

        class TdEstChain_RW : public TdEstChain
        {
         public:
             // Constructors/Destructor
             TdEstChain_RW( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping );

             // Getters
             static TdEstimatorConfig   GetConfig_100Hz (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_1Hz   (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_10mHz (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_100uHz(unsigned int Seed, bool EnableIntervalSkipping);
        };

    private:

        // Config

        // Resources

    public:

        // Constructors/Destructor
        cWatchQuartz_20MHz( unsigned int Seed, bool EnableIntervalSkipping );
};

// =========================================================================
// Function declarations
// =========================================================================

}

#endif
