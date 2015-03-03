
#ifndef TDFIXPOINT_HPP_
#define TDFIXPOINT_HPP_

// =========================================================================
// Includes
// =========================================================================



// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdFixPoint
{
    private:
        // Config
        double  t;
        double  TD_nom;
        double  TD_abs;

    public:
        TdFixPoint( double t, double TD_nom, double TD_abs );

        double  Get_t() const;
        double  GetTD_nom() const;
        double  GetTD_abs() const;

        bool operator<( const TdFixPoint& other ) const;
};

// =========================================================================
// Function declarations
// =========================================================================


#endif
