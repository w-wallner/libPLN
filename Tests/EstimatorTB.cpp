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

    Conf.PLN_FilterImpl              = RECURSIVE_FILTER;
//    Conf.PLN_FilterImpl              = KASDIN_WALTER_FILTER;

    Conf.PLN_FilterConf.Qd           = 1E-18 * sqrt(100);
    Conf.PLN_FilterConf.alpha        = 2.0;
    Conf.PLN_FilterConf.FilterLen    = 100;
    Conf.PLN_FilterConf.Seed         = 1234;

    Conf.HP_FilterConf.FilterType    = BLACKMAN;
//    Conf.HP_FilterConf.Type          = NO_FILTER;
    Conf.HP_FilterConf.f_c_nom       = 0.05;
    Conf.HP_FilterConf.FilterLen     = 501;
    Conf.HP_FilterConf.Cnt           = 1;

    Conf.InterpolConf.InterPolType   = CUBIC_SPLINE_INTERPOLATION;
    Conf.InterpolConf.InterPolType   = LINEAR_INTERPOLATION;

    Conf.TimeConf.T_val              = Conf.PLN_FilterConf.FilterLen * (1.0L/Conf.SampleConf.f_s);

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

    TdEstimatorConfig Conf_WPM_20MHz  = TdOracle_AvgOsc20MHz::TdEstChain_WPM::GetConfig_WPM_20MHz( 1 );
    TdEstimatorConfig Conf_WPM_1MHz   = TdOracle_AvgOsc20MHz::TdEstChain_WPM::GetConfig_WPM_1MHz ( 2 );
    TdEstimatorConfig Conf_WPM_10kHz  = TdOracle_AvgOsc20MHz::TdEstChain_WPM::GetConfig_WPM_10kHz( 3 );
    TdEstimatorConfig Conf_WPM_100Hz  = TdOracle_AvgOsc20MHz::TdEstChain_WPM::GetConfig_WPM_100Hz( 4 );

    TdEstimatorConfig Conf_WFM_100Hz  = TdOracle_AvgOsc20MHz::TdEstChain_WFM::GetConfig_WFM_100Hz( 5 );

    TdEstimatorConfig Conf_FFM_100Hz  = TdOracle_AvgOsc20MHz::TdEstChain_FFM::GetConfig_FFM_100Hz( 6 );

    TdEstimatorConfig Conf_RW_100Hz   = TdOracle_AvgOsc20MHz::TdEstChain_RW::GetConfig_RW_100Hz  ( 7 );

    TdEstChain  WpmChain;
    TdEstChain  WfmChain;
    TdEstChain  FfmChain;
    TdEstChain  RwChain;
    TdEstChain  c;

    WpmChain.AddTdEstimator( Conf_WPM_20MHz );
    WpmChain.AddTdEstimator( Conf_WPM_1MHz  );
    WpmChain.AddTdEstimator( Conf_WPM_10kHz );
    WpmChain.AddTdEstimator( Conf_WPM_100Hz );

    WfmChain.AddTdEstimator( Conf_WFM_100Hz );

    FfmChain.AddTdEstimator( Conf_FFM_100Hz );

    RwChain.AddTdEstimator( Conf_RW_100Hz );

    c = WpmChain;
    c = WfmChain;
    c = FfmChain;
    c = RwChain;

    double  fs;
    double  dt;
    size_t  MaxCnt;

    fs = 40E6;
    fs = 4E6;
    fs = 1E5;
    fs = 400;
    dt = 1.0L / fs;

    MaxCnt  = 100000;
    MaxCnt  = 1000000;

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
