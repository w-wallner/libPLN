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

#ifndef TDVECTORLINEAR_HPP_
#define TDVECTORLINEAR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVector.hpp"
#include "Utils/FFT_Types.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdVectorLinear : public TdVector
{
    private:

        // Config

        // Resources

        // Internal functions
        double  InterpolateAt( double t_req );

    public:

        // Constructors/Destructor
        TdVectorLinear( double t_beg, double TD_0, double TickLen, FFT_RealVector *pFFD, size_t ValidLen, TdVecDataType DataType );
        TdVectorLinear( const TdVectorLinear& other );
        ~TdVectorLinear();

        TdVectorLinear* Clone() const;

        // Operators
        TdVectorLinear&  operator=( const TdVectorLinear& other );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
