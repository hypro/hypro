#  Find module for freeglut.
#  @author Stefan Schupp

set(Glut_PREFIX "" CACHE PATH "The path to the previx of an Glut installation")

find_path(Glut_INCLUDE_DIR 
	NAMES glut.h 
	PATHS ${Glut_PREFIX}/include /usr/include/GL /usr/local/include)

find_library(Glut_LIBRARY NAMES glut 
	PATHS ${Glut_PREFIX}/lib /usr/lib /usr/local/lib)

if(Glut_INCLUDE_DIR AND Glut_LIBRARY)
	get_filename_component(Glut_LIBRARY_DIR ${Glut_LIBRARY} PATH)
   set(Glut_FOUND TRUE)
endif()


if(Glut_FOUND)
   if(NOT Glut_FIND_QUIETLY)
      MESSAGE(STATUS "Found Glut: ${Glut_LIBRARY}")
   endif()
elseif(Glut_FOUND)
   if(Glut_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find Glut")
   endif()
endif()
