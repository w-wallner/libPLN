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

#ifndef LIBPLN_TEST_TEST_LIB_HPP_
#define LIBPLN_TEST_TEST_LIB_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "libPLN.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

void    SampleEstimator ( TdEstimator   e,  double &t, double fs, size_t NumSamples, bool EnableOutput, bool SaveSamples, std::string FileName );
void    SampleChain     ( TdEstChain    c,  double &t, double fs, size_t NumSamples, bool EnableOutput, bool SaveSamples, std::string FileName );
void    SampleOracle    ( TdOracle      &o, double &t, double fs, size_t NumSamples, bool EnableOutput, bool SaveSamples, std::string FileName );

void    BenchmarkTdOracle( TdOracle o, std::vector<double> f_s, size_t NumSamples, std::string OutputPath );

#endif
