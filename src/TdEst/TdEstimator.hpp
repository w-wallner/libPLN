
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

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef enum
{
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
        TdVectorStorage     TdVecStorage;
        TdVecGen            *pTdVecGen;

        // House keeping
        TdGuess             LastGuess;
        double              Last_t_req;
        TdEstimate          LastAnswer;

        // Internal functions
        void    ForgetPast( double t_now );
        void    CheckLastGuess( double t_now, bool ForceReset );
        double  GuessFutureTD_nom( double t_req );

    public:

        TdEstimator( TdEstimatorConfig Conf );
        ~TdEstimator();

        TdEstimate  EstimateTd( double t_now, double t_req );

        // Debug functions
        double  Get_f_s();
};

// =========================================================================
// Function declarations
// =========================================================================


#endif
