
#ifndef TDVECTORCUBSPLINE_HPP_
#define TDVECTORCUBSPLINE_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVector.hpp"
#include "FFT_Types.hpp"

#include "spline.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdVectorCubSpline : public TdVector
{
    private:

        // Types
        typedef enum
        {
            UNINITIALIZED,
            INITIALIZED,
        }
        SplineState;

        // Config

        // Housekeeping
        SplineState State;

        // Resources
        tk::spline          s;
        std::vector<double> t;

        // Internal functions
        double  InterpolateAt( double t_req );

    public:

        // Constructors/Destructor
        TdVectorCubSpline( double t_beg, double TD_0, double TickLen, FFT_RealVector *pData, size_t ValidLen, TdVecDataType DataType );
        TdVectorCubSpline( const TdVectorCubSpline& other );
        ~TdVectorCubSpline();

        // Operators
        TdVectorCubSpline&  operator=( const TdVectorCubSpline& other );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
