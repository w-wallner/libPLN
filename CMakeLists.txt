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

add_subdirectory(src)
add_subdirectory(Tests)
add_subdirectory(Examples)
