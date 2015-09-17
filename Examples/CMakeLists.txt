
add_library(PLN_Examples    AverageOscillator_20MHz/AverageOscillator_20MHz.cpp
                            AverageOscillator_20MHz/FFM_Chain.cpp
                            AverageOscillator_20MHz/FPM_Chain.cpp
                            AverageOscillator_20MHz/RW_Chain.cpp
                            AverageOscillator_20MHz/WFM_Chain.cpp
                            AverageOscillator_20MHz/WPM_Chain.cpp
                            WatchQuartz_20MHz/WatchQuartz_20MHz.cpp
                            WatchQuartz_20MHz/FFM_Chain.cpp
                            WatchQuartz_20MHz/RW_Chain.cpp
                            WatchQuartz_20MHz/WFM_Chain.cpp)

target_include_directories(PLN_Examples PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                ${CMAKE_SOURCE_DIR}
                                                ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(PLN_Examples PLN)

install(TARGETS PLN_Examples
        RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin
        LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/lib
        ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/lib/static)
