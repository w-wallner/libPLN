// =========================================================================
// Includes
// =========================================================================

#include "TdVectorStorage.hpp"

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

TdVectorStorage::TdVectorStorage()
{
    State   = INVALID;
}

void
TdVectorStorage::AddTdVec( TdVector *pVec )
{

}

double
TdVectorStorage::GetBeginTime()
{
    // TODO
    return 0.0;
}

double
TdVectorStorage::GetEndTime()
{
    // TODO
    return 0.0;
}

void
TdVectorStorage::ResetToFixPoint( TdFixPoint fp )
{

}

double
TdVectorStorage::InterpolateTD_nom( double t_req )
{
    assert( t_req >= GetBeginTime() );
    assert( t_req <= GetEndTime() );

    // TODO: Find correct TD Vector
    // TODO: Interpolate TD_nom

    double TD_nom   = 0.0;

    return TD_nom;
}
