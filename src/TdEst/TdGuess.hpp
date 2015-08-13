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

#ifndef TDGUESS_HPP_
#define TDGUESS_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdFixPoint.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class  TdGuess
{
private:

    bool        active;

    TdFixPoint  fp;

public:

    TdGuess();

    bool        IsActive();
    bool        BecameValid( double t_now );
    void        Set( TdFixPoint fp );
    TdFixPoint  GetFP();
    void        Reset();
};

// =========================================================================
// Function declarations
// =========================================================================


#endif
