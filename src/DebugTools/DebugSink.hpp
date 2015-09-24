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

#ifndef DEBUG_SINK_HPP_
#define DEBUG_SINK_HPP_

// =========================================================================
// Includes
// =========================================================================

#include "DebugFileOutput.hpp"

#include "Utils/VectorTypes.hpp"
#include "TdEst/TdEstConfig.hpp"
#include "Filter/FilterImpResp.hpp"
#include "Filter/FilterKernel.hpp"

#include <iostream>
#include <fstream>

using namespace std;

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

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

        //------------------------------------------------------------------
        // Resources
        //------------------------------------------------------------------
        cDebugFileOutput    HpFilterConfig;
        cDebugFileOutput    PlnFilterConfig;
        cDebugFileOutput    HpFilterImpResp;
        cDebugFileOutput    PlnFilterImpResp;
        cDebugFileOutput    FilterKernel;
        cDebugFileOutput    WhiteNoise;
        cDebugFileOutput    HpFilteredNoise;
        cDebugFileOutput    PlnFilteredNoise;

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
        void    SetFileSavePath( std::string FileSavePath );

        void    EnableAll();

        void    EnableHpFilterConfigSaving();
        void    EnablePlnFilterConfigSaving();
        void    EnableHpFilterImpRespSaving();
        void    EnablePlnFilterImpRespSaving();
        void    EnableFilterKernelSaving();
        void    EnableWhiteNoiseSaving();
        void    EnablePlnFilteredNoiseSavind();
        void    EnableHpFilteredNoiseSavind();

        void    SaveHpFilterConfig( HP_FilterConfig_t c );
        void    SavePlnFilterConfig( PLN_FilterConfig_t c );
        void    SaveHpFilterImpResp( FilterImpResp *hp );
        void    SavePlnFilterImpResp( FilterImpResp *hp );
        void    SaveFilterKernel( cFilterKernel &H );
        void    SaveWhiteNoise( FFT_RealVector *pw );
        void    SavePlnFilteredNoise( FFT_RealVector *pw );
        void    SaveHpFilteredNoise( FFT_RealVector *pw );
};

// =========================================================================
// Global variables
// =========================================================================

extern cDebugSink   DebugSink;

// =========================================================================
// Function declarations
// =========================================================================

#endif
