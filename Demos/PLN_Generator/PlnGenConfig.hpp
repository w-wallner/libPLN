// ============================================================================
///
/// \file
///
/// \brief  TODO
///
/// TODO
///
/// \ingroup demos_pln_generator
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

#ifndef LIBPLN_DEMOS_PLNGENERATOR_PLNGENCONFIG_HPP_
#define LIBPLN_DEMOS_PLNGENERATOR_PLNGENCONFIG_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "TdVecGen/TdVecGen.hpp"

#include <boost/program_options.hpp>

namespace po = boost::program_options;

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class PlnGenConfig
{
    private:

        // -----------------------------------------------------------------
        // Resources
        // -----------------------------------------------------------------
        po::options_description     desc;
        po::variables_map           vm;

        // -----------------------------------------------------------------
        // Types
        // -----------------------------------------------------------------

        // Options
        struct GenericOptions
        {
            bool            verbose;
            bool            very_verbose;
        };

        struct SamplingOptions
        {
            std::string     fs;
        };

        struct PlnFilteringOptions
        {
            std::string     Method;
            double          Qd;
            std::string     alpha;
            size_t          length;
        };

        struct HpFilteringOptions
        {
            std::string     Method;
            double          f_c_nom;
            size_t          length;
        };

        struct InterpolationOpions
        {
            std::string     Method;
            std::string     fi;
        };

        struct RunOptions
        {
            size_t          ns;
            size_t          sl;
            unsigned int    seed;
        };

        struct  OutputOptions
        {
            std::string     Filename;
        };

        struct  Options
        {
            GenericOptions          generic;
            SamplingOptions         sample;
            PlnFilteringOptions     pln;
            HpFilteringOptions      hp;
            InterpolationOpions     interpolation;
            RunOptions              run;
            OutputOptions           output;
        };

    public:

        struct  PlnGenConfig_t
        {
            TdVecGenConfig_t        TdVecGenConfig;
            double                  fi;
            bool                    verbose;
            bool                    veryVerbose;
            size_t                  ns;
            std::string             Filename;
        };

        // Parse helpers
        struct DimensionMap_t
        {
            std::string Str;
            double      ScaleFactor;
        };

    private:

        // -----------------------------------------------------------------
        // Config strings
        // -----------------------------------------------------------------

        // Generic options
        static const std::string    help_desc;
        static const std::string    verbose_desc;
        static const std::string    very_verbose_desc;

        // Sampling options
        static const std::string    fs_desc1;
        static const std::string    fs_desc2;

        // PLN filtering options
        static const std::string    plnm_desc1;
        static const std::string    plnm_desc2;
        static const std::string    qd_desc;
        static const std::string    alpha_desc;
        static const std::string    kwl_desc1;
        static const std::string    kwl_desc2;

        // HP filtering options
        static const std::string    hpm_desc1;
        static const std::string    hpm_desc2;
        static const std::string    hpfc_desc1;
        static const std::string    hpfc_desc2;
        static const std::string    hpl_desc1;
        static const std::string    hpl_desc2;

        // Interpolation options
        static const std::string    im_desc1;
        static const std::string    im_desc2;
        static const std::string    if_desc1;
        static const std::string    if_desc2;

        // Run options
        static const std::string    ns_desc1;
        static const std::string    ns_desc2;
        static const std::string    sl_desc1;
        static const std::string    sl_desc2;
        static const std::string    seed_desc;

        // Output options
        static const std::string    ofn_desc1;
        static const std::string    ofn_desc2;

        // -----------------------------------------------------------------
        // Internal functions
        // -----------------------------------------------------------------
        void    PrintUsage();
        void    CheckMutualExlusive();
        void    CheckMutualExclusiveSub( std::string s1, std::string s2 );

        Options ReadOptions( int argc, char *argv[] );
        void    CheckLimits( Options o );
        static  double  ParseNumWithDimension( std::string Str, const DimensionMap_t Map[], size_t N );
        static  double  ParseFrequency( std::string Str );
        void    ExitOnError( std::string msg );

    public:

        // Config

        // Constructors/Destructor
        PlnGenConfig();

        // API
        PlnGenConfig_t  ParseProgramOptions( int argc, char *argv[] );
};

// =========================================================================
// Function declarations
// =========================================================================

#endif
