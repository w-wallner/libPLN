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

    // Check if last TD vector is the one that we want
    // This would be the typical case
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
        cout << "  Checking Storage[" << i << "]: " << Storage[i]->GetBeginTime() << "-" << Storage[i]->GetEndTime() << endl;

        if( Storage[i]->GetBeginTime() > t )
        {
            cout << "   <--" << endl;

            r = i;
            i = (l+r)/2;
        }
        else if( Storage[i]->GetEndTime() < t )
        {
            cout << "   -->" << endl;

            l = i;
            i = (l+r)/2;

            if( i == l )
            {
                i++;
            }
        }
        else
        {
            cout << "  Found!" << endl;
            return i;
        }

        LoopCnt ++;
        assert( LoopCnt < MaxCnt );
    }
}

TdVectorStorage::TdVectorStorage()
    : fp( 0.0, 0.0, 0.0 )
{
    this->ForgetTh1     = 0.0;
    this->ForgetTh2     = 0.0;
    this->EnableForget  = false;

    State   = INVALID;
    Storage.clear();
}

TdVectorStorage::TdVectorStorage( double ForgetTh1, double ForgetTh2 )
    : fp( 0.0, 0.0, 0.0 )
{
    this->ForgetTh1     = ForgetTh1;
    this->ForgetTh2     = ForgetTh2;
    this->EnableForget  = true;

    State   = INVALID;
    Storage.clear();
}

void
TdVectorStorage::AddTdVec( TdVector *pTdVec )
{
    cout << "Trying to add vector with time " << pTdVec->GetBeginTime() << "-" << pTdVec->GetEndTime() << endl;

    // Check if new vector matches
    switch( State )
    {
        case INVALID:
        {
            break;
        }

        case STARTUP:
        case RUNNING:
        {
            if( pTdVec->GetBeginTime() != GetEndTime() )
            {
                throw std::logic_error( "TdStorage: new vector does not continue time frame" );
            }

            break;
        }
    }

    Storage.push_back( pTdVec );

    cout << "New state: " << endl;
    std::vector<TdVector *>::iterator  it = Storage.begin();
    for( size_t i = 0; i < Storage.size(); i ++ )
    {
        cout << "  Storage[" << i << "]: " << (*it)->GetBeginTime() << "-" << (*it)->GetEndTime() << endl;
        it ++;
    }

    // Adjust state
    State = RUNNING;
}

double
TdVectorStorage::GetBeginTime()
{
    double t;

    switch( State )
    {
        case INVALID:
            t = 0.0;
            break;

        case STARTUP:
            t = fp.Get_t();
            break;

        case RUNNING:
            t   = (*Storage.begin())->GetBeginTime();
            break;
    }

    return t;
}

double
TdVectorStorage::GetEndTime()
{
    double t;

    switch( State )
    {
        case INVALID:
            t = 0.0;
            break;

        case STARTUP:
            t = fp.Get_t();
            break;

        case RUNNING:
            t   = (*Storage.rbegin())->GetEndTime();
            break;
    }

    return t;
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
    this->State = STARTUP;

    Storage.clear();
}

double
TdVectorStorage::InterpolateTD_nom( double t_req )
{
    assert( t_req >= GetBeginTime() );
    assert( t_req <= GetEndTime() );
    assert( State == RUNNING );

    // Find correct TD Vector and interpolate
    TdVector *pTdVec    = Storage[ FindIndex( t_req ) ];

    cout << "Found Vector for t_req = " << t_req << endl;
    cout << " Begin: " << pTdVec->GetBeginTime() << endl;
    cout << " End:   " << pTdVec->GetEndTime() << endl;

    double TD_nom       = pTdVec->InterpolateTD_nom( t_req );

    return TD_nom;
}

void
TdVectorStorage::ForgetPast( double t_now )
{
    if( EnableForget == false )
    {
        return;
    }

    double  t1  = t_now - ForgetTh1;
    double  t2  = t_now - ForgetTh2;

    if( GetBeginTime() > t1 )
    {
        return;
    }

    size_t cnt = FindIndex( t2 ) - 1;

    Storage.erase( Storage.begin(), Storage.begin() + cnt );
}
