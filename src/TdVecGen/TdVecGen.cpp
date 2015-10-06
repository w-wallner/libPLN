// ============================================================================
///
/// \file
///
/// \brief  Implementation of a generator class for time deviation vectors.
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

#include "TdVecGen.hpp"

#include <algorithm>

#include "TdVector/TdVectorLinear.hpp"
#include "TdVector/TdVectorCubSpline.hpp"

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

void
TdVecGen::ApplyConvFilter( FFT_RealVector *pw )
{
    pH->ApplyToSignal( pw );

    // Handle overlapping convolution part
    if( pLastFFD != NULL )
    {
        std::transform( pw->begin(), pw->begin() + pH->GetFilterLen(),
                        pLastFFD->begin() + TdVecLen,
                        pw->begin(), std::plus<double>() );
    }

    // Remember FFD vector for next call
    delete pLastFFD;
    pLastFFD = pw;
}

void
TdVecGen::ResetConvFilter()
{
   delete pLastFFD;
   pLastFFD = NULL;
}

TdVector *
TdVecGen::ConstructTdVector( FFT_RealVector *pData )
{
    TdVector *pTdVec = NULL;

    switch( IntpolType )
    {
        default:
        case LINEAR_INTERPOLATION:
        {
            pTdVec    = new TdVectorLinear( Last_t_end, LastRelativeTD, f_s, pData, TdVecLen );
            break;
        }
        case CUBIC_SPLINE_INTERPOLATION:
        {
            pTdVec    = new TdVectorCubSpline( Last_t_end, LastRelativeTD, f_s, pData, TdVecLen );
            break;
        }
    }

    // Remember TD vector endpoint
    Last_t_end  = pTdVec->GetEndTime();
    LastRelativeTD = pTdVec->GetEndRelTD();

    return pTdVec;
}

TdVecGen::TdVecGen( TdVecGenConfig_t Conf )
{
    // Save config stuff for debugging purpose
    DebugSink.SaveSampleConfig( Conf.SampleConf );
    DebugSink.SaveWhiteNoiseConfig( Conf.WhiteNoiseConf );
    DebugSink.SavePlnFilterConfig( Conf.PLN_FilterConf );
    DebugSink.SaveHpFilterConfig( Conf.HP_FilterConf );

    // Set up config
    this->TdVecLen          = Conf.SampleConf.TdVecLen;
    this->f_s               = Conf.SampleConf.f_s;
    this->IntpolType        = Conf.InterpolConf.InterPolType;

    this->Last_t_end        = 0.0L;
    this->LastRelativeTD    = 0.0L;

    this->FfdVecLen         = 0;
    this->pLastFFD          = NULL;

    this->pWNG              = new WhiteNoiseGenerator( Conf.WhiteNoiseConf );
    this->pH                = NULL;
}

TdVecGen::TdVecGen( const TdVecGen& other )
    : // Config
      f_s       ( other.f_s         ),
      IntpolType( other.IntpolType  ),
      TdVecLen  ( other.TdVecLen    ),
      // House keeping
      Last_t_end    ( other.Last_t_end  ),
      LastRelativeTD( other.LastRelativeTD ),
      FfdVecLen     ( other.FfdVecLen   )
{
    // Resources
    pWNG        = (other.pWNG     != NULL) ? new WhiteNoiseGenerator( *other.pWNG ) : NULL;
    pH          = (other.pH       != NULL) ? new cFilterKernel( *other.pH )         : NULL;
    pLastFFD    = (other.pLastFFD != NULL) ? new FFT_RealVector( *other.pLastFFD )  : NULL;
}

TdVecGen::~TdVecGen()
{
    ResetConvFilter();

    delete pWNG;
    delete pH;
}

TdVecGen&
TdVecGen::operator=( const TdVecGen& other )
{
    // Config
    this->f_s               = other.f_s;
    this->IntpolType        = other.IntpolType;
    this->TdVecLen          = other.TdVecLen;

    // House keeping
    this->Last_t_end        = other.Last_t_end;
    this->LastRelativeTD    = other.LastRelativeTD;
    this->FfdVecLen         = other.FfdVecLen;

    // Resources
    this->pWNG              = (other.pWNG     != NULL) ? new WhiteNoiseGenerator( *other.pWNG ) : NULL;
    this->pH                = (other.pH       != NULL) ? new cFilterKernel( *other.pH )         : NULL;
    this->pLastFFD          = (other.pLastFFD != NULL) ? new FFT_RealVector( *other.pLastFFD )  : NULL;

    // By convention, always return *this
    return *this;
}

void
TdVecGen::ResetToFixPoint( TdFixPoint fp )
{
    ResetConvFilter();

    Last_t_end      = fp.Get_t();
    LastRelativeTD  = fp.GetTD();
}

void
TdVecGen::SetSeed( unsigned int Seed )
{
    pWNG->SetSeed( Seed );
}

double
TdVecGen::GetEstimatedValue()
{
    return pWNG->GetRandomValue();
}
