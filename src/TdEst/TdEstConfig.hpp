// ============================================================================
///
/// \file
///
/// \brief  Configuration options for the time deviation estimator.
///
/// \ingroup module_td_estimator
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

#ifndef LIBPLN_SRC_TDEST_TDESTCONFIG_HPP_
#define LIBPLN_SRC_TDEST_TDESTCONFIG_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <cstddef>
#include <iostream>

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Configuration for sampling process that should be simulated
typedef struct
{
    double  f_s;            ///< Simulated sampling frequency
    size_t  TdVecLen;       ///< Length of simulated time deviation vectors
}
SampleConfig_t;

/// Configuration for the powerlaw noise generation process
typedef struct
{
    unsigned int    Seed;       ///< Seed for the random number generator.
    double          Qd;         ///< Standard variance for the random number generator.
}
WhiteNoiseConfig_t;

/// Enumeration to encode different ways how powerlaw noise can
/// be generated
typedef enum
{
    RECURSIVE_FILTER,           ///< Recursive filter. Available for noise types where alpha is even (WPM, WFM, RW noise).
    KASDIN_WALTER_FILTER,       ///< Generic Filter as proposed by Kasdin and Walter
}
PLN_FilterImpl_t;

/// Configuration for the powerlaw noise generation process
typedef struct
{
    PLN_FilterImpl_t    Implementation;     ///< Configuration for the PLN filter implementation
    double              alpha;              ///< Exponent of the powerlaw noise. The power spectral density is proportional to f^alpha.
    size_t              FilterLen;          ///< Length of the Filter. Only meaningful for the KW filter implementation.
}
PLN_FilterConfig_t;

/// Enumeration to encode different available high pass filter types
typedef enum
{
    IDENTITY,       ///< Identity filter
    BLACKMAN,       ///< Blackman window
    NO_FILTER,      ///< No filter
}
HP_FilterType_t;

/// High pass filter configuration
typedef struct
{
    HP_FilterType_t     FilterType;     ///< The type of the filter that should be used
    double              f_c_nom;        ///< Nominal cutoff frequency
    size_t              FilterLen;      ///< Length of the high pass filter
    size_t              Cnt;            ///< Number of times the filter should be applied
}
HP_FilterConfig_t;

/// Enumeration to encode different interpolation options.
typedef enum
{
    LINEAR_INTERPOLATION,               ///< Linear interpolation.
    CUBIC_SPLINE_INTERPOLATION          ///< Cubic spline interpolation.
}
InterpolationType_t;

/// Interpolation configuration
typedef struct
{
    InterpolationType_t  InterPolType;      ///< Type of interpolation that should be used
}
InterpolationConfig_t;

/// Time configuration
typedef struct
{
    bool    EnableIntervalSkipping;         ///< Allows the estimator to guess time deviation values for requests in the distant future.
    double  T_val;                          ///< Time in seconds between samples where this estimator is considered to be 'valid'.
}
TimeConfig_t;

/// Performance configuration
typedef struct
{
    size_t  ForgetTh;       ///< Size threshold for the number of stored time deviation vectors.
                            ///< If the size of the vector storage grows beyond this threshold,
                            ///< old vectors will be deleted.
                            ///< This value is a tradeoff between memory requirements and speed.
                            ///< 0 means 'choose default value'.
}
PerformanceConfig_t;

/// Performance configuration
typedef struct
{
    SampleConfig_t          SampleConf;             ///< Configuration for the simulated sampling process
    WhiteNoiseConfig_t      WhiteNoiseConf;         ///< Configuration for the white noise generator
    PLN_FilterConfig_t      PLN_FilterConf;         ///< Configuration for the PLN filter
    HP_FilterConfig_t       HP_FilterConf;          ///< Configuration for the high pass filter
    InterpolationConfig_t   InterpolConf;           ///< Configuration for the interpolation
}
TdVecGenConfig_t;

/// Configuration for a time deviation estimator
typedef struct
{
    TdVecGenConfig_t        TdVecGenConf;           ///< Configuration for time deviation vector generator
    TimeConfig_t            TimeConf;               ///< Configuration for timing relevant options
    PerformanceConfig_t     PerformanceConf;        ///< Configuration for performance relevant options
}
TdEstimatorConfig;

// =========================================================================
// Function declarations
// =========================================================================

std::ostream& operator<<(std::ostream& os, const SampleConfig_t& o);
std::ostream& operator<<(std::ostream& os, const WhiteNoiseConfig_t& o);
std::ostream& operator<<(std::ostream& os, const PLN_FilterImpl_t& o);
std::ostream& operator<<(std::ostream& os, const PLN_FilterConfig_t& o);
std::ostream& operator<<(std::ostream& os, const HP_FilterType_t& o);
std::ostream& operator<<(std::ostream& os, const HP_FilterConfig_t& o);
std::ostream& operator<<(std::ostream& os, const InterpolationType_t& o);
std::ostream& operator<<(std::ostream& os, const InterpolationConfig_t& o);
std::ostream& operator<<(std::ostream& os, const TimeConfig_t& o);
std::ostream& operator<<(std::ostream& os, const PerformanceConfig_t& o);
std::ostream& operator<<(std::ostream& os, const TdVecGenConfig_t& o);
std::ostream& operator<<(std::ostream& os, const TdEstimatorConfig& o);

#endif
