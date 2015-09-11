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

#include "TestLib.hpp"

#include <iostream>
#include <fstream>

using namespace std;

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Global variables
// =========================================================================

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

void
SampleEstimator( TdEstimator e, double &t, double fs, size_t NumSamples, bool EnableOutput, bool SaveSamples, std::string FileName )
{
    SampleChain( TdEstChain( e, 0 ), t, fs, NumSamples, EnableOutput, SaveSamples, FileName );
}

void
SampleChain( TdEstChain c, double &t, double fs, size_t NumSamples, bool EnableOutput, bool SaveSamples, std::string FileName )
{
    TdOracle    o( c );

    SampleOracle( o, t, fs, NumSamples, EnableOutput, SaveSamples, FileName );
}

void
SampleOracle( TdOracle &o, double &t, double fs, size_t NumSamples, bool EnableOutput, bool SaveSamples, std::string FileName )
{
    double      dt;
    double      TD;
    size_t      CntThStep;
    size_t      NextTh;
    ofstream    TdFile;
    size_t      i;

    dt          = 1.0L / fs;
    CntThStep   = NumSamples / 10;
    NextTh      = CntThStep;

    if( SaveSamples )
    {
        TdFile.open( FileName.c_str() );
        TdFile.precision( 30 );
    }

    for( i = 0; i < NumSamples; i ++ )
    {
        TD  = o.EstimateTD( t, t );

        if( SaveSamples )
        {
            TdFile << TD << endl;
        }

        if( EnableOutput )
        {
            if( i >= NextTh )
            {
                cout << "Calculated " << i << " of " << NumSamples << " samples (t = " << t << ")." << endl;
                NextTh += CntThStep;
            }
        }

        t   += dt;
    }

    if( EnableOutput )
    {
        cout << "Calculated " << i << " of " << NumSamples << " samples (t = " << t << ")." << endl;
    }

    if( SaveSamples )
    {
        TdFile.close();
    }
}
