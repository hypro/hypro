/**
 * Class that provides a converter for representations. The template parameter specifies the target representation, the source representation is
 * included as an overloading.
 * @file Converter.h
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since 	2015-05-08
 * @version	2015-05-08
 */
 
#pragma once

#include "../util/VariablePool.h"
#include "../config.h"

// include representations for conversion
#include "Box.h"
#include "../SupportFunction/SupportFunction.h"
#include "../Polytopes/VPolytope/VPolytope.h"

namespace hypro {

	template<typename Target, typename Source>
	class Converter {
	private:
		VariablePool& mPool;

	public:
		Converter() : mPool(hypro::VariablePool::getInstance()){
		}
		~Converter(){}

		Target convert(const Source& _source) const;

	private:
	};

} //namespace
#include "Box/converter.h"