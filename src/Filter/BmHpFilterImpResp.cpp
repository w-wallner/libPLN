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
//
// Source is based on the description in a DSP book
// and MATLAB example from the web
//
// Book title:
// 'The Scientist and Engineer's Guide to Digital Signal Processing'
//
// MATLAB implementation:
// http://www.gomatlab.de/window-sinc-filter-t19156.html
//
//=========================================================================

// =========================================================================
// Includes
// =========================================================================

#include "BmHpFilterImpResp.hpp"

#include <cmath>
#include <numeric>
#include <exception>
#include <stdexcept>

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

BmHpFilterImpResp::BmHpFilterImpResp( size_t FilterLen, double f_c_nom )
    : FilterImpResp(FilterLen)
{
    // Check input parameters
    if( FilterLen % 2 != 1 )
    {
        throw std::invalid_argument( "Blackman window filter length must be odd." );
    }

    // Get Blackman window
    std::vector<double> BlackmanWindow( FilterLen );

    for( size_t i = 0; i < FilterLen; i ++ )
    {
        double tmp  = ((double)i) / ((double) (FilterLen-1));
        BlackmanWindow[i] = 0.42L - 0.50L * cos(2.0L * M_PI * tmp) + 0.08L * cos(4.0L * M_PI * tmp);
    }

    // Get Window-sinc filter coeffs
    size_t  c = (FilterLen-1)/2;
    for( size_t i = 0; i < FilterLen; i ++ )
    {
        if( i == c )
        {
            h_[ i ] = 2.0L * M_PI * f_c_nom;
        }
        else
        {
            double tmp = ((double) i) - ((double) c);

            h_[ i ] = sin( 2.0L * M_PI * f_c_nom * tmp ) / tmp;
        }
        h_[ i ] *= BlackmanWindow[ i ];
    }

    // Normalize
    double Sum      = std::accumulate(h_.begin(), h_.end(), 0.0L );
    double Scale    = 1.0L / Sum;

    for( size_t i = 0; i < FilterLen; i ++ )
    {
        h_[ i ] *= Scale;
    }

    // Invert sign and add pulse to convert low pass to high pass
    for( size_t i = 0; i < FilterLen; i ++ )
    {
        h_[ i ] = -h_[i];
        if( i == c )
        {
            h_[i] += 1.0L;
        }
    }
}
