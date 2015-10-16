
if(WIN32)

    # Use FindFFTW3 module
    set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/" )
    
    # Find FFTW3
    set(FFTW3_ROOT_DIR ${FFTW_BINARY_PATH})
    find_package(FFTW3 COMPONENTS double)

else()
        
    set(FFTW3_LIBRARIES fftw3)
    
endif()

add_executable(PLN_Generator EXCLUDE_FROM_ALL main.cpp PlnGenConfig.cpp)
                        
target_include_directories(PLN_Generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                            ${CMAKE_SOURCE_DIR}
                                            ${CMAKE_SOURCE_DIR}/src)


target_link_libraries(PLN_Generator PLN ${FFTW3_LIBRARIES} boost_program_options)
