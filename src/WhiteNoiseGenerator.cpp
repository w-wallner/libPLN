// =========================================================================
// Includes
// =========================================================================

#include "WhiteNoiseGenerator.hpp"

#include <algorithm>

// Debug only
#include <iostream>

using namespace std;

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
