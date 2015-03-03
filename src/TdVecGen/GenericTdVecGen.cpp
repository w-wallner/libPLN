// =========================================================================
// Includes
// =========================================================================

#include "GenericTdVecGen.hpp"

#include <numeric>

#include "KwFilterImpResp.hpp"
#include "BmHpFilterImpResp.hpp"
#include "TdVectorLinear.hpp"
#include "TdVectorCubSpline.hpp"

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

GenericTdVecGen::GenericTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf )
    : TdVecGen( TdVecLen, TickLen, KwConf, InterpolConf )
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

    // Set up resources
    this->pLastFFD = NULL;
}

GenericTdVecGen::~GenericTdVecGen()
{
    if( pLastFFD != NULL )
    {
        delete pLastFFD;
    }
}

void
GenericTdVecGen::ResetToFixPoint( TdFixPoint fp )
{
    if( pLastFFD != NULL )
    {
        delete pLastFFD;
        pLastFFD = NULL;
    }

    TdVecGen::ResetToFixPoint( fp );
}

TdVector *
GenericTdVecGen::GetNextVector()
{
    // Startup of overlapping convolution
    if( State == UNINITIALIZED )
    {
        // Set up Last FFD vector
        pLastFFD = WhiteNoiseGen.GetFftVector( H.GetFFT_RealSize(), TdVecLen );
        H.ApplyToSignal( pLastFFD );

        State = INITIALIZED;
    }

    // Generate new FFD vector
    FFT_RealVector *pw = WhiteNoiseGen.GetFftVector( H.GetFFT_RealSize(), TdVecLen );
    H.ApplyToSignal( pw );

    // Handle overlapping convolution part
    std::transform( pw->begin(), pw->begin() + H.GetFilterLen(),
                    pLastFFD->begin() + TdVecLen, pw->begin(), std::plus<double>() );

    TdVector *pTdVec;
    switch( IntpolType )
    {
        case LINEAR_INTERPOLATION:
        {
            pTdVec    = new TdVectorLinear( Last_t_end, Last_TD_nom, TickLen, pw, TdVecLen );
            break;
        }
        case CUBIC_SPLINE_INTERPOLATION:
        {
            pTdVec    = new TdVectorCubSpline( Last_t_end, Last_TD_nom, TickLen, pw, TdVecLen );
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
