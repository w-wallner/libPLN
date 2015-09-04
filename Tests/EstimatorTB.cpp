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

#include "EstimatorTB.hpp"

#include <iostream>
#include <fstream>

#include "libPLN.hpp"
#include "Utils/NumericTricks.hpp"
#include "Examples/AverageOscillator_20MHz/AverageOscillator_20MHz.hpp"

using namespace std;
using namespace AverageOscillator_20MHz;

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef struct
{
    double  t_now;
    double  t_req;
    double  dt_req;
    size_t  cnt;
}
TdBench;

// =========================================================================
// Global variables
// =========================================================================

TdBench TdBenches[] =
{
    { 3.2,    3.2,   0.1, 5 },
    { 15,     16.0,  0.1, 1 },
    { 16.05,  16.1,  0.1, 1 },
    { 16.1,   16.2,  0.1, 1 },
    { 16.1,   16.15, 0.1, 1 },
    { 16.1,   3.35,  0.1, 1 },
};

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

void
EstimatorTestBench()
{
    cout << "Running " << __func__ << "()" << endl;

    TdEstimatorConfig Conf;

    Conf.SampleConf.f_s              = 1E3;
    Conf.SampleConf.f_s              = 1E1;
    Conf.SampleConf.TdVecLen         = 1000;

    Conf.KwImplOption                = USE_SHORTCUTS;
//    Conf.KwImplOption                = FORCE_GENERIC;

//    Conf.KwFilterConf.Qd             = 1E-24;
    Conf.KwConf.Qd             = 1E-18 * sqrt(100);
    Conf.KwConf.alpha          = 2.0;
    Conf.KwConf.FilterLen      = 100;
    Conf.KwConf.Seed           = 1234;

    Conf.HpConf.Type           = BLACKMAN;
//    Conf.HpConf.Type           = NO_FILTER;
    Conf.HpConf.f_c_nom        = 0.05;
    Conf.HpConf.FilterLen      = 501;
    Conf.HpConf.Cnt            = 1;

    Conf.InterpolConf.Type           = CUBIC_SPLINE_INTERPOLATION;
    Conf.InterpolConf.Type           = LINEAR_INTERPOLATION;

    Conf.TimeConf.T_val              = Conf.KwConf.FilterLen * (1.0L/Conf.SampleConf.f_s);

    Conf.PerformanceConf.ForgetTh    = 0;

    TdEstimator e( Conf );

    double  t_now   = 0.0;
    double  t_req   = 0.0;

    for( size_t i = 0; i < NumElements(TdBenches); i ++ )
    {
        t_now   = TdBenches[ i ].t_now;
        t_req   = TdBenches[ i ].t_req;

        TdEstimate  est;
        for( size_t j = 0; j < TdBenches[ i ].cnt; j ++ )
        {
            est = e.EstimateTD( t_now, t_req );

            cout << "TD[" << t_now << "/" << t_req << "]: " << est.TD << endl;

            t_req += TdBenches[ i ].dt_req;
        }
    }
}

void
FileBench()
{
    cout << "Running " << __func__ << "()" << endl;

    TdEstimatorConfig Conf  = TdOracle_AvgOsc20MHz::TdEstChain_WPM::GetConfig_WPM_20MHz( 123 );

    TdEstChain  c;

    c.AddTdEstimator( Conf );

    double  fs;
    double  dt;
    size_t  MaxCnt;

    fs = 4020E-6;
    dt = 1.0L / fs;

    MaxCnt  = 100000;

    size_t CntThStep    = MaxCnt / 10;
    size_t NextTh       = CntThStep;
    bool PrintTh;

    PrintTh = true;
//    PrintTh = false;

    ofstream    TdFile;

    TdFile.open( "/main/td.txt" );

    TdFile.precision( 30 );

    double  t = 0.0;
    double  TD;
    for( size_t i = 0; i < MaxCnt; i ++ )
    {
        TD = c.EstimateTD( t, t );

        TdFile << TD << endl;

        if( PrintTh )
        {
            if( i >= NextTh )
            {
                cout << "Calculated " << i << " samples (t = " << t << ")." << endl;
                NextTh += CntThStep;
            }
        }

        t   += dt;
    }

    TdFile.close();
}
