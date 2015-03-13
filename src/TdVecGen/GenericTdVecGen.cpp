// =========================================================================
// Includes
// =========================================================================

#include "GenericTdVecGen.hpp"

#include <numeric>

#include "KwFilterImpResp.hpp"
#include "BmHpFilterImpResp.hpp"

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

void
GenericTdVecGen::SetUpKwHpConvFilter( KW_FilterConfig KwConf, HP_FilterConfig HpConf, size_t TdVecLen )
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

    FfdVecLen   = H.GetFFT_RealSize();
}

GenericTdVecGen::GenericTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf )
    : TdVecGen( TdVecLen, TickLen, KwConf, InterpolConf )
{
    SetUpKwHpConvFilter( KwConf, HpConf, TdVecLen );
}

GenericTdVecGen::~GenericTdVecGen()
{
}

TdVector *
GenericTdVecGen::GetNextVector()
{
    // Generate new FFD vector
    FFT_RealVector *pw;
    pw = WhiteNoiseGen.GetFftVector( FfdVecLen, TdVecLen );

    ApplyConvFilter( pw );

    TdVector *pTdVec = ConstructTdVector( pw, FFD_DATA );

    return pTdVec;
}
