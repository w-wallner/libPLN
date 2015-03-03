
// =========================================================================
// Includes
// =========================================================================

#include "TdVecGen.hpp"

// Debug only
#include <iostream>
using namespace std;

#include "VectorOutput.hpp"

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

TdVecGen::TdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, InterpolationConfig InterpolConf )
    : WhiteNoiseGen( KwConf.Seed, KwConf.Qd )
{
    // Set up config
    this->TdVecLen      = TdVecLen;
    this->TickLen       = TickLen;
    this->IntpolType    = InterpolConf.Type;

    this->State         = UNINITIALIZED;
    this->Last_t_end    = 0.0L;
    this->Last_TD_nom   = 0.0L;
}

TdVecGen::~TdVecGen()
{
}

void
TdVecGen::ResetToFixPoint( TdFixPoint fp )
{
    this->State         = UNINITIALIZED;
    this->Last_t_end    = fp.Get_t();
    this->Last_TD_nom   = fp.GetTD_nom();
}
