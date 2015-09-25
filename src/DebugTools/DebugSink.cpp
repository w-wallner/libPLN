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
    ss << "." << FileType;

    return ss.str();
}

//------------------------------------------------------------------
// Constructors/Destructor
//-----------------------------------------------------------------
cDebugSink::cDebugSink()
{
    FilePrefix      = "";
    FileType        = "txt";
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
cDebugSink::SetFileType( std::string FileType )
{
    this->FileType = FileType;
}

void
cDebugSink::SetFileSavePath( std::string FileSavePath )
{
    this->FileSavePath = FileSavePath;
}

void
cDebugSink::EnableAll()
{
    EnableSampleConfigSaving();
    EnableWhiteNoiseConfigSaving();
    EnableHpFilterConfigSaving();
    EnablePlnFilterConfigSaving();
    EnableHpFilterImpRespSaving();
    EnablePlnFilterImpRespSaving();
    EnableFilterKernelSaving();
    EnableWhiteNoiseSaving();
    EnablePlnFilteredNoiseSavind();
    EnableHpFilteredNoiseSavind();
    EnableTimeDeviation();
}

void
cDebugSink::EnableSampleConfigSaving()
{
    SampleConfig.Enable( GetFilePath( "SampleConfig" ).c_str() );
}

void
cDebugSink::EnableWhiteNoiseConfigSaving()
{
    WhiteNoiseConfig.Enable( GetFilePath( "WhiteNoiseConfig" ).c_str() );
}

void
cDebugSink::EnableHpFilterConfigSaving()
{
    HpFilterConfig.Enable( GetFilePath( "HpFilterConfig" ).c_str() );
}

void
cDebugSink::EnablePlnFilterConfigSaving()
{
    PlnFilterConfig.Enable( GetFilePath( "PlnFilterConfig" ).c_str() );
}

void
cDebugSink::EnableHpFilterImpRespSaving()
{
    HpFilterImpResp.Enable( GetFilePath( "HpFilterImpResp" ).c_str() );
}

void
cDebugSink::EnablePlnFilterImpRespSaving()
{
    PlnFilterImpResp.Enable( GetFilePath( "PlnFilterImpResp" ).c_str() );
}

void
cDebugSink::EnableFilterKernelSaving()
{
    FilterKernel.Enable( GetFilePath( "FilterKernel" ).c_str() );
}

void
cDebugSink::EnableWhiteNoiseSaving()
{
    WhiteNoise.Enable( GetFilePath( "WhiteNoise" ).c_str() );
}

void
cDebugSink::EnablePlnFilteredNoiseSavind()
{
    PlnFilteredNoise.Enable( GetFilePath( "PlnFilteredNoise" ).c_str() );
}

void
cDebugSink::EnableHpFilteredNoiseSavind()
{
    HpFilteredNoise.Enable( GetFilePath( "HpFilteredNoise" ).c_str() );
}

void
cDebugSink::EnableTimeDeviation()
{
    TimeDeviation.Enable( GetFilePath( "TimeDeviation" ).c_str() );
}

void
cDebugSink::SaveSampleConfig( SampleConfig_t c )
{
    if( SampleConfig.IsEnabled() )
    {
        SampleConfig.Stream() << c;
    }
}

void
cDebugSink::SaveWhiteNoiseConfig( WhiteNoiseConfig_t c )
{
    if( WhiteNoiseConfig.IsEnabled() )
    {
        WhiteNoiseConfig.Stream() << c;
    }
}

void
cDebugSink::SaveHpFilterConfig( HP_FilterConfig_t c )
{
    if( HpFilterConfig.IsEnabled() )
    {
        HpFilterConfig.Stream() << c;
    }
}

void
cDebugSink::SavePlnFilterConfig( PLN_FilterConfig_t c )
{
    if( PlnFilterConfig.IsEnabled() )
    {
        PlnFilterConfig.Stream() << c;
    }
}

void
cDebugSink::SaveHpFilterImpResp( FilterImpResp *hp )
{
    if( HpFilterImpResp.IsEnabled() )
    {
        HpFilterImpResp.Stream() << "[HpFilterImpResp]" << endl;
        HpFilterImpResp.Stream() << endl;
        HpFilterImpResp.Stream() << "FilterLen = " << hp->GetFilterLen() << endl;
        HpFilterImpResp.Stream() << "ReponseLen = " << hp->GetResponseLen() << endl;
        HpFilterImpResp.Stream() << "h = " << hp->h() << endl;
    }
}

void
cDebugSink::SavePlnFilterImpResp( FilterImpResp *hp )
{
    if( PlnFilterImpResp.IsEnabled() )
    {
        PlnFilterImpResp.Stream() << "[PlnFilterImpResp]" << endl;
        PlnFilterImpResp.Stream() << endl;
        PlnFilterImpResp.Stream() << "FilterLen = " << hp->GetFilterLen() << endl;
        PlnFilterImpResp.Stream() << "ReponseLen = " << hp->GetResponseLen() << endl;
        PlnFilterImpResp.Stream() << "h = " << hp->h() << endl;
    }
}

void
cDebugSink::SaveFilterKernel( cFilterKernel &H )
{
    if( FilterKernel.IsEnabled() )
    {
        FilterKernel.Stream() << "[FilterKernel]" << endl;
        FilterKernel.Stream() << endl;
        FilterKernel.Stream() << "FilterLen = " << H.GetFilterLen() << endl;
        FilterKernel.Stream() << "MaxDataLen = " << H.GetMaxDataLen() << endl;
        FilterKernel.Stream() << "FFT_RealSize = " << H.GetFFT_RealSize() << endl;
        FilterKernel.Stream() << "H = " << H.GetFilterKernel();
    }
}

void
cDebugSink::SaveWhiteNoise( FFT_RealVector *pw )
{
    if( WhiteNoise.IsEnabled() )
    {
        WhiteNoise.Stream() << *pw;
        WhiteNoise.Stream() << endl;
    }
}

void
cDebugSink::SavePlnFilteredNoise( FFT_RealVector *pw )
{
    if( PlnFilteredNoise.IsEnabled() )
    {
        PlnFilteredNoise.Stream() << *pw;
        PlnFilteredNoise.Stream() << endl;
    }
}

void
cDebugSink::SaveHpFilteredNoise( FFT_RealVector *pw )
{
    if( HpFilteredNoise.IsEnabled() )
    {
        HpFilteredNoise.Stream() << *pw;
        HpFilteredNoise.Stream() << endl;
    }
}

void
cDebugSink::SaveTimeDeviation( TdVector *pTD )
{
    if( TimeDeviation.IsEnabled() )
    {
        TimeDeviation.Stream() << *pTD;
        TimeDeviation.Stream() << endl;
    }
}
