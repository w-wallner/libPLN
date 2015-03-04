
#ifndef TDVECGEN_GENERICTDVECGEN_HPP_
#define TDVECGEN_GENERICTDVECGEN_HPP_

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

class GenericTdVecGen : public TdVecGen
{
    private:

        // Config

        // Resources
        FFT_RealVector      *pLastFFD;

        // Internal functions
        void        SetUpKwHpConvFilter( KW_FilterConfig KwConf, HP_FilterConfig HpConf, size_t TdVecLen );

    public:
        GenericTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf );
        ~GenericTdVecGen();

        TdVector    *GetNextVector();

};

// =========================================================================
// Function declarations
// =========================================================================

#endif
