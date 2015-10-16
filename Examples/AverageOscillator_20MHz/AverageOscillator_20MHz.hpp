// ============================================================================
///
/// \file
///
/// \brief  Example of an average oscillator
///
/// The example implements the Allan Deviation as given in the publication [1].
///
/// [1]     A Novel, High Resolution Oscillator Model for DES Systems
///         Georg Gaderer, et al
///         Proceedings of the Frequency Control Symposium, 2008
///
/// \ingroup module_examples_avg_osc
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

#ifndef AVERAGE_OSCILLATOR_20MHZ_HPP_
#define AVERAGE_OSCILLATOR_20MHZ_HPP_

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

class cAvgOsc20MHz : public TdOracle
{
    public:

        // Types
        class TdEstChain_WPM : public TdEstChain
        {
         public:
             // Constructors/Destructor
             TdEstChain_WPM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping );

             // Getters
             static TdEstimatorConfig   GetConfig_20MHz(unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_1MHz (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_10kHz(unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_100Hz(unsigned int Seed, bool EnableIntervalSkipping);
        };

        class TdEstChain_FPM : public TdEstChain
        {
         public:
             // Constructors/Destructor
            TdEstChain_FPM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping );

             // Getters
             static TdEstimatorConfig   GetConfig_20MHz(unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_1MHz (unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_10kHz(unsigned int Seed, bool EnableIntervalSkipping);
             static TdEstimatorConfig   GetConfig_100Hz(unsigned int Seed, bool EnableIntervalSkipping);
        };

        class TdEstChain_WFM : public TdEstChain
        {
         public:
             // Constructors/Destructor
             TdEstChain_WFM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping );

             // Getters
             static TdEstimatorConfig   GetConfig_100Hz(unsigned int Seed, bool EnableIntervalSkipping);
        };

        class TdEstChain_FFM : public TdEstChain
        {
         public:
             // Constructors/Destructor
             TdEstChain_FFM( unsigned int SeedOffset, unsigned int Seed, bool EnableIntervalSkipping );

             // Getters
             static TdEstimatorConfig   GetConfig_100Hz(unsigned int Seed, bool EnableIntervalSkipping);
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
        };

    private:

        // Config

        // Resources

    public:

        // Constructors/Destructor
        cAvgOsc20MHz( unsigned int Seed, bool EnableIntervalSkipping );
};

// =========================================================================
// Function declarations
// =========================================================================

}

#endif
