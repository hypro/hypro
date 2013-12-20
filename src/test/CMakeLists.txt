if(${STATICLIB_SWITCH} STREQUAL "OFF")
    include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/lib )
    link_directories(${CMAKE_BUILD_DIR}/lib)

    ################################
    # Unit Tests
    ################################

    add_executable(runDatastructureTests
            PointTest.cpp
            VertexTest.cpp
    )

    add_dependencies(runDatastructureTests googletest)

    target_link_libraries(runDatastructureTests 
                            #${binary_dir}/gtest
                            #${binary_dir}/gtest_main
                            #debug ${binary_dir}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
                            #optimized ${binary_dir}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
                            ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
                            ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${Suffix}
                            ${Pthread}
                            hypro  
                            ${libraries})
    add_test( NAME datastructures COMMAND runDatastructureTests )
endif()

