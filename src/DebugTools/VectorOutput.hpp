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

#ifndef VECTOROUTPUT_HPP_
#define VECTOROUTPUT_HPP_

// =========================================================================
// Includes
// =========================================================================

#ifdef ENABLE_DEBUG_OUTPUT

#include <vector>
#include <iostream>
#include <complex>

#include "Utils/FFT_Types.hpp"

using namespace std;

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v) {
    out << "[";
    size_t last = v.size() - 1;
    for(size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last)
            out << ", ";
    }
    out << "]";
    return out;
}

void    PrintRealVector( std::string Name, std::vector<double> v );
void    PrintCompVector( std::string Name, std::vector< std::complex<double> > v );
void    PrintFftRealVector( std::string Name, FFT_RealVector v );
void    PrintFftCompVector( std::string Name, FFT_ComplexVector v );

#endif

#endif
