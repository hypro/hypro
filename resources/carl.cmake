set(RESOURCE_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/resources)

set(CARL_BUILD_DIR "${RESOURCE_INSTALL_LOCATION}/src/CArL-EP-build")
set(CARL_SRC_DIR "${RESOURCE_INSTALL_LOCATION}/src/CArL-EP")

set(carl_VERSION 21.11)

set(carl_cmake_options -DBUILD_DOXYGEN=OFF -DBUILD_STATIC=ON -DUSE_BLISS=ON -DUSE_COCOA=ON -DEXPORT_TO_CMAKE=ON)

find_package(Git QUIET)

if (GIT_FOUND)
    if (EXISTS ${RESOURCE_INSTALL_LOCATION}/src/CArL-EP-download/carl)
        message(STATUS "CArL already downloaded")
    else ()
        message(STATUS "Downloading CArL")
        file(MAKE_DIRECTORY ${RESOURCE_INSTALL_LOCATION}/src/CArL-download)
        execute_process(
                WORKING_DIRECTORY ${RESOURCE_INSTALL_LOCATION}/src/CArL-download
                COMMAND ${GIT_EXECUTABLE} clone https://github.com/smtrat/carl
        )
        execute_process(
                WORKING_DIRECTORY ${RESOURCE_INSTALL_LOCATION}/src/CArL-download
                COMMAND git checkout 5013c31c035990d9912a6265944e7d4add4c378b
        )
        message(STATUS "Configuring CArL")
        file(MAKE_DIRECTORY ${RESOURCE_INSTALL_LOCATION}/src/CArL-download-build)
        execute_process(
                WORKING_DIRECTORY ${RESOURCE_INSTALL_LOCATION}/src/CArL-download-build
                COMMAND cmake ../CArL-download/carl ${carl_cmake_options}
        )
        include(${RESOURCE_INSTALL_LOCATION}/src/CArL-download-build/carlConfig.cmake)
        message("Include ${RESOURCE_INSTALL_LOCATION}/src/CArL-download-build/carlConfig.cmake")
    endif ()
endif ()

ExternalProject_Add(
        CArL-EP
        SOURCE_DIR ${RESOURCE_INSTALL_LOCATION}/src/CArL-download-build
        BINARY_DIR ${RESOURCE_INSTALL_LOCATION}/src/CArL-download-build
        BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} carl
        INSTALL_COMMAND ""
)

set(carl_source "${RESOURCE_INSTALL_LOCATION}/src/CArL-download/carl/src")
set(carl_binary "${RESOURCE_INSTALL_LOCATION}/src/CArL-download-build")

add_imported_library(carl STATIC "${carl_binary}/${CMAKE_FIND_LIBRARY_PREFIXES}carl${CMAKE_STATIC_LIBRARY_SUFFIX}" "${carl_source}")
add_imported_library(carl SHARED "${carl_binary}/${CMAKE_FIND_LIBRARY_PREFIXES}carl${CMAKE_SHARED_LIBRARY_SUFFIX}" "${carl_source}")

target_link_libraries(${PROJECT_NAME}-objects PUBLIC carl_SHARED)
build_target_include_dirs_from(${PROJECT_NAME}-objects SYSTEM INTERFACE carl_SHARED)
foreach (item GMPXX_SHARED GMP_SHARED Boost_system_SHARED BLISS_SHARED COCOA_SHARED)
    target_link_libraries(${PROJECT_NAME}-objects PUBLIC ${item})
    if (NOT TARGET ${item})
        get_target_property(include ${item} INTERFACE_INCLUDE_DIRECTORY)
        get_target_property(lib ${item} IMPORTED_LOCATION)
        add_library(${item} STATIC IMPORTED GLOBAL)
        set_target_properties(${item} PROPERTIES IMPORTED_LOCATION "${lib}")
        set_target_properties(${item} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${include}")
    endif ()
endforeach ()


target_link_libraries(${PROJECT_NAME}-static PUBLIC carl_STATIC)
build_target_include_dirs_from(${PROJECT_NAME}-static SYSTEM INTERFACE carl_STATIC)
foreach (item GMPXX_STATIC GMP_STATIC Boost_system_STATIC BLISS_STATIC COCOA_STATIC)
    target_link_libraries(${PROJECT_NAME}-static PUBLIC ${item})
    if (NOT TARGET ${item})
        get_target_property(include ${item} INTERFACE_INCLUDE_DIRECTORY)
        get_target_property(lib ${item} IMPORTED_LOCATION)
        add_library(${item} STATIC IMPORTED GLOBAL)
        set_target_properties(${item} PROPERTIES IMPORTED_LOCATION "${lib}")
        set_target_properties(${item} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${include}")
    endif ()
endforeach ()

target_link_libraries(${PROJECT_NAME}-shared PUBLIC carl_SHARED)
build_target_include_dirs_from(${PROJECT_NAME}-shared SYSTEM INTERFACE carl_SHARED)
foreach (item GMPXX_SHARED GMP_SHARED Boost_system_SHARED BLISS_SHARED COCOA_SHARED)
    target_link_libraries(${PROJECT_NAME}-shared PUBLIC ${item})
    if (NOT TARGET ${item})
        get_target_property(include ${item} INTERFACE_INCLUDE_DIRECTORY)
        get_target_property(lib ${item} IMPORTED_LOCATION)
        add_library(${item} STATIC IMPORTED GLOBAL)
        set_target_properties(${item} PROPERTIES IMPORTED_LOCATION "${lib}")
        set_target_properties(${item} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${include}")
    endif ()
endforeach ()

build_target_include_dirs_from(${PROJECT_NAME}-objects SYSTEM PUBLIC carl_SHARED GMPXX_SHARED GMP_SHARED Boost_system_SHARED BLISS_SHARED COCOA_SHARED)

get_target_property(include EIGEN3 INTERFACE_INCLUDE_DIRECTORY)
target_link_libraries(${PROJECT_NAME}-static PUBLIC EIGEN3)
target_link_libraries(${PROJECT_NAME}-shared PUBLIC EIGEN3)

include(carlVersionMacros)

export_target(DEPENDENT_TARGETS GMPXX_SHARED)
export_target(DEPENDENT_TARGETS GMPXX_STATIC GMP_STATIC)
export_target(DEPENDENT_TARGETS EIGEN3)
if (CARL_LOGGING_POST_1910)
    export_target(DEPENDENT_TARGETS carl-logging-shared)
    export_target(DEPENDENT_TARGETS carl-logging-static)
endif ()

export_target(DEPENDENT_TARGETS carl_SHARED)
export_target(DEPENDENT_TARGETS carl_STATIC)

get_target_property(libs carl_SHARED INTERFACE_LINK_LIBRARIES)
# filter only non-system libs (post-fixed with "SHARED")
list(FILTER libs INCLUDE REGEX ".*_SHARED")
foreach (item ${libs})
    export_target(DEPENDENT_TARGETS ${item})
endforeach ()
get_target_property(libs carl_STATIC INTERFACE_LINK_LIBRARIES)
# filter only non-system libs (post-fixed with "STATIC")
list(FILTER libs INCLUDE REGEX ".*_STATIC")
foreach (item ${libs})
    export_target(DEPENDENT_TARGETS ${item})
endforeach ()

set(DEPENDENT_TARGETS ${DEPENDENT_TARGETS} PARENT_SCOPE)


add_dependencies(hypro_resources CArL-EP)
