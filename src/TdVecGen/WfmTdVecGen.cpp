// =========================================================================
// Includes
// =========================================================================

#include "WfmTdVecGen.hpp"

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
WfmTdVecGen::ResetRecursiveFilter()
{
    // For WFM there is nothing to do here
}

void
WfmTdVecGen::ApplyRecursiveFilter( FFT_RealVector *pw )
{
    // For WFM there is nothing to do here
}

WfmTdVecGen::WfmTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf )
    : RecursiveTdVecGen( TdVecLen, TickLen, KwConf, HpConf, InterpolConf )
{
    DataType    = FFD_DATA;
}

WfmTdVecGen::WfmTdVecGen( const WfmTdVecGen& other )
    : RecursiveTdVecGen( other )
{
}

WfmTdVecGen::~WfmTdVecGen()
{
}

WfmTdVecGen*
WfmTdVecGen::Clone() const
{
    return new WfmTdVecGen(*this);
}

WfmTdVecGen&
WfmTdVecGen::operator=( const WfmTdVecGen& other )
{
    RecursiveTdVecGen::operator=( other );

    // By convention, always return *this
    return *this;
}
