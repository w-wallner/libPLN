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

#ifndef TDVECGEN_HPP_
#define TDVECGEN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEst/TdEstConfig.hpp"
#include "TdVector/TdVector.hpp"
#include "TdEst/TdFixPoint.hpp"
#include "Filter/FilterKernel.hpp"
#include "WhiteNoiseGenerator.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdVecGen
{
    protected:

        // Types
        typedef enum
        {
            UNINITIALIZED,
            INITIALIZED,
        }
        TdGenState;

        // Config
        double              TickLen;
        InterpolationType   IntpolType;
        size_t              TdVecLen;

        // House keeping
        TdGenState          ConvState;
        double              Last_t_end;
        double              Last_TD_nom;
        size_t              FfdVecLen;

        // Resources
        WhiteNoiseGenerator     WhiteNoiseGen;
        FilterKernel            H;
        FFT_RealVector          *pLastFFD;

        // Internal functions
        void        DisableConvFilter();
        void        InitConvFilter();
        void        ApplyConvFilter( FFT_RealVector *pw );
        void        ResetConvFilter();

        TdVector    *ConstructTdVector( FFT_RealVector *pData, TdVecDataType DataType );

    public:

        // Constructors/Destructor
        TdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, InterpolationConfig InterpolConf );
        TdVecGen( const TdVecGen& other );
        virtual ~TdVecGen();

        virtual TdVecGen* Clone() const = 0;  // Virtual constructor (copying)

        // Operators
        TdVecGen&  operator=( const TdVecGen& other );

        // API
        virtual void        ResetToFixPoint( TdFixPoint fp );
        virtual void        SetSeed( unsigned int Seed );
        virtual TdVector    *GetNextVector() = 0;
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
