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

// =========================================================================
// Includes
// =========================================================================

#include "DebugFileOutput.hpp"

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

// =========================================================================
// Global variables
// =========================================================================

// =========================================================================
// Locale function prototypes
// =========================================================================

// =========================================================================
// Function definitions
// =========================================================================

cDebugFileOutput::cDebugFileOutput()
{
    Enabled     = false;
    Filename    = "";
}

cDebugFileOutput::~cDebugFileOutput()
{
    if( File.is_open() )
    {
        File.close();
    }
}

void
cDebugFileOutput::Enable(std::string Filename)
{
    this->Enabled = true;
    this->Filename = Filename;

    File.open( Filename.c_str() );
}

bool
cDebugFileOutput::IsEnabled()
{
    return Enabled;
}

std::ofstream&
cDebugFileOutput::Stream()
{
    return File;
}
