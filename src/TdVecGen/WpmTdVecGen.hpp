
#ifndef TDVECGEN_WPMTDVECGEN_HPP_
#define TDVECGEN_WPMTDVECGEN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "RecursiveTdVecGen.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

class WpmTdVecGen : public RecursiveTdVecGen
{
    private:

        // Config

        // Internal functions
        void    ResetRecursiveFilter();
        void    ApplyRecursiveFilter( FFT_RealVector *pw );

    public:
        WpmTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf );
        ~WpmTdVecGen();
};

#endif
