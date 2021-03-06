
add_library(PLN STATIC  TdEstChain.cpp
                        TdOracle.cpp
                        DebugTools/DebugConfig.cpp
                        DebugTools/DebugFileOutput.cpp
                        DebugTools/DebugSink.cpp
                        Filter/IdentityFilterImpResp.cpp
                        Filter/BmHpFilterImpResp.cpp
                        Filter/FilterImpResp.cpp
                        Filter/FilterKernel.cpp
                        Filter/KwFilterImpResp.cpp
                        TdEst/TdEstConfig.cpp
                        TdEst/TdEstimator.cpp
                        TdEst/TdFixPoint.cpp
                        TdEst/TdGuess.cpp
                        TdEst/TdVectorStorage/TdVectorStorage.cpp
                        TdVecGen/GenericTdVecGen.cpp
                        TdVecGen/RecursiveTdVecGen.cpp
                        TdVecGen/RwTdVecGen.cpp
                        TdVecGen/TdVecGen.cpp
                        TdVecGen/WfmTdVecGen.cpp
                        TdVecGen/WpmTdVecGen.cpp
                        TdVecGen/WhiteNoiseGenerator/WhiteNoiseGenerator.cpp
                        TdVecGen/TdVecGenFactory.cpp
                        TdVector/TdVector.cpp
                        TdVector/TdVectorCubSpline.cpp
                        TdVector/TdVectorLinear.cpp
                        Utils/ErrorHandling.cpp
                        Utils/FFT.cpp
                        Utils/NumericTricks.cpp
                        Utils/spline.cpp
                        Utils/VectorTypes.cpp)

target_include_directories(PLN PUBLIC   ${CMAKE_CURRENT_SOURCE_DIR}
                                        ${CMAKE_SOURCE_DIR}
                                        ${CMAKE_SOURCE_DIR}/src
                                        ${FFTW_BINARY_PATH}
                                        ${BOOST_BINARY_PATH})

install(TARGETS PLN
        RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin
        LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/lib
        ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/lib/static)
