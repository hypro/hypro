### General infos
#minimum required CMAKE version
#CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

#Add /cmake to the modules that are looked for by cmake i guess
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#compiler must be c++11 or c++14
#SET(CMAKE_CXX_STANDARD 11)

#set variable pointing to antlr tool 
set(ANTLR4CPP_JAR_LOCATION ${PROJECT_SOURCE_DIR}/resources/antlr-4.7-complete.jar)

#include external cmake file
include(ExternalAntlr4Cpp)

#include runtime to compile against
#ANTLR4CPP_INCLUDE_DIRS and ANTLR4CPP_LIBS is already defined by the package
include_directories(${ANTLR4CPP_INCLUDE_DIRS})
link_directories(${ANTLR4CPP_LIBS})
message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4CPP_INCLUDE_DIRS} ")

#Call macro to add lexer and grammar to your build dependencies
#antlrcpptest ist the project's name space
message(STATUS "cmake current src dir is: ${CMAKE_CURRENT_SOURCE_DIR} ")
#Maybe next command not needed as it generates the files from the grammars; however, we do not want to generate the files during runtime.
#antlr4cpp_process_grammar(demo antlrcpptest 
#	${CMAKE_CURRENT_SOURCE_DIR}/grammar/TLexer.g4
#	${CMAKE_CURRENT_SOURCE_DIR}/grammar/TParser.g4)
#message("Executed process_grammar!")

#include generated files 
include_directories(${antlr4cpp_include_dirs_antlrcpptest})

#starting point is main.cpp
#Also add generated grammer to demo binary target
add_executable(antlrtest main.cpp ${antlr4cpp_src_files_antlrcpptest})
add_dependencies(antlrtest antlr4cpp antlr4cpp_generation_antlrcpptest)
target_link_libraries(antlrtest antlr4-runtime)




