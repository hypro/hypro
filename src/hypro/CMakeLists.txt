# Collect source files
# algorithms
file(GLOB_RECURSE algorithm_sources RELATIVE ${CMAKE_SOURCE_DIR} algorithms/*.cpp)
#message(STATUS "Algorithm sources: ${algorithm_sources}")
# datastructures
file(GLOB_RECURSE datastructures_sources RELATIVE ${CMAKE_SOURCE_DIR} datastructures/*.cpp)
#message(STATUS "Datastructures sources: ${datastructures_sources}")
# parser
file(GLOB_RECURSE parser_sources RELATIVE ${CMAKE_SOURCE_DIR} parser/*.cpp)
#message(STATUS "Parser sources: ${parser_sources}")
# representations
file(GLOB_RECURSE representation_sources RELATIVE ${CMAKE_SOURCE_DIR} representations/*.cpp)
#message(STATUS "Representation sources: ${representation_sources}")
# util
file(GLOB_RECURSE util_sources RELATIVE ${CMAKE_SOURCE_DIR} util/*.cpp)
#message(STATUS "Util sources: ${util_sources}")
# unify lists according to needs (here: exclude parser)
set(sources ${algorithm_sources} ${datastructures_sources} ${representation_sources} ${util_sources})
#message(STATUS "All sources: ${sources}")

# filter out matlab-bindings
list(FILTER sources EXCLUDE REGEX MHyPro.cpp|MReach.cpp|CompareMHyProAndCORA/example_box.cpp|CompareMHyProAndCORA/example_zonotope.cpp)
# make sources available
set(${PROJECT_NAME}_sources ${sources} PARENT_SCOPE)
# make sources for parser available
set(${PROJECT_NAME}_parser_sources ${parser_sources} PARENT_SCOPE)
