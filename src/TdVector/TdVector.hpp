
#ifndef TDVECTOR_HPP_
#define TDVECTOR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "FFT_Types.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef enum
{
    FFD_DATA,
    TD_DATA,
}
TdVecDataType;

class TdVector
{
    protected:

        // Config
        double  TickLen;
        double  t_beg;
        double  t_end;
        double  TD_0;

        // Resources
        std::vector<double> TD;

        // Internal functions
        virtual double  InterpolateAt( double t_req ) = 0;

    public:

        // Constructors/Destructor
                TdVector( double t_beg, double TD_0, double TickLen, FFT_RealVector *pFFD, size_t ValidLen, TdVecDataType DataType );
                TdVector( const TdVector& other );
        virtual ~TdVector();

        // Operators
        TdVector&  operator=( const TdVector& other );

        // API
        double  GetBeginTime();
        double  GetEndTime();
        double  GetBeginTD();
        double  GetEndTD();

        double  InterpolateTD_nom( double t_req );
};

// =========================================================================
// Function declarations
// =========================================================================


#endif
