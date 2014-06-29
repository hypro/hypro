include_directories( ${PROJECT_SOURCE_DIR}/src/lib # in order to have all headers (even not installed ones)
)
link_directories( ${PROJECT_BINARY_DIR}/src/lib
                  ${PROJECT_BINARY_DIR}
)


set( EXAMPLES 
    ################################
    # insert examples in this list #
    ################################
    example_addition
    example_subtraction
    example_multiplication
    example_division
    example_eigen_float_t
    example_hausdorffApprox
    example_matrixPolyhedra
    example_parser
    #example_polytopeFileWriter
    example_power
    example_ppl_nncPolyhedra
    example_squareroot
    example_cubicroot
    example_test
)

foreach( example ${EXAMPLES} )
    add_executable( ${example} EXCLUDE_FROM_ALL ${example}.cpp )
    if(${STATICLIB_SWITCH} STREQUAL "ON")
        set_target_properties( ${example} PROPERTIES LINK_SEARCH_END_STATIC TRUE )
    endif()
    target_link_libraries( ${example} ${PROJECT_NAME} )
endforeach( example )