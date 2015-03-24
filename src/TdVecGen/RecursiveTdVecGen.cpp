// =========================================================================
// Includes
// =========================================================================

#include "RecursiveTdVecGen.hpp"

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
RecursiveTdVecGen::SetUpHpConvFilter( HP_FilterConfig HpConf, size_t TdVecLen )
{
    switch( HpConf.Type )
    {
        case NO_FILTER:
        {
            EnableHpFilter  = false;
            FfdVecLen       = TdVecLen;
            break;
        }

        case BLACKMAN:
        {
            BmHpFilterImpResp bm( HpConf.FilterLen, HpConf.f_c_nom );

            bm.Augment( HpConf.Cnt );

            H   = FilterKernel( TdVecLen, bm );

            EnableHpFilter  = true;
            FfdVecLen       = H.GetFFT_RealSize();
            break;
        }
    }
}

RecursiveTdVecGen::RecursiveTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf )
    : TdVecGen( TdVecLen, TickLen, KwConf, InterpolConf )
{
    DataType    = FFD_DATA;

    SetUpHpConvFilter( HpConf, TdVecLen );
}

RecursiveTdVecGen::RecursiveTdVecGen( const RecursiveTdVecGen& other )
    : TdVecGen( other ),
      EnableHpFilter( other.EnableHpFilter ),
      DataType      ( other.DataType       )
{
}

RecursiveTdVecGen::~RecursiveTdVecGen()
{
}

RecursiveTdVecGen&
RecursiveTdVecGen::operator=( const RecursiveTdVecGen& other )
{
    TdVecGen::operator=( other );

    this->EnableHpFilter    = other.EnableHpFilter;
    this->DataType          = other.DataType;

    // By convention, always return *this
    return *this;
}

TdVector *
RecursiveTdVecGen::GetNextVector()
{
    // Generate new FFD vector
    FFT_RealVector *pw;
    pw = WhiteNoiseGen.GetFftVector( FfdVecLen, TdVecLen );

    if( EnableHpFilter )
    {
        ApplyConvFilter( pw );
    }

    ApplyRecursiveFilter( pw );

    TdVector *pTdVec  = ConstructTdVector( pw, DataType );

    if( !EnableHpFilter )
    {
        delete pw;
    }

    return pTdVec;
}

void
RecursiveTdVecGen::ResetToFixPoint( TdFixPoint fp )
{
    ResetRecursiveFilter();

    TdVecGen::ResetToFixPoint( fp );
}
