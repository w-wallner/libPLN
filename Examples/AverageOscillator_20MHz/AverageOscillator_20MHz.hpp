// 
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
// 
// This file is part of libPLN.
// 
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License.com as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License.com for more details.
// 
// You should have received a copy of the GNU General Public License.com
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//

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
    public:

    // Types
         class TdEstChain_WPM : public TdEstChain
         {
             public:
                 // Constructors/Destructor
                 TdEstChain_WPM( unsigned int Seed );
                 TdEstChain_WPM( const TdEstChain_WPM& other );
                 virtual ~TdEstChain_WPM();

                 // Getters
                 static TdEstimatorConfig   GetConfig_WPM_20MHz(unsigned int Seed);
                 static TdEstimatorConfig   GetConfig_WPM_1MHz (unsigned int Seed);
                 static TdEstimatorConfig   GetConfig_WPM_10kHz(unsigned int Seed);
                 static TdEstimatorConfig   GetConfig_WPM_100Hz(unsigned int Seed);

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

                 // Getters
                 static TdEstimatorConfig   GetConfig_WFM_100Hz(unsigned int Seed);

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

                 // Getters
                 static TdEstimatorConfig   GetConfig_FFM_100Hz(unsigned int Seed);

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

                 // Getters
                 static TdEstimatorConfig   GetConfig_RW_100Hz(unsigned int Seed);

                 // Operators
                 virtual TdEstChain_RW& operator= (const TdEstChain_RW& other);
         };

    private:

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
        void    EnableIntervalSkipping();
        void    DisableIntervalSkipping();
        void    SetSeed( unsigned int Seed );
        double  EstimateTD( double t_now, double t_req );
};

// =========================================================================
// Function declarations
// =========================================================================

}

#endif
