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

#include "BasicTests.hpp"

#include "TdEst/TdVectorStorage/TdVectorStorage.hpp"
#include "TdVector/TdVectorCubSpline.hpp"
#include "TdVecGen/TdVecGen.hpp"
#include "TdVecGen/GenericTdVecGen.hpp"
#include "TdVecGen/WpmTdVecGen.hpp"
#include "TdVecGen/WfmTdVecGen.hpp"
#include "TdVecGen/RwTdVecGen.hpp"
#include "TdVecGen/TdVecGenFactory.hpp"

#include "DebugTools/DebugConfig.hpp"
#include "DebugTools/DebugSink.hpp"

#include "Examples/AverageOscillator_20MHz/AverageOscillator_20MHz.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace LibPLN_Examples;

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
TestTdVecStorage()
{
    cout << "Running " << __func__ << "()" << endl;

    TdVectorStorage    *pA;

    double                      TickLen     = 1.0;
    size_t                      ValidLen    = 10;
    TdVector::TdVecDataType     DataType    = TdVector::FFD_DATA;
    FFT_RealVector *pFFD = new FFT_RealVector(10);

    std::fill( pFFD->begin(), pFFD->end(), 1);

    double  t0 = 0.0;

    pA = new TdVectorStorage(8);

    for( size_t i = 0; i < 10; i ++ )
    {
        double  IntervalLen = ValidLen * TickLen;

        TdVector *pVec = new TdVectorCubSpline( t0, 0, TickLen, pFFD, ValidLen, DataType );

        pA->AddTdVec( pVec );

        t0 += IntervalLen;
    }

    cout << "pA[3.0] = " << pA->GetRelativeTD( 3.0 ) << endl;

    {
        TdVectorStorage     B(5);

        B = *pA;

        cout << "B[3.0] = " << B.GetRelativeTD( 3.0 ) << endl;
    }

    TdVectorStorage     C(*pA);

    cout << "pA[3.0] = " << pA->GetRelativeTD( 3.0 ) << endl;

    pA->ForgetPast( 95 );

    cout << "C[3.0] = " << C.GetRelativeTD( 3.0 ) << endl;
}

void
TestTdVecGen()
{
    cout << "Running " << __func__ << "()" << endl;

    DebugSink.SetFileSavePath( "/home/woife/" );
    DebugSink.SetFilePrefix( "Test" );
    DebugSink.EnableAll();

    TdVecGenConfig_t    TdVecGenConf;

    TdVecGenConf.SampleConf.TdVecLen = 500;
    TdVecGenConf.SampleConf.f_s  = 1.0;

    TdVecGenConf.WhiteNoiseConf.Qd           = 10E-2;
    TdVecGenConf.WhiteNoiseConf.Seed         = 5432;

    TdVecGenConf.PLN_FilterConf.Implementation  = RECURSIVE_FILTER;
    TdVecGenConf.PLN_FilterConf.Implementation  = KASDIN_WALTER_FILTER;
    TdVecGenConf.PLN_FilterConf.FilterLen    = 50;
    TdVecGenConf.PLN_FilterConf.alpha        = FSA::ALPHA_WPM;
    TdVecGenConf.PLN_FilterConf.alpha        = FSA::ALPHA_FPM;
    TdVecGenConf.PLN_FilterConf.alpha        = FSA::ALPHA_WFM;
    TdVecGenConf.PLN_FilterConf.alpha        = FSA::ALPHA_FFM;
    TdVecGenConf.PLN_FilterConf.alpha        = FSA::ALPHA_RW;

    TdVecGenConf.HP_FilterConf.Cnt           = 7;
    TdVecGenConf.HP_FilterConf.FilterLen     = 7;
    TdVecGenConf.HP_FilterConf.FilterType    = BLACKMAN;
//    TdVecGenConf.HP_FilterConf.FilterType    = IDENTITY;
//    TdVecGenConf.HP_FilterConf.FilterType    = NO_FILTER;
    TdVecGenConf.HP_FilterConf.f_c_nom       = 0.2;

    TdVecGenConf.InterpolConf.InterPolType   = CUBIC_SPLINE_INTERPOLATION;


    TdVecGen *pA = TdVecGenFactory::CreateTdVecGen( TdVecGenConf );

    cout << pA->GetNextVector()->GetEndTD() << endl;
    cout << pA->GetNextVector()->GetEndTD() << endl;
    /*
    cout << pA->GetNextVector()->GetEndTD() << endl;
    cout << endl;

    {
        TdVecGen *pB = pA->Clone();

        cout << pB->GetNextVector()->GetEndTD() << endl;
        cout << pB->GetNextVector()->GetEndTD() << endl;
        cout << pB->GetNextVector()->GetEndTD() << endl;
        cout << endl;
    }

    cout << pA->GetNextVector()->GetEndTD() << endl;
    cout << pA->GetNextVector()->GetEndTD() << endl;
    cout << pA->GetNextVector()->GetEndTD() << endl;
    cout << endl;
    */
}

void
TestWpmTdVecGen()
{
    cout << "Running " << __func__ << "()" << endl;

    std::string     FileName = "/main/VecSums.txt";
    std::ofstream   OutFile;

    OutFile.open( FileName.c_str(), std::ifstream::out );

    TdEstimatorConfig Conf = cAvgOsc20MHz::TdEstChain_WPM::GetConfig_20MHz( 123, true );

    GenericTdVecGen g( Conf.TdVecGenConf );

    TdVector *pTdVec;

    for( int i = 0; i < 100000; i ++ )
    {
        g.ResetToFixPoint( TdFixPoint( 0.0, 0.0 ) );

        pTdVec = g.GetNextVector();

        /*
        for( int j = 0; j < 100; j ++ )
        {
            cout << pTdVec->GetRelativeTD( j * TickLen ) << endl;
        }
        */

        OutFile << pTdVec->GetEndTD() << endl;

        delete pTdVec;
    }

    OutFile.close();
}

void
TestTdEst()
{
    cout << "Running " << __func__ << "()" << endl;
    cout << "(Nothing implemented yet)" << endl;
}
