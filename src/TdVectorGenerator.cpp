
#ifndef TDVECTORGENERATOR_CPP_
#define TDVECTORGENERATOR_CPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVectorGenerator.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

TdVectorGenerator::TdVectorGenerator( size_t TdVecLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf )
    : WhiteNoiseGen( KwConf.Seed, KwConf.Qd )
{
    // TODO: Filter construction

    std::vector<double> *pTest = WhiteNoiseGen.GetVector( 10, 5 );
}

void
TdVectorGenerator::ResetToFixPoint( TdFixPoint fp )
{
    // TODO
}

TdVector *
TdVectorGenerator::GetNextVector()
{
    TdVector *pTdVec    = new TdVector();

    return pTdVec;
}

#endif
