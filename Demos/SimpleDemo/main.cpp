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
};

// =========================================================================
// Global variables
// =========================================================================

TdQuerry    TdQuerries[] =
{// T_now   T_request
    { 0.1,  0.1, },     // Asking the current time, this returns a stable result that won't change
    { 0.1,  0.1, },     // Asking again --> Result stays the same
    { 0.1,  0.5, },     // Asking a future time --> estimate of possible future
    { 0.1,  0.4, },     // Asking *another* future time --> old estimate changes
    { 0.1,  0.5, },     // Asking for 0.5 again leads now to a different result
    { 0.1,  0.5, },     // Asking several times for the same future time returns the same result
    { 0.2,  0.5, },     // Event if the is done at another time
    { 0.3,  0.5, },
    { 0.5,  0.5, },     // The previous estimate now actually became the truth and won't change anymore
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

    if( argc >= 2 )
    {
        Seed = atoi( argv[1] );
    }
    else
    {
        cout << "Not seed supplied on the command line." << endl;
        cout << "You could have supplied one as the first command line argument." << endl;
        cout << "Using time() to supply a random seed." << endl;

        Seed = static_cast<int>(time(NULL));

        cout << "Your seed is " << Seed << "." << endl;
    }

    cAvgOsc20MHz MyOsc( Seed, true );

    cout << "Starting to querry the simulated oscillator for the time deviation at different points in time." << endl;
    cout << endl;

    for( int i = 0; i < ArrayLen(TdQuerries); i++ )
    {
        TdQuerry q = TdQuerries[i];

        if( q.T_now == q.T_request )
        {
            cout << "Actual time deviation at time " << q.T_now << " = " << MyOsc.EstimateTD( q.T_now, q.T_request ) << endl;
        }
        else
        {
            cout << "Estimate of time deviation for time " << q.T_request << " at time " << q.T_now << " is " << MyOsc.EstimateTD( q.T_now, q.T_request ) << endl;
        }
    }

    cout << endl;
    cout << "Finished" << endl;

    return EXIT_SUCCESS;
}
