// ============================================================================
///
/// \file
///
/// \brief  FFT API to interface with FFTW library
///
/// \ingroup module_fft
///
// ============================================================================

// ============================================================================
//
// This code is based on code from
// https://gitorious.org/cpp-bricks
//
// Original copyright statement:
//
//              Copyright David Munger 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// ============================================================================

#ifndef FFT_TYPES_HPP_
#define FFT_TYPES_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <vector>
#include <complex>
#include <limits>

#include <fftw3.h>

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// API to interface with the FFTW C library
///
/// This struct encapsulates the access to FFTW
struct FFTW_C_API
{
    typedef double real;                            ///< Data type for real data
    typedef std::complex<double> complex;           ///< Data type for complex data
    typedef fftw_plan plan;                         ///< Data type for FFTW's execution plans

    /// FFTW specific malloc
    ///
    /// \param n    Size of memory that needs to be allocated
    ///
    /// \return     Pointer to allocated memory or NULL
    static void *malloc(size_t n)
    {
        return fftw_malloc(n);
    }

    /// FFTW specific free
    ///
    /// \param p    Pointer to the memory that needs to be freed
    static void free(void *p)
    {
        fftw_free(p);
    }

    /// Create an execution plan for FFTW for 1D real to complex FFT
    ///
    /// \param n        Size of real data
    /// \param in       Pointer to real data
    /// \param out      Pointer to complex data
    /// \param flags    FFTW flags
    ///
    /// \return         Execution plan
    ///
    /// \remark This works as long as the data in std::complex is [real, imag]
    static plan plan_dft_r2c_1d(int n, real *in, complex *out, unsigned flags)
    {
        return fftw_plan_dft_r2c_1d(n, in, reinterpret_cast<fftw_complex*>(out), flags);
    }

    /// Create an execution plan for FFTW for 1D complex to real FFT
    ///
    /// \param n        Size of real data
    /// \param in       Pointer to complex data
    /// \param out      Pointer to real data
    /// \param flags    FFTW flags
    ///
    /// \return         Execution plan
    ///
    /// \remark this works as long as the data in std::complex is [real, imag]
    static plan plan_dft_c2r_1d(int n, complex *in, real *out, unsigned flags)
    {
        return fftw_plan_dft_c2r_1d(n, reinterpret_cast<fftw_complex*>(in), out, flags);
    }

    /// Execute a real to complex FFT
    ///
    /// \param p    Execution plan
    /// \param in   Pointer to real data
    /// \param out  Pointer to complex data
    static void execute_dft_r2c( const plan p, real *in, complex *out )
    {
        fftw_execute_dft_r2c( p, in, reinterpret_cast<fftw_complex*>(out) );
    }

    /// Execute a complex to real FFT
    ///
    /// \param p    Execution plan
    /// \param in   Pointer to complex data
    /// \param out  Pointer to real data
    static void execute_dft_c2r( const plan p, complex *in, real *out )
    {
        fftw_execute_dft_c2r( p, reinterpret_cast<fftw_complex*>(in), out );
    }

    /// Destroy an FFTW execution plan
    ///
    /// \param p    Plan that should be destroyed
    static void destroy_plan(plan p)
    {
        fftw_destroy_plan(p);
    }

    /// Execute an FFTW execution plan
    static void execute(const plan p)
    {
        return fftw_execute(p);
    }
};

/// Allocator for the FFTW C library
template <typename Tp>
class FFTW_Allocator
{
    public:

    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef Tp*         pointer;
    typedef const Tp*   const_pointer;
    typedef Tp&         reference;
    typedef const Tp&   const_reference;
    typedef Tp          value_type;

    template<typename Tp1> struct rebind{ typedef FFTW_Allocator<Tp1> other; };

    FFTW_Allocator() throw() { }
    FFTW_Allocator(const FFTW_Allocator&) throw() { }
    template<typename Tp1> FFTW_Allocator(const FFTW_Allocator<Tp1>&) throw() { }
    ~FFTW_Allocator() throw() { }

    pointer allocate(size_type n, const void* = 0)
    {
        return static_cast<Tp*>(FFTW_C_API::malloc(n * sizeof(Tp)));
    }

    void deallocate(pointer p, size_type)
    {
        FFTW_C_API::free(p);
    }

    void construct(pointer p) { ::new((void *)p) Tp(); }
    void construct(pointer p, const Tp& val) { ::new((void *)p) Tp(val); }
    void destroy(pointer p) { p->~Tp(); }

    inline size_type max_size() const
    {
        return std::numeric_limits<size_type>::max() / sizeof(Tp);
    }
};

/// Vector for real data using the FFTW allocator
typedef std::vector<double, FFTW_Allocator<double> > FFT_RealVector;

/// Vector for complex data using the FFTW allocator
typedef std::vector<std::complex<double>, FFTW_Allocator< std::complex<double> > > FFT_ComplexVector;

// =========================================================================
// Function declarations
// =========================================================================

#endif
