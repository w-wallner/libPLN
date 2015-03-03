
#ifndef TDVECGEN_HPP_
#define TDVECGEN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "Configs.hpp"
#include "TdVector.hpp"
#include "TdFixPoint.hpp"
#include "WhiteNoiseGenerator.hpp"
#include "FilterKernel.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdVecGen
{
    protected:

        // Types
        typedef enum
        {
            UNINITIALIZED,
            INITIALIZED,
        }
        TdGenState;

        // Config
        double              TickLen;
        InterpolationType   IntpolType;
        size_t              TdVecLen;

        // House keeping
        TdGenState          State;
        double              Last_t_end;
        double              Last_TD_nom;

        // Resources
        WhiteNoiseGenerator     WhiteNoiseGen;
        FilterKernel            H;

    public:

        TdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, InterpolationConfig InterpolConf );
        virtual ~TdVecGen();

        virtual void        ResetToFixPoint( TdFixPoint fp );
        virtual TdVector    *GetNextVector() = 0;
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
