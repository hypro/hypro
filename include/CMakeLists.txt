file(GLOB_RECURSE headers RELATIVE ${CMAKE_SOURCE_DIR}/include *.h)
file(GLOB_RECURSE template_implementations RELATIVE ${CMAKE_SOURCE_DIR}/include *.tpp)
list(FILTER headers EXCLUDE REGEX tmlib_tmp)
list(FILTER template_implementations EXCLUDE REGEX tmlib_tmp)

add_library(${PROJECT_NAME}-objects OBJECT ${${PROJECT_NAME}_sources})
add_dependencies(${PROJECT_NAME}-objects hypro_resources)
build_target_include_dirs_from(${PROJECT_NAME}-objects SYSTEM PUBLIC GLPK_STATIC ANTLR4_SHARED clp_STATIC coinUtils_STATIC z3_SHARED)
target_include_directories(${PROJECT_NAME}-objects
        PRIVATE ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        )

########################################################################################
# Create static and shared libraries

add_library(${PROJECT_NAME}-static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}-objects>)
set_target_properties(${PROJECT_NAME}-static PROPERTIES
        VERSION "${PROJECT_VERSION}"
        SOVERSION "${PROJECT_VERSION}"
        OUTPUT_NAME ${PROJECT_NAME}
        LINKER_LANGUAGE CXX
        )

#target_link_libraries(${PROJECT_NAME}-static PUBLIC ${${PROJECT_NAME}_LIBRARIES_STATIC})
target_link_libraries(${PROJECT_NAME}-static PUBLIC pthread)

target_include_directories(${PROJECT_NAME}-static
        PRIVATE ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        )

##### SHARED LIBRARY

add_library(${PROJECT_NAME}-shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}-objects>)
set_target_properties(${PROJECT_NAME}-shared PROPERTIES
        VERSION "${PROJECT_VERSION}"
        SOVERSION "${PROJECT_VERSION}"
        OUTPUT_NAME ${PROJECT_NAME}
        LINKER_LANGUAGE CXX
        )
# setting target sources allows to specify headers that will be installed later
target_sources(${PROJECT_NAME}-shared
        PUBLIC
        FILE_SET ${PROJECT_NAME}_headers
        TYPE HEADERS
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include
        FILES ${headers} ${template_implementations}
        )

#target_link_libraries(${PROJECT_NAME}-shared PUBLIC ${${PROJECT_NAME}_LIBRARIES_DYNAMIC})
target_link_libraries(${PROJECT_NAME}-shared PUBLIC pthread)

target_include_directories(${PROJECT_NAME}-shared
        PRIVATE ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        )

target_compile_features(${PROJECT_NAME}-objects PUBLIC cxx_std_17)
target_compile_features(${PROJECT_NAME}-static PUBLIC cxx_std_17)
target_compile_features(${PROJECT_NAME}-shared PUBLIC cxx_std_17)

target_compile_options(${PROJECT_NAME}-objects PUBLIC -fPIC)
target_compile_options(${PROJECT_NAME}-static PUBLIC -fPIC)
target_compile_options(${PROJECT_NAME}-shared PUBLIC -fPIC)
target_compile_options(${PROJECT_NAME}-objects PRIVATE -Wall -Wextra -Wno-attributes -pedantic -ftemplate-backtrace-limit=0 -funroll-loops)
target_compile_options(${PROJECT_NAME}-static PRIVATE -Wall -Wextra -Wno-attributes -pedantic -ftemplate-backtrace-limit=0 -funroll-loops)
target_compile_options(${PROJECT_NAME}-shared PRIVATE -Wall -Wextra -Wno-attributes -pedantic -ftemplate-backtrace-limit=0 -funroll-loops)
if (${DEVELOPER})
    target_compile_options(${PROJECT_NAME}-objects PRIVATE -Wswitch -Wno-deprecated-declarations -Wempty-body -Wconversion -Wreturn-type -Wparentheses -Wno-format -Wuninitialized -Wunreachable-code -Wunused-function -Wunused-value -Wunused-variable -fsanitize=address -fstack-protector-strong -g)
    target_compile_options(${PROJECT_NAME}-static PRIVATE -Wswitch -Wno-deprecated-declarations -Wempty-body -Wconversion -Wreturn-type -Wparentheses -Wno-format -Wuninitialized -Wunreachable-code -Wunused-function -Wunused-value -Wunused-variable -fsanitize=address -fstack-protector-strong -g)
    target_compile_options(${PROJECT_NAME}-shared PRIVATE -Wswitch -Wno-deprecated-declarations -Wempty-body -Wconversion -Wreturn-type -Wparentheses -Wno-format -Wuninitialized -Wunreachable-code -Wunused-function -Wunused-value -Wunused-variable -fsanitize=address -fstack-protector-strong -g)
endif ()
target_link_options(${PROJECT_NAME}-objects PUBLIC LINKER:-no-as-needed)
target_link_options(${PROJECT_NAME}-static PUBLIC LINKER:-no-as-needed)
target_link_options(${PROJECT_NAME}-shared PUBLIC LINKER:-no-as-needed)

# Meta-target which combines static and shared library
add_custom_target(${PROJECT_NAME} DEPENDS ${PROJECT_NAME}-shared ${PROJECT_NAME}-static)


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set_target_properties(${PROJECT_NAME}-shared PROPERTIES LINKER_LANGUAGE CXX INSTALL_RPATH "@loader_path/../lib")
    set_target_properties(${PROJECT_NAME}-static PROPERTIES LINKER_LANGUAGE CXX INSTALL_RPATH "@loader_path/../lib")
endif ()
set(HYPRO_TARGETS "${PROJECT_NAME}-shared" "${PROJECT_NAME}-static" CACHE STRING INTERNAL FORCE)


# Options for static linking
if (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mmacosx-version-min=10.7")
endif ()

# we do not specify destinations, since we use the defaults
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}-shared
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        FILE_SET ${PROJECT_NAME}_headers
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hypro
        )
install(TARGETS ${PROJECT_NAME}-static
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION
        )

install(EXPORT ${PROJECT_NAME}Targets
        FILE "${PROJECT_NAME}Targets.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
        )