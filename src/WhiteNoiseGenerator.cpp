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
    : dist(0, sqrt(Qd) ), gen(eng,dist)
{
}

WhiteNoiseGenerator::~WhiteNoiseGenerator()
{
}

std::vector<double> *
WhiteNoiseGenerator::GetVector( size_t VecLen, size_t FillLen )
{
    std::vector<double> *pVec = new std::vector<double>(VecLen, 0.0);

    for( size_t i = 0; i < FillLen; i ++ )
    {
        (*pVec)[ i ]   = gen();
    }

    return pVec;
}
