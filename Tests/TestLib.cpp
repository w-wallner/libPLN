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
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
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

    if( EnableOutput )
    {
        cout << "Sample configuration:" << endl;
        cout << "Sampling frequency: " << fs << "Hz" << endl;
        cout << "Step width: " << dt << "s" << endl;
        cout << "Number of samples: " << NumSamples << endl;
        cout << "T0: " << t << endl;
    }

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

void BenchmarkTdOracle( TdOracle o, std::vector<double> f_s, size_t NumSamples, std::string OutputPath )
{
    double  t;

    std::string     FrequListFileName;
    ofstream        FrequList;

    // Init
    FrequListFileName = OutputPath + "FrequList.txt";
    FrequList.open( FrequListFileName.c_str() );

    t = 0.0L;
    size_t  i = 0;
    for (std::vector<double>::iterator it = f_s.begin() ; it != f_s.end(); ++it, ++i)
    {
        // Init
        std::stringstream ssFilename;
        ssFilename << OutputPath << "td_" << i << ".txt";

        cout << endl;
        cout << "Starting benchmark " << i + 1 << "/" << f_s.size() << " for " << *it << endl;

        FrequList << *it << endl;
        SampleOracle( o, t, *it, NumSamples, true, true, ssFilename.str() );

        cout << "Finished benchmark for " << *it << endl;
    }
    FrequList.close();
}
