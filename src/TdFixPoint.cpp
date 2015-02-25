// =========================================================================
// Includes
// =========================================================================

#include "TdFixPoint.hpp"

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

TdFixPoint::TdFixPoint( double t, double TD_nom, double TD_abs )
{
    this->t         = t;
    this->TD_nom    = TD_nom;
    this->TD_abs    = TD_abs;
}

double
TdFixPoint::Get_t()
{
    return t;
}

double
TdFixPoint::GetTD_nom()
{
    return TD_nom;
}

double
TdFixPoint::GetTD_abs()
{
    return TD_abs;
}
