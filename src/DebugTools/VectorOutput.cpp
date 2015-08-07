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
