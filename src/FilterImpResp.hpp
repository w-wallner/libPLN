
#ifndef FILTERIMPRESP_HPP_
#define FILTERIMPRESP_HPP_

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

class FilterImpResp
{
    protected:

        // Config
        size_t  FilterLen;
        size_t  ResponseLen;

        // Resources
        FFT_RealVector h_;

        // Internal functions
        FilterImpResp();
        FilterImpResp( size_t FilterLen );

    public:

        FFT_RealVector &h();

        size_t  GetFilterLen();
        size_t  GetResponseLen();

        void    IncreaseResponse( size_t ResponseLen );
        void    Augment( size_t Cnt );
};


// =========================================================================
// Function declarations
// =========================================================================


#endif
