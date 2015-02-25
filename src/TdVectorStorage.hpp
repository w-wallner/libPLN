
#ifndef TDVECTORSTORAGE_HPP_
#define TDVECTORSTORAGE_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVector.hpp"
#include "TdFixPoint.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef enum
{
    INVALID,
    STARTUP,
    RUNNING,
}
TdVectorStorageState;

// =========================================================================
// Function declarations
// =========================================================================

class TdVectorStorage
{
    private:

        // Config

        // House keeping
        TdVectorStorageState    State;

        // Resources

    public:

        TdVectorStorage();

        void    AddTdVec( TdVector *pVec );
        double  GetBeginTime();
        double  GetEndTime();
        void    ResetToFixPoint( TdFixPoint fp );
        double  InterpolateTD_nom( double t_req );
};

#endif
