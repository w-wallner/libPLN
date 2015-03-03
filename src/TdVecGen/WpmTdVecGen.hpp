
#ifndef TDVECGEN_WPMTDVECGEN_HPP_
#define TDVECGEN_WPMTDVECGEN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVecGen.hpp"
#include "Configs.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

class WpmTdVecGen : public TdVecGen
{
    private:

        // Config
        bool                EnableHpFilter;

        // Resources
        FFT_RealVector      *pLastFFD;

    public:
        WpmTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf );
        ~WpmTdVecGen();

        void        ResetToFixPoint( TdFixPoint fp );
        TdVector    *GetNextVector();

};

#endif
