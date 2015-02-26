
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
    private:

        // Config
        size_t  FilterLen;
        size_t  ResponseLen;

        // Resources

    protected:

        // Resources
        FFT_RealVector h_;

        // Internal functions
        FilterImpResp();
        FilterImpResp( size_t FilterLen, size_t ResponseLen );

    public:

        FFT_RealVector &h();

        size_t  GetFilterLen();
        size_t  GetResponseLen();

        void    IncreaseResponse( size_t ResponseLen );
};


// =========================================================================
// Function declarations
// =========================================================================


#endif
