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

#ifndef TDESTCONFIG_HPP_
#define TDESTCONFIG_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <cstddef>

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef struct
{
    double  f_s;
    size_t  TdVecLen;
}
SampleConfig_t;

typedef enum
{
    RECURSIVE_FILTER,
    KASDIN_WALTER_FILTER,
}
PLN_FilterImpl_t;

typedef struct
{
    unsigned int    Seed;
    double          Qd;
    double          alpha;
    size_t          FilterLen;
}
PLN_FilterConfig_t;

typedef enum
{
    BLACKMAN,
    NO_FILTER,
}
HP_FilterType_t;

typedef struct
{
    HP_FilterType_t     FilterType;
    double              f_c_nom;
    size_t              FilterLen;
    size_t              Cnt;
}
HP_FilterConfig_t;

typedef enum
{
    LINEAR_INTERPOLATION,
    CUBIC_SPLINE_INTERPOLATION
}
InterpolationType_t;

typedef struct
{
    InterpolationType_t  InterPolType;
}
InterpolationConfig_t;

typedef struct
{
    double  T_val;
}
TimeConfig_t;

typedef struct
{
    size_t  ForgetTh;
}
PerformanceConfig_t;

typedef struct
{
    SampleConfig_t          SampleConf;
    PLN_FilterConfig_t      PLN_FilterConf;
    PLN_FilterImpl_t        PLN_FilterImpl;
    HP_FilterConfig_t       HP_FilterConf;
    InterpolationConfig_t   InterpolConf;
    TimeConfig_t            TimeConf;
    PerformanceConfig_t     PerformanceConf;
}
TdEstimatorConfig;

// =========================================================================
// Function declarations
// =========================================================================

#endif
