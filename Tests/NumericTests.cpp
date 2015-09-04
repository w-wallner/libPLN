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

// =========================================================================
// Includes
// =========================================================================

#include "NumericTests.hpp"

#include "Utils/NumericTricks.hpp"

#include <iostream>

using namespace std;
using namespace NumericTricks;

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef struct
{
    int n;
    int p;
}
Power2Test_t;

// =========================================================================
// Global variables
// =========================================================================

Power2Test_t    PowerOf2Tests[] =
{
    {   0,  1,  },
    {   1,  1,  },
    {   2,  2,  },
    {   3,  4,  },
    {   4,  4,  },
    {   5,  8,  },
    {   13, 16, },
    {   123456, 131072 },
};

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

void TestPowerOfTwo()
{
    cout << "Running " << __func__ << "()" << endl;

    Power2Test_t    *pT;

    for( int i = 0; i < NumElements(PowerOf2Tests); i ++ )
    {
        pT  = &PowerOf2Tests[i];

        int p = nextPowerOf2( pT->n );

        cout << "Next power of 2 greater than " << pT->n << " is " << p << endl;

        if( p != pT->p )
        {
            cerr << "===========================================" << endl;
            cerr << "   Testcase failed!!" << endl;
            cerr << "===========================================" << endl;
        }
    }
}
