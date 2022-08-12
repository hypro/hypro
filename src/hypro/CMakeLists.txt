# Collect source files
file(GLOB_RECURSE sources RELATIVE ${CMAKE_SOURCE_DIR} *.cpp)
# filter out matlab-bindings
list(FILTER sources EXCLUDE REGEX MHyPro.cpp|MReach.cpp|CompareMHyProAndCORA/example_box.cpp|CompareMHyProAndCORA/example_zonotope.cpp)
# make sources available
set(${PROJECT_NAME}_sources ${sources} PARENT_SCOPE)