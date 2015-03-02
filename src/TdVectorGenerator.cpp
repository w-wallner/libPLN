
#ifndef TDVECTORGENERATOR_CPP_
#define TDVECTORGENERATOR_CPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVectorGenerator.hpp"

#include "KwFilterImpResp.hpp"
#include "BmHpFilterImpResp.hpp"

#include <numeric>

// Debug only
#include <iostream>
using namespace std;

#include "VectorOutput.hpp"

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
    size_t  MaxDataLen  = 10;

    // Set up filter kernel
    KwFilterImpResp   kw( KwConf.FilterLen, KwConf.alpha );

    switch( HpConf.Type )
    {
        case NO_FILTER:
        {
            H   = FilterKernel( MaxDataLen, kw );
            break;
        }

        case BLACKMAN:
        {
            BmHpFilterImpResp bm( HpConf.FilterLen, HpConf.f_c_nom );

            bm.Augment( HpConf.Cnt );

            H   = FilterKernel( MaxDataLen, kw, bm );
            break;
        }
    }
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

    FFT_RealVector    *pw = WhiteNoiseGen.GetVector( H.GetResponseLen(), H.GetMaxDataLen() );

    H.ApplyToSignal( pw );

//    std::vector<double> TD( pw->size() );


//    std::partial_sum( pw->begin(), pw->end(), TD.begin() );


    return pTdVec;
}

#endif
