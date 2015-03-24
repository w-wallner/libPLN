// =========================================================================
// Includes
// =========================================================================

#include <AverageOscillator_20MHz.hpp>

namespace AverageOscillator_20MHz
{

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

TdOracle_AvgOsc20MHz::TdOracle_AvgOsc20MHz( unsigned int Seed )
    : WpmChain( Seed + 0 ), WfmChain( Seed + 20 ), FfmChain( Seed + 30 ), RwChain( Seed + 40 )
{
}

TdOracle_AvgOsc20MHz::TdOracle_AvgOsc20MHz( const TdOracle_AvgOsc20MHz& other )
    : WpmChain( other.WpmChain ), WfmChain( other.WfmChain ), FfmChain( other.FfmChain ), RwChain( other.RwChain )
{
}

TdOracle_AvgOsc20MHz::~TdOracle_AvgOsc20MHz()
{
}

// Operators
TdOracle_AvgOsc20MHz&
TdOracle_AvgOsc20MHz::operator=( const TdOracle_AvgOsc20MHz& other )
{
    this->WpmChain  = other.WpmChain;
    this->WfmChain  = other.WfmChain;
    this->FfmChain  = other.FfmChain;
    this->RwChain   = other.RwChain;

    // By convention, always return *this
    return *this;
}

double
TdOracle_AvgOsc20MHz::EstimateTD( double t_now, double t_req )
{
    double  TD = 0.0L;

    TD  += WpmChain.EstimateTD( t_now, t_req );
    TD  += WfmChain.EstimateTD( t_now, t_req );
    TD  += FfmChain.EstimateTD( t_now, t_req );
    TD  += RwChain.EstimateTD ( t_now, t_req );

    return TD;
}

}
