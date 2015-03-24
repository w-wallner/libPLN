
#ifndef TDVECGEN_HPP_
#define TDVECGEN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEstConfig.hpp"
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
        TdGenState          ConvState;
        double              Last_t_end;
        double              Last_TD_nom;
        size_t              FfdVecLen;

        // Resources
        WhiteNoiseGenerator     WhiteNoiseGen;
        FilterKernel            H;
        FFT_RealVector          *pLastFFD;

        // Internal functions
        void        DisableConvFilter();
        void        InitConvFilter();
        void        ApplyConvFilter( FFT_RealVector *pw );
        void        ResetConvFilter();

        TdVector    *ConstructTdVector( FFT_RealVector *pData, TdVecDataType DataType );

    public:

        // Constructors/Destructor
        TdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, InterpolationConfig InterpolConf );
        TdVecGen( const TdVecGen& other );
        virtual ~TdVecGen();

        virtual TdVecGen* Clone() const = 0;  // Virtual constructor (copying)

        // Operators
        TdVecGen&  operator=( const TdVecGen& other );

        // API
        virtual void        ResetToFixPoint( TdFixPoint fp );
        virtual TdVector    *GetNextVector() = 0;
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
