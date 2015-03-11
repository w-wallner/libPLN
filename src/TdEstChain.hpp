
#ifndef TDESTCHAIN_HPP_
#define TDESTCHAIN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEstimator.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

class TdEstChain
{
    private:

        // Types
        typedef struct
        {
            double          Scale;
            TdEstimator     *pEst;
        }
        ChainEntry;

        // Housekeeping
        double              Last_f_s;

        // Resources
        std::vector<ChainEntry>     Chain;

    public:

        TdEstChain();
        ~TdEstChain();

        void    AddTdEstimator( TdEstimatorConfig Conf, double Scale );
        double  EstimateTd( double t_now, double t_req );
};


#endif
