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

// =========================================================================
// Includes
// =========================================================================

#include "AverageOscillator_20MHz.hpp"

namespace AverageOscillator_20MHz
{

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef enum
{
    SeedOffsetWpmChain  = 0,
    SeedOffsetFpmChain  = 10,
    SeedOffsetWfmChain  = 20,
    SeedOffsetFfmChain  = 30,
    SeedOffsetRwChain   = 40,
}
tSeedOffset;

// =========================================================================
// Global variables
// =========================================================================

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

TdOracle_AvgOsc20MHz::TdOracle_AvgOsc20MHz( unsigned int Seed, bool EnableIntervalSkipping )
    : TdOracle()
{
    ChainVecEntry   WpmEntry;
    ChainVecEntry   WfmEntry;
    ChainVecEntry   FfmEntry;
    ChainVecEntry   RwEntry;

    WpmEntry.pChain     = new TdEstChain_WPM( SeedOffsetWpmChain, Seed, EnableIntervalSkipping );

    WfmEntry.pChain     = new TdEstChain_WFM( SeedOffsetWfmChain, Seed, EnableIntervalSkipping );

    FfmEntry.pChain     = new TdEstChain_FFM( SeedOffsetFfmChain, Seed, EnableIntervalSkipping );

    RwEntry.pChain      = new TdEstChain_RW ( SeedOffsetRwChain,  Seed, EnableIntervalSkipping );

    ChainVec.push_back( WpmEntry );
    ChainVec.push_back( WfmEntry );
    ChainVec.push_back( FfmEntry );
    ChainVec.push_back( RwEntry  );
}

TdOracle_AvgOsc20MHz::TdOracle_AvgOsc20MHz( const TdOracle_AvgOsc20MHz& other )
    : TdOracle( other )
{
}

TdOracle_AvgOsc20MHz::~TdOracle_AvgOsc20MHz()
{
}

}
