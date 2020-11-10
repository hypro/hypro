# Quick self-configuration if only doc is built
if("${PROJECT_NAME}" STREQUAL "")
	cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
	project(HyPro-doxygen NONE)
	include(FindDoxygen)
endif()

find_package(Doxygen)

# Configure doxygen settings file

set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR} )

set(ADDITIONAL_INCLUDES_DOXYGEN ${${PROJECT_NAME}_INCLUDE_DIRS})
get_target_property(INCLUDE COCOA_SHARED INTERFACE_INCLUDE_DIRECTORIES)
set(ADDITIONAL_INCLUDES_DOXYGEN ${ADDITIONAL_INCLUDES_DOXYGEN} ${INCLUDE})
get_target_property(INCLUDE GLPK_STATIC INTERFACE_INCLUDE_DIRECTORIES)
set(ADDITIONAL_INCLUDES_DOXYGEN ${ADDITIONAL_INCLUDES_DOXYGEN} ${INCLUDE})
get_target_property(INCLUDE ANTLR4_STATIC INTERFACE_INCLUDE_DIRECTORIES)
set(ADDITIONAL_INCLUDES_DOXYGEN ${ADDITIONAL_INCLUDES_DOXYGEN} ${INCLUDE})
string(REPLACE ";" " " ADDITIONAL_INPUTS_STRING "${ADDITIONAL_INCLUDES_DOXYGEN}")

message("additional doxygen includes are: ${ADDITIONAL_INCLUDES_DOXYGEN}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxygen.in ${CMAKE_CURRENT_BINARY_DIR}/Doxygen @ONLY)

add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxygen
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
)


# If pdf manual is enabled, do the same for the manual again
if(DOC_CREATE_PDF)
	find_package(LATEX COMPONENTS PDFLATEX BIBTEX)
    if(LATEX_FOUND)
        message(STATUS "Found pdflatex, create pdf-documentation.")
		# Configure config for Manual
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/manual/doxygen.conf.in ${CMAKE_CURRENT_BINARY_DIR}/manual/doxygen.conf)

		# Build the manual
		set(TEX_DIR ${DOXYGEN_OUTPUT_DIR}/manual/latex)
		add_custom_target(doc-pdf-latex
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/manual/doxygen.conf
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating LaTeX documentation with Doxygen" VERBATIM
        )

        add_custom_target(doc-pdf
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
            COMMAND ${PDFLATEX_COMPILER} refman.tex
			COMMAND ${PDFLATEX_COMPILER} refman.tex
			COMMAND mv refman.pdf ${DOXYGEN_OUTPUT_DIR}/doc_${PROJECT_NAME}-${PROJECT_VERSION}.pdf
            DEPENDS doc-pdf-latex
            COMMENT "Generating Pdf documentation with pdflatex" VERBATIM
        )
	else(LATEX_FOUND)
		message(STATUS "Did not find pdflatex, no pdf manual can be built.")
		set(DOXYGEN_CREATE_PDF NO)
	endif(LATEX_FOUND)
endif(DOC_CREATE_PDF)
