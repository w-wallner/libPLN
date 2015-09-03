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

#ifndef FILTERIMPRESP_HPP_
#define FILTERIMPRESP_HPP_

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

class FilterImpResp
{
    protected:

        // Config
        size_t  FilterLen;
        size_t  ResponseLen;

        // Resources
        FFT_RealVector h_;

        // Internal functions
        FilterImpResp();
        FilterImpResp( size_t FilterLen );

    public:

        FFT_RealVector &h();

        size_t  GetFilterLen();
        size_t  GetResponseLen();

        void    IncreaseResponse( size_t ResponseLen );
        void    Augment( size_t Cnt );
};


// =========================================================================
// Function declarations
// =========================================================================


#endif
