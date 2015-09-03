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

#ifndef TDORACLE_HPP_
#define TDORACLE_HPP_

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

// =========================================================================
// Function declarations
// =========================================================================

class TdOracle
{
    private:

        // Config

        // Resources

    public:

        // Constructors/Destructor
        TdOracle();
        TdOracle( const TdOracle& other );
        virtual ~TdOracle();

        // Operators
        TdOracle&  operator=( const TdOracle& other );

        // API
        virtual void    EnableIntervalSkipping() = 0;
        virtual void    DisableIntervalSkipping() = 0;
        virtual void    SetSeed( unsigned int Seed ) = 0;
        virtual double  EstimateTD( double t_now, double t_req ) = 0;
};

#endif
