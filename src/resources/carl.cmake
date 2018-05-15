
ExternalProject_Add(
	carl
	GIT_REPOSITORY http://github.com/smtrat/carl.git
	#GIT_TAG "17.04"
	BUILD_COMMAND make lib_carl
	INSTALL_COMMAND "")

ExternalProject_Add_Step(carl ReloadCMake
	COMMAND cmake ../..
	COMMENT "Re-run CMake."
	DEPENDEES build
	)

#Todo: Re-check, it should be possible to use load_library() afterwards, shouldn't it? Otherwise: Update lists
add_imported_library(CARL SHARED ${carl_LIBRARIES} ${carl_INCLUDE_DIR})
add_imported_library(CARL STATIC ${carl_LIBRARIES} ${carl_INCLUDE_DIR})
list(APPEND ${PROJECT_NAME}_LIBRARIES_STATIC ${carl_LIBRARIES})
list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${carl_INCLUDE_DIR})
set(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_INCLUDE_DIRS} PARENT_SCOPE)
set(${PROJECT_NAME}_LIBRARIES_STATIC ${${PROJECT_NAME}_LIBRARIES_STATIC} PARENT_SCOPE)

add_dependencies(CARL_SHARED carl)
add_dependencies(CARL_STATIC carl)
add_dependencies(resources CARL_SHARED)
add_dependencies(resources CARL_STATIC)
