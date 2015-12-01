include_directories( ${PROJECT_SOURCE_DIR}/src/lib # in order to have all headers (even not installed ones)
)
link_directories( ${PROJECT_BINARY_DIR}/src/lib
                  ${PROJECT_BINARY_DIR}
)

add_subdirectory(TwoTank)

set( EXAMPLES
    ################################
    # insert examples in this list #
    ################################
    example_acos
    example_addition
    example_benchmarks
    example_bouncingBall
    example_box
    example_converter
    example_convexHull
    example_division
    example_eigen_float_t
    example_facetEnumeration
    example_hausdorffApprox
    example_matrixPolyhedra
    example_multiplication
    example_openglPlotting
    example_orthogonalPolyhedron
    example_parser
    example_plot
    example_point
    example_polytope
    example_polytopeFileWriter
    example_power
    #example_probabilistic
    #example_ppl_nncPolyhedra
    example_reachability
    example_reduction
    example_SFconversion
    example_squareroot
    example_subtraction
    example_supportFunction
    example_cubicroot
    example_test
    example_useSMT
    example_vertexEnumeration
    #example_twotankreachability
    example_zonotope
    example_HPolytope
)

foreach( example ${EXAMPLES} )
#    if (${example} STREQUAL example_twotankreachability)
#        find_package(MATLAB)
#      	if (${MATLAB_FOUND})
#      	    add_definitions(-DHAS_MATLAB)
#                  include_directories(${MATLAB_INCLUDE_DIR})
#                  set(MATLAB_LIB ${MATLAB_LIB} ${MATLAB_LIBRARIES})
#                  add_executable( ${example} EXCLUDE_FROM_ALL ${example}.cpp TwoTank/${twotank_test_sources})
#      	    target_link_libraries( ${example} ${PROJECT_NAME} ${MATLAB_LIB})
#      	else()
#      	    add_executable(${example} EXCLUDE_FROM_ALL ${example}.cpp)
#      	    target_link_libraries( ${example} ${PROJECT_NAME})
#      	endif()
#    else()
        add_executable( ${example} EXCLUDE_FROM_ALL ${example}.cpp)
        target_link_libraries( ${example} ${PROJECT_NAME} ${libraries} )

        set( exampleFiles ${exampleFiles} ${example}.cpp )

#    endif()

    if(${STATICLIB_SWITCH} STREQUAL "ON")
            set_target_properties( ${example} PROPERTIES LINK_SEARCH_END_STATIC TRUE )
    endif()

endforeach( example )



# ATTENTION: This is just used to test if all examples compile.
#add_executable( allExamples EXCLUDE_FROM_ALL ${exampleFiles} )
#target_link_libraries( allExamples ${PROJECT_NAME} ${libraries} )

#if(${STATICLIB_SWITCH} STREQUAL "ON")
#	set_target_properties( allExamples PROPERTIES LINK_SEARCH_END_STATIC TRUE )
#endif()
