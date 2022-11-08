/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/** \example example_HPolytope-transformation.cpp
 * 	This example shows how to transform (linear & affine) a H-polytope without using conversion to V-polytopes
 */

#include "representations/GeometricObjectBase.h"
#include "util/plotting/Plotter.h"

using Number = mpq_class;
using Matrix = hypro::matrix_t<Number>;
using Vector = hypro::vector_t<Number>;

int main() {
	using namespace hypro;
	auto& pool = VariablePool::getInstance();
	auto& plt = Plotter<Number>::getInstance();
	// we create the constraints and constants defining a 2D-unit box.
	auto HPolyConstraints = Matrix( 4, 2 );
	HPolyConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
	auto HPolyConstants = Vector( 4 );
	HPolyConstants << 1, 1, 1, 1;

	// plotting of the original set
	plt.setFilename( "hpoly" );
	plt.rSettings().overwriteFiles = true;
	plt.addObject( HPolytope<Number>{ HPolyConstraints, HPolyConstants }.vertices() );
	plt.plot2d( PLOTTYPE::png, true );

	// To avoid conversion, we use Fourier-Motzkin variable elimination such that we solve
	// exists Y. AY <= b && x = BY + c
	auto formula = FormulaT<Number>{ carl::FormulaType::AND, hypro::constraintsToFormulas( halfspacesToConstraints<Number>( HPolyConstraints, HPolyConstants ) ) };
	// create transformation x = 2x, y = 3y
	Matrix trafo = Matrix::Zero( 2, 4 );
	Vector translation = Vector::Zero( 2 );
	trafo( 0, 0 ) = 2;
	trafo( 1, 1 ) = 3;
	trafo.block( 0, 2, 2, 2 ) = -Matrix::Identity( 2, 2 );
	FormulasT<Number> single_translations;
	for ( Eigen::Index row = 0; row < trafo.rows(); ++row ) {
		single_translations.push_back( FormulaT<Number>{ rowToConstraint<Number>( Vector( trafo.row( row ) ), translation( row ), carl::Relation::EQ ) } );
	}
	FormulaT<Number> translation_formula{ carl::FormulaType::AND, single_translations };
	formula = FormulaT<Number>( carl::FormulaType::AND, formula, translation_formula );
	std::cout << "Formula describing the problem: " << formula << std::endl;

	FourierMotzkinQE<Number> qe_method{ formula, QEQuery{ { QuantifierType::EXISTS, { pool.carlVarByIndex( 0 ), pool.carlVarByIndex( 1 ) } } } };
	auto result = qe_method.eliminateQuantifiers();

	std::cout << "Resulting formula: " << result << std::endl;

	// substitute variables back
	result = result.substitute( pool.carlVarByIndex( 2 ), PolyT<Number>( pool.carlVarByIndex( 0 ) ) );
	result = result.substitute( pool.carlVarByIndex( 3 ), PolyT<Number>( pool.carlVarByIndex( 1 ) ) );

	auto transformedPolytope = HPolytope<Number>( computeHalfspaces<Number, Number>( result, 2 ) );

	plt.addObject( transformedPolytope.vertices() );
	plt.setFilename( "hpoly_transformed" );
	plt.plot2d( PLOTTYPE::png, true );

	return 0;
}
