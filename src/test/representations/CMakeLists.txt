if(${STATICLIB_SWITCH} STREQUAL "OFF")
    include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/lib ${include_dirs} )
    link_directories(${CMAKE_BUILD_DIR}/lib)

    ################################
    # Unit Tests
    ################################

    add_executable(runRepresentationTests
					BoxTest.cpp
    )

    add_dependencies(runRepresentationTests googletest)

    target_link_libraries(runRepresentationTests
                            #${binary_dir}/gtest
                            #${binary_dir}/gtest_main
                            #debug ${binary_dir}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
                            #optimized ${binary_dir}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
                            #${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
                            #${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${Suffix}
                            ${Pthread}
                            hypro  
                            ${libraries})
    add_test( NAME representations COMMAND runRepresentationTests )
endif()
