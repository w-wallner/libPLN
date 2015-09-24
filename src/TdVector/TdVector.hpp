// ============================================================================
///
/// \file
///
/// \brief  Implementation of a Time Deviation vector
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

#ifndef TDVECTOR_HPP_
#define TDVECTOR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "Utils/VectorTypes.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Implementation of a Time Deviation vector
///
/// This class implements a data vector of equal-spaced time deviation values.
/// For more information on time deviation and related notations, have a
/// look in IEEE 1139 the excellent 'Handbook of Frequency Stability Analysis'.
///
/// \remark This class only implements relative Time Deviation!
///         The relative Fractional Frequency values are summed up, but to
///         become absolute Time Deviation values they would need to be
///         divided by the sampling frequency.
///         This is handled outside of this class.
///
class TdVector
{
    public:

        // -----------------------------------------------------------------
        // Types
        // -----------------------------------------------------------------

        /// Enumeration to specify the type of the input data form which a TD vector is generated
        typedef enum
        {
            FFD_DATA,       ///< The input data is Fractional Frequency Deviation data
            TD_DATA,        ///< The input data is already Time Deviation data
        }
        TdVecDataType;

    protected:

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------
        double  TickLen;    ///< Tick length in seconds between two neighbouring TD samples
        double  t_beg;      ///< The time (in seconds) when this TD sample begins
        double  t_end;      ///< The time (in seconds) when this TD sample ends
        double  TD_0;       ///< The initial TD at the begin of this sample

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------
        RealVector  TD;     ///< The actual TD data

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------

        /// Interpolates the TD in between samples in the time frame stored in this vector
        ///
        /// \param t_req    Requested time where the should be interpolated.
        ///                 Must fulfill t_beg <= t_req <= t_end
        ///
        /// \return         Interpolated TD at t_req
        virtual double  InterpolateAt( double t_req ) = 0;

    public:

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------

        /// Constructor
        ///
        /// \param t_beg        Time (in seconds) when this TD vector begins
        /// \param TD_0         Initial time deviation (in seconds) at the beginning of this TD vector
        /// \param TickLen      TickLen of the sampled vector (i.e. inverse of the sampling frequency)
        /// \param pData        Input data from which the TD vector is generated
        /// \param ValidLen     Length of the input data that is valid
        /// \param DataType     Type of the input data
        ///
        /// Depending on the type of input data different operations are performed:
        /// - FFD data: The FFD values are summed up, to get relative Time Deviation values.
        ///             To get absolute TD values, the values need to be divided by the sample rate.
        ///             This is done outside of this class.
        /// - TD data:  No conversion is needed
        TdVector( double t_beg, double TD_0, double TickLen, FFT_RealVector *pData, size_t ValidLen, TdVecDataType DataType );

        /// Copy constructor
        TdVector( const TdVector& other );

        /// Virtual destructor
        virtual ~TdVector() = 0;

        /// Virtual clone method.
        ///
        /// Inheriting classes must implement this.
        ///
        /// \return  A pointer to an object of the subclass type
        virtual TdVector* Clone() const = 0;

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------

        /// Copy operator
        TdVector&  operator=( const TdVector& other );

        friend std::ostream& operator<<(std::ostream& os, const TdVector& o);

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------

        /// Getter for the begin time of this TD vector
        ///
        /// \return Time (in seconds) at the beginning of this TD vector
        double  GetBeginTime();

        /// Getter for the end time of this TD vector
        ///
        /// \return Time (in seconds) at the end of this TD vector
        double  GetEndTime();

        /// Getter for the time deviation at the beginning of this TD vector
        ///
        /// \return Time deviation (in seconds) at the beginning of this TD vector
        double  GetBeginTD();

        /// Getter for the time deviation at the end of this TD vector
        ///
        /// \return Time deviation (in seconds) at the end of this TD vector
        double  GetEndTD();

        /// Interpolates the TD in between samples in the time frame stored in this vector
        ///
        /// \param t_req    Requested time where the should be interpolated.
        ///                 Must fulfill t_beg <= t_req <= t_end
        ///
        /// \return         Interpolated TD at t_req
        double  GetRelativeTD( double t_req );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
