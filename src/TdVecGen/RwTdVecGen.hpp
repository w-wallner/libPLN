
#ifndef TDVECGEN_RWTDVECGEN_HPP_
#define TDVECGEN_RWTDVECGEN_HPP_

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

class RwTdVecGen : public RecursiveTdVecGen
{
    private:

        // Config

        // House keeping
        double          FFD_0;

        // Internal functions
        void    ResetRecursiveFilter();
        void    ApplyRecursiveFilter( FFT_RealVector *pw );

    public:

        // Constructors/Destructor
        RwTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf );
        RwTdVecGen( const RwTdVecGen& other );
        ~RwTdVecGen();

        RwTdVecGen* Clone() const;  // Virtual constructor (copying)

        // Operators
        RwTdVecGen&  operator=( const RwTdVecGen& other );
};

#endif
