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

// =========================================================================
// Includes
// =========================================================================

#include "VectorOutput.hpp"

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

void
PrintRealVector( std::string Name, std::vector<double> v )
{
    cout << Name << "(" << v.size() << "): ";

    cout << "[";

    size_t last = v.size() - 1;
    for(size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i];
        if (i != last)
        {
            cout << ", ";
        }
    }
    cout << "]";
    cout << endl;
}

void
PrintCompVector( std::string Name, std::vector< std::complex<double> > v )
{
    cout << Name << "(" << v.size() << "): ";

    cout << "[";

    size_t last = v.size() - 1;
    for(size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i].real();
        if( v[i].imag() >= 0 )
        {
            cout << " + ";
        }
        else
        {
            cout << " - ";
        }
        cout << abs(v[i].imag()) << "i";
        if (i != last)
        {
            cout << ", ";
        }
    }
    cout << "]";
    cout << endl;
}

void
PrintFftRealVector( std::string Name, FFT_RealVector v )
{
    PrintRealVector( Name, std::vector< double >( v.begin(), v.end() ) );
}

void
PrintFftCompVector( std::string Name, FFT_ComplexVector v )
{
    PrintCompVector( Name, std::vector< std::complex<double> >( v.begin(), v.end() ) );
}
