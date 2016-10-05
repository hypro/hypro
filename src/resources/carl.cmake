ExternalProject_Add(
	carl
	GIT_REPOSITORY http://github.com/smtrat/carl.git
	INSTALL_COMMAND "")

# use internal find mechanism to locate carl after building.
load_library(hypro carl 0)

add_dependencies(resources carl)
