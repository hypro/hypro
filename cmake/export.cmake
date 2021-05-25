
# Add all targets to the build-tree export set
export(TARGETS ${HYPRO_TARGETS} FILE "${PROJECT_BINARY_DIR}/hyproTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
if(EXPORT_TO_CMAKE)
	message(STATUS "Exporting to cmake")
	export(PACKAGE ${PROJECT_NAME})
else()
	message(STATUS "Not exporting to cmake")
endif()

export_target(DEPENDENT_TARGETS carl-shared)
export_target(DEPENDENT_TARGETS carl-static)
if(CARL_LOGGING_POST_1910)
	message(STATUS "Export carl-logging")
	export_target(DEPENDENT_TARGETS carl-logging-shared)
	export_target(DEPENDENT_TARGETS carl-logging-static)
endif()

get_target_property(libs carl-shared INTERFACE_LINK_LIBRARIES)
# filter only non-system libs (post-fixed with "SHARED")
list(FILTER libs INCLUDE REGEX ".*_SHARED")
foreach(item ${libs})
	export_target(DEPENDENT_TARGETS ${item})
endforeach()
get_target_property(libs carl-static INTERFACE_LINK_LIBRARIES)
# filter only non-system libs (post-fixed with "STATIC")
list(FILTER libs INCLUDE REGEX ".*_STATIC")
foreach(item ${libs})
	export_target(DEPENDENT_TARGETS ${item})
endforeach()

if(STATICLIB_SWITCH)
	if(HYPRO_MATLAB_BINDINGS)
		export_target(DEPENDENT_TARGETS Matlab_STATIC)
	endif()
else()
	if(HYPRO_MATLAB_BINDINGS)
		#export_target(DEPENDENT_TARGETS Matlab_SHARED)
	endif()
endif()

#export_target(DEPENDENT_TARGETS Boost_SHARED)
#export_target(DEPENDENT_TARGETS Boost_STATIC)
#export_target(DEPENDENT_TARGETS COCOA_SHARED)
#export_target(DEPENDENT_TARGETS COCOA_STATIC)
export_target(DEPENDENT_TARGETS Boost_program_options_SHARED)
export_target(DEPENDENT_TARGETS Boost_program_options_STATIC)
#export_target(DEPENDENT_TARGETS Boost_system_SHARED)
#export_target(DEPENDENT_TARGETS Boost_system_STATIC)
export_target(DEPENDENT_TARGETS EIGEN3)
#export_target(DEPENDENT_TARGETS BLISS_SHARED)
#export_target(DEPENDENT_TARGETS BLISS_STATIC)
#export_target(DEPENDENT_TARGETS COCOA_SHARED)
#export_target(DEPENDENT_TARGETS COCOA_STATIC)
export_target(DEPENDENT_TARGETS GLPK_STATIC)
#export_target(DEPENDENT_TARGETS GMP_SHARED)
#export_target(DEPENDENT_TARGETS GMP_STATIC)
export_target(DEPENDENT_TARGETS GMPXX_SHARED)
export_target(DEPENDENT_TARGETS GMPXX_STATIC GMP_STATIC)
export_target(DEPENDENT_TARGETS ANTLR4_STATIC)
export_target(DEPENDENT_TARGETS ANTLR4_SHARED)
if(HYPRO_USE_MIMALLOC)
	export_target(DEPENDENT_TARGETS mimalloc_SHARED)
	export_target(DEPENDENT_TARGETS mimalloc_STATIC)
endif()
if(HYPRO_USE_CLP)
	export_target(DEPENDENT_TARGETS clp_STATIC)
	export_target(DEPENDENT_TARGETS coinUtils_STATIC)
endif()
if(HYPRO_USE_SMTRAT)
	export_target(DEPENDENT_TARGETS smtrat-solver-shared)
	export_target(DEPENDENT_TARGETS smtrat-module-LRAModule-shared)
	export_target(DEPENDENT_TARGETS smtrat-solver-static)
	export_target(DEPENDENT_TARGETS smtrat-module-LRAModule-static)
endif()
if (HYPRO_USE_Z3)
	export_target(DEPENDENT_TARGETS z3_SHARED)
endif ()


include(CMakePackageConfigHelpers)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/hyproConfigVersion.cmake
					VERSION ${hypro_VERSION}
					COMPATIBILITY SameMajorVersion )

set(TARGET ${PROJECT_NAME})

# Create the hyproConfig.cmake and hyproConfigVersion files
# ... for the build tree
set(CONF_INCLUDES ${INCLUDES})

set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src") # TODO looks not correct, this would be hypro_INCLUDE_DIR
#if(STATICLIB_SWITCH)
#	set(CONF_LINKER_LIBS ${hypro_STATIC_LIBRARIES})
#else ()
#	set(CONF_LINKER_LIBS ${hypro_DYNAMIC_LIBRARIES})
#endif()

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
		DESTINATION ${CMAKE_INSTALL_DIR} )

install(EXPORT ${PROJECT_NAME} FILE "${PROJECT_NAME}Targets.cmake" DESTINATION ${CMAKE_INSTALL_DIR})

# Install the export set for use with the install-tree
#install(EXPORT ${HYPRO_TARGETS} DESTINATION ${PROJECT_BINARY_DIR}) # COMPONENT dev)
