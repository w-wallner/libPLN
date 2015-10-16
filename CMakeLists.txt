cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project("libPLN")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

# FFTW binary dir for win32
IF(WIN32 AND NOT FFTW_BINARY_PATH)
    SET(FFTW_BINARY_PATH FFTW-NOTFOUND CACHE PATH "Source path for the FFTW binary directories" FORCE)
    MESSAGE(FATAL_ERROR "Please provide the path for the FFTW binaries")
ENDIF()

# BOOST binary dir for win32
IF(WIN32 AND NOT BOOST_BINARY_PATH)
    SET(BOOST_BINARY_PATH BOOST-NOTFOUND CACHE PATH "Source path for the BOOST binary directories" FORCE)
    MESSAGE(FATAL_ERROR "Please provide the path for the BOOST binaries")
ENDIF()

IF(UNIX AND CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    MESSAGE(STATUS "Detected x64 Linux system, setting -fPIC")
    SET( CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} -fPIC )
ENDIF()

add_subdirectory(src)
add_subdirectory(Examples)
add_subdirectory(Tests)
add_subdirectory(Demos)
