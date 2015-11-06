// ============================================================================
///
/// \file
///
/// \brief  Implementation of a TD vector that is linearly interpolated
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
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libPLN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libPLN.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================

#ifndef LIBPLN_SRC_TDVECTOR_TDVECTORLINEAR_HPP_
#define LIBPLN_SRC_TDVECTOR_TDVECTORLINEAR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVector.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class TdVectorLinear : public TdVector
{
    private:

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------

        /// Interpolates the TD in between samples in the time frame stored in this vector
        ///
        /// \param t_req    Requested time where the should be interpolated.
        ///                 Must fulfill t_beg <= t_req <= t_end
        ///
        /// \return         Interpolated TD at t_re
        double  InterpolateRelTD( double t_req );

    public:

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------

        /// Constructor
        ///
        /// \param t_beg            Time (in seconds) when this TD vector begins
        /// \param LastRelativeTD   Initial time deviation (in seconds) at the beginning of this TD vector
        /// \param f_s              Sampling frequency
        /// \param pData            Input data from which the TD vector is generated
        /// \param ValidLen         Length of the input data that is valid
        TdVectorLinear( double t_beg, double LastRelativeTD, double f_s, FFT_RealVector *pData, size_t ValidLen );

        /// Copy constructor
        TdVectorLinear( const TdVectorLinear& other );

        /// Destructor
        ~TdVectorLinear();

        /// Clone method
        ///
        /// Duplicates the current instance
        ///
        /// \return  A pointer to a duplicate of the current instance
        TdVectorLinear* Clone() const;

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------

        /// Copy operator
        TdVectorLinear&  operator=( const TdVectorLinear& other );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
