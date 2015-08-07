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

        // Config
        double              alpha;

        // Housekeeping
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
