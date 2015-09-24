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

#include "TdEstConfig.hpp"

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

std::ostream&
operator<<(std::ostream& os, const SampleConfig_t& o)
{
    os << "[SampleConfig]" << endl;
    os << endl;
    os << "TdVecLen = " << o.TdVecLen << endl;
    os << "f_s = " << o.f_s << endl;
    os << endl;

    return os;
}

std::ostream&
operator<<(std::ostream& os, const WhiteNoiseConfig_t& o)
{
    os << "[WhiteNoiseConfig]" << endl;
    os << endl;
    os << "Qd = " << o.Qd << endl;
    os << "Seed = " << o.Seed << endl;
    os << endl;

    return os;
}

std::ostream&
operator<<(std::ostream& os, const PLN_FilterImpl_t& o)
{
    switch( o )
    {
        case RECURSIVE_FILTER:      os << "RECURSIVE_FILTER";
                                    break;
        case KASDIN_WALTER_FILTER:  os << "KASDIN_WALTER_FILTER";
                                    break;
        default:                    os << "UNKNOWN_FILTER";
                                    break;
    }
    return os;
}

std::ostream&
operator<<(std::ostream& os, const PLN_FilterConfig_t& o)
{
    os << "[PlnFilterConfig]" << endl;
    os << endl;
    os << "FilterLen = " << o.FilterLen << endl;
    os << "alpha = " << o.alpha << endl;
    os << endl;

    return os;
}

std::ostream&
operator<<(std::ostream& os, const HP_FilterType_t& o)
{
    switch( o )
    {
        case BLACKMAN:   os << "BLACKMAN";
                         break;
        case NO_FILTER:  os << "NO_FILTER";
                         break;
        default:         os << "UNKNOWN_FILTER";
                         break;
    }
    return os;
}

std::ostream&
operator<<(std::ostream& os, const HP_FilterConfig_t& o)
{
    os << "[HpFilterConfig]" << endl;
    os << endl;
    os << "Cnt = " << o.Cnt << endl;
    os << "FilterLen = " << o.FilterLen << endl;
    os << "FilterType = " << o.FilterType << endl;
    os << "f_c_nom = " << o.f_c_nom << endl;
    os << endl;

    return os;
}

std::ostream&
operator<<(std::ostream& os, const InterpolationType_t& o)
{
    switch( o )
    {
        case LINEAR_INTERPOLATION:          os << "LINEAR_INTERPOLATION";
                                            break;
        case CUBIC_SPLINE_INTERPOLATION:    os << "CUBIC_SPLINE_INTERPOLATION";
                                            break;
        default:                            os << "UNKNOWN_INTERPOLATION";
                                            break;
    }
    return os;
}

std::ostream&
operator<<(std::ostream& os, const InterpolationConfig_t& o)
{
    os << "[InterpolationConfig]" << endl;
    os << endl;
    os << "InterPolType = " << o.InterPolType << endl;
    os << endl;

    return os;
}

std::ostream&
operator<<(std::ostream& os, const TimeConfig_t& o)
{
    os << "[TimeConfig]" << endl;
    os << endl;
    os << "EnableIntervalSkipping = " << o.EnableIntervalSkipping << endl;
    os << "T_val = " << o.T_val << endl;
    os << endl;

    return os;
}

std::ostream&
operator<<(std::ostream& os, const PerformanceConfig_t& o)
{
    os << "[PerformanceConfig]" << endl;
    os << endl;
    os << "ForgetTh = " << o.ForgetTh << endl;
    os << endl;

    return os;
}

std::ostream&
operator<<(std::ostream& os, const TdEstimatorConfig& o)
{
    os << o.WhiteNoiseConf;
    os << o.HP_FilterConf;
    os << o.InterpolConf;
    os << o.PLN_FilterConf;
    os << o.PLN_FilterImpl;
    os << o.PerformanceConf;
    os << o.SampleConf;
    os << o.TimeConf;
    os << endl;

    return os;
}
