
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
	CMAKE_ARGS "-DUSE_BLISS=ON -DUSE_COCOA=ON -DEXPORT_TO_CMAKE=ON"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} carl
	INSTALL_COMMAND ""
)

include(${CMAKE_BINARY_DIR}/resources/src/CArL-EP-build/carlConfig.cmake)
message("Include ${CMAKE_BINARY_DIR}/resources/src/CArL-EP-build/carlConfig.cmake")
add_dependencies(carl-shared CArL-EP)
add_dependencies(carl-static CArL-EP)
add_dependencies(resources carl-static carl-shared)
