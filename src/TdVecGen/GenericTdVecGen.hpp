
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

        // Internal functions
        void        SetUpKwHpConvFilter( KW_FilterConfig KwConf, HP_FilterConfig HpConf, size_t TdVecLen );

    public:

        // Constructors/Destructor
        GenericTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf );
        GenericTdVecGen( const GenericTdVecGen& other );
        ~GenericTdVecGen();

        GenericTdVecGen*    Clone() const;  // Virtual constructor (copying)

        // Operators
        GenericTdVecGen&    operator=( const GenericTdVecGen& other );

        // API
        TdVector    *GetNextVector();
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
