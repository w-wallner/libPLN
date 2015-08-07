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

#ifndef TDESTIMATOR_HPP_
#define TDESTIMATOR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEstConfig.hpp"
#include "TdVecGen.hpp"
#include "TdGuess.hpp"
#include "TdVectorStorage.hpp"

#include <iostream>

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
        double  GuessFutureTD_nom( double t_req );

    public:

        // Constructors/Destructor
        TdEstimator( TdEstimatorConfig Conf );
        TdEstimator( const TdEstimator& other );
        ~TdEstimator();

        // Operators
        TdEstimator&  operator=( const TdEstimator& other );

        // API
        TdEstimate  EstimateTD( double t_now, double t_req );

        // Getters
        double      Get_f_s();
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
