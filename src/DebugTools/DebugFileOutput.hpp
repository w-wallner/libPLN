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

#ifndef LIBPLN_SRC_DEBUGTOOLS_DEBUGFILEOUTPUT_HPP_
#define LIBPLN_SRC_DEBUGTOOLS_DEBUGFILEOUTPUT_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <string>
#include <fstream>

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

class cDebugFileOutput
{
    private:

        // Config
        bool            Enabled;
        std::string     Filename;

        // Resources
        std::ofstream   File;

    public:

        // Constructors/Destructor
        cDebugFileOutput();
        ~cDebugFileOutput();

        // API
        void            Enable(std::string Filename);
        bool            IsEnabled();
        std::ofstream&  Stream();
};

// =========================================================================
// Global variables
// =========================================================================

// =========================================================================
// Function declarations
// =========================================================================

#endif
