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

#include "RecursiveTdVecGen.hpp"

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
RecursiveTdVecGen::SetUpHpConvFilter( HP_FilterConfig_t HP_FilterConf, size_t TdVecLen )
{
    switch( HP_FilterConf.FilterType )
    {
        case NO_FILTER:
        {
            EnableHpFilter  = false;
            FfdVecLen       = TdVecLen;
            break;
        }

        case BLACKMAN:
        {
            BmHpFilterImpResp bm( HP_FilterConf.FilterLen, HP_FilterConf.f_c_nom );

            bm.Augment( HP_FilterConf.Cnt );

            H   = FilterKernel( TdVecLen, bm );

            EnableHpFilter  = true;
            FfdVecLen       = H.GetFFT_RealSize();
            break;
        }
    }
}

RecursiveTdVecGen::RecursiveTdVecGen( size_t TdVecLen, double TickLen, PLN_FilterConfig_t PLN_FilterConf, HP_FilterConfig_t HP_FilterConf, InterpolationConfig_t InterpolConf )
    : TdVecGen( TdVecLen, TickLen, PLN_FilterConf, InterpolConf )
{
    DataType    = TdVector::FFD_DATA;

    SetUpHpConvFilter( HP_FilterConf, TdVecLen );
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
