// ============================================================================
///
/// \file
///
/// \brief  Examples of a watch quartz (low precision)
///
/// In the publication [1], the last figure shows the Allan Deviation of
/// motor and quartz of several different watches.
/// The Allan Deviation implemented in this example is shaped to match
/// that of Watch B in the mentioned graph.
///
/// [1]     The Accuracy and Stability of Quartz Watches
///         Michael Lombardi
///         Horological Journal, February 2008
///
/// \ingroup module_examples_watch_quartz
///
// ============================================================================

// ============================================================================
//
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
//
// This file is part of libPLN.
//
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================

#ifndef LIBPLN_EXAMPLES_WATCH_QUARTZ_20MHZ_WATCH_QUARTZ_20MHZ_HPP_
#define LIBPLN_EXAMPLES_WATCH_QUARTZ_20MHZ_WATCH_QUARTZ_20MHZ_HPP_

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
