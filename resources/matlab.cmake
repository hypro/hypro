
set(Matlab_ROOT_DIR ${HYPRO_MATLAB_ROOT})
message(STATUS "Searching for Matlab in: ${Matlab_ROOT_DIR}")
#set(MATLAB_FIND_DEBUG TRUE)

#find_package(Matlab)

#if(Matlab_FOUND)
#    message(STATUS "Found Matlab.")
#else()
#    message(STATUS "Did not find Matlab.")
#endif()

load_library(hypro Matlab 0)
