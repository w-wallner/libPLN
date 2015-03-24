// =========================================================================
// Includes
// =========================================================================

#include "TdEstChain.hpp"

// Debug only
#include <iostream>
using namespace std;

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

void
TdEstChain::ClearChain()
{
    for( std::vector<ChainEntry>::iterator it = Chain.begin(); it < Chain.end(); ++it )
    {
        delete it->pEst;
    }

    Chain.clear();
}

TdEstChain::TdEstChain()
{
    Last_f_s = 0.0L;
}

TdEstChain::TdEstChain( const TdEstChain& other )
    : Last_f_s( other.Last_f_s )
{
    for( std::vector<ChainEntry>::const_iterator it = other.Chain.begin(); it != other.Chain.end(); ++it )
    {
        ChainEntry  e;

        e.Scale = it->Scale;
        e.pEst  = new TdEstimator( *it->pEst );

        Chain.push_back( e );
    }
}

TdEstChain::~TdEstChain()
{
    ClearChain();
}

TdEstChain&
TdEstChain::operator= (const TdEstChain& other)
{
    ClearChain();

    this->Last_f_s  = other.Last_f_s;

    // Copy chain entries
    for( std::vector<ChainEntry>::const_iterator it = other.Chain.begin(); it != other.Chain.end(); ++it )
    {
        ChainEntry  e;

        e.Scale = it->Scale;
        e.pEst  = new TdEstimator( *it->pEst );

        Chain.push_back( e );
    }

    // By convention, always return *this
    return *this;
}

void
TdEstChain::AddTdEstimator( TdEstimatorConfig Conf, double Scale )
{
    if( Chain.size() > 0 )
    {
        if( Conf.SampleConf.f_s >= Last_f_s )
        {
            throw std::invalid_argument( "Estimators can only be added in decreasing order of sampling frequency." );
        }
    }

    ChainEntry  e;

    e.Scale = Scale;
    e.pEst  = new TdEstimator( Conf );

    Chain.push_back( e );

    Last_f_s = Conf.SampleConf.f_s;
}

double
TdEstChain::EstimateTd( double t_now, double t_req )
{
    double  TD          = 0.0L;
    double  Scale       = 1.0L;

    for( std::vector<ChainEntry>::iterator it = Chain.begin(); it < Chain.end(); ++it )
    {
        TdEstimate  est = it->pEst->EstimateTd( t_now, t_req );

        if( est.Type == EXACTLY_KNOWN )
        {
            TD += est.TD;
        }
        else if( est.Type == ESTIMATED_FUTURE )
        {
            Scale *= it->Scale;
        }
    }

    return TD * Scale;
}
