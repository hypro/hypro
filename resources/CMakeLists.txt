
# initialize lists for include directories and library files
set(${PROJECT_NAME}_INCLUDE_DIRS "" CACHE STRING "Include directories var")

add_custom_target(${PROJECT_NAME}-resources)
add_custom_target(${PROJECT_NAME}-parser-resources)
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-resources)
add_dependencies(${PROJECT_NAME}-parser ${PROJECT_NAME}-parser-resources)

set(RESSOURCES_FLAGS "-std=c++17 -Wno-error ${CMAKE_CXX_FLAGS} -Wno-error")
#message("Ressoures flags: ${RESSOURCES_FLAGS}")

# Load modules
include(ExternalProject)
include(FetchContent)
if (DEVELOPER)
    include(CMakePrintHelpers)
endif ()

# Set default ExternalProject root directory
set(EP_PREFIX_DIR ${CMAKE_BINARY_DIR}/resources)
set_directory_properties(PROPERTIES EP_PREFIX ${EP_PREFIX_DIR})

# carl setup which deals with external carl and own carl instance (the later registers itself to cmake)
find_package(carl)
if (carl_FOUND)
    message(STATUS "Use system version of CArL version ${carl_VERSION}")
    # search for carl in config mode to locate the file carlConfig.cmake
    find_package(carl CONFIG)
    include(${carl_DIR}/carlConfig.cmake)
    message(STATUS "CARL DIR: ${carl_DIR}")
    include(carlVersionMacros)
    # correct aliasing works only after cmake 3.15, we will use this later
    #add_library(carl_STATIC ALIAS carl-static)
    #add_library(carl_SHARED ALIAS carl-shared)

    if (TARGET carl-shared)
        message(STATUS "CArL single library structure")
        # getting the include path is required for the macros to work correctly
        get_target_property(carl_abs_include_path carl-shared INTERFACE_INCLUDE_DIRECTORIES)
        export_target(DEPENDENT_TARGETS EIGEN3)
        if (CARL_LOGGING_POST_1910)
            export_target(DEPENDENT_TARGETS carl-logging-shared)
            export_target(DEPENDENT_TARGETS carl-logging-static)
        endif ()

        get_target_property(carl_libs_shared carl-shared INTERFACE_LINK_LIBRARIES)
        # filter only non-system libs (post-fixed with "SHARED")
        list(FILTER carl_libs_shared INCLUDE REGEX ".*_SHARED")

        get_target_property(carl_libs_static carl-static INTERFACE_LINK_LIBRARIES)
        # filter only non-system libs (post-fixed with "STATIC")
        list(FILTER carl_libs_static INCLUDE REGEX ".*_STATIC")

        export_target(DEPENDENT_TARGETS carl-shared)
        export_target(DEPENDENT_TARGETS carl-static)

        set(DEPENDENT_TARGETS ${DEPENDENT_TARGETS} PARENT_SCOPE)
        build_target_include_dirs_from(${PROJECT_NAME}-objects SYSTEM PUBLIC carl-shared)
        #build_target_include_dirs_from(${PROJECT_NAME}-objects SYSTEM PUBLIC ${carl_libs_shared})
        target_link_libraries(${PROJECT_NAME}-static PUBLIC carl-static)
        build_target_include_dirs_from(${PROJECT_NAME}-static SYSTEM INTERFACE carl-static)
        foreach (item ${carl_libs_static})
            target_link_libraries(${PROJECT_NAME}-static PUBLIC ${item})
            export_target(DEPENDENT_TARGETS ${item})
            if (NOT TARGET ${item})
                get_target_property(include ${item} INTERFACE_INCLUDE_DIRECTORY)
                get_target_property(lib ${item} IMPORTED_LOCATION)
                add_library(${item} STATIC IMPORTED GLOBAL)
                set_target_properties(${item} PROPERTIES IMPORTED_LOCATION "${lib}")
                set_target_properties(${item} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${include}")
            endif ()
        endforeach ()
        target_link_libraries(${PROJECT_NAME}-shared PUBLIC carl-shared)
        build_target_include_dirs_from(${PROJECT_NAME}-shared SYSTEM INTERFACE carl-shared)
        foreach (item ${carl_libs_shared})
            target_link_libraries(${PROJECT_NAME}-shared PUBLIC ${item})
            export_target(DEPENDENT_TARGETS ${item})
            if (NOT TARGET ${item})
                get_target_property(include ${item} INTERFACE_INCLUDE_DIRECTORY)
                get_target_property(lib ${item} IMPORTED_LOCATION)
                add_library(${item} SHARED IMPORTED GLOBAL)
                set_target_properties(${item} PROPERTIES IMPORTED_LOCATION "${lib}")
                set_target_properties(${item} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${include}")
            endif ()
        endforeach ()
    elseif (TARGET carl-common-shared AND TARGET carl-arith-shared AND TARGET carl-logging-shared AND TARGET carl-formula-shared)
        message(STATUS "CArL multi-library structure")
        export_target(DEPENDENT_TARGETS EIGEN3)
        set(carl_sublibraries_shared carl-common-shared carl-arith-shared carl-logging-shared carl-formula-shared)
        set(carl_sublibraries_static carl-common-static carl-arith-static carl-logging-static carl-formula-static)
        foreach (item ${carl_sublibraries_shared})
            # getting the include path is required for the macros to work correctly
            get_target_property(carl_abs_include_path ${item} INTERFACE_INCLUDE_DIRECTORIES)
            get_target_property(carl_libs_shared ${item} INTERFACE_LINK_LIBRARIES)
            # filter only non-system libs (post-fixed with "SHARED")
            list(FILTER carl_libs_shared INCLUDE REGEX ".*_SHARED")

            export_target(DEPENDENT_TARGETS ${item})

            set(DEPENDENT_TARGETS ${DEPENDENT_TARGETS} PARENT_SCOPE)
            build_target_include_dirs_from(${PROJECT_NAME}-objects SYSTEM PUBLIC ${item})
            target_link_libraries(${PROJECT_NAME}-shared PUBLIC ${item})
            build_target_include_dirs_from(${PROJECT_NAME}-shared SYSTEM INTERFACE ${item})
            foreach (dependency ${carl_libs_shared})
                target_link_libraries(${PROJECT_NAME}-shared PUBLIC ${dependency})
                export_target(DEPENDENT_TARGETS ${dependency})
                if (NOT TARGET ${dependency})
                    get_target_property(include ${dependency} INTERFACE_INCLUDE_DIRECTORY)
                    get_target_property(lib ${dependency} IMPORTED_LOCATION)
                    add_library(${dependency} SHARED IMPORTED GLOBAL)
                    set_target_properties(${dependency} PROPERTIES IMPORTED_LOCATION "${lib}")
                    set_target_properties(${dependency} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${include}")
                endif ()
            endforeach ()
        endforeach ()
        foreach (item ${carl_sublibraries_static})
            # getting the include path is required for the macros to work correctly
            get_target_property(carl_abs_include_path ${item} INTERFACE_INCLUDE_DIRECTORIES)
            get_target_property(carl_libs_static ${item} INTERFACE_LINK_LIBRARIES)
            # filter only non-system libs (post-fixed with "STATIC")
            list(FILTER carl_libs_static INCLUDE REGEX ".*_STATIC")

            export_target(DEPENDENT_TARGETS ${item})

            set(DEPENDENT_TARGETS ${DEPENDENT_TARGETS} PARENT_SCOPE)
            build_target_include_dirs_from(${PROJECT_NAME}-objects SYSTEM PUBLIC ${item})
            target_link_libraries(${PROJECT_NAME}-static PUBLIC ${item})
            build_target_include_dirs_from(${PROJECT_NAME}-static SYSTEM INTERFACE${item})
            foreach (dependency ${carl_libs_static})
                target_link_libraries(${PROJECT_NAME}-static PUBLIC ${dependency})
                export_target(DEPENDENT_TARGETS ${dependency})
                if (NOT TARGET ${dependency})
                    get_target_property(include ${dependency} INTERFACE_INCLUDE_DIRECTORY)
                    get_target_property(lib ${dependency} IMPORTED_LOCATION)
                    add_library(${dependency} STATIC IMPORTED GLOBAL)
                    set_target_properties(${dependency} PROPERTIES IMPORTED_LOCATION "${lib}")
                    set_target_properties(${dependency} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${include}")
                endif ()
            endforeach ()
        endforeach ()
    else ()
        message(FATAL_ERROR "Could not determine targets of CArL")
    endif ()
else ()
    message("-- Download version of CArL")
    include(carl.cmake)
    include(carlVersionMacros)
endif ()
# the variables which configure the usage of carl are defined here and need to be propagated to the parent scope, as add_subdirectory creates a new scope
set(CARL_OLD_INTERVALS ${CARL_OLD_INTERVALS} PARENT_SCOPE)
set(CARL_OLD_STRUCTURE ${CARL_OLD_STRUCTURE} PARENT_SCOPE)
set(CARL_POLY_MEMBER_SUBSTITUTE ${CARL_POLY_MEMBER_SUBSTITUTE} PARENT_SCOPE)
set(CARL_LOGGING_POST_1910 ${CARL_LOGGING_POST_1910} PARENT_SCOPE)

# Set up glpk.
# ATTENTION: It is important that this happens *before* CArL is loaded to ensure that the linker first links against
# glpk and second agains gmp and gmpxx inherited from CArL.
include(glpk.cmake)

# gtest needs to be build in any case, since one should not use system-versions of gtest
include(gtest.cmake)

if (HYPRO_BENCHMARK)
    message(STATUS "Download version of GBenchmark")
    set(GOOGLETEST_PATH)
    include(gbenchmark.cmake)
endif ()

if (HYPRO_USE_MIMALLOC)
    include(mimalloc.cmake)
endif ()

if (HYPRO_USE_CLP)
    message(STATUS "Use clp")
    include(clp.cmake)
endif ()

find_package(UUID QUIET REQUIRED)
if (NOT UUID_FOUND)
    message(SEND_ERROR "Package uuid-dev required to build antlr.")
endif ()

if (HYPRO_MATLAB_BINDINGS)
    include(matlab.cmake)
endif ()

#include external cmake file
include(ExternalAntlr4Cpp.cmake)

# # # # # # # # # # # # # # # # # # # # # #
# C.2. Optional libraries
# # # # # # # # # # # # # # # # # # # # # #

if (HYPRO_USE_COTIRE)
    # We use cotire, simply include it
    message(STATUS "Use cotire")
    include(cotire)
    cotire(${PROJECT_NAME}-shared)
    cotire(${PROJECT_NAME}-static)
else ()
    # We do not use cotire, create dummy function in case cotire is used somewhere
    function(cotire)
    endfunction(cotire)
endif ()

if (HYPRO_USE_PPL)
    load_library(${PROJECT_NAME} PPL 0)
endif ()

if (HYPRO_USE_SMTRAT)
    find_package(smtrat)
    target_link_libraries(${PROJECT_NAME}-shared PUBLIC smtrat-solver-shared smtrat-module-LRAModule-shared)
    target_link_libraries(${PROJECT_NAME}-static PUBLIC smtrat-solver-static smtrat-module-LRAModule-static)
endif ()

if (HYPRO_ENABLE_SPACEEX_OUTPUT)
    include(tinyxml.cmake)
endif ()

if (HYPRO_USE_Z3)
    load_library(${PROJECT_NAME} z3 0)
    if (NOT z3_FOUND)
        message(STATUS "Downloading Z3")
        include(z3.cmake)
    endif ()
    target_link_libraries(${PROJECT_NAME}-shared PUBLIC z3_SHARED)
endif ()

if (HYPRO_USE_SOPLEX)
    load_library(${PROJECT_NAME} soplex 0)
    target_link_libraries(${PROJECT_NAME}-shared PUBLIC ${soplex_LIBRARY} -lz)
    target_link_libraries(${PROJECT_NAME}-static PUBLIC ${soplex_LIBRARY} -lz)
endif ()

if (HYPRO_USE_MC++)
    load_library(${PROJECT_NAME} mc++ 0)
    if (NOT mc++_FOUND)
        message(STATUS "Downloading MC++")
        include(mc++.cmake)
    endif ()
endif ()

if (HYPRO_GSL_INTEGRATION)
    load_library(${PROJECT_NAME} GSL 0)
    #find_package(GSL)
    #if(GSL_FOUND)
    #    if(STATICLIB_SWITCH)
    #		add_library(GSL_STATIC STATIC} IMPORTED GLOBAL)
    #		set_target_properties(GSL_STATIC PROPERTIES IMPORTED_LOCATION "${GSL_LIBRARIES}")
    #		set_target_properties(GSL_STATIC PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${GSL_INCLUDE_DIR}")
    #    else()
    #		add_library(GSL_SHARED SHARED IMPORTED GLOBAL)
    #		set_target_properties(GSL_SHARED PROPERTIES IMPORTED_LOCATION "${GSL_LIBRARIES}")
    #		set_target_properties(GSL_SHARED PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${GSL_INCLUDE_DIR}")
    #	endif()
    #
    #    list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${GSL_INCLUDE_DIR})
    #else()
    #    message(STATUS "Library ${name} was not found.")
    #endif()
endif ()

# try finding graphviz - required for ReachTree plotting
include(graphviz.cmake)
if (HYPRO_HAS_GRAPHVIZ)
    set(HYPRO_HAS_GRAPHVIZ ${HYPRO_HAS_GRAPHVIZ} PARENT_SCOPE)
endif ()

# check whether gnuplot is present - allows direct usage during plotting
find_package(Gnuplot QUIET)
if (GNUPLOT_FOUND)
    message(STATUS "Found Gnuplot, Plotter allows direkt usage of gnuplot from HyPro")
    set(GNUPLOT_FOUND TRUE PARENT_SCOPE)
endif ()

if (HYPRO_USE_OPENMP)
    find_package(OpenMP REQUIRED)
    if (OPENMP_FOUND)
        #add_library(OpenMP ALIAS OpenMP::OpenMP_CXX)
        message(STATUS "OpenMP libraries: ${OpenMP_CXX_LIBRARIES}")
        list(GET OpenMP_CXX_LIBRARIES 0 openmp_lib)
        message(STATUS "List item 0: ${openmp_lib}")
        if ("${CMAKE_FIND_LIBRARY_SUFFIXES}" STREQUAL ".a")
            add_imported_library(OpenMP STATIC "${openmp_lib}" "${${LIBNAME}_INCLUDE_DIR}")
            export_target(DEPENDENT_TARGETS OpenMP_STATIC)
        else ()
            add_imported_library(OpenMP SHARED "${openmp_lib}" "${${LIBNAME}_INCLUDE_DIR}")
            export_target(DEPENDENT_TARGETS OpenMP_SHARED)
        endif ()
        target_compile_options(${PROJECT_NAME}-objects PUBLIC -fopenmp)
        target_compile_options(${PROJECT_NAME}-static PUBLIC -fopenmp)
        target_compile_options(${PROJECT_NAME}-shared PUBLIC -fopenmp)
        target_link_libraries(${PROJECT_NAME}-shared PUBLIC OpenMP_SHARED)
        target_link_libraries(${PROJECT_NAME}-objects PUBLIC OpenMP_SHARED)
        target_link_libraries(${PROJECT_NAME}-static PUBLIC OpenMP_SHARED)
    endif ()
endif ()

# for serialization
if (HYPRO_USE_SERIALIZATION)
    include(cereal.cmake)
endif ()


set(DEPENDENT_TARGETS ${DEPENDENT_TARGETS} PARENT_SCOPE)
