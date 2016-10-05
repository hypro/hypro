ExternalProject_Add(
	carl
	GIT_REPOSITORY http://github.com/smtrat/carl.git
	INSTALL_COMMAND "")

# Specify include dir
ExternalProject_Get_Property(carl source_dir)
ExternalProject_Get_Property(carl binary_dir)

if(STATICLIB_SWITCH)
	add_imported_library(carl STATIC "${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}carl${CMAKE_STATIC_LIBRARY_SUFFIX}" "${source_dir}/include")
else()
	add_imported_library(carl SHARED "${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}carl${CMAKE_SHARED_LIBRARY_SUFFIX}" "${source_dir}/include")
endif()

add_dependencies(resources carl)
