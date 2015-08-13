
add_executable(TestBench EXCLUDE_FROM_ALL main.cpp BasicTests.cpp EstimatorTB.cpp OracleTB.cpp)
                        
target_include_directories(TestBench PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                            ${CMAKE_SOURCE_DIR}
                                            ${CMAKE_SOURCE_DIR}/src)
                                      
target_link_libraries(TestBench PLN_Examples PLN fftw3)
