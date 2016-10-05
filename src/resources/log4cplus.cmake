ExternalProject_Add(log4cplus
		GIT_REPOSITORY https://github.com/log4cplus/log4cplus.git
		INSTALL_COMMAND ""
		)

add_dependencies(resources log4cplus)

ExternalProject_Get_Property(log4cplus source_dir)
ExternalProject_Get_Property(log4cplus binary_dir)

#message("source_dir: ${source_dir}")
#message("binary_dir: ${binary_dir}")
#message("shared library suffix: ${CMAKE_SHARED_LIBRARY_SUFFIX}")

add_imported_library(log4cplus SHARED "${binary_dir}/src/${CMAKE_FIND_LIBRARY_PREFIXES}log4cplus${CMAKE_SHARED_LIBRARY_SUFFIX}" "${binary_dir}/include")
