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
SampleConfig;

typedef enum
{
    USE_SHORTCUTS,
    FORCE_GENERIC
}
KW_ImplOption;

typedef struct
{
    unsigned int    Seed;
    double          Qd;
    double          alpha;
    size_t          FilterLen;
}
KW_FilterConfig;

typedef enum
{
    BLACKMAN,
    NO_FILTER,
}
HP_FilterType;

typedef struct
{
    HP_FilterType   Type;
    double          f_c_nom;
    size_t          FilterLen;
    size_t          Cnt;
}
HP_FilterConfig;

typedef enum
{
    LINEAR_INTERPOLATION,
    CUBIC_SPLINE_INTERPOLATION
}
InterpolationType;

typedef struct
{
    InterpolationType   Type;
}
InterpolationConfig;

typedef struct
{
    double  T_val;
}
TimeConfig;

typedef struct
{
    size_t  ForgetTh;
}
PerformanceConfig;

typedef struct
{
    SampleConfig            SampleConf;
    KW_FilterConfig         KwConf;
    KW_ImplOption           KwImplOption;
    HP_FilterConfig         HpConf;
    InterpolationConfig     InterpolConf;
    TimeConfig              TimeConf;
    PerformanceConfig       PerformanceConf;
}
TdEstimatorConfig;

// =========================================================================
// Function declarations
// =========================================================================


#endif
