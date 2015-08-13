// 
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
// 
// This file is part of libPLN.
// 
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//

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
