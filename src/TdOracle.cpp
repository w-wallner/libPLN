// ============================================================================
///
/// \file
///
/// \brief  Time deviation oracle, a combination of multiple time deviation
///         estimator chains.
///
/// \ingroup module_td_oracle
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

// =========================================================================
// Includes
// =========================================================================

#include "TdOracle.hpp"

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

// -----------------------------------------------------------------
// Internal functions
// -----------------------------------------------------------------
void
TdOracle::ClearChainStorage()
{
    for( std::vector<ChainVecEntry>::iterator it = ChainVec.begin(); it < ChainVec.end(); ++it )
    {
        delete it->pChain;
    }

    ChainVec.clear();
}

TdOracle::TdOracle()
{
}

TdOracle::TdOracle( TdEstChain c )
{
    AddChain( c );
}

TdOracle::TdOracle( const TdOracle& other )
{
    for( std::vector<ChainVecEntry>::const_iterator it = other.ChainVec.begin(); it != other.ChainVec.end(); ++it )
    {
        ChainVecEntry   e;

        e.pChain    = new TdEstChain( *it->pChain );

        ChainVec.push_back( e );
    }
}

TdOracle::~TdOracle()
{
    ClearChainStorage();
}

void
TdOracle::AddChain( TdEstChain c )
{
    ChainVecEntry   e;

    e.pChain        = new TdEstChain( c );

    ChainVec.push_back( e );
}

// -----------------------------------------------------------------
// Operators
// -----------------------------------------------------------------

TdOracle&
TdOracle::operator=( const TdOracle& other )
{
    ClearChainStorage();

    for( std::vector<ChainVecEntry>::const_iterator it = other.ChainVec.begin(); it != other.ChainVec.end(); ++it )
    {
        ChainVecEntry   e;

        e.pChain    = new TdEstChain( *it->pChain );

        ChainVec.push_back( e );
    }

    // By convention, always return *this
    return *this;
}

// -----------------------------------------------------------------
// API
// -----------------------------------------------------------------

void
TdOracle::EnableIntervalSkipping()
{
    for( std::vector<ChainVecEntry>::const_iterator it = ChainVec.begin(); it != ChainVec.end(); ++it )
    {
        it->pChain->EnableIntervalSkipping();
    }
}

void
TdOracle::DisableIntervalSkipping()
{
    for( std::vector<ChainVecEntry>::const_iterator it = ChainVec.begin(); it != ChainVec.end(); ++it )
    {
        it->pChain->DisableIntervalSkipping();
    }
}


void
TdOracle::SetSeed( unsigned int Seed )
{
    for( std::vector<ChainVecEntry>::const_iterator it = ChainVec.begin(); it != ChainVec.end(); ++it )
    {
        it->pChain->SetSeed( Seed );
    }
}

double
TdOracle::EstimateTD( double t_now, double t_req )
{
    double  TD = 0.0L;

    for( std::vector<ChainVecEntry>::const_iterator it = ChainVec.begin(); it != ChainVec.end(); ++it )
    {
        TD  += it->pChain->EstimateTD( t_now, t_req );
    }

    return TD;
}
