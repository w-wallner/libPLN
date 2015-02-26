
#ifndef TDVECTORGENERATOR_CPP_
#define TDVECTORGENERATOR_CPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVectorGenerator.hpp"

#include "KwFilterImpResp.hpp"
#include "BmHpFilterImpResp.hpp"

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
// Function declarations
// =========================================================================

TdVectorGenerator::TdVectorGenerator( size_t TdVecLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf )
    : WhiteNoiseGen( KwConf.Seed, KwConf.Qd )
{
    // TODO: Filter construction

    KwFilterImpResp   kw( 10, 20, -1.0 );
    BmHpFilterImpResp bm( 11, 20, 0.1 );

    FilterKernel      KW( 10, kw, bm );


//    std::vector<double> *pTest = WhiteNoiseGen.GetVector( 10, 5 );
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
