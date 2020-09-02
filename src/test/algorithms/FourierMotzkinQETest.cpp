#include "../defines.h"
#include "gtest/gtest.h"
#include <algorithms/quantifierElimination/qe.h>

using namespace hypro;

using Pol = PolyT<mpq_class>;
using Constr = ConstraintT<mpq_class>;
using Form = FormulaT<mpq_class>;

TEST( FourierMotzkinEliminationTest, SingleVariable ) {
	carl::Variable x = carl::freshRealVariable( "x" );
	carl::Variable y = carl::freshRealVariable( "y" );
	carl::Variable z = carl::freshRealVariable( "z" );

	Constr c1 = Constr( Pol( x ) - Pol( y ) + Pol( z ), carl::Relation::GEQ );
	Constr c2 = Constr( Pol( x ) + Pol( y ) + Pol( -5 ), carl::Relation::LEQ );

	FormulasT<mpq_class> constraints;
	constraints.emplace_back( c1 );
	constraints.emplace_back( c2 );

	Form inFormula = Form( carl::FormulaType::AND, constraints );

	// std::cout << "Formula: " << inFormula << ", eliminate " << x << std::endl;

	QEQuery query;
	query.emplace_back( std::make_pair( QuantifierType::EXISTS, std::vector<carl::Variable>{ x } ) );

	auto newFormula = eliminateQuantifiers( inFormula, query );
}

TEST( FourierMotzkinEliminationTest, NoReminder ) {
	carl::Variable x = carl::freshRealVariable( "x" );
	carl::Variable y = carl::freshRealVariable( "y" );

	Constr c1 = Constr( Pol( x ) - Pol( y ), carl::Relation::GEQ );
	Constr c2 = Constr( Pol( x ) - Pol( y ) + Pol( -5 ), carl::Relation::LEQ );

	FormulasT<mpq_class> constraints;
	constraints.emplace_back( c1 );
	constraints.emplace_back( c2 );

	Form inFormula = Form( carl::FormulaType::AND, constraints );

	std::cout << "Formula: " << inFormula << ", eliminate " << x << std::endl;

	QEQuery query;
	query.emplace_back( std::make_pair( QuantifierType::EXISTS, std::vector<carl::Variable>{ x } ) );

	auto newFormula = eliminateQuantifiers( inFormula, query );

	std::cout << "New formula: " << newFormula << std::endl;

	EXPECT_EQ( Form( carl::FormulaType::TRUE ), newFormula );
}

TEST( FourierMotzkinEliminationTest, Reminder ) {
	carl::Variable x = carl::freshRealVariable( "x" );
	carl::Variable y = carl::freshRealVariable( "y" );
	carl::Variable z = carl::freshRealVariable( "z" );

	Constr c1 = Constr( Pol( x ) - Pol( y ), carl::Relation::GEQ );
	Constr c2 = Constr( Pol( x ) - Pol( y ) + Pol( -5 ), carl::Relation::LEQ );
	Constr c3 = Constr( Pol( y ) - Pol( z ), carl::Relation::LEQ );

	FormulasT<mpq_class> constraints;
	constraints.emplace_back( c1 );
	constraints.emplace_back( c2 );
	constraints.emplace_back( c3 );

	Form inFormula = Form( carl::FormulaType::AND, constraints );

	std::cout << "Formula: " << inFormula << ", eliminate " << x << std::endl;

	QEQuery query;
	query.emplace_back( std::make_pair( QuantifierType::EXISTS, std::vector<carl::Variable>{ x } ) );

	auto newFormula = eliminateQuantifiers( inFormula, query );

	std::cout << "New formula: " << newFormula << std::endl;

	EXPECT_EQ( Form( c3 ), newFormula );
}

