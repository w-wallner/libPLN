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

TdOracle_AvgOsc20MHz::TdOracle_AvgOsc20MHz( unsigned int Seed )
    : WpmChain( SeedOffsetWpmChain + Seed ), WfmChain( SeedOffsetWfmChain + Seed ), FfmChain( SeedOffsetFfmChain + Seed ), RwChain( SeedOffsetRwChain + Seed )
{
}

TdOracle_AvgOsc20MHz::TdOracle_AvgOsc20MHz( const TdOracle_AvgOsc20MHz& other )
    : WpmChain( other.WpmChain ), WfmChain( other.WfmChain ), FfmChain( other.FfmChain ), RwChain( other.RwChain )
{
}

TdOracle_AvgOsc20MHz::~TdOracle_AvgOsc20MHz()
{
}

// Operators
TdOracle_AvgOsc20MHz&
TdOracle_AvgOsc20MHz::operator=( const TdOracle_AvgOsc20MHz& other )
{
    this->WpmChain  = other.WpmChain;
    this->WfmChain  = other.WfmChain;
    this->FfmChain  = other.FfmChain;
    this->RwChain   = other.RwChain;

    // By convention, always return *this
    return *this;
}

// API
void
TdOracle_AvgOsc20MHz::EnableIntervalSkipping()
{
    WpmChain.EnableIntervalSkipping();
    WfmChain.EnableIntervalSkipping();
    FfmChain.EnableIntervalSkipping();
    RwChain.EnableIntervalSkipping ();
}

void
TdOracle_AvgOsc20MHz::DisableIntervalSkipping()
{
    WpmChain.DisableIntervalSkipping();
    WfmChain.DisableIntervalSkipping();
    FfmChain.DisableIntervalSkipping();
    RwChain.DisableIntervalSkipping ();
}

void
TdOracle_AvgOsc20MHz::SetSeed( unsigned int Seed )
{
    WpmChain.SetSeed( SeedOffsetWpmChain + Seed );
    WfmChain.SetSeed( SeedOffsetWfmChain + Seed );
    FfmChain.SetSeed( SeedOffsetFfmChain + Seed );
    RwChain.SetSeed ( SeedOffsetRwChain  + Seed  );
}

double
TdOracle_AvgOsc20MHz::EstimateTD( double t_now, double t_req )
{
    double  TD = 0.0L;

    TD  += WpmChain.EstimateTD( t_now, t_req );
    TD  += WfmChain.EstimateTD( t_now, t_req );
    TD  += FfmChain.EstimateTD( t_now, t_req );
    TD  += RwChain.EstimateTD ( t_now, t_req );

    return TD;
}

}
