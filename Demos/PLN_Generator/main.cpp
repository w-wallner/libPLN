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
#include <fstream>
#include <iomanip>

#include "PlnGenConfig.hpp"

#include "TdVecGen/TdVecGen.hpp"
#include "TdVecGen/TdVecGenFactory.hpp"

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
SampleTdVecGen( PlnGenConfig::PlnGenConfig_t conf )
{
    TdVecGen*   pTdVecGen   = TdVecGenFactory::CreateTdVecGen( conf.TdVecGenConfig );

    double  dt  = 1.0L/conf.fi;
    double  t   = 0.0L;

    size_t  SampleCnt;
    size_t  VecCnt  = 1;

    ofstream out;
    out.open( conf.Filename.c_str() );
    out << std::setprecision(30);

    for( SampleCnt = 0; SampleCnt < conf.ns; )
    {
        TdVector    *pTdVec = pTdVecGen->GetNextVector();
        double      T_end   = pTdVec->GetEndTime();

        if( conf.veryVerbose )
        {
            cout << "Sampling vector #" << VecCnt++ << endl;
            cout << "Begin time: " << pTdVec->GetBeginTime() << endl;
            cout << "End time:   " << pTdVec->GetEndTime() << endl;
            cout << "Begin time deviation: " << pTdVec->GetBeginTD() << endl;
            cout << "End time deviation:   " << pTdVec->GetEndTD() << endl;
            cout << endl;
        }

        while(( t < T_end ) && (SampleCnt < conf.ns) )
        {
            out << pTdVec->GetTD( t ) << endl;

            t += dt;
            SampleCnt ++;
        }

        delete pTdVec;
    }

    out.close();

    delete pTdVecGen;
}

int main( int argc, char *argv[] )
{
    PlnGenConfig                    c;
    PlnGenConfig::PlnGenConfig_t    conf;

    conf = c.ParseProgramOptions( argc, argv );

    if( conf.verbose )
    {
        cout << "Configured TimeDeviationVectorGenerator config: " << endl;
        cout << endl;
        cout << conf.TdVecGenConfig;
    }

    SampleTdVecGen( conf );

    if( conf.verbose )
    {
        cout << "Finished" << endl;
    }

    return EXIT_SUCCESS;
}
