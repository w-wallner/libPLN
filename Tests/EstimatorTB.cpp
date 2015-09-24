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
#include "Examples/WatchQuartz_20MHz/WatchQuartz_20MHz.hpp"
#include "TestLib.hpp"

using namespace std;
using namespace LibPLN_Examples;

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

    Conf.WhiteNoiseConf.Qd           = 1E-18 * sqrt(100);
    Conf.WhiteNoiseConf.Seed         = 1234;

    Conf.PLN_FilterConf.alpha        = FSA::ALPHA_WPM;
    Conf.PLN_FilterConf.FilterLen    = 100;

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

        double TD;
        for( size_t j = 0; j < TdBenches[ i ].cnt; j ++ )
        {
            TD = e.EstimateTD( t_now, t_req );

            cout << "TD[" << t_now << "/" << t_req << "]: " << TD << endl;

            t_req += TdBenches[ i ].dt_req;
        }
    }
}

void
AvgOscChainTestBench()
{
    cout << "Running " << __func__ << "()" << endl;

    unsigned int Seed = 1;
    bool         Skip = true;

    cAvgOsc20MHz::TdEstChain_WPM    WpmChain(10, Seed, Skip);
    cAvgOsc20MHz::TdEstChain_FPM    FpmChain(20, Seed, Skip);
    cAvgOsc20MHz::TdEstChain_WFM    WfmChain(30, Seed, Skip);
    cAvgOsc20MHz::TdEstChain_FFM    FfmChain(40, Seed, Skip);
    cAvgOsc20MHz::TdEstChain_RW     RwChain (50, Seed, Skip);
    TdEstChain  c(FSA::ALPHA_WFM, 0);

    c = WpmChain;
    //c = FpmChain;
    //c = WfmChain;
    //c = FfmChain;
    //c = RwChain;

    double  fs;
    double  dt;
    size_t  NumSamples;
    double  t;

    t = 0.0;

    fs = 40E6;
    //fs = 4E6;
    //fs = 1E5;
    //fs = 400;

    NumSamples  = 10200;
    NumSamples  = 100000;
    NumSamples  = 1000000;

    SampleChain( c, t, fs, NumSamples, true, true, "/main/td.txt" );
}

void
WatchChainTestBench()
{
    cout << "Running " << __func__ << "()" << endl;

    unsigned int Seed = 1;
    bool         Skip = true;

    cWatchQuartz_20MHz::TdEstChain_WFM  WfmChain(10, Seed, Skip);
    //cWatchQuartz_20MHz::TdEstChain_FFM  FfmChain(20, Seed, Skip);
    //cWatchQuartz_20MHz::TdEstChain_RW   RwChain (30, Seed, Skip);
    TdEstChain  c(FSA::ALPHA_WFM, 0);

    c = WfmChain;
    //c = FfmChain;
    //c = RwChain;

    double  fs;
    double  dt;
    size_t  NumSamples;
    double  t;

    t = 0.0;

    fs = 40E6;
    fs = 4E6;
    fs = 1E5;
    fs = 1E3;
    fs = 2E2;
    //fs = 1E2;
    //fs = 1E1;
    //fs = 1E0;
    //fs = 1E-1;
    //fs = 400;
    //fs = 1E-2;

    NumSamples  = 10200;
//    NumSamples  = 100000;
//    NumSamples  = 1000000;
//    NumSamples  = 10000000;
//    NumSamples  = 100000000;

    SampleChain( c, t, fs, NumSamples, true, true, "/main/td.txt" );
}
