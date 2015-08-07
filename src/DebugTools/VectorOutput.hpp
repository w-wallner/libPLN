
#ifndef VECTOROUTPUT_HPP_
#define VECTOROUTPUT_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <vector>
#include <iostream>
#include <complex>

#include "FFT_Types.hpp"

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
