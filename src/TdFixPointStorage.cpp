
// =========================================================================
// Includes
// =========================================================================

#include "TdFixPointStorage.hpp"

#include <stdexcept>
#include <cassert>

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
TdFixPointStorage::PrintStatus()
{
    cout << "FixPoint storage size: " << Storage.size() << endl;

    for( std::set<TdFixPoint>::iterator it = Storage.begin(); it != Storage.end(); ++it )
    {
        cout << "  TD(" << it->Get_t() << "): " << it->GetTD_nom() << "/" << it->GetTD_abs() << endl;
    }
}

TdFixPointStorage::TdFixPointStorage()
{
    this->ForgetTh1     = 0.0L;
    this->ForgetTh2     = 0.0L;
    this->EnableForget  = false;

    // Set up [0.0/0.0]@0.0 as initial fixpoint
    ResetToFixPoint( TdFixPoint( 0.0, 0.0, 0.0 ) );
}

TdFixPointStorage::TdFixPointStorage( double ForgetTh1, double ForgetTh2 )
{
    this->ForgetTh1     = ForgetTh1;
    this->ForgetTh2     = ForgetTh2;
    this->EnableForget  = true;

    // Set up [0.0/0.0]@0.0 as initial fixpoint
    ResetToFixPoint( TdFixPoint( 0.0, 0.0, 0.0 ) );
}

void
TdFixPointStorage::Add( TdFixPoint fp )
{
    Storage.insert( fp );
}

double
TdFixPointStorage::InterpolateTD_abs( double t_req )
{
    assert( Storage.size() != 0 );

    if( t_req <= Storage.begin()->Get_t() )
    {
        return Storage.begin()->GetTD_abs();
    }

    if( t_req > Storage.rbegin()->Get_t() )
    {
        return Storage.rbegin()->GetTD_abs();
    }

    std::set<TdFixPoint>::iterator  r = Storage.upper_bound( TdFixPoint( t_req, 0.0, 0.0 ) );
    std::set<TdFixPoint>::iterator  l = r;
    std::advance(l, -1);

    double dx   = r->Get_t() - l->Get_t();
    double dy   = r->GetTD_abs() - l->GetTD_abs();
    double k    = dy/dx;
    double x    = t_req - l->Get_t();
    double d    = l->GetTD_abs();

    double  TD_abs = k*x + d;

    return TD_abs;
}

TdFixPoint
TdFixPointStorage::GetLatest()
{
    return  *Storage.rbegin();
}

void
TdFixPointStorage::ResetToFixPoint( TdFixPoint fp )
{
    Storage.clear();
    Storage.insert( fp );
}

void
TdFixPointStorage::ForgetPast( double t_now )
{
    // TODO
}
