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

#ifndef TDVECTOR_HPP_
#define TDVECTOR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "Utils/FFT_Types.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdVector
{
    public:

        // -----------------------------------------------------------------
        // Types
        // -----------------------------------------------------------------
        typedef enum
        {
            FFD_DATA,
            TD_DATA,
        }
        TdVecDataType;

    protected:

        // Config
        double  TickLen;
        double  t_beg;
        double  t_end;
        double  TD_0;

        // Resources
        std::vector<double> TD;

        // Internal functions
        virtual double  InterpolateAt( double t_req ) = 0;

    public:

        // Constructors/Destructor
                TdVector( double t_beg, double TD_0, double TickLen, FFT_RealVector *pFFD, size_t ValidLen, TdVecDataType DataType );
                TdVector( const TdVector& other );
        virtual ~TdVector();

        virtual TdVector* Clone() const = 0;  // Virtual constructor (copying)

        // Operators
        TdVector&  operator=( const TdVector& other );

        // API
        double  GetBeginTime();
        double  GetEndTime();
        double  GetBeginTD();
        double  GetEndTD();

        double  InterpolateTD_nom( double t_req );
};

// =========================================================================
// Function declarations
// =========================================================================


#endif
