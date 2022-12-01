
ExternalProject_Add(
        tinyxml
        GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
        DOWNLOAD_NO_PROGRESS 1
        LOG_CONFIGURE ON
        LOG_BUILD ON
        INSTALL_COMMAND "")

# Specify include dir
ExternalProject_Get_Property(tinyxml source_dir)
ExternalProject_Get_Property(tinyxml binary_dir)

#message(STATUS "tinyxml source dir: ${source_dir}")
#message(STATUS "tinyxml binary dir: ${binary_dir}")

add_imported_library(HYPRO_TINYXML STATIC "${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}tinyxml2${CMAKE_STATIC_LIBRARY_SUFFIX}" "${source_dir}")

add_dependencies(${PROJECT_NAME}_resources tinyxml)

target_link_libraries(${PROJECT_NAME}-objects INTERFACE HYPRO_TINYXML_STATIC)
target_link_libraries(${PROJECT_NAME}-shared PUBLIC $<BUILD_INTERFACE:HYPRO_TINYXML_STATIC>)
target_link_libraries(${PROJECT_NAME}-static PUBLIC $<BUILD_INTERFACE:HYPRO_TINYXML_STATIC>)

target_include_directories(${PROJECT_NAME}-objects
        PUBLIC ${tinyxml_INCLUDE_DIR}
        )
target_include_directories(${PROJECT_NAME}-static
        PRIVATE ${tinyxml_INCLUDE_DIR}
        )
target_include_directories(${PROJECT_NAME}-shared
        PUBLIC ${tinyxml_INCLUDE_DIR}
        )