TEST( FourierMotzkinEliminationTest, MultipleVariables ) {
	carl::Variable x = carl::freshRealVariable( "x" );
	carl::Variable y = carl::freshRealVariable( "y" );
	carl::Variable z = carl::freshRealVariable( "z" );

	Constr c1 = Constr( Pol( x ) - Pol( y ) + Pol( z ), carl::Relation::GEQ );
	Constr c2 = Constr( Pol( y ), carl::Relation::GEQ );
	Constr c3 = Constr( Pol( x ) + Pol( y ) + Pol( -5 ), carl::Relation::LEQ );

	FormulasT<mpq_class> constraints;
	constraints.emplace_back( c1 );
	constraints.emplace_back( c2 );
	constraints.emplace_back( c3 );

	Form inFormula = Form( carl::FormulaType::AND, constraints );

	std::cout << "Formula: " << inFormula << std::endl;

	QEQuery query;
	query.emplace_back( std::make_pair( QuantifierType::EXISTS, std::vector<carl::Variable>{ x, y } ) );

	auto newFormula = eliminateQuantifiers( inFormula, query );

	std::cout << "New formula: " << newFormula << std::endl;
}

TEST( FourierMotzkinEliminationTest, SingleVariableEquation ) {
	carl::Variable x = carl::freshRealVariable( "x" );
	carl::Variable y = carl::freshRealVariable( "y" );
	carl::Variable z = carl::freshRealVariable( "z" );

	Constr c1 = Constr( Pol( x ) + Pol( z ), carl::Relation::GEQ );
	Constr c2 = Constr( Pol( x ) - Pol( y ), carl::Relation::LEQ );
	Constr c3 = Constr( Pol( x ) + Pol( y ) + Pol( -5 ), carl::Relation::EQ );

	FormulasT<mpq_class> constraints;
	constraints.emplace_back( c1 );
	constraints.emplace_back( c2 );
	constraints.emplace_back( c3 );

	Form inFormula = Form( carl::FormulaType::AND, constraints );

	std::cout << "Formula: " << inFormula << std::endl;

	QEQuery query;
	query.emplace_back( std::make_pair( QuantifierType::EXISTS, std::vector<carl::Variable>{ x } ) );

	auto newFormula = eliminateQuantifiers( inFormula, query );

	std::cout << "New formula: " << newFormula << std::endl;

	EXPECT_EQ( Form( carl::FormulaType::AND,
					 FormulasT<mpq_class>{ Form( Constr( Pol( 5 ) - Pol( y ) + Pol( z ), carl::Relation::GEQ ) ),
										   Form( Constr( Pol( 5 ) - Pol( y ) * Pol( 2 ), carl::Relation::LEQ ) ) } ),
			   newFormula );
}

TEST( FourierMotzkinEliminationTest, SingleVariableEquationInconsistent ) {
	carl::Variable x = carl::freshRealVariable( "x" );
	carl::Variable y = carl::freshRealVariable( "y" );
	carl::Variable z = carl::freshRealVariable( "z" );

	Constr c1 = Constr( Pol( x ) + Pol( z ), carl::Relation::GEQ );
	Constr c2 = Constr( Pol( x ) - Pol( y ), carl::Relation::LEQ );
	Constr c3 = Constr( Pol( x ) + Pol( -5 ), carl::Relation::EQ );
	Constr c4 = Constr( Pol( x ) + Pol( -3 ), carl::Relation::EQ );

	FormulasT<mpq_class> constraints;
	constraints.emplace_back( c1 );
	constraints.emplace_back( c2 );
	constraints.emplace_back( c3 );
	constraints.emplace_back( c4 );

	Form inFormula = Form( carl::FormulaType::AND, constraints );

	std::cout << "Formula: " << inFormula << std::endl;

	QEQuery query;
	query.emplace_back( std::make_pair( QuantifierType::EXISTS, std::vector<carl::Variable>{ x } ) );

	auto newFormula = eliminateQuantifiers( inFormula, query );

	std::cout << "New formula: " << newFormula << std::endl;

	EXPECT_EQ( Form( carl::FormulaType::FALSE ), newFormula );
}

