
ExternalProject_Add(
	carl
	GIT_REPOSITORY http://github.com/smtrat/carl.git
	GIT_TAG "17.04"
	BUILD_COMMAND make lib_carl
	INSTALL_COMMAND "")

ExternalProject_Add_Step(carl ReloadCMake
	COMMAND cmake ../..
	COMMENT "Re-run CMake."
	DEPENDEES build
	)

add_dependencies(resources carl)
