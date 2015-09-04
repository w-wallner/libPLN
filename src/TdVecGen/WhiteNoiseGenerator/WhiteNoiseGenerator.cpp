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

WhiteNoiseGenerator::WhiteNoiseGenerator( unsigned int Seed, double Qd )
    : eng(Seed), dist(0.0L, sqrt(Qd) ), gen(eng,dist)
{
}

WhiteNoiseGenerator::~WhiteNoiseGenerator()
{
}

FFT_RealVector *
WhiteNoiseGenerator::GetFftVector( size_t VecLen, size_t FillLen )
{
    assert( VecLen >= FillLen );

    FFT_RealVector *pVec = new FFT_RealVector(VecLen, 0.0);

    for( size_t i = 0; i < FillLen; i ++ )
    {
        (*pVec)[ i ]   = gen();
    }

    return pVec;
}

std::vector<double> *
WhiteNoiseGenerator::GetStdVector( size_t VecLen, size_t FillLen )
{
    std::vector<double> *pVec = new std::vector<double>(VecLen, 0.0);

    for( size_t i = 0; i < FillLen; i ++ )
    {
        (*pVec)[ i ]   = gen();
    }

    return pVec;
}

void
WhiteNoiseGenerator::SetSeed( unsigned int Seed )
{
    eng.seed( Seed );
    gen.engine() = eng;
}

double
WhiteNoiseGenerator::GetRandomValue()
{
    return gen();
}
