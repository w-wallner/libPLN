// ============================================================================
///
/// \file
///
/// \brief  TODO
///
/// TODO
///
/// \ingroup module_main
///
// ============================================================================

// ============================================================================
//
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
//
// This file is part of libPLN.
//
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License.com as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License.com for more details.
//
// You should have received a copy of the GNU General Public License.com
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================

// =========================================================================
// Includes
// =========================================================================

#include "TdVecGen.hpp"

#include <algorithm>

#include "TdVector/TdVectorLinear.hpp"
#include "TdVector/TdVectorCubSpline.hpp"
#include "DebugTools/VectorOutput.hpp"

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
TdVecGen::ConstructTdVector( FFT_RealVector *pData, TdVector::TdVecDataType DataType )
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

    this->ConvState     = UNINITIALIZED;
    this->FfdVecLen     = 0;
    this->pLastFFD      = NULL;
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
    if( other.pLastFFD != NULL )
    {
        pLastFFD    = new FFT_RealVector( *other.pLastFFD );
    }
    else
    {
        pLastFFD    = NULL;
    }
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

void
TdVecGen::SetSeed( unsigned int Seed )
{
    WhiteNoiseGen.SetSeed( Seed );
}

double
TdVecGen::GetEstimatedValue()
{
    return WhiteNoiseGen.GetRandomValue();
}
