// ============================================================================
///
/// \file
///
/// \brief  Estimator for time deviation values
///
/// \ingroup module_td_estimator
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

#include "TdEstimator.hpp"

#include <cassert>
#include <numeric>

#include "TdGuess.hpp"
#include "TdVecGen/TdVecGen.hpp"
#include "TdVecGen/GenericTdVecGen.hpp"
#include "TdVecGen/WpmTdVecGen.hpp"
#include "TdVecGen/WfmTdVecGen.hpp"
#include "TdVecGen/RwTdVecGen.hpp"
#include "TdVecGen/TdVecGenFactory.hpp"

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
TdEstimator::ForgetPast( double t_now )
{
    // Forward forgetting to storages, etc.
    TdVecStorage.ForgetPast( t_now );
}

void
TdEstimator::CheckLastGuess( double t_now, bool ForceReset )
{
    if( LastGuess.IsActive() )
    {
        if( LastGuess.BecameValid( t_now ) )
        {
            // Reset VectorGen and Storage
            pTdVecGen->ResetToFixPoint  ( LastGuess.GetFP() );
            TdVecStorage.ResetToFixPoint( LastGuess.GetFP() );

            LastGuess.Reset();
        }
        else if( ForceReset )
        {
            LastGuess.Reset();
        }
    }
}

double
TdEstimator::GuessFutureRelativeTD( double t_req )
{
    assert( TdVecStorage.GetEndTime() < t_req );

    double RelativeTD;

    // ---------------------------------------------------------------------------
    // ATTENTION: This is only an estimate
    // It won't be equally good for all types of noise
    // ---------------------------------------------------------------------------
    RelativeTD  = pTdVecGen->GetEstimatedValue();

    LastGuess.Set( TdFixPoint( t_req, RelativeTD ) );

    return RelativeTD;
}

TdEstimator::TdEstimator( TdEstimatorConfig Conf )
    : TdVecStorage( Conf.PerformanceConf.ForgetTh ),
      LastResult( 0.0L, 0.0L )
{
    // Config
    f_s         = Conf.SampleConf.f_s;
    TdVecLen    = Conf.SampleConf.TdVecLen;
    alpha       = Conf.PLN_FilterConf.alpha;

    T_val                   = Conf.TimeConf.T_val;
    IntervalSkippingEnabled = Conf.TimeConf.EnableIntervalSkipping;

    // Resulting config
    TickLen     = 1.0L / f_s;
    MaxTdVecCnt = std::max( 2.0, T_val / (TickLen * TdVecLen) );

    if( T_val < TickLen )
    {
        throw std::invalid_argument( "T_val is smaller than TickLen, this can't make sense." );
    }

    // Set up components
    pTdVecGen = TdVecGenFactory::CreateTdVecGen( Conf.SampleConf.TdVecLen, TickLen,
                                                 Conf.WhiteNoiseConf, Conf.PLN_FilterConf, Conf.HP_FilterConf, Conf.InterpolConf );

    // Init all components to a common starting point
    TdFixPoint  StartingPoint   = TdFixPoint( 0.0, 0.0 );

    pTdVecGen->ResetToFixPoint     ( StartingPoint );
    TdVecStorage.ResetToFixPoint   ( StartingPoint );
}

TdEstimator::TdEstimator( const TdEstimator& other )
: // Config
  f_s                       ( other.f_s          ),
  TickLen                   ( other.TickLen      ),
  alpha                     ( other.alpha        ),
  T_val                     ( other.T_val        ),
  TdVecLen                  ( other.TdVecLen     ),
  MaxTdVecCnt               ( other.MaxTdVecCnt  ),
  IntervalSkippingEnabled   ( other.IntervalSkippingEnabled ),
  // Resources
  TdVecStorage              ( other.TdVecStorage ),
  // House keeping
  LastGuess                 ( other.LastGuess    ),
  LastResult                ( other.LastResult   )
{
    pTdVecGen = other.pTdVecGen->Clone();
}

TdEstimator::~TdEstimator()
{
    delete pTdVecGen;
}

TdEstimator&
TdEstimator::operator=( const TdEstimator& other )
{
    // Config
    this->f_s                       = other.f_s;
    this->TickLen                   = other.TickLen;
    this->alpha                     = other.alpha;
    this->T_val                     = other.T_val;
    this->TdVecLen                  = other.TdVecLen;
    this->MaxTdVecCnt               = other.MaxTdVecCnt;
    this->IntervalSkippingEnabled   = other.IntervalSkippingEnabled;

    // Resources
    this->TdVecStorage  = other.TdVecStorage;
    this->pTdVecGen     = other.pTdVecGen->Clone();

    // House keeping
    this->LastGuess     = other.LastGuess;
    this->LastResult    = other.LastResult;

    // By convention, always return *this
    return *this;
}

void
TdEstimator::EnableIntervalSkipping()
{
    IntervalSkippingEnabled = true;
}

void
TdEstimator::DisableIntervalSkipping()
{
    IntervalSkippingEnabled = false;
}

void
TdEstimator::SetSeed( unsigned int Seed )
{
    pTdVecGen->SetSeed( Seed );
}

double
TdEstimator::EstimateTD( double t_now, double t_req )
{
    double  TD_nom;
    double  TD_abs;

    // Handle time issues
    CheckLastGuess( t_now, true );
    ForgetPast( t_now );

    // Verify input arguments
    if( t_req < t_now )
    {
        throw std::invalid_argument( "Requests for the past (t_req < t_now) are not supported t" );
    }

    // Evaluate request
    if( t_req == LastResult.Get_t() )
    {
        TD_nom  = LastResult.GetRelativeTD();
    }
    else if // Case 1: Request is in the distant future
    (
        ( IntervalSkippingEnabled                     ) &&
        ( t_req > (TdVecStorage.GetEndTime() + T_val) )
    )
    {
        TD_nom  = GuessFutureRelativeTD( t_req );

        // Check if our new guess may become valid immediately
        CheckLastGuess( t_now, false );
    }
    // Case 2+3: Request is in the near future or recent past
    else if( TdVecStorage.GetBeginTime() <= t_req )
    {
        // Request TD vectors until correct answer is known
        size_t  LoopCnt = 0;
        size_t  MaxCnt  = MaxTdVecCnt;

        while( TdVecStorage.GetEndTime() <= t_req )
        {
            TdVecStorage.AddTdVec( pTdVecGen->GetNextVector() );

            LoopCnt ++;

            // If interval skipping is enabled,
            // this implies that the loop cnt has an upper bound
            assert(( !IntervalSkippingEnabled ) || ( LoopCnt <= MaxCnt ) );
        }

        TD_nom  = TdVecStorage.GetRelativeTD( t_req );
    }
    else
    {
        assert( false );
    }

    TD_abs  = TD_nom / f_s;

    LastResult  = TdFixPoint( t_req, TD_nom );

    return TD_abs;
}

double
TdEstimator::Get_f_s()
{
    return f_s;
}

double
TdEstimator::GetAlpha()
{
    return alpha;
}
