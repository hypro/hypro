
find_package(Graphviz QUIET)

if (${GRAPHVIZ_FOUND})
    set(HYPRO_HAS_GRAPHVIZ ON PARENT_SCOPE)

    add_imported_library(CGRAPH SHARED
            "${GRAPHVIZ_CGRAPH_LIBRARY}"
            "${GRAPHVIZ_INCLUDE_DIRS}")
    add_imported_library(GVC SHARED
            "${GRAPHVIZ_GVC_LIBRARY}"
            "${GRAPHVIZ_INCLUDE_DIRS}")

    add_dependencies(${PROJECT_NAME}-resources CGRAPH_SHARED GVC_SHARED)

    target_link_libraries(${PROJECT_NAME}-shared PUBLIC CGRAPH_SHARED GVC_SHARED)
    target_link_libraries(${PROJECT_NAME}-static PUBLIC CGRAPH_SHARED GVC_SHARED)

    target_include_directories(${PROJECT_NAME}-objects
            PRIVATE ${GRAPHVIZ_INCLUDE_DIRS}
            )
    target_include_directories(${PROJECT_NAME}-static
            PRIVATE ${GRAPHVIZ_INCLUDE_DIRS}
            )
    target_include_directories(${PROJECT_NAME}-shared
            PRIVATE ${GRAPHVIZ_INCLUDE_DIRS}
            )

    list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${GRAPHVIZ_INCLUDE_DIRS})
    message(STATUS "Found Graphviz, enable plotting of ReachTrees from HyPro")
endif ()
