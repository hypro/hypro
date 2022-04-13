set(JUST_INSTALL_CEREAL ON)
set(SKIP_PORTABILITY_TEST ON)
set(BUILD_TESTS OFF)

FetchContent_Declare(
        cereal
        GIT_REPOSITORY https://github.com/USCiLab/cereal.git
        GIT_TAG v1.3.1
)

# make targets for cereal available
FetchContent_MakeAvailable(cereal)

#add_subdirectory(${cereal_SOURCE_DIR} cereal-build)

set(cereal_INCLUDE_DIR ${cereal_SOURCE_DIR}/include)

message(STATUS "Cereal source dir: ${cereal_SOURCE_DIR}")
message(STATUS "Cereal include dir: ${cereal_INCLUDE_DIR}")
add_dependencies(${PROJECT_NAME}_resources cereal::cereal)

target_link_libraries(${PROJECT_NAME}-objects INTERFACE cereal::cereal)
target_link_libraries(${PROJECT_NAME}-shared PRIVATE $<BUILD_INTERFACE:cereal::cereal>)
#target_link_libraries(${PROJECT_NAME}-static PRIVATE $<BUILD_INTERFACE:cereal::cereal>)

target_include_directories(${PROJECT_NAME}-objects
        PUBLIC ${cereal_INCLUDE_DIR}
        )
target_include_directories(${PROJECT_NAME}-static
        PRIVATE ${cereal_INCLUDE_DIR}
        )
target_include_directories(${PROJECT_NAME}-shared
        PUBLIC ${cereal_INCLUDE_DIR}
        )

#list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${cereal_INCLUDE_DIR})