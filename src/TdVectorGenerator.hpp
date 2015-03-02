
#ifndef TDVECTORGENERATOR_HPP_
#define TDVECTORGENERATOR_HPP_

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

class TdVectorGenerator
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

        TdVectorGenerator( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf );
        ~TdVectorGenerator();

        void        ResetToFixPoint( TdFixPoint fp );
        TdVector    *GetNextVector();
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
