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

#ifndef TDVECGEN_RECURSIVETDVECGEN_HPP_
#define TDVECGEN_RECURSIVETDVECGEN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVecGen.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

class RecursiveTdVecGen : public TdVecGen
{
    protected:

        // Config
        bool            EnableHpFilter;
        TdVecDataType   DataType;

        // Internal functions
        virtual void    ResetRecursiveFilter() = 0;
        virtual void    ApplyRecursiveFilter( FFT_RealVector *pw ) = 0;
        void            SetUpHpConvFilter( HP_FilterConfig HpConf, size_t TdVecLen );

    public:

        // Constructors/Destructor
        RecursiveTdVecGen( size_t TdVecLen, double TickLen, KW_FilterConfig KwConf, HP_FilterConfig HpConf, InterpolationConfig InterpolConf );
        RecursiveTdVecGen( const RecursiveTdVecGen& other );
        virtual ~RecursiveTdVecGen();

        virtual RecursiveTdVecGen* Clone() const = 0;  // Virtual constructor (copying)

        // Operators
        RecursiveTdVecGen&  operator=( const RecursiveTdVecGen& other );

        // API
        TdVector        *GetNextVector();
        virtual void    ResetToFixPoint( TdFixPoint fp );
};

#endif
