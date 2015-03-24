
#ifndef TDORACLE_HPP_
#define TDORACLE_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEstChain.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

class TdOracle
{
    private:

        // Config

        // Resources

    public:

        // Constructors/Destructor
        TdOracle();
        TdOracle( const TdOracle& other );
        virtual ~TdOracle();

        // Operators
        TdOracle&  operator=( const TdOracle& other );

        // API
        virtual double  EstimateTd( double t_now, double t_req ) = 0;
};

#endif
