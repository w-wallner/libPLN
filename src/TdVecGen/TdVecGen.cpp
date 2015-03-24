
// =========================================================================
// Includes
// =========================================================================

#include "TdVecGen.hpp"

#include <algorithm>

#include "TdVectorLinear.hpp"
#include "TdVectorCubSpline.hpp"

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

void
TdVecGen::DisableConvFilter()
{
    ConvState   = UNINITIALIZED;
    FfdVecLen   = 0;
    pLastFFD    = NULL;
}

void
TdVecGen::InitConvFilter()
{
    if( ConvState == UNINITIALIZED )
    {
        // Set up Last FFD vector
        pLastFFD = WhiteNoiseGen.GetFftVector( FfdVecLen, TdVecLen );

        H.ApplyToSignal( pLastFFD );

        ConvState = INITIALIZED;
    }
}

void
TdVecGen::ApplyConvFilter( FFT_RealVector *pw )
{
    // Startup of overlapping convolution
    InitConvFilter();

    H.ApplyToSignal( pw );

    // Handle overlapping convolution part
    std::transform( pw->begin(), pw->begin() + H.GetFilterLen(),
                    pLastFFD->begin() + TdVecLen, pw->begin(), std::plus<double>() );

    // Remember FFD vector for next call
    delete pLastFFD;
    pLastFFD = pw;
}

void
TdVecGen::ResetConvFilter()
{
    ConvState = UNINITIALIZED;

    if( pLastFFD != NULL )
    {
        delete pLastFFD;
        pLastFFD = NULL;
    }
}

TdVector *
TdVecGen::ConstructTdVector( FFT_RealVector *pData, TdVecDataType DataType )
{
    TdVector *pTdVec = NULL;

    switch( IntpolType )
    {
    default:
        case LINEAR_INTERPOLATION:
        {
            pTdVec    = new TdVectorLinear( Last_t_end, Last_TD_nom, TickLen, pData, TdVecLen, DataType );
            break;
        }
        case CUBIC_SPLINE_INTERPOLATION:
        {
            pTdVec    = new TdVectorCubSpline( Last_t_end, Last_TD_nom, TickLen, pData, TdVecLen, DataType );
            break;
        }
    }

    // Remember TD vector endpoint
    Last_t_end  = pTdVec->GetEndTime();
    Last_TD_nom = pTdVec->GetEndTD();

    return pTdVec;
}

TdVecGen::TdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, InterpolationConfig InterpolConf )
    : WhiteNoiseGen( KwConf.Seed, KwConf.Qd )
{
    // Set up config
    this->TdVecLen      = TdVecLen;
    this->TickLen       = TickLen;
    this->IntpolType    = InterpolConf.Type;

    this->Last_t_end    = 0.0L;
    this->Last_TD_nom   = 0.0L;

    DisableConvFilter();
}

TdVecGen::TdVecGen( const TdVecGen& other )
    : // Config
      TickLen   ( other.TickLen     ),
      IntpolType( other.IntpolType  ),
      TdVecLen  ( other.TdVecLen    ),
      // House keeping
      ConvState     ( other.ConvState   ),
      Last_t_end    ( other.Last_t_end  ),
      Last_TD_nom   ( other.Last_TD_nom ),
      FfdVecLen     ( other.FfdVecLen   ),
      // Resources
      WhiteNoiseGen ( other.WhiteNoiseGen ),
      H             ( other.H             )
{
    pLastFFD    = new FFT_RealVector( *other.pLastFFD );
}

TdVecGen::~TdVecGen()
{
    ResetConvFilter();
}

TdVecGen&
TdVecGen::operator=( const TdVecGen& other )
{
    // Config
    this->TickLen       = other.TickLen;
    this->IntpolType    = other.IntpolType;
    this->TdVecLen      = other.TdVecLen;

    // House keeping
    this->ConvState     = other.ConvState;
    this->Last_t_end    = other.Last_t_end;
    this->Last_TD_nom   = other.Last_TD_nom;
    this->FfdVecLen     = other.FfdVecLen;

    // Resources
    this->WhiteNoiseGen = other.WhiteNoiseGen;
    this->H             = other.H;
    this->pLastFFD      = new FFT_RealVector( *other.pLastFFD );

    // By convention, always return *this
    return *this;
}

void
TdVecGen::ResetToFixPoint( TdFixPoint fp )
{
    ResetConvFilter();

    Last_t_end  = fp.Get_t();
    Last_TD_nom = fp.GetTD_nom();
}
