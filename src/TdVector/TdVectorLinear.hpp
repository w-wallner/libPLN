
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

        // Constructors/Destructor
        TdVectorLinear( double t_beg, double TD_0, double TickLen, FFT_RealVector *pFFD, size_t ValidLen, TdVecDataType DataType );
        TdVectorLinear( const TdVectorLinear& other );
        ~TdVectorLinear();

        // Operators
        TdVectorLinear&  operator=( const TdVectorLinear& other );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
