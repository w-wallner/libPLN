// ============================================================================
///
/// \file
///
/// \brief  Estimator for time deviation values
///
/// \ingroup module_td_estimator
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

#ifndef TD_ESTIMATOR_HPP_
#define TD_ESTIMATOR_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdEstConfig.hpp"
#include "TdGuess.hpp"
#include "TdEst/TdVectorStorage/TdVectorStorage.hpp"
#include "TdVecGen/TdVecGen.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

/// Estimator for TD values
///
/// This class implements an estimator for time deviation values. The
/// estimator is responsible for producing time devation values of a
/// specified powerlaw noise type and produces samples of this type with a
/// specified simulated sampling frequency. If configured, a high pass
/// can be used to prevent this estimator from influencing higher frequency
/// parts of the power spectral density.
///
/// Several such estimators can be combined to cover the full frequency
/// spectrum of a given oscillator.
/// This combination will be done by the TdEstChain class.
class TdEstimator
{
    private:

        // -----------------------------------------------------------------
        // Config
        // -----------------------------------------------------------------
        double  f_s;                                ///< Simulated sampling frequnency (in hertz)
        double  TickLen;                            ///< Time (in seconds) between two simulated samples (i.g. inverse of f_s)
        double  T_val;                              ///< Time between two requested samples where this estimator considers its contribution valid
        size_t  TdVecLen;                           ///< Length of individual time deviation vectors
        size_t  MaxTdVecCnt;                        ///< Maximum number of TD vectors that is calculated in a loop (used for internal error detection)
        bool    IntervalSkippingEnabled;            ///< Specifies if the TD estimator may skip intervals and just guess a future request

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------
        TdVecGen            *pTdVecGen;             ///< Generator for time deviation vectors
        TdVectorStorage     TdVecStorage;           ///< Internal storage for time deviation vectors

        // -----------------------------------------------------------------
        // House keeping
        // -----------------------------------------------------------------
        TdGuess             LastGuess;              ///< The last guess for a future request
        TdFixPoint          LastResult;             ///< The answer that was given to the last request

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------

        /// Forget data that is not needed any more
        ///
        /// \param t_now    Current time (in seconds)
        void    ForgetPast( double t_now );

        /// Check if the last guess became valid
        ///
        /// \param  t_now       Current time (in seconds)
        /// \param  ForceReset  If true, mark the current guess as invalid
        ////                    If false, the guess stays valid
        void    CheckLastGuess( double t_now, bool ForceReset );

        /// Guess a future time deviation request
        ///
        /// \param  t_req   The time in the future (in seconds) for which a time deviation is requested.
        ///
        /// \return         The estimated time deviation at that time.
        double  GuessFutureRelativeTD( double t_req );

    public:

        // -----------------------------------------------------------------
        // Constructors/Destructor
        // -----------------------------------------------------------------

        /// Constructor
        ///
        /// \param  Conf    The configuration for this time deviation estimator
        TdEstimator( TdEstimatorConfig Conf );

        /// Copy constructor
        ///
        /// \param other    The instance that should be copied
        TdEstimator( const TdEstimator& other );

        /// Destructor
        ~TdEstimator();

        // -----------------------------------------------------------------
        // Operators
        // -----------------------------------------------------------------

        /// Assignment operator
        ///
        /// \param other    The instance that should be assigned
        ///
        /// \return         An assigned instance
        TdEstimator&  operator=( const TdEstimator& other );

        // -----------------------------------------------------------------
        // API
        // -----------------------------------------------------------------

        /// Enable that intervals may be skipped if requests are in the distant future
        ///
        /// In this case, the estimator just returns a guess for a future time deviation value
        void    EnableIntervalSkipping();

        /// Disable interval skipping
        void    DisableIntervalSkipping();

        /// Set the seed for the random number generator
        ///
        /// \param Seed     The new seed for the random number generator
        void    SetSeed( unsigned int Seed );

        /// Request an estimate for the time deviation at a given point in time
        ///
        /// \param t_now    The current time (in seconds)
        /// \param t_req    The time (in seconds) for which the time deviation is requested
        ///
        /// \return         Estimated time deviation (in seconds) at the requested time
        double  EstimateTD( double t_now, double t_req );

        // -----------------------------------------------------------------
        // Getters
        // -----------------------------------------------------------------

        /// Getter for the configured sampling frequency
        ///
        /// \return The configured sampling frequency
        double      Get_f_s();
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
