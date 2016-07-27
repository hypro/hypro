# File: macros.cmake
# Authors: Igor N. Bongartz
# Erstellt: 2015-10-29
# Version: 2015-10-29
#
# This file contains several macros which are used in this project. Notice that several are copied straight from web ressources.

# Macro
# List handling macros
# Source: http://www.cmake.org/pipermail/cmake/2004-June/005187.html 12.6.2015

MACRO(LIST_PREPEND var value)
     SET(${var} ${value} ${${var}})
ENDMACRO(LIST_PREPEND)

MACRO(LIST_PREPEND_UNIQUE var value)
     SET(LIST_ADD_UNIQUE_FLAG 0)
     FOREACH(i ${${var}})
         IF ("${i}" MATCHES "${value}")
             SET(LIST_ADD_UNIQUE_FLAG 1)
         ENDIF("${i}" MATCHES "${value}")
     ENDFOREACH(i)
     IF(NOT LIST_ADD_UNIQUE_FLAG)
         SET(${var} ${value} ${${var}})
     ENDIF(NOT LIST_ADD_UNIQUE_FLAG)
ENDMACRO(LIST_PREPEND_UNIQUE)

MACRO(LIST_APPEND var value)
     SET(${var} ${${var}} ${value})
ENDMACRO(LIST_APPEND)

MACRO(LIST_APPEND_UNIQUE var value)
     SET(LIST_ADD_UNIQUE_FLAG 0)
     FOREACH(i ${${var}})
         IF ("${i}" STREQUAL "${value}")
             SET(LIST_ADD_UNIQUE_FLAG 1)
        ENDIF("${i}" STREQUAL "${value}")
     ENDFOREACH(i)
     IF(NOT LIST_ADD_UNIQUE_FLAG)
         SET(${var} ${${var}} ${value})
     ENDIF(NOT LIST_ADD_UNIQUE_FLAG)
ENDMACRO(LIST_APPEND_UNIQUE)

# Function
# collect_files in subdirectories and save them into variables
# Igor Bongartz 06.2015

