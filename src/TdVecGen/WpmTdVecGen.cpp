// =========================================================================
// Includes
// =========================================================================

#include "WpmTdVecGen.hpp"

#include <numeric>

#include "TdVectorLinear.hpp"
#include "TdVectorCubSpline.hpp"

// Debugn only
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

WpmTdVecGen::WpmTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf )
    : RecursiveTdVecGen( TdVecLen, TickLen, KwConf, HpConf, InterpolConf )
{
}

WpmTdVecGen::~WpmTdVecGen()
{
}

TdVector *
WpmTdVecGen::GetNextVector()
{
    // Generate new FFD vector
    FFT_RealVector *pw;
    pw = WhiteNoiseGen.GetFftVector( FfdVecLen, TdVecLen );

    if( EnableHpFilter )
    {
        ApplyConvFilter( pw );
    }

    // Apply recursive filtering
    // For WPM there is nothing to do here

    return ConstructTdVector( pw, TD_DATA );;
}
