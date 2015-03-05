
#ifndef TDESTIMATOR_HPP_
#define TDESTIMATOR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <TdVecGen.hpp>
#include <iostream>
#include <memory>

#include "Configs.hpp"
#include "TdGuess.hpp"
#include "TdVectorStorage.hpp"
#include "TdFixPointStorage.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef enum
{
    ESTIMATED_PAST,
    EXACTLY_KNOWN,
    ESTIMATED_FUTURE,
}
EstimateType;

typedef struct
{
    double          TD;
    EstimateType    Type;
}
TdEstimate;

class TdEstimator
{
    private:

        // Config
        double  f_s;
        double  TickLen;
        double  T_val;
        size_t  TdVecLen;
        size_t  MaxTdVecCnt;

        // Resources
        TdGuess             LastGuess;
        TdFixPointStorage   FixPointStorage;
        TdVectorStorage     TdVecStorage;
        TdVecGen   *pTdVecGen;

        // Internal functions
        void    ForgetPast( double t_now );
        void    CheckLastGuess( double t_now, bool ForceReset );
        double  GuessFutureTD( double t_req );
        double  GuessPastTD( double t_req );

    public:

        TdEstimator( SampleConfig SampleConf, KW_ImplOption KwImplOption, KW_FilterConfig KwFilterConf, HP_FilterConfig HpFilterConf, InterpolationConfig InterpolConf );
        ~TdEstimator();

        TdEstimate  EstimateTd( double t_now, double t_req, double Scaling );
};

// =========================================================================
// Function declarations
// =========================================================================


#endif
