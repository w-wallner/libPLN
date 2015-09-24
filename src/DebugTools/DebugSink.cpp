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

// =========================================================================
// Includes
// =========================================================================

#include "DebugSink.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Global variables
// =========================================================================

cDebugSink   DebugSink;

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

//------------------------------------------------------------------
// Internal functions
//------------------------------------------------------------------
std::string
cDebugSink::GetFilePath( std::string FileName )
{
    stringstream    ss;

    ss << FileSavePath;
    if( !FilePrefix.empty() )
    {
        ss << FilePrefix << "_";
    }
    ss << FileName;

    return ss.str();
}

//------------------------------------------------------------------
// Constructors/Destructor
//-----------------------------------------------------------------
cDebugSink::cDebugSink()
{
    FilePrefix      = "";
    FileSavePath    = "/main/";
}

cDebugSink::~cDebugSink()
{
}

//------------------------------------------------------------------
// API
//------------------------------------------------------------------

void
cDebugSink::SetFilePrefix( std::string FilePrefix )
{
    this->FilePrefix = FilePrefix;
}

void
cDebugSink::SetFileSavePath( std::string FileSavePath )
{
    this->FileSavePath = FileSavePath;
}

void
cDebugSink::EnableHpFilterImpRespSaving()
{
    HpFilterImpResp.Enable( GetFilePath( "HpFilterImpResp.txt" ).c_str() );
}

void
cDebugSink::EnablePlnFilterImpRespSaving()
{
    PlnFilterImpResp.Enable( GetFilePath( "PlnFilterImpResp.txt" ).c_str() );
}

void
cDebugSink::EnableFilterKernelSaving()
{
    FilterKernel.Enable( GetFilePath( "FilterKernel.txt" ).c_str() );
}

void
cDebugSink::EnableWhiteNoiseSaving()
{
    WhiteNoise.Enable( GetFilePath( "WhiteNoise.txt" ).c_str() );
}

void
cDebugSink::EnablePlnFilteredNoiseSavind()
{
    PlnFilteredNoise.Enable( GetFilePath( "PlnFilteredNoise.txt" ).c_str() );
}

void
cDebugSink::EnableHpFilteredNoiseSavind()
{
    HpFilteredNoise.Enable( GetFilePath( "HpFilteredNoise.txt" ).c_str() );
}

void
cDebugSink::SaveHpFilterImpResp( FilterImpResp *hp )
{
    if( HpFilterImpResp.IsEnabled() )
    {
        HpFilterImpResp.Stream() << hp->h();
    }
}

void
cDebugSink::SavePlnFilterImpResp( FilterImpResp *hp )
{
    if( PlnFilterImpResp.IsEnabled() )
    {
        PlnFilterImpResp.Stream() << hp->h();
    }
}

void
cDebugSink::SaveFilterKernel( cFilterKernel &H )
{
    if( FilterKernel.IsEnabled() )
    {
        FilterKernel.Stream() << H.GetFilterKernel();
    }
}

void
cDebugSink::SaveWhiteNoise( FFT_RealVector *pw )
{
    if( WhiteNoise.IsEnabled() )
    {
        WhiteNoise.Stream() << *pw;
    }
}

void
cDebugSink::SavePlnFilteredNoise( FFT_RealVector *pw )
{
    if( PlnFilteredNoise.IsEnabled() )
    {
        PlnFilteredNoise.Stream() << *pw;
    }
}

void
cDebugSink::SaveHpFilteredNoise( FFT_RealVector *pw )
{
    if( HpFilteredNoise.IsEnabled() )
    {
        HpFilteredNoise.Stream() << *pw;
    }
}
