// 
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
// 
// This file is part of libPLN.
// 
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//

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
    alpha    = -5;

    ScaleRef.t      = 0.0L;
    ScaleRef.TD_nom = 0.0L;
    ScaleRef.TD_abs = 0.0L;

    ScaleRefCandidate.t         = 0.0L;
    ScaleRefCandidate.TD_nom    = 0.0L;
    ScaleRefCandidate.TD_abs    = 0.0L;

    CandidateValid  = false;
}

TdEstChain::TdEstChain( const TdEstChain& other )
    : alpha( other.alpha ),
      ScaleRef( other.ScaleRef ),
      ScaleRefCandidate( other.ScaleRefCandidate ),
      CandidateValid( other.CandidateValid )
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

    this->ScaleRef          = other.ScaleRef;
    this->ScaleRefCandidate = other.ScaleRefCandidate;
    this->CandidateValid    = other.CandidateValid;

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
    if( Chain.size() == 0 )
    {
        alpha = Conf.KwConf.alpha;
    }
    else
    {
        if( Conf.KwConf.alpha != alpha )
        {
            throw std::invalid_argument( "Configured alpha value does not match existing value." );
        }

        if( Conf.SampleConf.f_s >= Chain.rbegin()->pEst->Get_f_s() )
        {
            throw std::invalid_argument( "Estimators can only be added in strictly decreasing order of sampling frequency." );
        }
    }

    ChainEntry  e;

    e.Scale = Scale;
    e.pEst  = new TdEstimator( Conf );

    Chain.push_back( e );
}

double
TdEstChain::EstimateTD( double t_now, double t_req )
{
    if( t_now > t_req )
    {
        throw std::invalid_argument( "Request in the past are not supported." );
    }

    double  TD_nom  = 0.0L;
    double  TD_abs  = 0.0L;
    double  Scale   = 1.0L;

    // Update ScaleRef candidate
    if( CandidateValid )
    {
        if( ScaleRefCandidate.t <= t_now )
        {
            ScaleRef = ScaleRefCandidate;
        }

        CandidateValid = false;
    }

    // Get current nominal Time Deviation and scale factor
    for( std::vector<ChainEntry>::iterator it = Chain.begin(); it < Chain.end(); ++it )
    {
        TdEstimate  est = it->pEst->EstimateTD( t_now, t_req );

        if( est.Type == EXACTLY_KNOWN )
        {
            TD_nom += est.TD;
        }
        else if( est.Type == ESTIMATED_FUTURE )
        {
            Scale *= it->Scale;
        }
        else
        {
            assert( false );
        }
    }

    // Calculate absolute Time Deviation
    double  dTD_nom = TD_nom - ScaleRef.TD_nom;

    TD_abs = ScaleRef.TD_abs + dTD_nom * Scale;

    // Remember scale point
    if( t_now == t_req )
    {
        ScaleRef.t      = t_req;
        ScaleRef.TD_nom = TD_nom;
        ScaleRef.TD_abs = TD_abs;
    }
    else
    {
        ScaleRefCandidate.t      = t_req;
        ScaleRefCandidate.TD_nom = TD_nom;
        ScaleRefCandidate.TD_abs = TD_abs;

        CandidateValid = true;
    }

    return TD_abs;
}
