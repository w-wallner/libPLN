// =========================================================================
// Includes
// =========================================================================

#include <FilterImpResp.hpp>

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

FilterImpResp::FilterImpResp()
    :h_( 0 )
{
    this->FilterLen     = 0;
    this->ResponseLen   = 0;
}

FilterImpResp::FilterImpResp( size_t FilterLen )
    :h_( FilterLen )
{
    this->FilterLen     = FilterLen;
    this->ResponseLen   = FilterLen;
}

FFT_RealVector &
FilterImpResp::h()
{
    return h_;
}

size_t
FilterImpResp::GetFilterLen()
{
    return FilterLen;
}

size_t
FilterImpResp::GetResponseLen()
{
    return ResponseLen;
}

void
FilterImpResp::IncreaseResponse( size_t ResponseLen )
{
    if( ResponseLen < this->ResponseLen )
    {
        throw "New ResponseLen is smaller than older ResponseLen";
    }

    h_.resize( ResponseLen, 0.0L );
    this->ResponseLen = ResponseLen;
}

