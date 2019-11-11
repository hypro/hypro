file(GLOB_RECURSE PARSER_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
list(FILTER PARSER_SOURCES EXCLUDE REGEX "ParserWrapper")
set(PARSER_SOURCES ${PARSER_SOURCES} PARENT_SCOPE)

message("Parser sources: ${PARSER_SOURCES}")

add_library(${PROJECT_NAME}_parser OBJECT ${PARSER_SOURCES})
target_compile_definitions(${PROJECT_NAME}_parser PUBLIC OBJ)

target_link_libraries(${PROJECT_NAME}_parser PUBLIC ANTLR4_SHARED)

add_dependencies(${PROJECT_NAME}_parser resources)
