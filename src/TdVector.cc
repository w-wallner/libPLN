// =========================================================================
// Includes
// =========================================================================

#include "TdVector.hpp"

#include <cassert>
#include <numeric>

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

TdVector::TdVector( double t_beg, double TD_0, double TickLen, FFT_RealVector *pFFD, size_t ValidLen )
    : TD( ValidLen + 1 )
{
    this->t_beg     = t_beg;
    this->t_end     = t_beg + TickLen * ValidLen;
    this->TickLen   = TickLen;
    this->TD_0      = TD_0;

    TD[0] = 0.0L;

    std::partial_sum( pFFD->begin(), pFFD->begin() + ValidLen, TD.begin()+1 );
}

TdVector::~TdVector()
{
}

double
TdVector::GetBeginTime()
{
    return t_beg;
}

double
TdVector::GetEndTime()
{
    return t_end;
}

double
TdVector::GetBeginTD()
{
    return *TD.begin() + TD_0;
}

double
TdVector::GetEndTD()
{
    return *TD.rbegin() + TD_0;
}

double
TdVector::InterpolateTD_nom( double t_req )
{
    assert( t_req >= t_beg );
    assert( t_req <= t_end );

    return TD_0 + InterpolateAt( t_req );
}
