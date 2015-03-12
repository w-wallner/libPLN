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

TdEstChain::TdEstChain()
{
    Last_f_s = 0.0L;
}

TdEstChain::~TdEstChain()
{
    for( std::vector<ChainEntry>::iterator it = Chain.begin(); it < Chain.end(); ++it )
    {
        delete it->pEst;
    }

    Chain.clear();
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
    double  Td          = 0.0L;
    double  Scale       = 1.0L;
    bool    ScaleNext   = false;

    for( std::vector<ChainEntry>::iterator it = Chain.begin(); it < Chain.end(); ++it )
    {
        if( ScaleNext )
        {
            Scale *= it->Scale;
            ScaleNext = false;
        }

        TdEstimate  est = it->pEst->EstimateTd( t_now, t_req );

        Td += est.TD * Scale;

        if( est.Type == ESTIMATED_FUTURE )
        {
            ScaleNext = true;
        }
    }

    return Td;
}
