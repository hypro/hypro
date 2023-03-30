# based on https://stackoverflow.com/a/68376537 and https://stackoverflow.com/a/40423683
if (MSVC)
    execute_process(
            COMMAND ping www.google.com -n 2
            ERROR_QUIET
            RESULT_VARIABLE NO_CONNECTION
    )
else ()
    execute_process(
            COMMAND ping www.google.com -c 2
            ERROR_QUIET
            RESULT_VARIABLE NO_CONNECTION
    )
endif ()

if (NOT NO_CONNECTION EQUAL 0)
    set(FETCHCONTENT_FULLY_DISCONNECTED ON)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR}
            PROPERTY EP_UPDATE_DISCONNECTED 1)
    message(WARNING "Offline mode: requires already populated _deps and downloaded sources for external projects")
else ()
    set(FETCHCONTENT_FULLY_DISCONNECTED OFF)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR}
            PROPERTY EP_UPDATE_DISCONNECTED 0)
endif ()
