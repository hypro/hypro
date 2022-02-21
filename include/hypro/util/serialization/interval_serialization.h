/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 17.02.22.
 */

#ifndef HYPRO_INTERVAL_SERIALIZATION_H
#define HYPRO_INTERVAL_SERIALIZATION_H

#include "mpq_serialization.h"

#include <carl/interval/Interval.h>

namespace cereal {

/*
 * Following https://uscilab.github.io/cereal/archive_specialization.html it is required, that for adding templated serialization
 * functions, at least one template parameter needs to have higher precedence than the standard ones from cereal, which mostly
 * requires specialization of at least one template parameter. Intervals only have one parameter, so we use a full specialization.
 */

template <class Archive>
void save( Archive& archive,
		   carl::Interval<double> const& intv ) {
	archive( intv.lower(), intv.lowerBoundType(), intv.upper(), intv.upperBoundType() );
}

template <class Archive>
void load( Archive& archive,
		   carl::Interval<double>& intv ) {
	double lb, ub;
	carl::BoundType lbt, ubt;
	archive( lb, lbt, ub, ubt );
	intv = carl::Interval<double>{ lb, lbt, ub, ubt };
}

template <class Archive>
void save( Archive& archive,
		   carl::Interval<mpq_class> const& intv ) {
	archive( intv.lower(), intv.lowerBoundType(), intv.upper(), intv.upperBoundType() );
}

template <class Archive>
void load( Archive& archive,
		   carl::Interval<mpq_class>& intv ) {
	mpq_class lb, ub;
	carl::BoundType lbt, ubt;
	archive( lb, lbt, ub, ubt );
	intv = carl::Interval<mpq_class>{ lb, lbt, ub, ubt };
}

}  // namespace cereal

#endif	// HYPRO_INTERVAL_SERIALIZATION_H
