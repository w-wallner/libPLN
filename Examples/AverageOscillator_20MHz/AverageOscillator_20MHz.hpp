
#ifndef AVERAGEOSCILLATOR_20MHZ_HPP_
#define AVERAGEOSCILLATOR_20MHZ_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEstChain.hpp"

namespace AverageOscillator_20MHz
{

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================



class TdOracle_AvgOsc20MHz
{
    private:

        // Types
        class TdEstChain_WPM : public TdEstChain
        {
            public:     TdEstChain_WPM( unsigned int Seed );
        };

        class TdEstChain_WFM : public TdEstChain
        {
           public:     TdEstChain_WFM( unsigned int Seed );
        };

        class TdEstChain_FFM : public TdEstChain
        {
           public:     TdEstChain_FFM( unsigned int Seed );
        };

        class TdEstChain_RW : public TdEstChain
        {
            public:     TdEstChain_RW( unsigned int Seed );
        };

        // Config

        // Resources
        TdEstChain_WPM      WpmChain;
        TdEstChain_WFM      WfmChain;
        TdEstChain_FFM      FfmChain;
        TdEstChain_RW       RwChain;

    public:

        TdOracle_AvgOsc20MHz( unsigned int Seed );
        double  EstimateTd( double t_now, double t_req );
};




// =========================================================================
// Function declarations
// =========================================================================

}

#endif
