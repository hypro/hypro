#pragma once

#define INCL_FROM_GOHEADER true

#include "types.h"
#include "../config.h"
#include "../util/adaptions_eigen/adaptions_eigen.h"

/**
 * @brief      Purely virtual class defining an interface for geometric objects.
 * @tparam     Number  The used number type.
 */
template<typename Number>
class GeometricObject {

public:
	virtual ~GeometricObject(){}

	virtual std::size_t dimension() const = 0;

};


#include "conversion/Converter.h"
