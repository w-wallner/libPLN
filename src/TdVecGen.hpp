
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
    private:

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

        // House keeping
        TdGenState          State;
        double              Last_t_end;
        double              Last_TD_nom;
        FFT_RealVector      *pLastFFD;

        // Resources
        WhiteNoiseGenerator     WhiteNoiseGen;
        FilterKernel            H;

    public:

        TdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf );
        ~TdVecGen();

        void        ResetToFixPoint( TdFixPoint fp );
        TdVector    *GetNextVector();
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
