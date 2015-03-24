// =========================================================================
// Includes
// =========================================================================

#include "TdEstimator.hpp"

#include <cassert>
#include <numeric>

#include "TdGuess.hpp"
#include "TdVecGen.hpp"
#include "GenericTdVecGen.hpp"
#include "WpmTdVecGen.hpp"
#include "WfmTdVecGen.hpp"
#include "RwTdVecGen.hpp"

// Debug only
#include <iostream>
using namespace std;

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
TdEstimator::GuessFutureTD_nom( double t_req )
{
    assert( TdVecStorage.GetEndTime() < t_req );

    double TD_nom = 0;

    LastGuess.Set( TdFixPoint( t_req, TD_nom ) );

    return TD_nom;
}

TdEstimator::TdEstimator( TdEstimatorConfig Conf )
    : TdVecStorage   ( Conf.PerformanceConf.ForgetTh1, Conf.PerformanceConf.ForgetTh2 )
{
    // Config
    f_s         = Conf.SampleConf.f_s;
    TdVecLen    = Conf.SampleConf.TdVecLen;

    T_val       = Conf.TimeConf.T_val;

    // House keeping
    Last_t_req      = 0.0L;
    LastAnswer.TD   = 0.0L;
    LastAnswer.Type = ESTIMATED_FUTURE;

    // Resulting config
    TickLen     = 1.0L / f_s;
    MaxTdVecCnt = std::max( 2.0, T_val / (TickLen * TdVecLen) );

    if( T_val < TickLen )
    {
        throw std::invalid_argument( "T_val is smaller than TickLen, this can't make sense." );
    }

    // Set up components
    switch( Conf.KwImplOption )
    {
        case USE_SHORTCUTS:
        {
            if( Conf.KwConf.alpha == 2.0L )
            {
                pTdVecGen    = new WpmTdVecGen( Conf.SampleConf.TdVecLen, TickLen, Conf.KwConf, Conf.HpConf, Conf.InterpolConf );
            }
            else if( Conf.KwConf.alpha == 0.0L )
            {
                pTdVecGen    = new WfmTdVecGen( Conf.SampleConf.TdVecLen, TickLen, Conf.KwConf, Conf.HpConf, Conf.InterpolConf );
            }
            else if( Conf.KwConf.alpha == -2.0L )
            {
                pTdVecGen    = new RwTdVecGen( Conf.SampleConf.TdVecLen, TickLen, Conf.KwConf, Conf.HpConf, Conf.InterpolConf );
            }
            else
            {
                pTdVecGen    = new GenericTdVecGen( Conf.SampleConf.TdVecLen, TickLen, Conf.KwConf, Conf.HpConf, Conf.InterpolConf );
            }
            break;
        }

        case FORCE_GENERIC:
        {
            pTdVecGen    = new GenericTdVecGen( Conf.SampleConf.TdVecLen, TickLen, Conf.KwConf, Conf.HpConf, Conf.InterpolConf );
            break;
        }
    }

    // Init all components to a common starting point
    TdFixPoint  StartingPoint   = TdFixPoint( 0.0, 0.0 );

    pTdVecGen->ResetToFixPoint     ( StartingPoint );
    TdVecStorage.ResetToFixPoint   ( StartingPoint );
}

TdEstimator::~TdEstimator()
{
    delete pTdVecGen;
}

TdEstimate
TdEstimator::EstimateTd( double t_now, double t_req )
{
    TdEstimate e;

    // Handle time issues
    CheckLastGuess( t_now, true );
    ForgetPast( t_now );

    // Verify input arguments
    if( t_req < t_now )
    {
        throw std::invalid_argument( "Requests for the past (t_req < t_now) are not supported t" );
    }

    // Evaluate request
    if( t_req == Last_t_req )
    {
        return  LastAnswer;
    }

    // Case 1: Request is in the distant future
    if( (TdVecStorage.GetEndTime() + T_val) < t_req )
    {
        e.TD    = GuessFutureTD_nom( t_req ) * f_s;
        e.Type  = ESTIMATED_FUTURE;

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
            assert( LoopCnt <= MaxCnt );
        }

        e.TD    = TdVecStorage.InterpolateTD_nom( t_req ) * f_s;
        e.Type  = EXACTLY_KNOWN;
    }

    LastAnswer  = e;
    Last_t_req  = t_req;

    return e;
}

double
TdEstimator::Get_f_s()
{
    return f_s;
}
