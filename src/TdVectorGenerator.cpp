
// =========================================================================
// Includes
// =========================================================================

#include "TdVectorGenerator.hpp"

#include "KwFilterImpResp.hpp"
#include "BmHpFilterImpResp.hpp"
#include "TdVectorLinear.hpp"
#include "TdVectorCubSpline.hpp"

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
// Global variables
// =========================================================================

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

TdVectorGenerator::TdVectorGenerator( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf )
    : WhiteNoiseGen( KwConf.Seed, KwConf.Qd )
{
    // Set up filter kernel
    KwFilterImpResp   kw( KwConf.FilterLen, KwConf.alpha );

    switch( HpConf.Type )
    {
        case NO_FILTER:
        {
            H   = FilterKernel( TdVecLen, kw );
            break;
        }

        case BLACKMAN:
        {
            BmHpFilterImpResp bm( HpConf.FilterLen, HpConf.f_c_nom );

            bm.Augment( HpConf.Cnt );

            H   = FilterKernel( TdVecLen, kw, bm );
            break;
        }
    }

    // Set up config
    this->TickLen       = TickLen;
    this->IntpolType    = InterpolConf.Type;

    this->State         = UNINITIALIZED;
    this->Last_t_end    = 0.0;
    this->Last_TD_nom   = 0.0;

    // Set up house keeping
    this->pLastFFD      = NULL;
}

TdVectorGenerator::~TdVectorGenerator()
{
    if( pLastFFD != NULL )
    {
        delete pLastFFD;
    }
}

void
TdVectorGenerator::ResetToFixPoint( TdFixPoint fp )
{
    this->State         = UNINITIALIZED;
    this->Last_t_end    = fp.Get_t();
    this->Last_TD_nom   = fp.GetTD_nom();

    if( pLastFFD != NULL )
    {
        delete pLastFFD;
        pLastFFD = NULL;
    }
}

TdVector *
TdVectorGenerator::GetNextVector()
{
    // Startup of overlapping convolution
    if( State == UNINITIALIZED )
    {
        // Set up Last FFD vector
        pLastFFD = WhiteNoiseGen.GetFftVector( H.GetFFT_RealSize(), H.GetMaxDataLen() );
        H.ApplyToSignal( pLastFFD );

        State = INITIALIZED;
    }

    // Generate new FFD vector
    FFT_RealVector *pw = WhiteNoiseGen.GetFftVector( H.GetFFT_RealSize(), H.GetMaxDataLen() );
    H.ApplyToSignal( pw );

    // Handle overlapping convolution part
    std::transform( pw->begin(), pw->begin() + H.GetFilterLen(),
                    pLastFFD->begin() + H.GetMaxDataLen(), pw->begin(), std::plus<double>() );

    TdVector *pTdVec;
    switch( IntpolType )
    {
        case LINEAR_INTERPOLATION:
        {
            pTdVec    = new TdVectorLinear( Last_t_end, Last_TD_nom, TickLen, pw, H.GetMaxDataLen() );
            break;
        }
        case CUBIC_SPLINE_INTERPOLATION:
        {
            pTdVec    = new TdVectorCubSpline( Last_t_end, Last_TD_nom, TickLen, pw, H.GetMaxDataLen() );
            break;
        }
    }

    // Remember FFD vector for next call
    delete pLastFFD;
    pLastFFD = pw;

    Last_t_end  = pTdVec->GetEndTime();
    Last_TD_nom = pTdVec->GetEndTD();

    return pTdVec;
}
