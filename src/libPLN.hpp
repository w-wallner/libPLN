// ============================================================================
///
/// \file
///
/// \brief  Main header file for libPLN.
///
/// This is the main header file for libPLN usage.
///
/// \ingroup module_main
///
// ============================================================================

// ============================================================================
/// \mainpage
///
/// \image html Mainpage/Burst_TD_Plot.png "Example plot showing PowerLaw Noise generated with libPLN"
///
/// \section sec_descr Description
///
/// LibPLN is a library that can efficiently produced PowerLaw Noise (PLN).
/// This is done by implementing a modified version of the filter approach
/// that was proposed by Kasdin and Walter in [1].
///
/// [1] Discrete simulation of power law noise
///     N.J. Kasdin, T. Walter
///     Frequency Control Symposium, 1992
///
/// \section sec_about About
///
/// LibPLN was developed by Wolfgang Wallner as part of his master thesis.
/// It is the result of an ongoing effort from 2013-2015 during which time
/// he was dealing with the simulation PLN and time synchronization via
/// IEEE 1588.
///
/// LibPLN is licensed under the GPL v3
///
/// Contact information:    wolfgang-wallner AT gmx.at
///
/// \section sec_install Installation
///
/// TODO
///
/// \section sec_usage Usage
///
/// TODO
///
/// \section sec_tools Tools
///
/// When dealing with the generation of PLN, one needs tools to efficiently
/// analyze the generated noise.
///
/// TODO: List resources
///
/// \section sec_credits Credits
///
/// LibPLN uses code from several open source projects:
///
/// - FFTW: the Fastest Fourier Transform in the West
///     http://www.fftw.org/
///
/// - Spline: a cubic spline implementation in C++
///     http://kluge.in-chemnitz.de/opensource/spline/
///
/// - Numeric tricks:
///     http://www.geeksforgeeks.org/next-power-of-2/
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

#ifndef LIBPLN_HPP_
#define LIBPLN_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEst/TdEstimator.hpp"
#include "TdEstChain.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

#endif
