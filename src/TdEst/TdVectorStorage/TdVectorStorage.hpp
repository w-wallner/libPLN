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

#ifndef TDVECTORSTORAGE_HPP_
#define TDVECTORSTORAGE_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <set>

#include "TdVector/TdVector.hpp"
#include "TdEst/TdFixPoint.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef enum
{
    STARTUP,
    RUNNING,
}
TdVectorStorageState;

// =========================================================================
// Function declarations
// =========================================================================

class TdVectorStorage
{
    private:

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------
        size_t  ForgetTh;

        // -----------------------------------------------------------------
        // House keeping
        // -----------------------------------------------------------------
        TdVectorStorageState    State;

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------
        std::vector<TdVector *> Storage;
        TdFixPoint              fp;

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------
        size_t  FindIndex( double t );
        void    ClearStorage();

        // Debug functions
        void    Print();

    public:

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------
        TdVectorStorage( size_t ForgetTh );
        TdVectorStorage( const TdVectorStorage& other );
        ~TdVectorStorage();

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------
        TdVectorStorage&    operator= (const TdVectorStorage& other);

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------
        void    AddTdVec( TdVector *pTdVec );
        double  GetBeginTime();
        double  GetBeginTD();
        double  GetEndTime();
        double  GetEndTD();
        void    ResetToFixPoint( TdFixPoint fp );
        double  GetRelativeTD( double t_req );
        void    ForgetPast( double t_now );
};

#endif
