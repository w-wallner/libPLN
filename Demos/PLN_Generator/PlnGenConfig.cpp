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

// =========================================================================
// Includes
// =========================================================================

#include "PlnGenConfig.hpp"

#include <iostream>
#include <ctime>

#include <boost/lexical_cast.hpp>

#include <utils.h>

#include "Utils/FrequencyStabilityAnalysis.hpp"

using namespace std;
using boost::lexical_cast;

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Static variables
// =========================================================================

// Generic options
const std::string    PlnGenConfig::help_desc            = "help";
const std::string    PlnGenConfig::verbose_desc         = "verbose";
const std::string    PlnGenConfig::very_verbose_desc    = "very-verbose";

// Sampling options
const std::string    PlnGenConfig::fs_desc1             = "sampling-frequency";
const std::string    PlnGenConfig::fs_desc2             = "fs";

// PLN filtering options
const std::string    PlnGenConfig::plnm_desc1           = "pln-filter-method";
const std::string    PlnGenConfig::plnm_desc2           = "plnm";
const std::string    PlnGenConfig::qd_desc              = "qd";
const std::string    PlnGenConfig::alpha_desc           = "alpha";
const std::string    PlnGenConfig::kwl_desc1            = "kw-filter-length";
const std::string    PlnGenConfig::kwl_desc2            = "kwl";

// HP filtering options
const std::string    PlnGenConfig::hpm_desc1            = "high-pass-filter-method";
const std::string    PlnGenConfig::hpm_desc2            = "hpm";
const std::string    PlnGenConfig::hpfc_desc1           = "high-pass-f-c-nom";
const std::string    PlnGenConfig::hpfc_desc2           = "hpfc";
const std::string    PlnGenConfig::hpl_desc1            = "high-pass-filter-length";
const std::string    PlnGenConfig::hpl_desc2            = "hpl";

// Interpolation options
const std::string    PlnGenConfig::im_desc1             = "interpolation-method";
const std::string    PlnGenConfig::im_desc2             = "im";
const std::string    PlnGenConfig::if_desc1             = "interpolation-frequency";
const std::string    PlnGenConfig::if_desc2             = "if";

// Run options
const std::string    PlnGenConfig::ns_desc1             = "number-of-samples";
const std::string    PlnGenConfig::ns_desc2             = "ns";
const std::string    PlnGenConfig::sl_desc1             = "segment-length";
const std::string    PlnGenConfig::sl_desc2             = "sl";
const std::string    PlnGenConfig::seed_desc            = "seed";

// Output options
const std::string    PlnGenConfig::ofn_desc1            = "output-filename";
const std::string    PlnGenConfig::ofn_desc2            = "of";

// Frequency dimension map for parser
static const PlnGenConfig::DimensionMap_t FrequencyMap[] =
{
    {   "GHz",  1E9  },
    {   "MHz",  1E6  },
    {   "kHz",  1E3  },
    {   "Hz",   1E0  },
    {   "mHz",  1E-3 },
};

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

void
PlnGenConfig::PrintUsage()
{
    cout << desc;
}

void
PlnGenConfig::CheckMutualExlusive()
{
    // Generic options
    // -

    // Sampling options
    CheckMutualExclusiveSub( fs_desc1, fs_desc2 );

    // PLN filtering options
    CheckMutualExclusiveSub( plnm_desc1, plnm_desc2 );
    CheckMutualExclusiveSub( kwl_desc1, kwl_desc2 );

    // HP filtering options
    CheckMutualExclusiveSub( hpm_desc1, hpm_desc2 );
    CheckMutualExclusiveSub( hpfc_desc1, hpfc_desc2 );
    CheckMutualExclusiveSub( hpl_desc1, hpl_desc2 );

    // Interpolation options
    CheckMutualExclusiveSub( im_desc1, im_desc2 );
    CheckMutualExclusiveSub( if_desc1, if_desc2 );

    // Run options
    CheckMutualExclusiveSub( ns_desc1, ns_desc2 );
    CheckMutualExclusiveSub( sl_desc1, sl_desc2 );

    // Output options
    CheckMutualExclusiveSub( ofn_desc1, ofn_desc2 );
}
void
PlnGenConfig::CheckMutualExclusiveSub( std::string s1, std::string s2 )
{
    if(vm.count(s1.c_str()) && vm.count(s2.c_str()))
    {
        cout << "The following options are mutually exclusive:" << endl;
        cout << "  " << s1 << endl;
        cout << "  " << s2 << endl;

        exit( EXIT_FAILURE );
    }
}

