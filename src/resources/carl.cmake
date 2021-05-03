set(RESOURCE_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/resources)

set(CARL_BUILD_DIR "${RESOURCE_INSTALL_LOCATION}/src/CArL-EP-build")
set(CARL_SRC_DIR "${RESOURCE_INSTALL_LOCATION}/src/CArL-EP")

set(carl_VERSION 20.09)

set(carl_cmake_options -DBUILD_DOXYGEN=OFF -DBUILD_STATIC=ON -DUSE_BLISS=ON -DUSE_COCOA=ON -DEXPORT_TO_CMAKE=ON)

ExternalProject_Add(
	CArL-EP
	SOURCE_DIR ${RESOURCE_INSTALL_LOCATION}/src/CArL-EP-download
	BINARY_DIR ${RESOURCE_INSTALL_LOCATION}/src/CArL-EP-download-build
	GIT_TAG 45805617d17032016623507aed52ac0210013d34
	GIT_REPOSITORY https://github.com/smtrat/carl
	#CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DCMAKE_PREFIX_PATH=<INSTALL_DIR> ${carl_cmake_options}
	#CONFIGURE_COMMAND ${CMAKE_COMMAND} ${carl_cmake_options}
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} carl
	INSTALL_COMMAND ""
)
ExternalProject_Add_Step(
	CArL-EP
	dowload_and_configure
	COMMAND ""
	COMMENT "Downloading and configuring CArL"
	DEPENDEES configure
)
ExternalProject_Add_StepTargets(CArL-EP dowload_and_configure)

execute_process(
	WORKING_DIRECTORY ${RESOURCE_INSTALL_LOCATION}/src/CArL-EP-download
    COMMAND git clone https://github.com/smtrat/carl
	COMMAND git checkout 45805617d17032016623507aed52ac0210013d34
)
execute_process(
	WORKING_DIRECTORY ${RESOURCE_INSTALL_LOCATION}/src/CArL-EP-download-build
    COMMAND cmake ../CArL-EP-download
)
include(${RESOURCE_INSTALL_LOCATION}/src/CArL-EP-download-build/carlConfig.cmake)
message("Include ${RESOURCE_INSTALL_LOCATION}/src/CArL-EP-download-build/carlConfig.cmake")

add_imported_library(carl STATIC "${CMAKE_BINARY_DIR}/resources/lib/${CMAKE_FIND_LIBRARY_PREFIXES}carl$#{CMAKE_STATIC_LIBRARY_SUFFIX}" "${source_dir}/src")
add_imported_library(carl SHARED "${CMAKE_BINARY_DIR}/resources/lib/${CMAKE_FIND_LIBRARY_PREFIXES}carl$#{CMAKE_SHARED_LIBRARY_SUFFIX}" "${source_dir}/src")

add_dependencies(hypro_resources CArL-EP)




#ExternalProject_Add(
#	CArL-EP
#	#SOURCE_DIR ${TARGETDIR}/src/CArL-EP
#	#BINARY_DIR ${TARGETDIR}/src/CArL-EP-build
#	GIT_TAG 45805617d17032016623507aed52ac0210013d34
#	GIT_REPOSITORY https://github.com/smtrat/carl
#	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DCMAKE_PREFIX_PATH=<INSTALL_DIR> ${CMAKE_OPTIONS}
#	BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} carl
#	INSTALL_COMMAND ""
#)
#
#ExternalProject_Get_Property(CArL-EP source_dir)
#ExternalProject_Get_Property(CArL-EP binary_dir)

# Configure external project
#execute_process(
#    COMMAND ${CMAKE_COMMAND} ${source_dir}
#    WORKING_DIRECTORY ${CARL_BUILD_DIR}
#)
#
#ExternalProject_Add_StepDependencies(carl build foobar)

#message(STATUS "CArL source dir: ${source_dir}")
#message(STATUS "CArL binary dir: ${binary_dir}")
#
#add_imported_library(carl STATIC "${CMAKE_BINARY_DIR}/resources/lib/${CMAKE_FIND_LIBRARY_PREFIXES}carl$#{CMAKE_STATIC_LIBRARY_SUFFIX}" "${source_dir}/src")
#add_imported_library(carl SHARED "${CMAKE_BINARY_DIR}/resources/lib/${CMAKE_FIND_LIBRARY_PREFIXES}carl$#{CMAKE_SHARED_LIBRARY_SUFFIX}" "${source_dir}/src")
#
#include(${binary_dir}/carlConfig.cmake)
#get_target_property(libs CArL-EP INTERFACE_LINK_LIBRARIES)
#foreach(item ${libs})
#	#target_link_libraries(${PROJECT_NAME}-static PUBLIC ${item})
#	message(STATUS "Carl library: ${item}")
#endforeach()

#add_dependencies(carl_SHARED CArL-EP)
#add_dependencies(carl_STATIC CArL-EP)
#add_dependencies(hypro_resources carl_STATIC carl_SHARED CArL-EP)
#add_dependencies(hypro_resources  CArL-EP-download)

## load version macros after ressources to make sure carl_VERSION is set
#include(carlVersionMacros)

#file(MAKE_DIRECTORY ${CARL_BUILD_DIR})
#execute_process(
#	COMMAND ${CMAKE_COMMAND} -DTARGETDIR=${CMAKE_BINARY_DIR}/resources ${CMAKE_SOURCE_DIR}/src/resources/carl
#	WORKING_DIRECTORY ${CARL_BUILD_DIR}
#)
#execute_process(
#	COMMAND ${CMAKE_COMMAND} --build . --target CArL-EP-download
#	WORKING_DIRECTORY ${CARL_BUILD_DIR}
#)
#
#ExternalProject_Add(
#	CArL-EP
#	DOWNLOAD_COMMAND ""
#	CMAKE_ARGS "-DUSE_BLISS=ON -DUSE_COCOA=ON -DEXPORT_TO_CMAKE=ON"
#	CONFIGURE_COMMAND ""
#	BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} carl
#	INSTALL_COMMAND ""
#)



