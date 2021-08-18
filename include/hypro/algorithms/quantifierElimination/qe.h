#pragma once

#include "../../carlTypes.h"
#include "FourierMotzkinQE.h"

namespace hypro {

template <typename Number>
FormulaT<Number> eliminateQuantifiers( const FormulaT<Number>& qfree, const QEQuery& quantifiers ) {
	FourierMotzkinQE<Number> elim( qfree, quantifiers );
	return elim.eliminateQuantifiers();
}

}  // namespace hypro