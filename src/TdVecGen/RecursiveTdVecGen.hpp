
#ifndef TDVECGEN_RECURSIVETDVECGEN_HPP_
#define TDVECGEN_RECURSIVETDVECGEN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVecGen.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

class RecursiveTdVecGen : public TdVecGen
{
    protected:

        // Config
        bool        EnableHpFilter;

        // Internal functions
        void        SetUpHpConvFilter( HP_FilterConfig HpConf, size_t TdVecLen );

    public:

        RecursiveTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf );
};

#endif
