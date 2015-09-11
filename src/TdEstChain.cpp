// ============================================================================
///
/// \file
///
/// \brief  Chain of time deviation estimators
///
/// \ingroup module_td_estimator
///
// ============================================================================

// ============================================================================
//
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
//
// This file is part of libPLN.
//
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License.com as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License.com for more details.
//
// You should have received a copy of the GNU General Public License.com
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================

// =========================================================================
// Includes
// =========================================================================

#include "TdEstChain.hpp"

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

TdEstChain::TdEstChain( double alpha, unsigned int SeedOffset )
{
    this->alpha         = alpha;
    this->SeedOffset    = SeedOffset;
}

TdEstChain::TdEstChain( const TdEstChain& other )
{
    this->alpha         = other.alpha;
    this->SeedOffset    = other.SeedOffset;

    for( std::vector<ChainEntry>::const_iterator it = other.Chain.begin(); it != other.Chain.end(); ++it )
    {
        ChainEntry  e;

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

    // Copy chain entries
    for( std::vector<ChainEntry>::const_iterator it = other.Chain.begin(); it != other.Chain.end(); ++it )
    {
        ChainEntry  e;

        e.pEst  = new TdEstimator( *it->pEst );

        Chain.push_back( e );
    }

    // By convention, always return *this
    return *this;
}

void
TdEstChain::EnableIntervalSkipping()
{
    for( std::vector<ChainEntry>::iterator it = Chain.begin(); it < Chain.end(); ++it )
    {
        it->pEst->EnableIntervalSkipping();
    }
}

void
TdEstChain::DisableIntervalSkipping()
{
    for( std::vector<ChainEntry>::iterator it = Chain.begin(); it < Chain.end(); ++it )
    {
        it->pEst->DisableIntervalSkipping();
    }
}

void
TdEstChain::SetSeed( unsigned int Seed )
{
    unsigned int Cnt = 0;

    for( std::vector<ChainEntry>::iterator it = Chain.begin(); it < Chain.end(); ++it )
    {
        it->pEst->SetSeed( Seed + SeedOffset + Cnt );

        Cnt ++;
    }
}

void
TdEstChain::AddTdEstimator( TdEstimatorConfig Conf )
{
    if( Conf.PLN_FilterConf.alpha != alpha )
    {
        throw std::invalid_argument( "Configured alpha value does not match existing value." );
    }

    if( Conf.SampleConf.f_s >= Chain.rbegin()->pEst->Get_f_s() )
    {
        throw std::invalid_argument( "Estimators can only be added in strictly decreasing order of sampling frequency." );
    }

    ChainEntry  e;

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

    double  TD  = 0.0L;

    // Sum up over all chain entries
    for( std::vector<ChainEntry>::iterator it = Chain.begin(); it < Chain.end(); ++it )
    {
        TD += it->pEst->EstimateTD( t_now, t_req );
    }

    return TD;
}