function(collect_files prefix name)
  file(GLOB_RECURSE subfiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${name} ${name}/*)

  foreach(subfile ${subfiles})
    if(${subfile} MATCHES ".*([.]in)")
      string(REGEX REPLACE ".in" "" subfile_name ${subfile})
      configure_file(${CMAKE_SOURCE_DIR}/src/${prefix}/${name}/${subfile} ${CMAKE_SOURCE_DIR}/src/${prefix}/${name}/${subfile_name})

    elseif((${subfile} MATCHES ".*([.]h)") OR (${subfile} MATCHES ".*([.]tpp)"))
      get_filename_component(subdir ${subfile} DIRECTORY)
      if(NOT ${subdir} STREQUAL "")
        LIST_APPEND_UNIQUE(${prefix}_${name}_subdir ${subdir})
        list(APPEND ${prefix}_${name}_${subdir}_headers ${name}/${subfile})
      endif()
      list(APPEND ${prefix}_${name}_headers ${name}/${subfile})

    elseif(${subfile} MATCHES ".*([.]cpp)")
      list(APPEND ${prefix}_${name}_sources ${name}/${subfile})
    endif()
  endforeach()

  foreach(subdir ${${prefix}_${name}_subdir})
    install(FILES			${${prefix}_${name}_${subdir}_headers}
    DESTINATION		include/${prefix}/lib/${name}/${subdir})
  endforeach()

	#Install
	install(FILES			${${prefix}_${name}_headers}
  DESTINATION		include/${prefix}/lib/${name})

	#SET the scope
	set(${prefix}_${name}_headers ${${prefix}_${name}_headers} PARENT_SCOPE)
	set(${prefix}_${name}_sources ${${prefix}_${name}_sources} PARENT_SCOPE)
endfunction(collect_files)

macro(load_library group name version)
    string(TOUPPER ${name} LIBNAME)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ${DYNAMIC_EXT})
    set(Boost_USE_STATIC_LIBS OFF)
    find_package(${name} ${version} ${ARGN} QUIET)
    if(${name}_FOUND OR ${LIBNAME}_FOUND)
        if (${name}_FOUND)
            set(LIBNAME ${name})
        endif()
        list(APPEND ${group}_LIBRARIES_DYNAMIC ${${LIBNAME}_LIBRARIES})
        list(APPEND ${group}_INCLUDE_DIRS ${${LIBNAME}_INCLUDE_DIR})
        set(LOGMSG "Found ${name}:")
        set(LOGMSGLIBS "")
        if(${LIBNAME}_VERSION)
            set(LOGMSG "${LOGMSG} Version ${${LIBNAME}_VERSION}")
        endif()
        if(${LIBNAME}_LIBRARIES)
            set(LOGMSGLIBS "${${LIBNAME}_LIBRARIES}")
        endif()

        unset(${LIBNAME}_FOUND CACHE)
        unset(${LIBNAME}_INCLUDE_DIR CACHE)
        unset(${LIBNAME}_LIBRARIES CACHE)
        unset(${LIBNAME}_LIBRARY CACHE)

        set(CMAKE_FIND_LIBRARY_SUFFIXES ${STATIC_EXT})
        set(Boost_USE_STATIC_LIBS ON)
        if (ARGN)
            list(REMOVE_ITEM ARGN "REQUIRED")
        endif()
        find_package(${name} ${version} ${ARGN} QUIET)
        if(${LIBNAME}_FOUND)
            list(APPEND ${group}_LIBRARIES_STATIC ${${LIBNAME}_LIBRARIES})
            if(${LIBNAME}_LIBRARIES)
                set(LOGMSGLIBS "${LOGMSGLIBS}, ${${LIBNAME}_LIBRARIES}")
            endif()
        else()
            list(GET ${${group}_LIBRARIES_DYNAMIC} -1 ${LIBNAME}_LIBRARIES_DYNAMIC)
            list(APPEND ${group}_LIBRARIES_STATIC ${${LIBNAME}_LIBRARIES_DYNAMIC})
        endif()
        if(LOGMSGLIBS)
            set(LOGMSGLIBS "(${LOGMSGLIBS})")
        endif()
        message(STATUS "${LOGMSG} ${LOGMSGLIBS}")

        unset(${LIBNAME}_LIBRARIES CACHE)
        unset(${LIBNAME}_LIBRARY CACHE)
    else()
        message("-- Library ${name} was not found.")
    endif()
endmacro(load_library)

macro(export_target output TARGET)
    get_target_property(TYPE ${TARGET} TYPE)
    if(TYPE STREQUAL "SHARED_LIBRARY")
        get_target_property(LOCATION ${TARGET} IMPORTED_LOCATION)
        get_target_property(INCLUDE ${TARGET} INTERFACE_INCLUDE_DIRECTORIES)
        set(${output} "${${output}}
add_library(${TARGET} SHARED IMPORTED)
set_target_properties(${TARGET} PROPERTIES IMPORTED_LOCATION \"${LOCATION}\")
set_target_properties(${TARGET} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES \"${INCLUDE}\")
")
    elseif(TYPE STREQUAL "STATIC_LIBRARY")
        get_target_property(LOCATION ${TARGET} IMPORTED_LOCATION)
        get_target_property(INCLUDE ${TARGET} INTERFACE_INCLUDE_DIRECTORIES)
        set(${output} "${${output}}
add_library(${TARGET} STATIC IMPORTED)
set_target_properties(${TARGET} PROPERTIES IMPORTED_LOCATION \"${LOCATION}\")
set_target_properties(${TARGET} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES \"${INCLUDE}\")
")
        if(NOT "${ARGN}" STREQUAL "")
            set(${output} "${${output}}set_target_properties(${TARGET} PROPERTIES IMPORTED_LINK_INTERFACE_LIBRARIES \"${ARGN}\")
")
        endif()
    elseif(TYPE STREQUAL "INTERFACE_LIBRARY")
        get_target_property(INCLUDE ${TARGET} INTERFACE_INCLUDE_DIRECTORIES)
        set(${output} "${${output}}
add_library(${TARGET} INTERFACE IMPORTED)
set_target_properties(${TARGET} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES \"${INCLUDE}\")
")
    else()
        message(STATUS "Unknown type ${TYPE}")
    endif()
endmacro(export_target)
