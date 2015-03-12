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
    TdVecStorage.ForgetPast   ( t_now );
}

void
TdEstimator::CheckLastGuess( double t_now, bool ForceReset )
{
    if( LastGuess.IsActive() )
    {
        if( LastGuess.BecameValid( t_now ) )
        {
            // Reset VectorGen and Storage
            pTdVecGen->ResetToFixPoint  ( LastGuess.Get() );
            TdVecStorage.ResetToFixPoint( LastGuess.Get() );

            LastGuess.Reset();
        }
        else if( ForceReset )
        {
            LastGuess.Reset();
        }
    }
}

double
TdEstimator::GuessFutureTD( double t_req )
{
    assert( TdVecStorage.GetEndTime() < t_req );

    double TD_nom = TdVecStorage.GetEndTD();

    LastGuess.Set( TdFixPoint( t_req, TD_nom ) );

    return TD_nom * f_s;
}

double
TdEstimator::GuessPastTD( double t_req )
{
    assert( TdVecStorage.GetBeginTime() > t_req );

    return TdVecStorage.GetBeginTD();
}


TdEstimator::TdEstimator( TdEstimatorConfig Conf )
    : TdVecStorage   ( Conf.TimeConf.ForgetTh1, Conf.TimeConf.ForgetTh2 )
{
    // Config
    f_s         = Conf.SampleConf.f_s;
    TdVecLen    = Conf.SampleConf.TdVecLen;

    T_val       = Conf.TimeConf.T_val;

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

    // Evaluate request
    double  TD_abs;

    // Case 1: Request is in the distant future
    if( (TdVecStorage.GetEndTime() + T_val) < t_req )
    {
        e.TD    = GuessFutureTD( t_req );
        e.Type  = ESTIMATED_FUTURE;

        // Check if our new guess may become valid immediately
        CheckLastGuess( t_now, false );
    }
    // Case 2+3: Request is in the near future or recent past
    else if( TdVecStorage.GetBeginTime() <= t_req )
    {
        double  TD_nom = 0.0;

        // Request TD vectors until correct answer is known
        size_t  LoopCnt = 0;
        size_t  MaxCnt  = MaxTdVecCnt;

        while( TdVecStorage.GetEndTime() <= t_req )
        {
            TdVecStorage.AddTdVec( pTdVecGen->GetNextVector() );

            LoopCnt ++;
            assert( LoopCnt <= MaxCnt );
        }

        TD_nom  = TdVecStorage.InterpolateTD_nom( t_req );

        // Scale output
        TD_abs = TD_nom * f_s;

        e.TD    = TD_abs;
        e.Type  = EXACTLY_KNOWN;
    }
    // Case 4: Request is in the distant past
    else
    {
        // Interpolate from FixPoints
        e.TD    = GuessPastTD( t_req );
        e.Type  = ESTIMATED_PAST;
    }

    return e;
}
