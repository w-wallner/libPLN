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
TdVectorStorage::Print()
{
    size_t  size    = Storage.size();

    cout << "Size: " << size << endl;

    for( size_t i = 0; i < size; i ++ )
    {
        cout << "[" << i << "]: " << Storage[i]->GetBeginTime() << " - " << Storage[i]->GetEndTime() << endl;
    }
}

TdVectorStorage::TdVectorStorage()
    : fp( 0.0, 0.0 )
{
    this->ForgetTh1     = 0.0;
    this->ForgetTh2     = 0.0;
    this->EnableForget  = false;

    State   = STARTUP;
    Storage.clear();
}

TdVectorStorage::TdVectorStorage( double ForgetTh1, double ForgetTh2 )
    : fp( 0.0, 0.0 )
{
    if( ForgetTh1 < ForgetTh2 )
    {
        throw std::invalid_argument( "Forget threshold 1 must be larger or equal than forget threshold 2." );
    }

    this->ForgetTh1     = ForgetTh1;
    this->ForgetTh2     = ForgetTh2;
    this->EnableForget  = true;

    State   = STARTUP;
    Storage.clear();
}

TdVectorStorage::~TdVectorStorage()
{
    for( std::vector<TdVector *>::iterator it = Storage.begin(); it < Storage.end(); ++it )
    {
        delete *it;
    }
    Storage.clear();
}

void
TdVectorStorage::AddTdVec( TdVector *pTdVec )
{
    if( pTdVec->GetBeginTime() != GetEndTime() )
    {
        cout << "Current storage: " << endl;
        Print();
        cout << endl;
        cout << "New Vector: " << pTdVec->GetBeginTime() << " - " << pTdVec->GetEndTime() << endl;
        cout << endl;

        std::ostringstream strs;

        strs << "TdStorage: new vector does not continue time frame.";
        strs << "New BeginTime (" << pTdVec->GetBeginTime() << ")";
        strs << " does not match current EndTime (" << GetEndTime() << ")";

        throw std::logic_error( strs.str() );
    }

    Storage.push_back( pTdVec );

    // Adjust state
    State = RUNNING;
}

double
TdVectorStorage::GetBeginTime()
{
    double t = 0.0L;

    if( State == RUNNING )
    {
        t = (*Storage.begin())->GetBeginTime();
    }
    else
    {
        t = fp.Get_t();
    }

    return t;
}

double
TdVectorStorage::GetBeginTD()
{
    double t = 0.0L;

    if( State == RUNNING )
    {
        t = (*Storage.begin())->GetBeginTD();
    }
    else
    {
        t = fp.GetTD_nom();
    }

    return t;
}

double
TdVectorStorage::GetEndTime()
{
    double t = 0.0L;

    if( State == RUNNING )
    {
        t = (*Storage.rbegin())->GetEndTime();
    }
    else
    {
        t = fp.Get_t();
    }

    return t;
}

double
TdVectorStorage::GetEndTD()
{
    double t = 0.0L;

    if( State == RUNNING )
    {
        t = (*Storage.rbegin())->GetEndTD();
    }
    else
    {
        t = fp.GetTD_nom();
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
    TdVector    *pTdVec = Storage[ FindIndex( t_req ) ];
    double      TD_nom  = pTdVec->InterpolateTD_nom( t_req );

    return TD_nom;
}

void
TdVectorStorage::ForgetPast( double t_now )
{
    if( EnableForget == false )
    {
        return;
    }

    if( Storage.size() == 0 )
    {
        return;
    }

    double  t1  = t_now - ForgetTh1;
    double  t2  = t_now - ForgetTh2;

    if( (*Storage.begin())->GetEndTime() > t1 )
    {
        return;
    }

    if( (*Storage.rbegin())->GetEndTime() < t2 )
    {
        return;
    }

    size_t cnt = FindIndex( t2 );
    if( cnt == 0 )
    {
        return;
    }

    std::vector<TdVector *>::iterator Begin = Storage.begin();
    std::vector<TdVector *>::iterator End  = Storage.begin() + cnt;

    for( std::vector<TdVector *>::iterator it = Begin; it < End ; ++it )
    {
        delete (*it);
    }

    Storage.erase( Begin, End );
}
