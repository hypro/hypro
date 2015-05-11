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

namespace hypro {

	template<typename Target, typename Source>
	class Converter {
	public:
		Converter();
		~Converter();

		Target operator(const Source& _source);

	private:
	};
} //namespace