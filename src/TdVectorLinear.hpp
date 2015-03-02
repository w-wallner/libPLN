
#ifndef TDVECTORLINEAR_HPP_
#define TDVECTORLINEAR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVector.hpp"
#include "FFT_Types.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdVectorLinear : public TdVector
{
    private:

        // Config

        // Resources

        // Internal functions
        double  InterpolateAt( double t_req );

    public:

        TdVectorLinear( double BeginTime, double BeginOffset, double TickLen, FFT_RealVector *pFFD );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
