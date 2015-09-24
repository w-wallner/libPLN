// ============================================================================
///
/// \file
///
/// \brief  Implementation of time deviation generator using recursive filters.
///         This approach is valid for several classes of powerlaw noise, i.e.
///         those where alpha is an even number (WPM, WFM and RW noise).
///
/// \ingroup module_td_vec_gen
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

#include "RecursiveTdVecGen.hpp"

#include "Filter/IdentityFilterImpResp.hpp"
#include "Filter/BmHpFilterImpResp.hpp"

#include "DebugTools/DebugSink.hpp"

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

RecursiveTdVecGen::RecursiveTdVecGen( size_t TdVecLen, double TickLen, WhiteNoiseConfig_t WhiteNoiseConf, PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, InterpolationConfig_t InterpolConf )
    : TdVecGen( TdVecLen, TickLen, WhiteNoiseConf, PLN_FilterConf, InterpolConf )
{
    DataType    = TdVector::FFD_DATA;

    // Set up high pass convolution filter
    switch( HP_FilterConf.FilterType )
    {
        case NO_FILTER:
        {
            EnableHpFilter  = false;
            FfdVecLen       = TdVecLen;
            break;
        }

        case IDENTITY:
        {
            IdentityFilterImpResp id( HP_FilterConf.FilterLen );
            id.Augment( HP_FilterConf.Cnt );

            DebugSink.SaveHpFilterImpResp( &id );

            H = cFilterKernel( TdVecLen, id );

            DebugSink.SaveFilterKernel( H );

            EnableHpFilter  = true;
            FfdVecLen       = H.GetFFT_RealSize();
            break;
        }

        case BLACKMAN:
        {
            BmHpFilterImpResp bm( HP_FilterConf.FilterLen, HP_FilterConf.f_c_nom );
            bm.Augment( HP_FilterConf.Cnt );

            DebugSink.SaveHpFilterImpResp( &bm );

            H   = cFilterKernel( TdVecLen, bm );

            DebugSink.SaveFilterKernel( H );

            EnableHpFilter  = true;
            FfdVecLen       = H.GetFFT_RealSize();
            break;
        }
    }
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

    DebugSink.SaveWhiteNoise( pw );

    if( EnableHpFilter )
    {
        ApplyConvFilter( pw );
    }

    DebugSink.SaveHpFilteredNoise( pw );

    ApplyRecursiveFilter( pw );

    DebugSink.SavePlnFilteredNoise( pw );

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
