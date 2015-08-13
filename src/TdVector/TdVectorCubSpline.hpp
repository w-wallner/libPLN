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

#ifndef TDVECTORCUBSPLINE_HPP_
#define TDVECTORCUBSPLINE_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVector/TdVector.hpp"
#include "Utils/FFT_Types.hpp"
#include "Utils/spline.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdVectorCubSpline : public TdVector
{
    private:

        // Types
        typedef enum
        {
            UNINITIALIZED,
            INITIALIZED,
        }
        SplineState;

        // Config

        // Housekeeping
        SplineState State;

        // Resources
        tk::spline          s;
        std::vector<double> t;

        // Internal functions
        double  InterpolateAt( double t_req );

    public:

        // Constructors/Destructor
        TdVectorCubSpline( double t_beg, double TD_0, double TickLen, FFT_RealVector *pData, size_t ValidLen, TdVecDataType DataType );
        TdVectorCubSpline( const TdVectorCubSpline& other );
        ~TdVectorCubSpline();

        TdVectorCubSpline* Clone() const;

        // Operators
        TdVectorCubSpline&  operator=( const TdVectorCubSpline& other );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
