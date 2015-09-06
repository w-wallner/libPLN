// ============================================================================
///
/// \file
///
/// \brief  TODO
///
/// TODO
///
/// \ingroup module_main
///
// ============================================================================

// ============================================================================
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
// ============================================================================

#ifndef TDESTIMATOR_HPP_
#define TDESTIMATOR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEstConfig.hpp"
#include "TdGuess.hpp"
#include "TdEst/TdVectorStorage/TdVectorStorage.hpp"
#include "TdVecGen/TdVecGen.hpp"

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
        bool    IntervalSkippingEnabled;

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
        double  GuessFutureRelativeTD( double t_req );

    public:

        // Constructors/Destructor
        TdEstimator( TdEstimatorConfig Conf );
        TdEstimator( const TdEstimator& other );
        ~TdEstimator();

        // Operators
        TdEstimator&  operator=( const TdEstimator& other );

        // API
        void    EnableIntervalSkipping();
        void    DisableIntervalSkipping();
        void    SetSeed( unsigned int Seed );
        double  EstimateTD( double t_now, double t_req );

        // Getters
        double      Get_f_s();
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
