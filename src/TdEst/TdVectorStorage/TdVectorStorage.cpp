// ============================================================================
///
/// \file
///
/// \brief  Storage for time deviation vectors.
///
/// \ingroup module_td_vector_storage
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

#include "TdVectorStorage.hpp"

#include <cassert>
#include <stdexcept>

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

static const size_t DefaultForgetTh = 200;

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

size_t
TdVectorStorage::FindIndex( double t )
{
    size_t  l   = 0;
    size_t  r   = Storage.size()-1;
    size_t  i   = (l+r)/2;

    assert( t <= GetEndTime()   );
    assert( t >= GetBeginTime() );

    // Check if last TD vector is the one that we want
    // This is expected to be a typical case
    if
    (
        ( Storage[r]->GetBeginTime() <= t ) &&
        ( Storage[r]->GetEndTime()   >= t )
    )
    {
        return r;
    }

    size_t  LoopCnt = 0;
    size_t  MaxCnt  = Storage.size();
    while( true )
    {
        if( Storage[i]->GetBeginTime() > t )
        {
            r = i;
            i = (l+r)/2;
        }
        else if( Storage[i]->GetEndTime() < t )
        {
            l = i;
            i = (l+r)/2;

            if( i == l )
            {
                i++;
            }
        }
        else
        {
            return i;
        }

        LoopCnt ++;
        assert( LoopCnt <= MaxCnt );
    }
}

void
TdVectorStorage::ClearStorage()
{
    for( std::vector<TdVector *>::iterator it = Storage.begin(); it < Storage.end(); ++it )
    {
        delete *it;
    }
    Storage.clear();
}

void
TdVectorStorage::Print()
{
    size_t  size    = Storage.size();

    cout << "Size: " << size << endl;

    for( size_t i = 0; i < size; i ++ )
    {
        cout << "[" << i << "]: " << Storage[i]->GetBeginTime() << " - " << Storage[i]->GetEndTime() << endl;
    }
}

TdVectorStorage::TdVectorStorage( size_t ForgetTh )
    : fp( 0.0, 0.0 )
{

    if( ForgetTh == 0 )
    {
        this->ForgetTh = DefaultForgetTh;
    }
    else
    {
        this->ForgetTh = ForgetTh;
    }

    ClearStorage();
}

TdVectorStorage::TdVectorStorage( const TdVectorStorage& other )
    : ForgetTh  ( other.ForgetTh ),
      fp        ( other.fp       )
{
    // Copy storage contents
    for( std::vector<TdVector *>::const_iterator it = other.Storage.begin(); it != other.Storage.end(); ++it )
    {
        TdVector *pVec = (*it)->Clone();

        Storage.push_back( pVec );
    }
}

TdVectorStorage::~TdVectorStorage()
{
    ClearStorage();
}

TdVectorStorage&
TdVectorStorage::operator= (const TdVectorStorage& other)
{
    ClearStorage();

    this->ForgetTh  = other.ForgetTh;
    this->fp        = other.fp;

    // Copy storage contents
    for( std::vector<TdVector *>::const_iterator it = other.Storage.begin(); it != other.Storage.end(); ++it )
    {
        TdVector *pVec = (*it)->Clone();

        Storage.push_back( pVec );
    }

    // By convention, always return *this
    return *this;
}

void
TdVectorStorage::AddTdVec( TdVector *pTdVec )
{
    if
    (
        ( !Storage.empty() ) &&
        ( pTdVec->GetBeginTime() != GetEndTime() )
    )
    {
        cout << "Current storage: " << endl;
        Print();
        cout << endl;
        cout << "New Vector: " << pTdVec->GetBeginTime() << " - " << pTdVec->GetEndTime() << endl;
        cout << endl;

        std::ostringstream strs;

        strs << "TdStorage: new vector does not continue time frame. ";
        strs << "New BeginTime (" << pTdVec->GetBeginTime() << ")";
        strs << " does not match current EndTime (" << GetEndTime() << ")";

        throw std::logic_error( strs.str() );
    }

    Storage.push_back( pTdVec );
}

double
TdVectorStorage::GetBeginTime()
{
    double t = 0.0L;

    if( Storage.empty() )
    {
        t = fp.Get_t();
    }
    else
    {
        t = (*Storage.begin())->GetBeginTime();
    }

    return t;
}

double
TdVectorStorage::GetBeginTD()
{
    double TD = 0.0L;

    if( Storage.empty() )
    {
        TD = fp.GetTD();
    }
    else
    {
        TD = (*Storage.begin())->GetBeginTD();
    }

    return TD;
}

double
TdVectorStorage::GetEndTime()
{
    double t = 0.0L;

    if( Storage.empty() )
    {
        t = fp.Get_t();
    }
    else
    {
        t = (*Storage.rbegin())->GetEndTime();
    }

    return t;
}

double
TdVectorStorage::GetEndTD()
{
    double TD = 0.0L;

    if( Storage.empty() )
    {
        TD = fp.GetTD();
    }
    else
    {
        TD = (*Storage.rbegin())->GetEndTD();
    }

    return TD;
}

void
TdVectorStorage::ResetToFixPoint( TdFixPoint fp )
{
    // Check if new Fixpoint is plausible
    if( fp.Get_t() < this->fp.Get_t() )
    {
        throw std::invalid_argument( "TdStorage: only resetting to a future fixpoint is supported" );
    }

    this->fp    = fp;

    ClearStorage();
}

double
TdVectorStorage::GetTD( double t_req )
{
    assert( t_req >= GetBeginTime() );
    assert( t_req <= GetEndTime() );
    assert( !Storage.empty() );

    // Find correct TD Vector and interpolate
    TdVector    *pTdVec = Storage[ FindIndex( t_req ) ];
    double      TD      = pTdVec->GetTD( t_req );

    return TD;
}

void
TdVectorStorage::ForgetPast( double t_now )
{
    if( Storage.size() < ForgetTh )
    {
        return;
    }

    size_t cnt = 0;

    if( GetEndTime() < t_now )
    {
        cnt = Storage.size();
    }
    else
    {
        cnt = FindIndex( t_now );
    }

    if( cnt == 0 )
    {
        return;
    }

    std::vector<TdVector *>::iterator Begin = Storage.begin();
    std::vector<TdVector *>::iterator End   = Storage.begin() + cnt;

    for( std::vector<TdVector *>::iterator it = Begin; it < End ; ++it )
    {
        delete (*it);
    }

    Storage.erase( Begin, End );
}
