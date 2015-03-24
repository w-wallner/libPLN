
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
        bool            EnableHpFilter;
        TdVecDataType   DataType;

        // Internal functions
        virtual void    ResetRecursiveFilter() = 0;
        virtual void    ApplyRecursiveFilter( FFT_RealVector *pw ) = 0;
        void            SetUpHpConvFilter( HP_FilterConfig HpConf, size_t TdVecLen );

    public:

        // Constructors/Destructor
        RecursiveTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf );
        RecursiveTdVecGen( const RecursiveTdVecGen& other );
        virtual ~RecursiveTdVecGen();

        virtual RecursiveTdVecGen* Clone() const = 0;  // Virtual constructor (copying)

        // Operators
        RecursiveTdVecGen&  operator=( const RecursiveTdVecGen& other );

        // API
        TdVector        *GetNextVector();
        virtual void    ResetToFixPoint( TdFixPoint fp );
};

#endif
