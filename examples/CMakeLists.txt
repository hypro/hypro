file(GLOB EXAMPLES RELATIVE ${CMAKE_CURRENT_LIST_DIR} example_*.cpp)

foreach( example ${EXAMPLES} )
		string(REPLACE ".cpp" "" example_name ${example} )
        add_executable( ${example_name} EXCLUDE_FROM_ALL ${example})
        target_link_libraries( ${example_name} ${PROJECT_NAME})

    if(${STATICLIB_SWITCH} STREQUAL "ON")
    	set_target_properties( ${example_name} PROPERTIES LINK_SEARCH_END_STATIC TRUE )
    endif()
endforeach( example )

# ATTENTION: This is just used to test if all examples compile.
add_executable( allExamples EXCLUDE_FROM_ALL ${EXAMPLES} )
target_link_libraries( allExamples ${PROJECT_NAME})

if(${STATICLIB_SWITCH} STREQUAL "ON")
	set_target_properties( allExamples PROPERTIES LINK_SEARCH_END_STATIC TRUE )
endif()
