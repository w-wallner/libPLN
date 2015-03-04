// =========================================================================
// Includes
// =========================================================================

#include "TdEstimator.hpp"

#include <cassert>
#include "TdGuess.hpp"
#include "TdFixPointStorage.hpp"
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
    FixPointStorage.ForgetPast( t_now );
}

void
TdEstimator::CheckLastGuess( double t_now, bool ForceReset )
{
    if( LastGuess.IsActive() )
    {
        if( LastGuess.BecameValid( t_now ) )
        {
            // Insert into Fixpoint DB
            FixPointStorage.Add( LastGuess.Get() );

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
TdEstimator::GuessTD( double t_req )
{
    // Estimate future TD based on last FixPoint
    TdFixPoint  LastFP = FixPointStorage.GetLatest();
    TdFixPoint  NewFP( t_req, LastFP.GetTD_nom(), LastFP.GetTD_abs() );

    LastGuess.Set( NewFP );

    return NewFP.GetTD_abs();
}


TdEstimator::TdEstimator( SampleConfig SampleConf, KW_ImplOption KwImplOption, KW_FilterConfig KwFilterConf, HP_FilterConfig HpFilterConf, InterpolationConfig InterpolConf )
{
    // Config
    f_s         = SampleConf.f_s;
    T_val       = SampleConf.T_val;
    TdVecLen    = SampleConf.TdVecLen;

    // Resulting config
    TickLen     = 1.0L / f_s;
    MaxTdVecCnt = T_val / (TickLen * TdVecLen);

    // Set up components
    switch( KwImplOption )
    {
        case USE_SHORTCUTS:
        {
            if( KwFilterConf.alpha == 2.0L )
            {
                pTdVecGen    = new WpmTdVecGen( SampleConf.TdVecLen, TickLen, KwFilterConf, HpFilterConf, InterpolConf );
            }
            else if( KwFilterConf.alpha == 0.0L )
            {
                pTdVecGen    = new WfmTdVecGen( SampleConf.TdVecLen, TickLen, KwFilterConf, HpFilterConf, InterpolConf );
            }
            else if( KwFilterConf.alpha == -2.0L )
            {
                pTdVecGen    = new RwTdVecGen( SampleConf.TdVecLen, TickLen, KwFilterConf, HpFilterConf, InterpolConf );
            }
            else
            {
                pTdVecGen    = new GenericTdVecGen( SampleConf.TdVecLen, TickLen, KwFilterConf, HpFilterConf, InterpolConf );
            }
            break;
        }

        case FORCE_GENERIC:
        {
            pTdVecGen    = new GenericTdVecGen( SampleConf.TdVecLen, TickLen, KwFilterConf, HpFilterConf, InterpolConf );
            break;
        }
    }

    // Init all components to a common starting point
    TdFixPoint  StartingPoint   = TdFixPoint( 0.0, 0.0, 0.0);

    pTdVecGen->ResetToFixPoint     ( StartingPoint );
    TdVecStorage.ResetToFixPoint   ( StartingPoint );
    FixPointStorage.ResetToFixPoint( StartingPoint );
}

TdEstimator::~TdEstimator()
{
    delete pTdVecGen;
}

double
TdEstimator::EstimateTd( double t_now, double t_req, double Scaling )
{
    // Handle time issues
    CheckLastGuess( t_now, true );
    ForgetPast( t_now );

    // Evaluate request
    double  TD_abs;

    // Case 1: Request is in the distant future
    if( (TdVecStorage.GetEndTime() + T_val) < t_req )
    {
        TD_abs   = GuessTD( t_req );

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
        TD_abs = TD_nom * f_s * Scaling;

        FixPointStorage.Add( TdFixPoint( t_req, TD_nom, TD_abs ) );
    }
    // Case 4: Request is in the distant past
    else
    {
        // Interpolate from FixPoints
        TD_abs = FixPointStorage.InterpolateTD_abs( t_req );
    }

    return TD_abs;
}
