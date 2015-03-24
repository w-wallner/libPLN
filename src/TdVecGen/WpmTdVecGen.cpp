// =========================================================================
// Includes
// =========================================================================

#include "WpmTdVecGen.hpp"

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
WpmTdVecGen::ResetRecursiveFilter()
{
    // For WPM there is nothing to do here
}

void
WpmTdVecGen::ApplyRecursiveFilter( FFT_RealVector *pw )
{
    // For WPM there is nothing to do here
}

WpmTdVecGen::WpmTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf )
    : RecursiveTdVecGen( TdVecLen, TickLen, KwConf, HpConf, InterpolConf )
{
    DataType    = TD_DATA;
}

WpmTdVecGen::WpmTdVecGen( const WpmTdVecGen& other )
    : RecursiveTdVecGen( other )
{
}

WpmTdVecGen::~WpmTdVecGen()
{
}

WpmTdVecGen*
WpmTdVecGen::Clone() const
{
    return new WpmTdVecGen(*this);
}

WpmTdVecGen&
WpmTdVecGen::operator=( const WpmTdVecGen& other )
{
    RecursiveTdVecGen::operator=( other );

    // By convention, always return *this
    return *this;
}
