// ============================================================================
///
/// \file
///
/// \brief  Generic implementation of a time deviation generator based
///         on the powerlaw noise simulation approach proposed by Kasdin
///         and Walter.
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

#include "GenericTdVecGen.hpp"

#include <numeric>

#include "Filter/IdentityFilterImpResp.hpp"
#include "Filter/KwFilterImpResp.hpp"
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

void
GenericTdVecGen::SetUpPLNConvFilter( PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, size_t TdVecLen )
{
    // Set up filter kernel
    KwFilterImpResp   kw( PLN_FilterConf.FilterLen, PLN_FilterConf.alpha );
    DebugSink.SavePlnFilterImpResp( &kw );

    switch( HP_FilterConf.FilterType )
    {
        case NO_FILTER:
        {
            H   = cFilterKernel( TdVecLen, kw );
            break;
        }

        case IDENTITY:
        {
            IdentityFilterImpResp id( HP_FilterConf.FilterLen );
            id.Augment( HP_FilterConf.Cnt );

            DebugSink.SaveHpFilterImpResp( &id );

            H = cFilterKernel( TdVecLen, kw, id );
            break;
        }

        case BLACKMAN:
        {
            BmHpFilterImpResp bm( HP_FilterConf.FilterLen, HP_FilterConf.f_c_nom );
            bm.Augment( HP_FilterConf.Cnt );

            DebugSink.SaveHpFilterImpResp( &bm );

            H   = cFilterKernel( TdVecLen, kw, bm );
            break;
        }
    }

    DebugSink.SaveFilterKernel( H );

    FfdVecLen   = H.GetFFT_RealSize();
}

GenericTdVecGen::GenericTdVecGen( TdVecGenConfig_t Conf )
    : TdVecGen( Conf )
{
    SetUpPLNConvFilter( Conf.PLN_FilterConf, Conf.HP_FilterConf, TdVecLen );
}

GenericTdVecGen::GenericTdVecGen( const GenericTdVecGen& other )
    : TdVecGen( other )
{
}

GenericTdVecGen::~GenericTdVecGen()
{
}

GenericTdVecGen*
GenericTdVecGen::Clone() const
{
    return new GenericTdVecGen(*this);
}

GenericTdVecGen&
GenericTdVecGen::operator=( const GenericTdVecGen& other )
{
    TdVecGen::operator=( other );

    // By convention, always return *this
    return *this;
}

TdVector *
GenericTdVecGen::GetNextVector()
{
    // Generate new FFD vector
    FFT_RealVector *pw;
    pw = WhiteNoiseGen.GetFftVector( FfdVecLen, TdVecLen );
    DebugSink.SaveWhiteNoise( pw );

    ApplyConvFilter( pw );
    DebugSink.SaveHpFilteredNoise( pw );

    TdVector *pTdVec = ConstructTdVector( pw );
    DebugSink.SaveTimeDeviation( pTdVec );

    return pTdVec;
}
