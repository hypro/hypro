# Quick self-configuration if only doc is built
if("${PROJECT_NAME}" STREQUAL "")
	cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
	project(HyPro-doxygen NONE)
	include(FindDoxygen)
endif()

find_package(Doxygen)

if(DOXYGEN)
    # Configure doxygen settings file

    set(DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/doxygen )

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxygen.in ${CMAKE_CURRENT_BINARY_DIR}/Doxygen @ONLY)

    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxygen
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif()
