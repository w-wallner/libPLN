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

#include "GenericTdVecGen.hpp"

#include <numeric>

#include "Filter/KwFilterImpResp.hpp"
#include "Filter/BmHpFilterImpResp.hpp"

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

    ApplyConvFilter( pw );

    TdVector *pTdVec = ConstructTdVector( pw, TdVector::FFD_DATA );

    return pTdVec;
}
