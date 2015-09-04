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

#include "TdVectorStorage.hpp"
#include "TdVector/TdVectorCubSpline.hpp"
#include "TdVecGen/TdVecGen.hpp"
#include "TdVecGen/GenericTdVecGen.hpp"
#include "TdVecGen/WpmTdVecGen.hpp"
#include "TdVecGen/WfmTdVecGen.hpp"
#include "TdVecGen/RwTdVecGen.hpp"

#include "AverageOscillator_20MHz/AverageOscillator_20MHz.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace AverageOscillator_20MHz;

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

void    TestTdVecStorage()
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

    cout << "pA[3.0] = " << pA->InterpolateTD( 3.0 ) << endl;

    {
        TdVectorStorage     B(5);

        B = *pA;

        cout << "B[3.0] = " << B.InterpolateTD( 3.0 ) << endl;
    }

    TdVectorStorage     C(*pA);

    cout << "pA[3.0] = " << pA->InterpolateTD( 3.0 ) << endl;

    pA->ForgetPast( 95 );

    cout << "C[3.0] = " << C.InterpolateTD( 3.0 ) << endl;
}

void TestTdVecGen()
{
    cout << "Running " << __func__ << "()" << endl;

    size_t TdVecLen;
    double TickLen;
    KW_FilterConfig KwConf;
    HP_FilterConfig HpConf;
    InterpolationConfig InterpolConf;

    TdVecLen = 100;
    TickLen  = 1.0;

    KwConf.FilterLen    = 10;
    KwConf.Qd           = 10E-2;
    KwConf.Seed         = 5432;
    KwConf.alpha        = -2.0;

    HpConf.Cnt          = 1;
    HpConf.FilterLen    = 11;
    HpConf.Type         = BLACKMAN;
    HpConf.f_c_nom      = 0.5;

    InterpolConf.Type   = CUBIC_SPLINE_INTERPOLATION;

    TdVecGen *pA;

    //pA = new GenericTdVecGen( TdVecLen, TickLen, KwConf, HpConf, InterpolConf );
    //pA = new WpmTdVecGen( TdVecLen, TickLen, KwConf, HpConf, InterpolConf );
    //pA = new WfmTdVecGen( TdVecLen, TickLen, KwConf, HpConf, InterpolConf );
    pA = new RwTdVecGen( TdVecLen, TickLen, KwConf, HpConf, InterpolConf );

    cout << pA->GetNextVector()->GetEndTD() << endl;
    cout << pA->GetNextVector()->GetEndTD() << endl;
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
}

void    TestWpmTdVecGen()
{
    cout << "Running " << __func__ << "()" << endl;

    std::string     FileName = "/main/VecSums.txt";
    std::ofstream   OutFile;

    OutFile.open( FileName.c_str(), std::ifstream::out );

    TdEstimatorConfig Conf = TdOracle_AvgOsc20MHz::TdEstChain_WPM::GetConfig_WPM_20MHz( 123 );
    double  TickLen = 1.0L / Conf.SampleConf.f_s;

    GenericTdVecGen g( Conf.SampleConf.TdVecLen, TickLen, Conf.KwConf, Conf.HpConf, Conf.InterpolConf );

    TdVector *pTdVec;

    for( int i = 0; i < 100000; i ++ )
    {
        g.ResetToFixPoint( TdFixPoint( 0.0, 0.0 ) );

        pTdVec = g.GetNextVector();

        /*
        for( int j = 0; j < 100; j ++ )
        {
            cout << pTdVec->InterpolateTD_nom( j * TickLen ) << endl;
        }
        */

        OutFile << pTdVec->GetEndTD() << endl;

        delete pTdVec;
    }

    OutFile.close();
}

void TestTdEst()
{
    cout << "Running " << __func__ << "()" << endl;
    cout << "(Nothing implemented yet)" << endl;
}
