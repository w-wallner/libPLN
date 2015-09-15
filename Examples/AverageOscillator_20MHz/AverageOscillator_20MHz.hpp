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

#ifndef AVERAGEOSCILLATOR_20MHZ_HPP_
#define AVERAGEOSCILLATOR_20MHZ_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "libPLN.hpp"

namespace AverageOscillator_20MHz
{

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdOracle_AvgOsc20MHz : public TdOracle
{
    public:

        // Types
        class TdEstChain_WPM : public TdEstChain
        {
         public:
             // Constructors/Destructor
             TdEstChain_WPM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping );

             // Getters
             static TdEstimatorConfig   GetConfig_WPM_20MHz(unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_WPM_1MHz (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_WPM_10kHz(unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_WPM_100Hz(unsigned int Seed, bool EnableIntervalSkipping);
        };

        class TdEstChain_FPM : public TdEstChain
        {
         public:
             // Constructors/Destructor
            TdEstChain_FPM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping );

             // Getters
             static TdEstimatorConfig   GetConfig_FPM_20MHz(unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_FPM_1MHz (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_FPM_10kHz(unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_FPM_100Hz(unsigned int Seed, bool EnableIntervalSkipping);
        };

        class TdEstChain_WFM : public TdEstChain
        {
         public:
             // Constructors/Destructor
             TdEstChain_WFM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping );

             // Getters
             static TdEstimatorConfig   GetConfig_WFM_100Hz(unsigned int Seed, bool EnableIntervalSkipping);
        };

        class TdEstChain_FFM : public TdEstChain
        {
         public:
             // Constructors/Destructor
             TdEstChain_FFM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping );

             // Getters
             static TdEstimatorConfig   GetConfig_FFM_100Hz(unsigned int Seed, bool EnableIntervalSkipping);
        };

        class TdEstChain_RW : public TdEstChain
        {
         public:
             // Constructors/Destructor
             TdEstChain_RW( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping );

             // Getters
             static TdEstimatorConfig   GetConfig_RW_100Hz(unsigned int Seed, bool EnableIntervalSkipping);
        };

    private:

        // Config

        // Resources

    public:

        // Constructors/Destructor
        TdOracle_AvgOsc20MHz( unsigned int Seed, bool EnableIntervalSkipping );
};

// =========================================================================
// Function declarations
// =========================================================================

}

#endif
