// ============================================================================
///
/// \file
///
/// \brief
///
/// \ingroup
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

#ifndef LIBPLN_SRC_DEBUGTOOLS_DEBUGSINK_HPP_
#define LIBPLN_SRC_DEBUGTOOLS_DEBUGSINK_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "DebugFileOutput.hpp"

#include "Utils/VectorTypes.hpp"
#include "TdEst/TdEstConfig.hpp"

#include <iostream>
#include <fstream>

using namespace std;

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class FilterImpResp;
class cFilterKernel;
class TdVector;

class cDebugSink
{
    private:

        //------------------------------------------------------------------
        // Types
        //------------------------------------------------------------------

        //------------------------------------------------------------------
        // Config
        //------------------------------------------------------------------
        std::string     FilePrefix;
        std::string     FileSavePath;
        std::string     FileType;

        //------------------------------------------------------------------
        // Resources
        //------------------------------------------------------------------
        cDebugFileOutput    SampleConfig;
        cDebugFileOutput    WhiteNoiseConfig;
        cDebugFileOutput    HpFilterConfig;
        cDebugFileOutput    PlnFilterConfig;
        cDebugFileOutput    HpFilterImpResp;
        cDebugFileOutput    PlnFilterImpResp;
        cDebugFileOutput    FilterKernel;
        cDebugFileOutput    WhiteNoise;
        cDebugFileOutput    HpFilteredNoise;
        cDebugFileOutput    PlnFilteredNoise;
        cDebugFileOutput    TimeDeviation;

        //------------------------------------------------------------------
        // Internal state
        //------------------------------------------------------------------

        //------------------------------------------------------------------
        // Internal functions
        //------------------------------------------------------------------
        std::string     GetFilePath( std::string FileName );

    public:

        //------------------------------------------------------------------
        // Constructors/Destructor
        //------------------------------------------------------------------
        cDebugSink();
        ~cDebugSink();

        //------------------------------------------------------------------
        // API
        //------------------------------------------------------------------
        void    SetFilePrefix( std::string FilePrefix );
        void    SetFileType( std::string FileType );
        void    SetFileSavePath( std::string FileSavePath );

        void    EnableAll();

        void    EnableSampleConfigSaving();
        void    EnableWhiteNoiseConfigSaving();
        void    EnableHpFilterConfigSaving();
        void    EnablePlnFilterConfigSaving();
        void    EnableHpFilterImpRespSaving();
        void    EnablePlnFilterImpRespSaving();
        void    EnableFilterKernelSaving();
        void    EnableWhiteNoiseSaving();
        void    EnablePlnFilteredNoiseSavind();
        void    EnableHpFilteredNoiseSavind();
        void    EnableTimeDeviation();

        void    SaveSampleConfig( SampleConfig_t c );
        void    SaveWhiteNoiseConfig( WhiteNoiseConfig_t c );
        void    SaveHpFilterConfig( HP_FilterConfig_t c );
        void    SavePlnFilterConfig( PLN_FilterConfig_t c );
        void    SaveHpFilterImpResp( FilterImpResp *hp );
        void    SavePlnFilterImpResp( FilterImpResp *hp );
        void    SaveFilterKernel( cFilterKernel *pH );
        void    SaveWhiteNoise( FFT_RealVector *pw );
        void    SavePlnFilteredNoise( FFT_RealVector *pw );
        void    SaveHpFilteredNoise( FFT_RealVector *pw );
        void    SaveTimeDeviation( TdVector *pTD );
};

// =========================================================================
// Global variables
// =========================================================================

extern cDebugSink   DebugSink;

// =========================================================================
// Function declarations
// =========================================================================

#endif
