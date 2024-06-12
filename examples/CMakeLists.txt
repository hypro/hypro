file(GLOB_RECURSE EXAMPLES RELATIVE ${CMAKE_CURRENT_LIST_DIR} example_*.cpp)

add_custom_target(allExamples)

if (STATICLIB_SWITCH)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(BUILD_SHARED_LIBS OFF)
endif ()

foreach (example ${EXAMPLES})
    string(REPLACE ".cpp" "" example_name ${example})
    string(REPLACE "tutorial/" "" example_name ${example_name})
    string(REPLACE "label_synchronization_benchmarks/" "" example_name ${example_name})
    add_executable(${example_name} EXCLUDE_FROM_ALL ${example})
    if (HYPRO_USE_MIMALLOC)
        get_target_property(mimalloc_library mimalloc_SHARED IMPORTED_LOCATION)
        #message(STATUS "Mimalloc location: ${mimalloc_library}")
        set_property(TARGET ${example_name}
                PROPERTY
                ENVIRONMENT LD_PRELOAD=${mimalloc_library})
    endif ()

    if (STATICLIB_SWITCH)
        #set_target_properties( ${example_name} PROPERTIES LINK_SEARCH_END_STATIC TRUE )
        set(CMAKE_EXE_LINKER_FLAGS "-static")
        set(BUILD_SHARED_LIBS OFF)
        target_link_libraries(${example_name} ${PROJECT_NAME}-static ${PROJECT_NAME}-parser)
    else ()
        target_link_libraries(${example_name} ${PROJECT_NAME}-shared ${PROJECT_NAME}-parser)
        #target_include_directories( ${example_name} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../build/locals/antlr4cpp/include/antlr4-runtime" )
    endif ()
    add_dependencies(allExamples ${example_name})
endforeach (example)

if (${STATICLIB_SWITCH} STREQUAL "ON")
    set_target_properties(allExamples PROPERTIES LINK_SEARCH_END_STATIC TRUE)
endif ()

target_sources(example_parallel_composition PRIVATE
            ${CMAKE_SOURCE_DIR}/src/tool/cli/cli.cpp ${CMAKE_SOURCE_DIR}/src/tool/cli/settingsProcessing.cpp
            ${CMAKE_SOURCE_DIR}/src/tool/cli/DynamicStrategyBuilder.cc
            ${CMAKE_SOURCE_DIR}/src/tool/reachability/analysis.cpp
            ${CMAKE_SOURCE_DIR}/src/tool/preprocessing/preprocessing.cpp)

find_package(Boost COMPONENTS program_options REQUIRED)
target_link_libraries(example_parallel_composition ${PROJECT_NAME}-shared ${PROJECT_NAME}-parser ${GBENCHMARK_LIBRARIES} Boost::program_options)

target_include_directories(example_parallel_composition PRIVATE ${CMAKE_SOURCE_DIR}/test/include/ ${CMAKE_SOURCE_DIR}/include/tool/)
add_dependencies(example_parallel_composition ${PROJECT_NAME}-resources)
