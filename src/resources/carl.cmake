
set(CARL_BUILD_DIR "${CMAKE_BINARY_DIR}/resources/src/CArL-config-EP-build")
file(MAKE_DIRECTORY ${CARL_BUILD_DIR})
execute_process(
	COMMAND ${CMAKE_COMMAND} -DTARGETDIR=${CMAKE_BINARY_DIR}/resources ${CMAKE_SOURCE_DIR}/src/resources/carl
	WORKING_DIRECTORY ${CARL_BUILD_DIR}
)
execute_process(
	COMMAND ${CMAKE_COMMAND} --build . --target CArL-EP-download
	WORKING_DIRECTORY ${CARL_BUILD_DIR}
)

ExternalProject_Add(
	CArL-EP
	DOWNLOAD_COMMAND ""
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} carl lib_carl_static
	INSTALL_COMMAND ${CMAKE_MAKE_PROGRAM} install/fast
)

include(${CMAKE_BINARY_DIR}/resources/src/CArL-EP-build/carlConfig.cmake)
message("Include ${CMAKE_BINARY_DIR}/resources/src/CArL-EP-build/carlConfig.cmake")
add_dependencies(carl CArL-EP)
add_dependencies(lib_carl_static CArL-EP)
add_dependencies(resources carl lib_carl_static)

#ExternalProject_Add(
#	carl
#	GIT_REPOSITORY http://github.com/smtrat/carl.git
#	#GIT_TAG "17.04"
#	BUILD_COMMAND make carl
#	INSTALL_COMMAND "")
#
#ExternalProject_Add_Step(carl ReloadCMake
#	COMMAND cmake ../..
#	COMMENT "Re-run CMake."
#	DEPENDEES build
#	)
#
#add_custom_target(Boost_SHARED)
#
#
##Todo: Re-check, it should be possible to use load_library() afterwards, shouldn't it? Otherwise: Update lists
#add_imported_library(carl SHARED "${carl_LIBRARIES}" "${carl_INCLUDE_DIR}")
#add_imported_library(lib_carl_static STATIC "${carl_LIBRARIES}" "${carl_INCLUDE_DIR}")
#list(APPEND ${PROJECT_NAME}_LIBRARIES_STATIC ${carl_LIBRARIES})
#list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${carl_INCLUDE_DIR})
#set(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_INCLUDE_DIRS} PARENT_SCOPE)
#set(${PROJECT_NAME}_LIBRARIES_STATIC ${${PROJECT_NAME}_LIBRARIES_STATIC} PARENT_SCOPE)
#
#add_dependencies(carl carl)
#add_dependencies(lib_carl_static carl)
#add_dependencies(resources carl)
#add_dependencies(resources lib_carl_static)
