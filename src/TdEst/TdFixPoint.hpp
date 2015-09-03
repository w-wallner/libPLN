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

#ifndef TDFIXPOINT_HPP_
#define TDFIXPOINT_HPP_

// =========================================================================
// Includes
// =========================================================================

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdFixPoint
{
    private:
        // Config
        double  t;
        double  TD_nom;

    public:
        TdFixPoint( double t, double TD_nom );

        double  Get_t() const;
        double  GetTD_nom() const;

        bool operator<( const TdFixPoint& other ) const;
};

// =========================================================================
// Function declarations
// =========================================================================


#endif
