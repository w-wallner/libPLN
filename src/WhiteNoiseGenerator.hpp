// 
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
// 
// This file is part of libPLN.
// 
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//

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
