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

#include "WhiteNoiseGenerator.hpp"

#include <algorithm>
#include <cassert>

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

WhiteNoiseGenerator::WhiteNoiseGenerator( WhiteNoiseConfig_t WhiteNoiseConfig )
{
    pGen = new GEN( ENG(WhiteNoiseConfig.Seed), DIST(0.0L, sqrt(WhiteNoiseConfig.Qd)) );
}

WhiteNoiseGenerator::WhiteNoiseGenerator( const WhiteNoiseGenerator& other )
{
    pGen = (other.pGen != NULL) ? new GEN( *other.pGen ) : NULL;
}

WhiteNoiseGenerator::~WhiteNoiseGenerator()
{
    delete pGen;
    pGen = NULL;
}

WhiteNoiseGenerator&
WhiteNoiseGenerator::operator=( const WhiteNoiseGenerator& other )
{
    pGen = (other.pGen != NULL) ? new GEN( *other.pGen ) : NULL;

    // By convention, always return *this
    return *this;
}

FFT_RealVector *
WhiteNoiseGenerator::GetFftVector( size_t VecLen, size_t FillLen )
{
    assert( FillLen <= VecLen );

    FFT_RealVector *pVec = new FFT_RealVector(VecLen, 0.0);

    for( size_t i = 0; i < FillLen; i ++ )
    {
        (*pVec)[ i ]   = (*pGen)();
    }

    return pVec;
}

RealVector *
WhiteNoiseGenerator::GetStdVector( size_t VecLen, size_t FillLen )
{
    assert( FillLen <= VecLen );

    RealVector *pVec = new RealVector(VecLen, 0.0);

    for( size_t i = 0; i < FillLen; i ++ )
    {
        (*pVec)[ i ]   = (*pGen)();
    }

    return pVec;
}

void
WhiteNoiseGenerator::SetSeed( unsigned int Seed )
{
    pGen->engine() = ENG(Seed);
}

double
WhiteNoiseGenerator::GetRandomValue()
{
    return (*pGen)();
}
