
#include "util.h"

namespace hypro {
namespace polytope {

	/*
	template<>
	Parma_Polyhedra_Library::Constraint createConstraint(const vector_t<mpq_class>& constraint, mpq_class constantPart) {
		std::cout << "MPQ_Version." << std::endl;
		Parma_Polyhedra_Library::Linear_Expression polynom;
		polynom.set_space_dimension( constraint.rows() );
		for ( unsigned d = 0; d < constraint.rows(); ++d ) {
			polynom.set_coefficient( hypro::VariablePool::getInstance().pplVarByIndex( d ), carl::getNum(constraint(d)) * carl::getDenom(constraint(d)) * fReach_DENOMINATOR );
		}
		polynom.set_inhomogeneous_term( -carl::getNum(constantPart) * carl::getDenom(constantPart) * fReach_DENOMINATOR );
		Parma_Polyhedra_Library::Constraint res;
		res = polynom <= 0;
		return res;
	}
	*/

} // namespace polytope
} // namespace hypro
