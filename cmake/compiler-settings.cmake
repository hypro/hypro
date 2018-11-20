
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_USE_OWN_TR1_TUPLE=1")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++ -isystem\ /usr/include/libcxxabi/ -D__STRICT_ANSI__")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5)
		message(FATAL_ERROR "gcc version should be larger or equal than 5.")
	endif()
	if (APPLE)
		message(STATUS "Using clang on apple")
		set(CMAKE_MACOSX_RPATH 1)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++")
	else()
		message(STATUS "Using clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    endif()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -fomit-frame-pointer -msse -msse2 -funroll-loops")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O1")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	message(STATUS "Using g++")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7)
		message(FATAL_ERROR "gcc version should be larger or equal than 7.")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=auto")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O1")
else()
	message("-- Possibly unsupported compiler")
endif()

if(HYPRO_COVERAGE)
	include(CodeCoverage)
	APPEND_COVERAGE_COMPILER_FLAGS()
	setup_target_for_coverage(hypro_coverage test ${PROJECT_NAME})
endif()

# general compiler and linker settings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-attributes -pedantic -fPIC -ftemplate-backtrace-limit=0")
if(STATICLIB_SWITCH)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -pthread -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
	SET(BUILD_SHARED_LIBRARIES OFF)
else()
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".so;.dylib")
	SET(BUILD_SHARED_LIBRARIES ON)
endif()

if(DEVELOPER)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
		-Wswitch \
		-Wno-deprecated-declarations \
		-Wempty-body \
		-Wconversion \
		-Wreturn-type \
		-Wparentheses \
		-Wno-format \
		-Wuninitialized \
		-Wunreachable-code \
		-Wunused-function \
		-Wunused-value \
		-Wunused-variable")
endif()