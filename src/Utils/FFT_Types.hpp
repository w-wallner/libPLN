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

struct FFTW_C_API
{
    typedef double real;
    typedef std::complex<double> complex;
    typedef fftw_plan plan;

    static void *malloc(size_t n)
    {
        return fftw_malloc(n);
    }

    static void free(void *p)
    {
        fftw_free(p);
    }

    // this works as long as the data in std::complex is [real, imag]
    static plan plan_dft_r2c_1d(int n, real *in, complex *out, unsigned flags)
    {
        return fftw_plan_dft_r2c_1d(n, in, reinterpret_cast<fftw_complex*>(out), flags);
    }

    // this works as long as the data in std::complex is [real, imag]
    static plan plan_dft_c2r_1d(int n, complex *in, real *out, unsigned flags)
    {
        return fftw_plan_dft_c2r_1d(n, reinterpret_cast<fftw_complex*>(in), out, flags);
    }

    static void execute_dft_r2c( const plan p, real *in, complex *out )
    {
        fftw_execute_dft_r2c( p, in, reinterpret_cast<fftw_complex*>(out) );
    }

    static void execute_dft_c2r( const plan p, complex *in, real *out )
    {
        fftw_execute_dft_c2r( p, reinterpret_cast<fftw_complex*>(in), out );
    }

    static void destroy_plan(plan p)
    {
        fftw_destroy_plan(p);
    }

    static void execute(const plan p)
    {
        return fftw_execute(p);
    }
};


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

    //    size
    inline size_type max_size() const
    {
        return std::numeric_limits<size_type>::max() / sizeof(Tp);
    }
};

typedef std::vector<double, FFTW_Allocator<double> > FFT_RealVector;
typedef std::vector<std::complex<double>, FFTW_Allocator< std::complex<double> > > FFT_ComplexVector;

// =========================================================================
// Function declarations
// =========================================================================


#endif
