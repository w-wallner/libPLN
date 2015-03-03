// =========================================================================
// Includes
// =========================================================================

#include "TdVectorCubSpline.hpp"

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

double
TdVectorCubSpline::InterpolateAt( double t_req )
{
    if( State == UNINITIALIZED )
    {
        t.resize( TD.size() );

        t[0] = t_beg;
        for( size_t i = 1; i < t.size(); i ++ )
        {
            t[ i ] = t[i-1] + TickLen;
        }

        s.set_points( t, TD );

        State = INITIALIZED;
    }

    return s(t_req);
}

TdVectorCubSpline::TdVectorCubSpline( double t_beg, double TD_0, double TickLen, FFT_RealVector *pFFD, size_t ValidLen, TdVecDataType DataType )
    : TdVector( t_beg, TD_0, TickLen, pFFD, ValidLen, DataType )
{
    State   = UNINITIALIZED;
}