PlnGenConfig::Options
PlnGenConfig::ReadOptions( int argc, char *argv[] )
{
    po::store( po::parse_command_line( argc, argv, desc ), vm );
    po::notify(vm);

    if( vm.count(help_desc.c_str()) )
    {
        PrintUsage();
        exit( EXIT_SUCCESS );
    }

    CheckMutualExlusive();

    Options options;

    // Generic options
    if(vm.count( verbose_desc.c_str() ))
    {
        options.generic.verbose = true;
    }
    else
    {
        options.generic.verbose = false;
    }

    if(vm.count( very_verbose_desc.c_str() ))
    {
        options.generic.very_verbose = true;
    }
    else
    {
        options.generic.very_verbose = false;
    }

    // Sampling options
    if(vm.count( fs_desc1.c_str() ))
    {
        options.sample.fs = vm[fs_desc1.c_str()].as<std::string>();
    }
    else if(vm.count( fs_desc2.c_str() ))
    {
        options.sample.fs = vm[fs_desc2.c_str()].as<std::string>();
    }
    else
    {
        options.sample.fs = "";
    }

    // PLN filtering options
    if(vm.count( plnm_desc1.c_str() ))
    {
        options.pln.Method = vm[plnm_desc1.c_str()].as<std::string>();
    }
    else if(vm.count( plnm_desc2.c_str() ))
    {
        options.pln.Method = vm[plnm_desc2.c_str()].as<std::string>();
    }
    else
    {
        options.pln.Method = "";
    }

    if(vm.count( qd_desc.c_str() ))
    {
        options.pln.Qd = vm[qd_desc.c_str()].as<double>();
    }
    else
    {
        options.pln.Qd = 0.0;
    }

    if(vm.count( alpha_desc.c_str() ))
    {
        options.pln.alpha = vm[alpha_desc.c_str()].as<std::string>();
    }
    else
    {
        options.pln.alpha = "";
    }

    if(vm.count( kwl_desc1.c_str() ))
    {
        options.pln.length = vm[kwl_desc1.c_str()].as<unsigned long>();
    }
    else if(vm.count( kwl_desc2.c_str() ))
    {
        options.pln.length = vm[kwl_desc2.c_str()].as<unsigned long>();
    }
    else
    {
        options.pln.length = 0;
    }

    // HP filtering options
    if(vm.count( hpm_desc1.c_str() ))
    {
        options.hp.Method = vm[hpm_desc1.c_str()].as<std::string>();
    }
    else if(vm.count( hpm_desc2.c_str() ))
    {
        options.hp.Method = vm[hpm_desc2.c_str()].as<std::string>();
    }
    else
    {
        options.hp.Method = "";
    }

    if(vm.count( hpfc_desc1.c_str() ))
    {
        options.hp.f_c_nom = vm[hpfc_desc1.c_str()].as<double>();
    }
    else if(vm.count( hpfc_desc2.c_str() ))
    {
        options.hp.f_c_nom = vm[hpfc_desc2.c_str()].as<double>();
    }
    else
    {
        options.hp.f_c_nom = 0.0;
    }

    if(vm.count( hpl_desc1.c_str() ))
    {
        options.hp.length = vm[hpl_desc1.c_str()].as<unsigned long>();
    }
    else if(vm.count( hpl_desc2.c_str() ))
    {
        options.hp.length = vm[hpl_desc2.c_str()].as<unsigned long>();
    }
    else
    {
        options.hp.length = 0;
    }

    // Interpolation options
    if(vm.count( im_desc1.c_str() ))
    {
        options.interpolation.Method = vm[im_desc1.c_str()].as<std::string>();
    }
    else if(vm.count( im_desc2.c_str() ))
    {
        options.interpolation.Method = vm[im_desc2.c_str()].as<std::string>();
    }
    else
    {
        options.interpolation.Method = "";
    }

    if(vm.count( if_desc1.c_str() ))
    {
        options.interpolation.fi = vm[if_desc1.c_str()].as<std::string>();
    }
    else if(vm.count( if_desc2.c_str() ))
    {
        options.interpolation.fi = vm[if_desc2.c_str()].as<std::string>();
    }
    else
    {
        options.interpolation.fi = "";
    }

    // Run options
    if(vm.count( ns_desc1.c_str() ))
    {
        options.run.ns = vm[ns_desc1.c_str()].as<unsigned long>();
    }
    else if(vm.count( ns_desc2.c_str() ))
    {
        options.run.ns = vm[ns_desc2.c_str()].as<unsigned long>();
    }
    else
    {
        options.run.ns = 0;
    }

    if(vm.count( sl_desc1.c_str() ))
    {
        options.run.sl = vm[sl_desc1.c_str()].as<unsigned long>();
    }
    else if(vm.count( sl_desc2.c_str() ))
    {
        options.run.sl = vm[sl_desc2.c_str()].as<unsigned long>();
    }
    else
    {
        options.run.sl = 0;
    }

    if(vm.count( seed_desc.c_str() ))
    {
        options.run.seed = vm[seed_desc.c_str()].as<unsigned int>();
    }
    else
    {
        options.run.seed = 0;
    }

    // Output options
    if(vm.count( ofn_desc1.c_str() ))
    {
        options.output.Filename = vm[ofn_desc1.c_str()].as<std::string>();
    }
    else if(vm.count( ofn_desc2.c_str() ))
    {
        options.output.Filename = vm[ofn_desc2.c_str()].as<std::string>();
    }
    else
    {
        options.output.Filename = "";
    }

    return options;
}

