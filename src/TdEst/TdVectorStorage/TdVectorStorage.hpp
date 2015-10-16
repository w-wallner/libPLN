// ============================================================================
///
/// \file
///
/// \brief  Storage for time deviation vectors.
///
/// \ingroup module_td_vector_storage
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

#ifndef TDVECTORSTORAGE_HPP_
#define TDVECTORSTORAGE_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <set>

#include "TdVector/TdVector.hpp"
#include "TdEst/TdFixPoint.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

/// Storage that stores a continuous series of time deviation vectors.
///
/// A continuous series of time deviation vectors can be stored in this
/// storage, and it can then be asked to retrieve a time deviation value
/// anywhere inside the stored time frame.
class TdVectorStorage
{
    private:

        // -----------------------------------------------------------------
        // Types
        // -----------------------------------------------------------------

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------
        size_t  ForgetTh;       ///< Threshold for the internal storage when
                                ///< to start forgetting. If the internal
                                ///< storage contains this number of time
                                ///< deviation vectors, it will forget all
                                ///< vectors that are already in the past.

        // -----------------------------------------------------------------
        // House keeping
        // -----------------------------------------------------------------

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------
        std::vector<TdVector *> Storage;        ///< Internal storage for the time deviation vectors
        TdFixPoint              fp;             ///< Last configured fixpoint, from where the vectors series started

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------
        size_t  FindIndex( double t );          ///< Calculate the index in the internal storage that contains the data at time t.
                                                ///< \param t   The time (in seconds) that needs to be searched.
                                                ///< \return    The index in the internal storage where to find t.
        void    ClearStorage();                 ///< Clear the internal storage.

        // -----------------------------------------------------------------
        // Debug functions
        // -----------------------------------------------------------------
        void    Print();                        ///< Print information about the current contents of the internal storage

    public:

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------

        /// Constructor
        ///
        /// \param ForgetTh     The threshold at which fill point that the internal storage should start to forget old values.
        TdVectorStorage( size_t ForgetTh );

        /// Copy constructor
        ///
        /// \param other        The instance that we want to copy
        TdVectorStorage( const TdVectorStorage& other );

        /// Destructor
        ~TdVectorStorage();

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------

        /// Assignment operator
        ///
        /// \param other        The instance that we want to assign
        ///
        /// \return     An assigned instance
        TdVectorStorage&    operator= (const TdVectorStorage& other);

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------

        /// Adds a time deviation vector to the storage
        ///
        /// \param pTdVec   Pointer to the time deviation vector that should be added
        void    AddTdVec( TdVector *pTdVec );

        /// Getter for the time (in seconds) when the currently saved vector series begins
        ///
        /// \return Time (in seconds) at the beginning of the currently saved vector series
        double  GetBeginTime();

        /// Getter for the relative time deviation value at the beginning of the currently saved vector series
        ///
        /// \return Relative time deviation at the beginning of the currently saved vector series
        double  GetBeginTD();

        /// Getter for the time (in seconds) at the end of the currently saved vector series
        ///
        /// \return Time (in seconds) at the end of the currently saved vector series
        double  GetEndTime();

        /// Getter for the relative time deviation value at the end of the currently saved vector series
        ///
        /// \return Relative time deviation at the end of the currently saved vector series
        double  GetEndTD();

        /// Reset the vector storage to a new fixpoint
        ///
        /// \param fp   New fixpoint
        void    ResetToFixPoint( TdFixPoint fp );

        /// Get the relative time deviation at a specified point in time
        ///
        /// \param t_req    Requested point in time (in seconds)
        ///
        /// \return         Interpolated time deviation value at the requested time.
        double  GetTD( double t_req );

        /// Forget data values from the past
        ///
        /// Time deviation from the past may be forgotten (i.e. deallocated)
        ///
        /// \param  t_now   The current time (in seconds)
        void    ForgetPast( double t_now );
};

#endif
