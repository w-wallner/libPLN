
#ifndef TDVECGEN_WFMTDGEN_CPP_
#define TDVECGEN_WFMTDGEN_CPP_

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

class WfmTdVecGen : public RecursiveTdVecGen
{
    private:

        // Config

        // Internal functions
        void    ResetRecursiveFilter();
        void    ApplyRecursiveFilter( FFT_RealVector *pw );

    public:

        // Constructors/Destructor
        WfmTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf );
        WfmTdVecGen( const WfmTdVecGen& other );
        ~WfmTdVecGen();

        WfmTdVecGen* Clone() const;  // Virtual constructor (copying)

        // Operators
        WfmTdVecGen&  operator=( const WfmTdVecGen& other );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
