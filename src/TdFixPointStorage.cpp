
// =========================================================================
// Includes
// =========================================================================

#include "TdFixPointStorage.hpp"

#include <stdexcept>
#include <cassert>

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

TdFixPointStorage::TdFixPointStorage()
{
    // Set up [0.0/0.0]@0.0 as initial fixpoint
    Storage.insert( TdFixPoint( 0.0, 0.0, 0.0 ) );
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

    if
    (
        ( t_req < Storage.begin()->Get_t() ) ||
        ( t_req > Storage.end()->Get_t()   )
    )
    {
        throw std::invalid_argument( "FixPoint storage: requested time is out of range" );
    }

    if( Storage.size() < 2 )
    {
        throw std::logic_error( "FixPoint storage: not enough fixpoints available for interpolation" );
    }

//    Storage.find()


    // TODO
    return 0.0;
}

TdFixPoint
TdFixPointStorage::GetLatest()
{
    return  *Storage.rbegin();
}

void
TdFixPointStorage::ForgetPast( double t_now )
{
    // TODO
}
