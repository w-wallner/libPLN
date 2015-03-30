
#ifndef TDVECTORSTORAGE_HPP_
#define TDVECTORSTORAGE_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <set>

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
        size_t  ForgetTh;

        // House keeping
        TdVectorStorageState    State;

        // Resources
        std::vector<TdVector *> Storage;
        TdFixPoint              fp;

        // Internal functions
        size_t  FindIndex( double t );
        void    ClearStorage();

        // Debug functions
        void    Print();

    public:

        // Constructors/Destructor
        TdVectorStorage( size_t ForgetTh );
        TdVectorStorage( const TdVectorStorage& other );
        ~TdVectorStorage();

        // Operators
        TdVectorStorage&    operator= (const TdVectorStorage& other);

        // API
        void    AddTdVec( TdVector *pTdVec );
        double  GetBeginTime();
        double  GetBeginTD();
        double  GetEndTime();
        double  GetEndTD();
        void    ResetToFixPoint( TdFixPoint fp );
        double  InterpolateTD( double t_req );
        void    ForgetPast( double t_now );
};

#endif
