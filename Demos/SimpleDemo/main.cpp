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

// =========================================================================
// Includes
// =========================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Examples/AverageOscillator_20MHz/AverageOscillator_20MHz.hpp"

using namespace std;
using namespace LibPLN_Examples;

// =========================================================================
// Defines
// =========================================================================

#define ArrayLen(A) (sizeof(A)/sizeof(A[0]))

// =========================================================================
// Type definitions
// =========================================================================

struct TdQuerry
{
    double  T_now;
    double  T_request;
    char    Description[200];
};

// =========================================================================
// Global variables
// =========================================================================

TdQuerry    TdQuerries[] =
{// T_now   T_request
    { 0.1,  0.1, "Asking the current time, this returns a stable result that won't change",                     },
    { 0.1,  0.1, "Asking the current time again --> result stays the same",                                     },
    { 0.1,  0.5, "Asking for an estimate at a future time",                                                     },
    { 0.1,  0.4, "Asking for an estimate at *another* future time --> old estimate becomes invalid",            },
    { 0.1,  0.5, "Asking for an estimate of future time again --> this leads now to a different result",        },
    { 0.1,  0.5, "Asking again for an estimate at the same future time several times returns the same result",  },
    { 0.2,  0.5, "... even if the is done at another time",                                                     },
    { 0.3,  0.5, "... and again.",                                                                              },
    { 0.5,  0.5, "The previous estimate now actually became the truth and won't change anymore",                },
};

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

int main( int argc, char *argv[] )
{
    int Seed;

    cout << "===========================================================" << endl;
    cout << "Simple demo program to demonstrate the usage of libPLN" << endl;
    cout << "===========================================================" << endl;
    cout << endl;

    if( argc >= 2 )
    {
        Seed = atoi( argv[1] );

        if( Seed == 0 )
        {
            Seed = static_cast<int>(time(NULL));
        }
    }
    else
    {
        cout << "No seed has been supplied on the command line." << endl;
        cout << "You could have supplied one as the first command line argument." << endl;
        cout << " --> Using time() to supply a random seed for this run." << endl;
        cout << "If a seed value of 0 is supplied, a time based seed is chosen without this warning." << endl;

        Seed = static_cast<int>(time(NULL));

        cout << "Your seed for the current run is " << Seed << "." << endl;
    }

    cAvgOsc20MHz MyOsc( Seed, true );

    cout << endl;
    cout << "Starting to query the simulated oscillator for the time deviation at different points in time." << endl;
    cout << endl;

    for( int i = 0; i < ArrayLen(TdQuerries); i++ )
    {
        TdQuerry q = TdQuerries[i];

        cout << "Step " << i+1 << ": ";

        if( q.T_now == q.T_request )
        {
            cout << "Requesting the current time deviation at time " << q.T_now << endl;
        }
        else
        {
            cout << "Requesting and estimate for time deviation at time " << q.T_request << endl;
        }
        cout << "Description of current request: " << q.Description << endl;

        double TD = MyOsc.EstimateTD( q.T_now, q.T_request );

        cout << "  Current time:   " << q.T_now << endl;
        cout << "  Requested time: " << q.T_request << endl;
        cout << "  Result: " << TD << endl;
        cout << endl;
    }

    cout << "Finished" << endl;

    return EXIT_SUCCESS;
}
