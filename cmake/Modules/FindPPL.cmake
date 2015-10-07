# Copyright (c) 2012-2013, Lars Baehren <lbaehren@gmail.com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
#  * Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#--------------------------------------------------------------------------------

# - Check for the presence of PPL
#
# The following variables are set when PPL is found:
#  PPL_FOUND      = Set to true, if all components of PPL have been found.
#  PPL_INCLUDES   = Include path for the header files of PPL
#  PPL_LIBRARIES  = Link these to use PPL
#  PPL_LFLAGS     = Linker flags (optional)

if (NOT PPL_FOUND)

  if (NOT PPL_ROOT_DIR)
    set (PPL_ROOT_DIR ${CMAKE_INSTALL_PREFIX})
  endif (NOT PPL_ROOT_DIR)

  ##_____________________________________________________________________________
  ## Check for the header files

  find_path (PPL_INCLUDES
    NAMES ppl_c.h
    HINTS ${PPL_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
    PATH_SUFFIXES include
    )

  ##_____________________________________________________________________________
  ## Check for the library

  set (PPL_LIBRARIES "")

  ## libppl

  find_library (PPL_PPL_LIBRARY ppl
    HINTS ${PPL_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
    PATH_SUFFIXES lib
    )
  if (PPL_PPL_LIBRARY)
    list (APPEND PPL_LIBRARIES ${PPL_PPL_LIBRARY})
  endif (PPL_PPL_LIBRARY)

  ## libppl_c

  find_library (PPL_PPL_C_LIBRARY ppl_c
    HINTS ${PPL_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
    PATH_SUFFIXES lib
    )
  if (PPL_PPL_C_LIBRARY)
    list (APPEND PPL_LIBRARIES ${PPL_PPL_C_LIBRARY})
  endif (PPL_PPL_C_LIBRARY)

  ##_____________________________________________________________________________
  ## Check for the executable

  find_program (PPL_EXECUTABLE <package name>
    HINTS ${PPL_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
    PATH_SUFFIXES bin
    )

  ##_____________________________________________________________________________
  ## Actions taken when all components have been found

  find_package_handle_standard_args (PPL DEFAULT_MSG PPL_LIBRARIES PPL_INCLUDES)

  if (PPL_FOUND)
    if (NOT PPL_FIND_QUIETLY)
      message (STATUS "Found PPL: " ${PPL_LIBRARIES})
      #message (STATUS "PPL_ROOT_DIR  = ${PPL_ROOT_DIR}")
      #message (STATUS "PPL_INCLUDES  = ${PPL_INCLUDES}")
      #message (STATUS "PPL_LIBRARIES = ${PPL_LIBRARIES}")
    endif (NOT PPL_FIND_QUIETLY)
  else (PPL_FOUND)
    if (PPL_FIND_REQUIRED)
      message (FATAL_ERROR "Could not find PPL!")
    endif (PPL_FIND_REQUIRED)
  endif (PPL_FOUND)

  ##_____________________________________________________________________________
  ## Mark advanced variables

  mark_as_advanced (
    PPL_ROOT_DIR
    PPL_INCLUDES
    PPL_LIBRARIES
    )

endif (NOT PPL_FOUND)