void
PlnGenConfig::CheckLimits( Options o )
{
//    o.generic.verbose
//    o.hp.

}

double
PlnGenConfig::ParseNumWithDimension( std::string Str, const DimensionMap_t Map[], size_t N )
{
    size_t  FactorOffset;
    double  x;
    double  ScaleFactor;

    ScaleFactor = 1;
    for( size_t i = 0; i < N; i++ )
    {
        FactorOffset    = Str.find( Map[i].Str );

        if( string::npos != FactorOffset )
        {
            ScaleFactor = Map[i].ScaleFactor;
            Str = Str.substr( 0, FactorOffset );
            break;
        }
    }

    try
    {
        x = lexical_cast<double>( Str );
    }
    catch(...)
    {
        cerr << "ERROR: Could not parse dimensional value, terminating." << endl;
        exit( EXIT_FAILURE );
    }

    x *= ScaleFactor;

    return x;
}

double
PlnGenConfig::ParseFrequency( std::string Str )
{
    return  ParseNumWithDimension( Str, FrequencyMap, ArrayLen( FrequencyMap ) );
}

void
PlnGenConfig::ExitOnError( std::string msg )
{
    cerr << msg << endl;

    exit( EXIT_FAILURE );
}

PlnGenConfig::PlnGenConfig()
    : desc("Allowed options")
{
    // Declare the supported command line options
    desc.add_options()
        // Generic options
        ( help_desc.c_str(),                                        "Print the help text"                                                                       )
        ( verbose_desc.c_str(),                                     "Print verbose information during program execution"                                        )
        ( very_verbose_desc.c_str(),                                "Print even more verbose information during program execution"                              )

        // Sampling options
        ( fs_desc1.c_str(),             po::value<std::string>(),   "Simulated sampling frequency [Hz], optional GHz, MHz, kHz"                                 )
        ( fs_desc2.c_str(),             po::value<std::string>(),   "Shortcut for previous option"                                                              )

        // PLN filtering options
        ( plnm_desc1.c_str(),           po::value<std::string>(),   "PLN generation method. Options: kasdin-walter, recursive. Default: kasdin-walter"          )
        ( plnm_desc2.c_str(),           po::value<std::string>(),   "Shortcut for previous option"                                                              )
        ( qd_desc.c_str(),              po::value<double>(),        "Standard variance Qd for the random number generator"                                      )
        ( alpha_desc.c_str(),           po::value<std::string>(),   "Alpha value for the generated powerlaw noise (Sy~f^alpha)"                                 )
        ( kwl_desc1.c_str(),            po::value<size_t>(),        "Length of the Kasdin/Walter filter"                                                        )
        ( kwl_desc2.c_str(),            po::value<size_t>(),        "Shortcut for previous option"                                                              )

        // HP filtering options
        ( hpm_desc1.c_str(),            po::value<std::string>(),   "High pass filter method: Options: blackman, none. Default: none"                           )
        ( hpm_desc2.c_str(),            po::value<std::string>(),   "Shortcut for previous option"                                                              )
        ( hpfc_desc1.c_str(),           po::value<double>(),        "Nominal cut-off frequency of the high pass filter"                                         )
        ( hpfc_desc2.c_str(),           po::value<double>(),        "Shortcut for previous option"                                                              )
        ( hpl_desc1.c_str(),            po::value<size_t>(),        "Length of the high pass filter"                                                            )
        ( hpl_desc2.c_str(),            po::value<size_t>(),        "Shortcut for previous option"                                                              )

        // Interpolation options
        ( im_desc1.c_str(),             po::value<std::string>(),   "Interpolation method. Options: linear, cubic-spline. Default: linear"                      )
        ( im_desc2.c_str(),             po::value<std::string>(),   "Shortcut for previous option"                                                              )
        ( if_desc1.c_str(),             po::value<std::string>(),   "Interpolated frequency [Hz], optional GHz, MHz, kHz. Default: equals sampling frequency"   )
        ( if_desc2.c_str(),             po::value<std::string>(),   "Shortcut for previous option"                                                              )

        // Run options
        ( ns_desc1.c_str(),             po::value<size_t>(),        "Number of simulated sample values"                                                         )
        ( ns_desc2.c_str(),             po::value<size_t>(),        "Shortcut for previous option"                                                              )
        ( sl_desc1.c_str(),             po::value<size_t>(),        "Length of individual simulated segments"                                                   )
        ( sl_desc2.c_str(),             po::value<size_t>(),        "Shortcut for previous option"                                                              )
        ( seed_desc.c_str(),            po::value<unsigned int>(),  "Seed for the random number generator. 0 means random seed. Default: 0"                     )

        // Output options
        ( ofn_desc1.c_str(),            po::value<std::string>(),   "Output file name. Default: 'td.txt'"                                                       )
        ( ofn_desc2.c_str(),            po::value<std::string>(),   "Shortcut for previous option"                                                              )
    ;
}

