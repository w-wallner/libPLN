
#ifndef TDFIXPOINTSTORAGE_HPP_
#define TDFIXPOINTSTORAGE_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdFixPoint.hpp"

#include <set>

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdFixPointStorage
{
    private:
        // Config
        double  ForgetTh1;
        double  ForgetTh2;
        bool    EnableForget;

        // Resources
        std::set<TdFixPoint>    Storage;

        // Internal functions
        void        PrintStatus();

    public:
        TdFixPointStorage();
        TdFixPointStorage( double ForgetTh1, double ForgetTh2 );

        void        Add( TdFixPoint fp );
        double      InterpolateTD_abs( double t_req );
        TdFixPoint  GetLatest();

        void        ResetToFixPoint( TdFixPoint fp );
        void        ForgetPast( double t_now );
};

// =========================================================================
// Function declarations
// =========================================================================


#endif
