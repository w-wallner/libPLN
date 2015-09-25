// ============================================================================
///
/// \file
///
/// \brief  Implementation of a TD vector that is interpolated using cubic splines
///
/// \ingroup module_td_vector
///
// ============================================================================

// ============================================================================
// 
// Copyright 2015 Wolfgang Wallner (wolfgang-wallner AT gmx.at)
// 
// This file is part of libPLN.
// 
// libPLN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License.com as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License.com for more details.
// 
// You should have received a copy of the GNU General Public License.com
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================

#ifndef TD_VECTOR_CUB_SPLINE_HPP_
#define TD_VECTOR_CUB_SPLINE_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVector/TdVector.hpp"
#include "Utils/spline.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Implements a TD deviation vector that can be interpolated using cubic splines
class TdVectorCubSpline : public TdVector
{
    private:

        // -----------------------------------------------------------------
        // Types
        // -----------------------------------------------------------------

        /// Enumeration to encode the current state of the
        /// interpolation data structures
        typedef enum
        {
            UNINITIALIZED,          ///< Uninitialized: Before interpolation, initialization is needed
            INITIALIZED,            ///< Initialized:   Ready to interpolate
        }
        SplineState;

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------

        // -----------------------------------------------------------------
        // Housekeeping
        // -----------------------------------------------------------------
        SplineState State;          ///< Current state of the interpolation data structures

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------
        tk::spline          s;      ///< The main spline interpolation data structure
        std::vector<double> t;      ///< The times corresponding to the time deviation values

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------

        /// Interpolates the TD in between samples in the time frame stored in this vector
        ///
        /// \param t_req    Requested time where the should be interpolated.
        ///                 Must fulfill t_beg <= t_req <= t_end
        ///
        /// \return         Interpolated TD at t_req
        double  InterpolateRelTD( double t_req );

    public:

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------

        /// Constructor
        ///
        /// \param t_beg            Time (in seconds) when this TD vector begins
        /// \param LastRelativeTD   Initial time deviation (in seconds) at the beginning of this TD vector
        /// \param TickLen          TickLen of the sampled vector (i.e. inverse of the sampling frequency)
        /// \param pData            Input data from which the TD vector is generated
        /// \param ValidLen         Length of the input data that is valid
        TdVectorCubSpline( double t_beg, double LastRelativeTD, double TickLen, FFT_RealVector *pData, size_t ValidLen );

        /// Copy constructor
        TdVectorCubSpline( const TdVectorCubSpline& other );

        /// Destructor
        ~TdVectorCubSpline();

        /// Clone method
        ///
        /// Duplicates the current instance
        ///
        /// \return  A pointer to a duplicate of the current instance
        TdVectorCubSpline* Clone() const;

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------

        /// Copy operator
        TdVectorCubSpline&  operator=( const TdVectorCubSpline& other );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
