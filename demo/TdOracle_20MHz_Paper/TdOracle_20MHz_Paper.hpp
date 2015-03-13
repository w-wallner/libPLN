
#ifndef TDORACLE_20MHZ_PAPER_HPP_
#define TDORACLE_20MHZ_PAPER_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEstChain.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================



class TdOracle_20MHz_Paper
{
    private:

        // Types
        class TdEstChain_WPM : public TdEstChain
        {
            private:

            public:

                TdEstChain_WPM( unsigned int Seed );

        };

        // Config

        // Resources
        TdEstChain_WPM      WpmChain;

    public:

        TdOracle_20MHz_Paper( unsigned int Seed );
        double  EstimateTd( double t_now, double t_req );
};




// =========================================================================
// Function declarations
// =========================================================================


#endif