TEST( FourierMotzkinEliminationTest, SingleVariableEquationInconsistent2 ) {
	carl::Variable x = carl::freshRealVariable( "x" );
	carl::Variable y = carl::freshRealVariable( "y" );
	carl::Variable z = carl::freshRealVariable( "z" );

	Constr c1 = Constr( Pol( x ) + Pol( z ), carl::Relation::GEQ );
	Constr c2 = Constr( Pol( x ) - Pol( y ), carl::Relation::LEQ );
	Constr c3 = Constr( Pol( x ) + Pol( y ), carl::Relation::EQ );
	Constr c4 = Constr( Pol( x ) + Pol( z ), carl::Relation::EQ );

	FormulasT<mpq_class> constraints;
	constraints.emplace_back( c1 );
	constraints.emplace_back( c2 );
	constraints.emplace_back( c3 );
	constraints.emplace_back( c4 );

	Form inFormula = Form( carl::FormulaType::AND, constraints );

	// std::cout << "Formula: " << inFormula << std::endl;

	QEQuery query;
	query.emplace_back( std::make_pair( QuantifierType::EXISTS, std::vector<carl::Variable>{ x } ) );

	auto newFormula = eliminateQuantifiers( inFormula, query );

	// std::cout << "New formula: " << newFormula << std::endl;

	EXPECT_EQ( Form( carl::FormulaType::AND,
					 FormulasT<mpq_class>{ Form( Constr( Pol( y ) - Pol( z ), carl::Relation::LEQ ) ),
										   Form( Constr( -Pol( y ), carl::Relation::LEQ ) ),
										   Form( Constr( -Pol( z ) - Pol( y ), carl::Relation::LEQ ) ) } ),
			   newFormula );

	// same test with matrix-representation
	using Matrix = hypro::matrix_t<mpq_class>;
	using Vector = hypro::vector_t<mpq_class>;

	Matrix constraintMatrix = Matrix::Zero( 6, 3 );
	Vector constantsVector = Vector::Zero( 6 );

	constraintMatrix( 0, 0 ) = -1;
	constraintMatrix( 0, 2 ) = -1;

	constraintMatrix( 1, 0 ) = 1;
	constraintMatrix( 1, 1 ) = -1;

	constraintMatrix( 2, 0 ) = 1;
	constraintMatrix( 2, 1 ) = 1;

	constraintMatrix( 3, 0 ) = -1;
	constraintMatrix( 3, 1 ) = -1;

	constraintMatrix( 4, 0 ) = 1;
	constraintMatrix( 4, 2 ) = 1;

	constraintMatrix( 5, 0 ) = -1;
	constraintMatrix( 5, 2 ) = -1;

	auto [newConstraints, newConstants] = eliminateCol( constraintMatrix, constantsVector, 0 );

	Vector expectedConstraint1 = Vector( 3 );
	expectedConstraint1 << 0, -1, -1;
	EXPECT_TRUE( hasRow( newConstraints, expectedConstraint1 ) );

	Vector expectedConstraint2 = Vector( 3 );
	expectedConstraint2 << 0, 1, -1;
	EXPECT_TRUE( hasRow( newConstraints, expectedConstraint2 ) );

	Vector expectedConstraint3 = Vector( 3 );
	expectedConstraint3 << 0, -2, 0;
	EXPECT_TRUE( hasRow( newConstraints, expectedConstraint3 ) );

	Vector expectedConstraint4 = Vector( 3 );
	expectedConstraint4 << 0, -1, 1;
	EXPECT_TRUE( hasRow( newConstraints, expectedConstraint4 ) );
}

TEST( FourierMotzkinEliminationTest, MatrixVersionSimple ) {
	using Matrix = hypro::matrix_t<mpq_class>;
	using Vector = hypro::vector_t<mpq_class>;

	Matrix constraints = Matrix::Zero( 4, 2 );
	Vector constants = Vector::Zero( 4 );

	constraints( 0, 0 ) = 1;
	constraints( 1, 0 ) = -1;
	constraints( 2, 1 ) = 1;
	constraints( 3, 1 ) = -1;
	constants << 3, -2, 1, 1;

	Matrix expectedConstraints = Matrix( 2, 2 );
	expectedConstraints << 0, 1, 0, -1;

	Vector expectedConstants = Vector( 2 );
	expectedConstants << 1, -1;

	auto [newConstraints, newConstants] = eliminateCol( constraints, constants, 0 );
	EXPECT_EQ( Eigen::Index( 2 ), newConstraints.rows() );
	EXPECT_EQ( Eigen::Index( 2 ), newConstraints.cols() );
	EXPECT_EQ( Eigen::Index( 2 ), newConstants.rows() );
	EXPECT_EQ( expectedConstraints, newConstraints );
}