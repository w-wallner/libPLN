// =========================================================================
// Includes
// =========================================================================

#include "RwTdVecGen.hpp"

#include <algorithm>
#include <numeric>

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
RwTdVecGen::ResetRecursiveFilter()
{
    FFD_0   = 0.0L;
}

void
RwTdVecGen::ApplyRecursiveFilter( FFT_RealVector *pw )
{
    std::partial_sum( pw->begin(), pw->end(), pw->begin() );

    std::transform( pw->begin(), pw->end(), pw->begin(),
              bind2nd(std::plus<double>(), FFD_0) );

    FFD_0 = *pw->rbegin();
}

RwTdVecGen::RwTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf )
    : RecursiveTdVecGen( TdVecLen, TickLen, KwConf, HpConf, InterpolConf )
{
    DataType    = FFD_DATA;
    FFD_0       = 0.0L;
}

RwTdVecGen::~RwTdVecGen()
{
}
