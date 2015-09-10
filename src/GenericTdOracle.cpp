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

#include "GenericTdOracle.hpp"

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
GenericTdOracle::ClearChainStorage()
{
    for( std::vector<ChainVecEntry>::iterator it = ChainVec.begin(); it < ChainVec.end(); ++it )
    {
        delete it->pChain;
    }

    ChainVec.clear();
}

// -----------------------------------------------------------------
// Constructors/Destructor
// -----------------------------------------------------------------

GenericTdOracle::GenericTdOracle()
    : TdOracle()
{
}

GenericTdOracle::GenericTdOracle( const GenericTdOracle& other )
    : TdOracle( other )
{
    for( std::vector<ChainVecEntry>::const_iterator it = other.ChainVec.begin(); it != other.ChainVec.end(); ++it )
    {
        ChainVecEntry   e;

        e.pChain        = new TdEstChain( *it->pChain );
        e.SeedOffset    = it->SeedOffset;

        ChainVec.push_back( e );
    }
}

GenericTdOracle::~GenericTdOracle()
{
    ClearChainStorage();
}

// -----------------------------------------------------------------
// Operators
// -----------------------------------------------------------------

GenericTdOracle&
GenericTdOracle::operator=( const GenericTdOracle& other )
{
    ClearChainStorage();

    for( std::vector<ChainVecEntry>::const_iterator it = other.ChainVec.begin(); it != other.ChainVec.end(); ++it )
    {
        ChainVecEntry   e;

        e.pChain        = new TdEstChain( *it->pChain );
        e.SeedOffset    = it->SeedOffset;

        ChainVec.push_back( e );
    }

    // By convention, always return *this
    return *this;
}

// -----------------------------------------------------------------
// API
// -----------------------------------------------------------------

void
GenericTdOracle::EnableIntervalSkipping()
{
    for( std::vector<ChainVecEntry>::const_iterator it = ChainVec.begin(); it != ChainVec.end(); ++it )
    {
        it->pChain->EnableIntervalSkipping();
    }
}

void
GenericTdOracle::DisableIntervalSkipping()
{
    for( std::vector<ChainVecEntry>::const_iterator it = ChainVec.begin(); it != ChainVec.end(); ++it )
    {
        it->pChain->DisableIntervalSkipping();
    }
}


void
GenericTdOracle::SetSeed( unsigned int Seed )
{
    for( std::vector<ChainVecEntry>::const_iterator it = ChainVec.begin(); it != ChainVec.end(); ++it )
    {
        it->pChain->SetSeed( Seed + it->SeedOffset );
    }
}

double
GenericTdOracle::EstimateTD( double t_now, double t_req )
{
    double  TD = 0.0L;

    for( std::vector<ChainVecEntry>::const_iterator it = ChainVec.begin(); it != ChainVec.end(); ++it )
    {
        TD  += it->pChain->EstimateTD( t_now, t_req );
    }

    return TD;
}
