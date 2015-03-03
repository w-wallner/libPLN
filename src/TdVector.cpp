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

TdVector::TdVector( double t_beg, double TD_0, double TickLen, FFT_RealVector *pData, size_t ValidLen, TdVecDataType DataType )
    : TD( ValidLen + 1 )
{
    this->t_beg     = t_beg;
    this->t_end     = t_beg + TickLen * ValidLen;
    this->TickLen   = TickLen;
    this->TD_0      = TD_0;

    switch( DataType )
    {
        case FFD_DATA:
        {
            TD[0]       = 0.0L;
            EnableTD_0  = true;

            std::partial_sum( pData->begin(), pData->begin() + ValidLen, TD.begin()+1 );
            break;
        }
        case TD_DATA:
        {
            TD[0]       = TD_0;
            EnableTD_0  = false;

            std::copy( pData->begin(), pData->begin() + ValidLen, TD.begin() + 1 );
            break;
        }
    }
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
    double  TD_ = *TD.begin();

    if( EnableTD_0 )
    {
        TD_  += TD_0;
    }

    return TD_;
}

double
TdVector::GetEndTD()
{
    double  TD_ = *TD.rbegin();

    if( EnableTD_0 )
    {
        TD_  += TD_0;
    }

    return TD_;
}

double
TdVector::InterpolateTD_nom( double t_req )
{
    assert( t_req >= t_beg );
    assert( t_req <= t_end );

    double  TD_ = InterpolateAt( t_req );

    if( EnableTD_0 )
    {
        TD_  += TD_0;
    }

    return TD_;
}
