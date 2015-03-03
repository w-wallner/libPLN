// =========================================================================
// Includes
// =========================================================================

#include "WpmTdVecGen.hpp"

#include <numeric>

#include "BmHpFilterImpResp.hpp"
#include "TdVectorLinear.hpp"
#include "TdVectorCubSpline.hpp"

// Debugn only
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

WpmTdVecGen::WpmTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf )
    : TdVecGen( TdVecLen, TickLen, KwConf, InterpolConf )
{
    switch( HpConf.Type )
    {
        case NO_FILTER:
        {
            EnableHpFilter  = false;
            break;
        }

        case BLACKMAN:
        {
            EnableHpFilter  = true;
            BmHpFilterImpResp bm( HpConf.FilterLen, HpConf.f_c_nom );

            bm.Augment( HpConf.Cnt );

            H   = FilterKernel( TdVecLen, bm );
            break;
        }
    }

    // Set up resources
    this->pLastFFD = NULL;
}

WpmTdVecGen::~WpmTdVecGen()
{
    if( pLastFFD != NULL )
    {
        delete pLastFFD;
    }
}

void
WpmTdVecGen::ResetToFixPoint( TdFixPoint fp )
{
    if( pLastFFD != NULL )
    {
        delete pLastFFD;
        pLastFFD = NULL;
    }

    TdVecGen::ResetToFixPoint( fp );
}

TdVector *
WpmTdVecGen::GetNextVector()
{
    // Startup of overlapping convolution
    if( State == UNINITIALIZED )
    {
        if( EnableHpFilter )
        {
            // Set up Last FFD vector
            pLastFFD = WhiteNoiseGen.GetFftVector( H.GetFFT_RealSize(), TdVecLen );

            H.ApplyToSignal( pLastFFD );
        }

        State = INITIALIZED;
    }

    // Generate new FFD vector
    FFT_RealVector *pw;
    if( EnableHpFilter )
    {
         pw = WhiteNoiseGen.GetFftVector( H.GetFFT_RealSize(), TdVecLen );
    }
    else
    {
        pw = WhiteNoiseGen.GetFftVector( TdVecLen, TdVecLen );
    }

    if( EnableHpFilter )
    {
        H.ApplyToSignal( pw );

        // Handle overlapping convolution part
        std::transform( pw->begin(), pw->begin() + H.GetFilterLen(),
                        pLastFFD->begin() + TdVecLen, pw->begin(), std::plus<double>() );
    }

    TdVector *pTdVec;
    switch( IntpolType )
    {
        case LINEAR_INTERPOLATION:
        {
            pTdVec    = new TdVectorLinear( Last_t_end, Last_TD_nom, TickLen, pw, TdVecLen, TD_DATA );
            break;
        }
        case CUBIC_SPLINE_INTERPOLATION:
        {
            pTdVec    = new TdVectorCubSpline( Last_t_end, Last_TD_nom, TickLen, pw, TdVecLen, TD_DATA );
            break;
        }
    }

    // Remember FFD vector for next call
    if( EnableHpFilter )
    {
        delete pLastFFD;
        pLastFFD = pw;
    }

    Last_t_end  = pTdVec->GetEndTime();
    Last_TD_nom = pTdVec->GetEndTD();

    return pTdVec;
}
