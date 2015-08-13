// 
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
// 
// This file is part of libPLN.
// 
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
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
    : WpmChain( Seed + 0 ), WfmChain( Seed + 20 ), FfmChain( Seed + 30 ), RwChain( Seed + 40 )
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
