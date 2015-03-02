
#ifndef WHITENOISEGENERATOR_HPP_
#define WHITENOISEGENERATOR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <vector>
#include <cstddef>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>

#include "FFT_Types.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef boost::mt19937                     ENG;    // Mersenne Twister
typedef boost::normal_distribution<double> DIST;   // Normal Distribution
typedef boost::variate_generator<ENG,DIST> GEN;    // Variate generator

// =========================================================================
// Function declarations
// =========================================================================

class WhiteNoiseGenerator
{
    private:

        // Config

        // Resources
        ENG  eng;
        DIST dist;
        GEN  gen;

    public:

        WhiteNoiseGenerator( unsigned int Seed, double Qd );
        ~WhiteNoiseGenerator();

        FFT_RealVector      *GetFftVector( size_t VecLen, size_t FillLen );
        std::vector<double> *GetStdVector( size_t VecLen, size_t FillLen );
};


#endif
