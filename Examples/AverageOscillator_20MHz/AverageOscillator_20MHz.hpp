
#ifndef AVERAGEOSCILLATOR_20MHZ_HPP_
#define AVERAGEOSCILLATOR_20MHZ_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdOracle.hpp"

namespace AverageOscillator_20MHz
{

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdOracle_AvgOsc20MHz : public TdOracle
{
    private:

        // Types
        class TdEstChain_WPM : public TdEstChain
        {
            public:
                // Constructors/Destructor
                TdEstChain_WPM( unsigned int Seed );
                TdEstChain_WPM( const TdEstChain_WPM& other );
                virtual ~TdEstChain_WPM();

                // Operators
                virtual TdEstChain_WPM& operator= (const TdEstChain_WPM& other);
        };

        class TdEstChain_WFM : public TdEstChain
        {
            public:
                // Constructors/Destructor
                TdEstChain_WFM( unsigned int Seed );
                TdEstChain_WFM( const TdEstChain_WFM& other );
                virtual ~TdEstChain_WFM();

                // Operators
                virtual TdEstChain_WFM& operator= (const TdEstChain_WFM& other);
        };

        class TdEstChain_FFM : public TdEstChain
        {
            public:
                // Constructors/Destructor
                TdEstChain_FFM( unsigned int Seed );
                TdEstChain_FFM( const TdEstChain_FFM& other );
                virtual ~TdEstChain_FFM();

                // Operators
                virtual TdEstChain_FFM& operator= (const TdEstChain_FFM& other);
        };

        class TdEstChain_RW : public TdEstChain
        {
            public:
                // Constructors/Destructor
                TdEstChain_RW( unsigned int Seed );
                TdEstChain_RW( const TdEstChain_RW& other );
                virtual ~TdEstChain_RW();

                // Operators
                virtual TdEstChain_RW& operator= (const TdEstChain_RW& other);
        };

        // Config

        // Resources
        TdEstChain_WPM      WpmChain;
        TdEstChain_WFM      WfmChain;
        TdEstChain_FFM      FfmChain;
        TdEstChain_RW       RwChain;

    public:

        // Constructors/Destructor
        TdOracle_AvgOsc20MHz( unsigned int Seed );
        TdOracle_AvgOsc20MHz( const TdOracle_AvgOsc20MHz& other );
        virtual ~TdOracle_AvgOsc20MHz();

        // Operators
        TdOracle_AvgOsc20MHz&  operator=( const TdOracle_AvgOsc20MHz& other );

        // API

        double  EstimateTD( double t_now, double t_req );
};

// =========================================================================
// Function declarations
// =========================================================================

}

#endif
