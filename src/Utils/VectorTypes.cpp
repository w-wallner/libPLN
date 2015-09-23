// ============================================================================
///
/// \file
///
/// \brief  Vector types
///
/// \ingroup module_vector_types
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

#include "VectorTypes.hpp"

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

std::ostream& operator<<(std::ostream& os, const RealVector& o)
{
    for( size_t i = 0; i < o.size(); i++ )
    {
        os << o[i];

        if( i + 1 < o.size() )
        {
            os << ", ";
        }
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const ComplexVector& o)
{
    for( size_t i = 0; i < o.size(); i++ )
    {
        os << o[i].real();

        if( o[i].imag() >= 0 )
        {
            os << " + ";
        }
        else
        {
            os << " - ";
        }

        os << abs(o[i].imag());
        os << "i";

        if( i + 1 < o.size() )
        {
            os << ", ";
        }
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const FFT_RealVector& o)
{
    for( size_t i = 0; i < o.size(); i++ )
    {
        os << o[i];

        if( i + 1 < o.size() )
        {
            os << ", ";
        }
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const FFT_ComplexVector& o)
{
    for( size_t i = 0; i < o.size(); i++ )
    {
        os << o[i].real();

        if( o[i].imag() >= 0 )
        {
            os << " + ";
        }
        else
        {
            os << " - ";
        }

        os << abs(o[i].imag());
        os << "i";

        if( i + 1 < o.size() )
        {
            os << ", ";
        }
    }

    return os;
}
