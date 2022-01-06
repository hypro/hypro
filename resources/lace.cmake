# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/resources)

ExternalProject_Add(
        lace
        GIT_REPOSITORY https://github.com/trolando/lace.git
        INSTALL_COMMAND "")

# Specify include dir
ExternalProject_Get_Property(lace source_dir)
ExternalProject_Get_Property(lace binary_dir)

include_directories(${source_dir})
message("LACE source dir: ${source_dir}")
message("LACE binary dir: ${binary_dir}")