PlnGenConfig::PlnGenConfig_t
PlnGenConfig::ParseProgramOptions( int argc, char *argv[] )
{
    PlnGenConfig_t      ret;

    Options o = ReadOptions( argc, argv );

    if( argc == 1 )
    {
        cout << "No parameters supplied, using default parameters, and enabling the verbose flag." << endl;
        o.generic.verbose   = true;
    }

    // Generic config
    ret.verbose     = o.generic.verbose | o.generic.very_verbose;
    ret.veryVerbose = o.generic.very_verbose;

    // White noise config
    if( o.pln.Qd > 0.0L )
    {
        ret.TdVecGenConfig.WhiteNoiseConf.Qd = o.pln.Qd;
    }
    else
    {
        ret.TdVecGenConfig.WhiteNoiseConf.Qd   = 1E-9L;

        if( ret.verbose )
        {
            cout << "Using default Qd: " << ret.TdVecGenConfig.WhiteNoiseConf.Qd << endl;
        }
    }

    if( o.run.seed != 0 )
    {
        ret.TdVecGenConfig.WhiteNoiseConf.Seed = o.run.seed;
    }
    else
    {
        ret.TdVecGenConfig.WhiteNoiseConf.Seed = static_cast<unsigned int>(time(NULL));

        if( ret.verbose )
        {
            cout << "Using time-based seed: " << ret.TdVecGenConfig.WhiteNoiseConf.Seed << endl;
        }
    }

    // PLN config
    if( o.pln.Method == "kasdin-walter" )
    {
        ret.TdVecGenConfig.PLN_FilterConf.Implementation = KASDIN_WALTER_FILTER;
    }
    else
    {
        ret.TdVecGenConfig.PLN_FilterConf.Implementation = RECURSIVE_FILTER;
    }

    if( o.pln.alpha.empty() )
    {
        ret.TdVecGenConfig.PLN_FilterConf.alpha = FSA::ALPHA_RW;

        if( ret.verbose )
        {
            cout << "Using default alpha: " << ret.TdVecGenConfig.PLN_FilterConf.alpha << endl;
        }
    }
    else if( o.pln.alpha == "wpm" )
    {
        ret.TdVecGenConfig.PLN_FilterConf.alpha = FSA::ALPHA_WPM;
    }
    else if( o.pln.alpha == "fpm" )
    {
        ret.TdVecGenConfig.PLN_FilterConf.alpha = FSA::ALPHA_FPM;
    }
    else if( o.pln.alpha == "wfm" )
    {
        ret.TdVecGenConfig.PLN_FilterConf.alpha = FSA::ALPHA_WFM;
    }
    else if( o.pln.alpha == "ffm" )
    {
        ret.TdVecGenConfig.PLN_FilterConf.alpha = FSA::ALPHA_FFM;
    }
    else if( o.pln.alpha == "rw" )
    {
        ret.TdVecGenConfig.PLN_FilterConf.alpha = FSA::ALPHA_RW;
    }
    else
    {
        ret.TdVecGenConfig.PLN_FilterConf.alpha = lexical_cast<double>( o.pln.alpha );

        if(( ret.TdVecGenConfig.PLN_FilterConf.alpha < FSA::ALPHA_RW) || ( ret.TdVecGenConfig.PLN_FilterConf.alpha > FSA::ALPHA_WPM))
        {
            ExitOnError( "Alpha outside allowed range [-2,2]" );
        }
    }

    if( ret.TdVecGenConfig.PLN_FilterConf.Implementation == RECURSIVE_FILTER )
    {
        if
        (
            ( ret.TdVecGenConfig.PLN_FilterConf.alpha != FSA::ALPHA_RW  ) &&
            ( ret.TdVecGenConfig.PLN_FilterConf.alpha != FSA::ALPHA_WFM ) &&
            ( ret.TdVecGenConfig.PLN_FilterConf.alpha != FSA::ALPHA_WPM )
        )
        {
            ret.TdVecGenConfig.PLN_FilterConf.Implementation = KASDIN_WALTER_FILTER;

            if( ret.verbose )
            {
                cout << "Recursive filter can only be used with alpha = -2.0, 0.0 or 2.0" << endl;
                cout << "Falling back on Kasdin-Walter filter implementation" << endl;
            }
        }
    }

    ret.TdVecGenConfig.PLN_FilterConf.FilterLen = o.pln.length;

    if( ret.TdVecGenConfig.PLN_FilterConf.Implementation == KASDIN_WALTER_FILTER )
    {
        if( ret.TdVecGenConfig.PLN_FilterConf.FilterLen == 0 )
        {
            ret.TdVecGenConfig.PLN_FilterConf.FilterLen = 1000;

            if( ret.verbose )
            {
                cout << "Using default KW filter length: " << ret.TdVecGenConfig.PLN_FilterConf.FilterLen << endl;
            }
        }
    }

    // HP config
    if( o.hp.Method == "blackman" )
    {
        ret.TdVecGenConfig.HP_FilterConf.FilterType = BLACKMAN;
    }
    else if( o.hp.Method == "none" )
    {
        ret.TdVecGenConfig.HP_FilterConf.FilterType = NO_FILTER;
    }
    else
    {
        ret.TdVecGenConfig.HP_FilterConf.FilterType = NO_FILTER;

        if( ret.verbose )
        {
            cout << "Using no high-pass filter" << endl;
        }
    }

    if(ret.TdVecGenConfig.HP_FilterConf.FilterType != NO_FILTER)
    {
        if(o.hp.f_c_nom == 0.0L)
        {
            ret.TdVecGenConfig.HP_FilterConf.f_c_nom = 0.3;
            cout << "Using no high-pass filter" << endl;
        }
        else if(( o.hp.f_c_nom > 0.0L ) && ( o.hp.f_c_nom < 1.0L ))
        {
            ret.TdVecGenConfig.HP_FilterConf.f_c_nom = o.hp.f_c_nom;
        }
        else
        {
            ExitOnError( "Nominal cut-off frequency must be in the interval (0.0,1.0)" );
        }

        ret.TdVecGenConfig.HP_FilterConf.FilterLen    = o.hp.length;
        ret.TdVecGenConfig.HP_FilterConf.Cnt          = 1;
    }
    else
    {
        ret.TdVecGenConfig.HP_FilterConf.f_c_nom      = 0.0L;
        ret.TdVecGenConfig.HP_FilterConf.Cnt          = 0;
        ret.TdVecGenConfig.HP_FilterConf.FilterLen    = 0;
    }

    // Sample config
    if( !o.sample.fs.empty() )
    {
        ret.TdVecGenConfig.SampleConf.f_s = ParseFrequency( o.sample.fs );
    }
    else
    {
        ret.TdVecGenConfig.SampleConf.f_s = 1E6L;

        if( ret.verbose )
        {
            cout << "Using default sampling frequency: " << ret.TdVecGenConfig.SampleConf.f_s << endl;
        }
    }

    if( o.run.sl != 0 )
    {
        ret.TdVecGenConfig.SampleConf.TdVecLen = o.run.sl;
    }
    else
    {
        if
        (
            ( ret.TdVecGenConfig.PLN_FilterConf.Implementation == RECURSIVE_FILTER ) &&
            ( ret.TdVecGenConfig.HP_FilterConf.FilterType == NO_FILTER )
        )
        {
            ret.TdVecGenConfig.SampleConf.TdVecLen = 1000;

            if( ret.verbose )
            {
                cout << "Using default segment length: " << ret.TdVecGenConfig.SampleConf.TdVecLen << endl;
            }
        }
        else
        {
            ret.TdVecGenConfig.SampleConf.TdVecLen =  ret.TdVecGenConfig.PLN_FilterConf.FilterLen;
            ret.TdVecGenConfig.SampleConf.TdVecLen += ret.TdVecGenConfig.HP_FilterConf.FilterLen;
            ret.TdVecGenConfig.SampleConf.TdVecLen += 10;

            if( ret.verbose )
            {
                cout << "Selecting a segment length based on the configured filter lengths: " << ret.TdVecGenConfig.SampleConf.TdVecLen << endl;
            }
        }
    }

    // Interpolation config
    if( o.interpolation.Method == "linear" )
    {
        ret.TdVecGenConfig.InterpolConf.InterPolType  = LINEAR_INTERPOLATION;
    }
    else if( o.interpolation.Method == "cubic-spline" )
    {
        ret.TdVecGenConfig.InterpolConf.InterPolType  = CUBIC_SPLINE_INTERPOLATION;
    }
    else
    {
        ret.TdVecGenConfig.InterpolConf.InterPolType  = LINEAR_INTERPOLATION;

        if( ret.verbose )
        {
            cout << "Using default interpolation method: linear" << endl;
        }
    }

    if( o.interpolation.fi.empty() )
    {
        if( ret.verbose )
        {
            cout << "Using sampling frequency as interpolation frequency (default)" << endl;
        }

        ret.fi = ret.TdVecGenConfig.SampleConf.f_s;
    }
    else
    {
        ret.fi = ParseFrequency( o.interpolation.fi );

        if( ret.fi <= ret.TdVecGenConfig.SampleConf.f_s )
        {
            ExitOnError( "Interpolated frequency has to be higher than simulated sampling frequency" );
        }
    }

    if( o.run.ns != 0 )
    {
        ret.ns = o.run.ns;
    }
    else
    {
        ret.ns = 1000000;

        if( ret.verbose )
        {
            cout << "Using default number of samples: " << ret.ns << endl;
        }
    }

    if( !o.output.Filename.empty() )
    {
        ret.Filename = o.output.Filename;
    }
    else
    {
        ret.Filename = "td.txt";

        if( ret.verbose )
        {
            cout << "Using default output filename: " << ret.Filename << endl;
        }
    }

    return ret;
}
