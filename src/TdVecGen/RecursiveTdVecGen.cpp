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
#include "TdVecGen/WhiteNoiseGenerator/WhiteNoiseGenerator.hpp"

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

RecursiveTdVecGen::RecursiveTdVecGen( TdVecGenConfig_t Conf )
    : TdVecGen( Conf )
{
    // Set up high pass convolution filter
    switch( Conf.HP_FilterConf.FilterType )
    {
        case NO_FILTER:
        {
            EnableHpFilter  = false;
            FfdVecLen       = TdVecLen;
            break;
        }

        case IDENTITY:
        {
            IdentityFilterImpResp id( Conf.HP_FilterConf.FilterLen );
            id.Augment( Conf.HP_FilterConf.Cnt );

            DebugSink.SaveHpFilterImpResp( &id );

            pH = new cFilterKernel( TdVecLen, id );

            DebugSink.SaveFilterKernel( pH );

            EnableHpFilter  = true;
            FfdVecLen       = pH->GetFFT_RealSize();
            break;
        }

        case BLACKMAN:
        {
            BmHpFilterImpResp bm( Conf.HP_FilterConf.FilterLen, Conf.HP_FilterConf.f_c_nom );
            bm.Augment( Conf.HP_FilterConf.Cnt );

            DebugSink.SaveHpFilterImpResp( &bm );

            pH = new cFilterKernel( TdVecLen, bm );

            DebugSink.SaveFilterKernel( pH );

            EnableHpFilter  = true;
            FfdVecLen       = pH->GetFFT_RealSize();
            break;
        }
    }
}

RecursiveTdVecGen::RecursiveTdVecGen( const RecursiveTdVecGen& other )
    : TdVecGen( other ),
      EnableHpFilter( other.EnableHpFilter )
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

    // By convention, always return *this
    return *this;
}

TdVector *
RecursiveTdVecGen::GetNextVector()
{
    // Generate new FFD vector
    FFT_RealVector *pw;
    pw = pWNG->GetFftVector( FfdVecLen, TdVecLen );
    DebugSink.SaveWhiteNoise( pw );

    ApplyRecursiveFilter( pw );
    DebugSink.SavePlnFilteredNoise( pw );

    if( EnableHpFilter )
    {
        ApplyConvFilter( pw );
    }
    DebugSink.SaveHpFilteredNoise( pw );

    TdVector *pTdVec  = ConstructTdVector( pw );
    DebugSink.SaveTimeDeviation( pTdVec );

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
