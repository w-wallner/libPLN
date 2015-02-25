// =========================================================================
// Includes
// =========================================================================

#include <cassert>

#include "TdEstimator.hpp"

#include "TdGuess.hpp"
#include "TdFixPointStorage.hpp"

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
    // TODO
    // Forward forgetting to storages, etc.
}

void
TdEstimator::CheckLastGuess( double t_now )
{
    if( LastGuess.IsActive() )
    {
        if( LastGuess.BecameValid( t_now ) )
        {
            // Insert into Fixpoint DB
            FixPointStorage.Add( LastGuess.Get() );

            // Reset VectorGen and Storage
            pTdVecGen->ResetToFixPoint ( LastGuess.Get() );
            TdVecStorage.ResetToFixPoint( LastGuess.Get() );
        }

        LastGuess.Reset();
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
    f_s     = SampleConf.f_s;
    T_val   = SampleConf.T_val;

    TickLen = 1.0L / f_s;

    // TODO: Init TD Vec Generator
    pTdVecGen    = new TdVectorGenerator( SampleConf.TdVecLen, KwFilterConf, HpFilterConf, InterpolConf );

    // TODO: Init TD Vec Storage
    // TODO: Init Fixpoint Storage
}

TdEstimator::~TdEstimator()
{
    delete pTdVecGen;
}

double
TdEstimator::EstimateTd( double t_now, double t_req, double Scaling )
{
    // Handle time issues
    CheckLastGuess( t_now );
    ForgetPast( t_now );

    // Evaluate request
    double  TD_abs;

    // Case 1: Request is in the distant future
    if( (TdVecStorage.GetEndTime() + T_val) < t_req )
    {
        TD_abs   = GuessTD( t_req );
    }
    // Case 2+3: Request is in the near future or recent past
    else if( TdVecStorage.GetBeginTime() < t_req )
    {
        double  TD_nom = 0.0;

        // Request TD vectors until correct answer is known
        size_t  LoopCnt = 0;
        while( TdVecStorage.GetEndTime() < t_req )
        {
            TdVecStorage.AddTdVec( pTdVecGen->GetNextVector() );

            LoopCnt ++;
            assert( LoopCnt < 100 );
        }

        TD_nom  = TdVecStorage.InterpolateTD_nom( t_req );

        // Scale output
        TD_abs = TD_nom * TickLen * Scaling;
    }
    // Case 4: Request is in the distant past
    else
    {
        // Interpolate from FixPoints
        TD_abs = FixPointStorage.InterpolateTD_abs( t_req );
    }

    return TD_abs;
}
