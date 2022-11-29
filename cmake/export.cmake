# the following is inspired by https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-to-create-a-ProjectConfig.cmake-file
# some of the parts still need adjustment


# Add all targets to the build-tree export set
export(TARGETS ${HYPRO_TARGETS} FILE "${PROJECT_BINARY_DIR}/hyproTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
if (EXPORT_TO_CMAKE)
    message(STATUS "Exporting to cmake")
    set(CMAKE_EXPORT_PACKAGE_REGISTRY True)
    export(PACKAGE ${PROJECT_NAME})
else ()
    message(STATUS "Not exporting to cmake")
endif ()

if (STATICLIB_SWITCH)
    if (HYPRO_MATLAB_BINDINGS)
        export_target(DEPENDENT_TARGETS Matlab_STATIC)
    endif ()
else ()
    if (HYPRO_MATLAB_BINDINGS)
        #export_target(DEPENDENT_TARGETS Matlab_SHARED)
    endif ()
endif ()

export_target(DEPENDENT_TARGETS GLPK_STATIC)
export_target(DEPENDENT_TARGETS ANTLR4_STATIC)
export_target(DEPENDENT_TARGETS ANTLR4_SHARED)
export_target(DEPENDENT_TARGETS cereal::cereal)
if (HYPRO_USE_MIMALLOC)
    export_target(DEPENDENT_TARGETS mimalloc_SHARED)
    export_target(DEPENDENT_TARGETS mimalloc_STATIC)
endif ()
if (HYPRO_USE_CLP)
    export_target(DEPENDENT_TARGETS clp_STATIC)
    export_target(DEPENDENT_TARGETS coinUtils_STATIC)
endif ()
if (HYPRO_USE_SMTRAT)
    export_target(DEPENDENT_TARGETS smtrat-solver-shared)
    export_target(DEPENDENT_TARGETS smtrat-module-LRAModule-shared)
    export_target(DEPENDENT_TARGETS smtrat-solver-static)
    export_target(DEPENDENT_TARGETS smtrat-module-LRAModule-static)
endif ()
if (HYPRO_USE_TINYXML)
    export_target(DEPENDENT_TARGETS HYPRO_TINYXML_STATIC)
endif ()
if (HYPRO_USE_Z3)
    export_target(DEPENDENT_TARGETS z3_SHARED)
endif ()
if (HYPRO_GSL_INTEGRATION)
    export_target(DEPENDENT_TARGETS GSL_SHARED)
    export_target(DEPENDENT_TARGETS GSL_STATIC)
endif ()
if (HYPRO_HAS_GRAPHVIZ)
    export_target(DEPENDENT_TARGETS CGRAPH_SHARED)
    export_target(DEPENDENT_TARGETS GVC_SHARED)
endif ()


include(CMakePackageConfigHelpers)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/hyproConfigVersion.cmake
        VERSION ${hypro_VERSION}
        COMPATIBILITY SameMajorVersion)

set(TARGET ${PROJECT_NAME})

# Create the hyproConfig.cmake and hyproConfigVersion files
# ... for the build tree
set(CONF_INCLUDES ${INCLUDES})
set(CONF_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

configure_package_config_file(cmake/hyproConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/hyproConfig.cmake
        INSTALL_DESTINATION ${PROJECT_BINARY_DIR}
        PATH_VARS PROJECT_BINARY_DIR #SYSCONFIG_INSTALL_DIR
        )

file(RELATIVE_PATH REL_INCLUDE_DIR "${CMAKE_INSTALL_DIR}" "${INCLUDE_INSTALL_DIR}")
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${hypro_CMAKE_DIR}/${REL_INCLUDE_DIR}")

configure_package_config_file(cmake/hyproConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/installedConfig/hyproConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_DIR}
        PATH_VARS INCLUDE_INSTALL_DIR #SYSCONFIG_INSTALL_DIR
        )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/installedConfig/hyproConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/hyproConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_DIR})

install(EXPORT ${PROJECT_NAME} FILE "${PROJECT_NAME}Targets.cmake" DESTINATION ${CMAKE_INSTALL_DIR})

# Install the export set for use with the install-tree
#install(EXPORT ${HYPRO_TARGETS} DESTINATION ${PROJECT_BINARY_DIR}) # COMPONENT dev)
