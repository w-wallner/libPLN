
#ifndef TDESTIMATOR_HPP_
#define TDESTIMATOR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <iostream>
#include <memory>

#include "Configs.hpp"
#include "TdGuess.hpp"
#include "TdVectorGenerator.hpp"
#include "TdVectorStorage.hpp"
#include "TdFixPointStorage.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdEstimator
{
    private:

        // Config
        double  f_s;
        double  TickLen;
        double  T_val;

        // Resources
        TdGuess             LastGuess;
        TdFixPointStorage   FixPointStorage;
        TdVectorStorage     TdVecStorage;
        TdVectorGenerator   *pTdVecGen;

        // Internal functions
        void    ForgetPast( double t_now );
        void    CheckLastGuess( double t_now, bool ForceReset );
        double  GuessTD( double t_req );

    public:

        TdEstimator( SampleConfig SampleConf, KW_ImplOption KwImplOption, KW_FilterConfig KwFilterConf, HP_FilterConfig HpFilterConf, InterpolationConfig InterpolConf );
        ~TdEstimator();

        // TODO: change return type to TdEstimate
        double  EstimateTd( double t_now, double t_req, double Scaling );
};

// =========================================================================
// Function declarations
// =========================================================================


#endif
