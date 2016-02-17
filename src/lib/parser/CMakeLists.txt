set(lib_hypro_parser_headers
	#parser/componentParser.h
	#parser/helper.h
	#parser/Parser.h
	#parser/utils.h
	parser/flowstar/flowstarParser.h
	parser/flowstar/helper.h
	parser/flowstar/polnomialParser.h
	parser/flowstar/components.h
	parser/flowstar/componentParser.h
	parser/flowstar/componentsAdapt.h
    PARENT_SCOPE)

set(lib_hypro_parser_sources
    parser/Parser.cpp
    PARENT_SCOPE)