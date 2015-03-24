// =========================================================================
// Includes
// =========================================================================

#include "BasicTests.hpp"

#include "TdVectorCubSpline.hpp"
#include "TdVecGen.hpp"
#include "GenericTdVecGen.hpp"
#include "WpmTdVecGen.hpp"
#include "WfmTdVecGen.hpp"
#include "RwTdVecGen.hpp"

#include <iostream>

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
void    TestTdVecStorage();
void    TestTdVecGen();
void    TestTdEst();

// =========================================================================
// Function definitions
// =========================================================================

void    TestTdVecStorage()
{
    TdVectorStorage    *pA;

    double          TickLen     = 1.0;
    size_t          ValidLen    = 10;
    TdVecDataType   DataType    = FFD_DATA;
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

    cout << "pA[3.0] = " << pA->InterpolateTD_nom( 3.0 ) << endl;

    {
        TdVectorStorage     B(5);

        B = *pA;

        cout << "B[3.0] = " << B.InterpolateTD_nom( 3.0 ) << endl;
    }

    TdVectorStorage     C(*pA);

    cout << "pA[3.0] = " << pA->InterpolateTD_nom( 3.0 ) << endl;

    pA->ForgetPast( 95 );

    cout << "C[3.0] = " << C.InterpolateTD_nom( 3.0 ) << endl;
}

void TestTdVecGen()
{
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

void TestTdEst()
{

}

void BasicTest1()
{
//    TestTdVecStorage();
//    TestTdVecGen();
    TestTdEst();
}
