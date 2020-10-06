
include(apple-llvm)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_USE_OWN_TR1_TUPLE=1")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5)
		message(FATAL_ERROR "gcc version should be larger or equal than 5.")
	endif()
	if (APPLE)
		message(STATUS "Using clang on apple")
		set(CMAKE_MACOSX_RPATH 1)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++")
		set(USE_LLVM_FROM_BREW NO)
		set(LIB_FILESYSTEM "c++fs")
		if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10.0)
			message(STATUS "clang ${CMAKE_CXX_COMPILER_VERSION} does not support C++17.")
			set(USE_LLVM_FROM_BREW YES)
		else()
			exec_program("sw_vers -productVersion" OUTPUT_VARIABLE MACOS_VERSION)
			if (MACOS_VERSION VERSION_LESS 10.15)
				message(STATUS "Found Mac OS X in version ${MACOS_VERSION} but version >= 10.15 needed for the proper libc++.")
				set(USE_LLVM_FROM_BREW YES)
			endif()
		endif()

		if(USE_LLVM_FROM_BREW)
			if(EXISTS "/usr/local/opt/llvm/bin/clang++")
				set(CMAKE_C_COMPILER /usr/local/opt/llvm/bin/clang CACHE PATH "" FORCE)
				set(CMAKE_CXX_COMPILER /usr/local/opt/llvm/bin/clang++ CACHE PATH "" FORCE)
				set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/opt/llvm/include -I/usr/local/opt/llvm/include/c++/v1/")
				set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib")
				set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib")
				exec_program("${CMAKE_CXX_COMPILER} --version" OUTPUT_VARIABLE tmp_version)
				string(REGEX REPLACE ".*version ([0-9.]+).*" "\\1" CMAKE_CXX_COMPILER_VERSION "${tmp_version}")
				if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7)
					set(LIB_FILESYSTEM "c++experimental")
				endif()
				message(STATUS "Auto-detected brew-installed llvm version ${CMAKE_CXX_COMPILER_VERSION}")
			else()
				message(FATAL_ERROR "Did not find a proper compiler. Please run \"brew install llvm\" or upgrade to XCode >= 10.1.")
			endif()
		endif()
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
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-as-needed")
else()
	message("-- Possibly unsupported compiler")
endif()

if(HYPRO_COVERAGE)
	include(CodeCoverage)
	APPEND_COVERAGE_COMPILER_FLAGS()
	setup_target_for_coverage(NAME hypro_coverage EXECUTABLE test DEPENDENCIES ${PROJECT_NAME} allTests)
endif()

# general compiler and linker settings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-attributes -pedantic -fPIC -ftemplate-backtrace-limit=0")
if(STATICLIB_SWITCH)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -pthread -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
	set(BUILD_SHARED_LIBRARIES OFF)
else()
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".so;.dylib")
	set(BUILD_SHARED_LIBRARIES ON)
endif()

# enable eigen3 vectorization
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -DEIGEN_DONT_VECTORIZE")

# flags related to development
if(DEVELOPER)

#GCC_ASAN_PRELOAD=$(gcc -print-file-name=libasan.so)
#CLANG_ASAN_PRELOAD=$(clang -print-file-name=libclang_rt.asan-x86_64.so)

	#detect asan location
	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		execute_process (
    		COMMAND bash -c "gcc -print-file-name=libasan.so"
    		OUTPUT_VARIABLE asanLocation
		)
	endif()
	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		execute_process (
			COMMAND bash -c "clang -print-file-name=libclang_rt.asan-x86_64.so"
			OUTPUT_VARIABLE asanLocation
		)
	endif()
	message(STATUS "asan runtime location for preloading: ${asanLocation}")


	set(DEV_FLAGS "\
 -Wswitch\
 -Wno-deprecated-declarations\
 -Wempty-body\
 -Wconversion\
 -Wreturn-type\
 -Wparentheses\
 -Wno-format\
 -Wuninitialized\
 -Wunreachable-code\
 -Wunused-function\
 -Wunused-value\
 -Wunused-variable\
 -fsanitize=address \
 -fstack-protector-strong\
 -g" CACHE INTERNAL "")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEV_FLAGS}")
endif()

message(STATUS "Current cmake flags: ${CMAKE_CXX_FLAGS}")
