
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

        typedef struct
        {
            double  t;
            double  TD_nom;
            double  TD_abs;
        }
        ScalePoint;

        // Housekeeping
        double              Last_f_s;
        ScalePoint          ScaleRef;
        ScalePoint          ScaleRefCandidate;
        bool                CandidateValid;

        // Resources
        std::vector<ChainEntry>     Chain;

        // Internal functions
        void    ClearChain();

    public:

        // Constructors/Destructor
        TdEstChain();
        TdEstChain( const TdEstChain& other );
        ~TdEstChain();

        // Operators
        TdEstChain& operator= (const TdEstChain& other);

        // API
        void    AddTdEstimator( TdEstimatorConfig Conf, double Scale );
        double  EstimateTD( double t_now, double t_req );
};

#endif
