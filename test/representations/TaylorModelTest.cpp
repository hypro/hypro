/*
 * Test_TaylorModel.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: chen
 */

#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/representations/TaylorModel/continuous.h>
#include <hypro/util/VariablePool.h>

using namespace hypro;

template <typename Number>
class TaylorModelTest : public ::testing::Test {
  protected:
	virtual void SetUp() { vpool.clear(); }

	virtual void TearDown() {}

	hypro::VariablePool& vpool = hypro::VariablePool::getInstance();
};

TYPED_TEST( TaylorModelTest, Addition ) {
	carl::Variable x = this->vpool.newCarlVariable( "x" );
	carl::Variable y = this->vpool.newCarlVariable( "y" );
	carl::Variable z = this->vpool.newCarlVariable( "z" );
	carl::Variable x0 = this->vpool.newCarlVariable( "x0" );
	carl::Variable y0 = this->vpool.newCarlVariable( "y0" );

	TaylorModel<TypeParam> tmv_1_x( { Term<carl::Interval<TypeParam>>( 1 ) } );

	TaylorModel<TypeParam> tmv_1_y( { Term<carl::Interval<TypeParam>>( 2 ), (carl::Interval<TypeParam>)1 * x0 * x0 } );

	TaylorModel<TypeParam> tmv_1_z( { (carl::Interval<TypeParam>)1 * y0, (carl::Interval<TypeParam>)1 * x0 * y0 } );

	TaylorModelVec<TypeParam> tmv_1;
	tmv_1.assign( x, tmv_1_x );
	tmv_1.assign( y, tmv_1_y );
	tmv_1.assign( z, tmv_1_z );

	std::cout << tmv_1 << std::endl;

	TaylorModel<TypeParam> tmv_2_x( { Term<carl::Interval<TypeParam>>( 3 ) } );
	TaylorModel<TypeParam> tmv_2_y( { Term<carl::Interval<TypeParam>>( 5 ), (carl::Interval<TypeParam>)3 * x0 * x0 } );
	TaylorModel<TypeParam> tmv_2_z( { (carl::Interval<TypeParam>)1 * x0, (carl::Interval<TypeParam>)1 * x0 * y0 } );

	TaylorModelVec<TypeParam> tmv_2;
	tmv_2.assign( y, tmv_2_y );
	tmv_2.assign( z, tmv_2_z );
	tmv_2.assign( x, tmv_2_x );

	std::cout << '+' << std::endl;

	std::cout << tmv_2 << std::endl;

	tmv_1 += tmv_2;

	std::cout << '=' << std::endl;
	std::cout << tmv_1 << std::endl;
}

TYPED_TEST( TaylorModelTest, Subtraction ) {}

TYPED_TEST( TaylorModelTest, Multiplication ) {
	carl::Variable x = this->vpool.newCarlVariable( "x" );

	carl::Interval<TypeParam> remainder1( -0.1, 0.1 ), remainder2( -0.1, 0.1 );

	TaylorModel<TypeParam> tm1( { (carl::Interval<TypeParam>)-1 * x, (carl::Interval<TypeParam>)1 * x * x },
								remainder1 );
	TaylorModel<TypeParam> tm2( { Term<carl::Interval<TypeParam>>( 1 ), (carl::Interval<TypeParam>)2 * x,
								  (carl::Interval<TypeParam>)-1 * x * x },
								remainder2 );

	carl::Interval<TypeParam> range_of_x( 2, 4 );
	Domain<TypeParam> domain;
	domain.assign( x, range_of_x );

	TaylorModel<TypeParam> tmResult;
	tmResult = tm1.multiply( tm2, domain, 2 );

	std::cout << "We compute the product of the Taylor models" << std::endl;

	std::cout << tm1 << std::endl;
	std::cout << "and" << std::endl;
	std::cout << tm2 << std::endl;

	std::cout << "The result is" << std::endl;
	std::cout << tmResult << std::endl;

	carl::Variable y = this->vpool.newCarlVariable( "y" );

	TaylorModel<TypeParam> tm3( { Term<carl::Interval<TypeParam>>( 6 ), (carl::Interval<TypeParam>)5 * y,
								  (carl::Interval<TypeParam>)1 * y * y },
								remainder1 );
	TaylorModel<TypeParam> tm4( { Term<carl::Interval<TypeParam>>( -2 ), (carl::Interval<TypeParam>)-4 * y,
								  (carl::Interval<TypeParam>)-1 * y * y },
								remainder2 );

	carl::Interval<TypeParam> range_of_y( -1, 1 );
	domain.clear();
	domain.assign( y, range_of_y );

	tmResult = tm3.multiply( tm4, domain, 2 );

	std::cout << "We compute the product of the Taylor models" << std::endl;

	std::cout << tm3 << std::endl;
	std::cout << "and" << std::endl;
	std::cout << tm4 << std::endl;

	std::cout << "The result is" << std::endl;
	std::cout << tmResult << std::endl;
}

TYPED_TEST( TaylorModelTest, Polynomial_Substitution ) {
	carl::Variable x = this->vpool.newCarlVariable( "x" );
	carl::Variable y = this->vpool.newCarlVariable( "y" );

	MultivariatePolynomial<carl::Interval<double>> poly(
		  { Term<carl::Interval<double>>( carl::Interval<double>( 1 ) ), carl::Interval<double>( -2 ) * x * x } );

	std::cout << "We substitute x for y in the following polynomial:" << std::endl;

	std::cout << poly << std::endl;

	MultivariatePolynomial<carl::Interval<double>> poly_y_to_x( { (carl::Interval<double>)1 * x } );
	MultivariatePolynomial<carl::Interval<double>> poly_x_to_y( { (carl::Interval<double>)1 * y } );
	std::map<carl::Variable, MultivariatePolynomial<carl::Interval<double>>> substitution;
	std::pair<const carl::Variable, MultivariatePolynomial<carl::Interval<double>>> y_to_x( y, poly_y_to_x );
	std::pair<const carl::Variable, MultivariatePolynomial<carl::Interval<double>>> x_to_y( x, poly_x_to_y );

	substitution.insert( x_to_y );
	substitution.insert( y_to_x );

	MultivariatePolynomial<carl::Interval<double>> result;
	result = poly.substitute( substitution );

	std::cout << "The result is" << std::endl;

	std::cout << result << std::endl;
}

TYPED_TEST( TaylorModelTest, Substitution ) {
	carl::Variable x = this->vpool.newCarlVariable( "x" );
	carl::Variable x0 = this->vpool.newCarlVariable( "x0" );
	carl::Variable t = this->vpool.newCarlVariable( "t" );

	carl::Interval<double> remainder1( -0.1, 0.1 ), remainder2( -0.5, 0.5 ), T( 0.2, 0.2 ), remainder_zero( 0 );

	TaylorModel<double> tm1( { Term<carl::Interval<double>>( 1 ), (carl::Interval<double>)2 * x * t * t,
							   (carl::Interval<double>)-0.2 * x * x * t },
							 remainder1 );

	TaylorModel<double> tm2( { Term<carl::Interval<double>>( 0.1 ), carl::Interval<double>( -1 ) * x0 * x0 },
							 remainder2 );
	TaylorModel<double> tmT( T );

	std::cout << "We substitute" << std::endl;

	std::cout << tm2 << std::endl;

	std::cout << "for the variable x in" << std::endl;

	std::cout << tm1 << std::endl;

	std::cout << "and substitute 0.5 for t." << std::endl;

	std::cout << "The ranges of the variables are" << std::endl;

	carl::Interval<double> range_of_x0( -1, 1 ), range_of_t( 0.2, 0.2 );
	Domain<double> domain;
	domain.assign( x0, range_of_x0 );
	domain.assign( t, range_of_t );

	std::cout << domain << std::endl;

	std::map<carl::Variable, TaylorModel<double>> substitution;
	std::pair<const carl::Variable, TaylorModel<double>> x_to_tm2( x, tm2 );
	std::pair<const carl::Variable, TaylorModel<double>> t_to_tmT( t, tmT );

	substitution.insert( x_to_tm2 );
	substitution.insert( t_to_tmT );

	TaylorModel<double> result;
	result = tm1.substitute( substitution, domain, 2 );

	std::cout << "The result is" << std::endl;

	std::cout << result << std::endl;
}

TYPED_TEST( TaylorModelTest, Integration ) {
	carl::Variable x = this->vpool.newCarlVariable( "x" );
	carl::Variable y = this->vpool.newCarlVariable( "y" );

	carl::Interval<double> remainder( 1, 2 );
	TaylorModel<double> tm(
		  { Term<carl::Interval<double>>( x ), (carl::Interval<double>)-2 * x * y, Term<carl::Interval<double>>( 5 ) },
		  remainder );

	std::cout << "Before integration on y in [2,3]:" << std::endl;
	std::cout << tm << std::endl;

	carl::Interval<double> range_of_y( 2, 3 );
	tm.integration_assign( y, range_of_y );

	std::cout << "After integration on y in [2,3]:" << std::endl;
	std::cout << tm << std::endl;
}

TYPED_TEST( TaylorModelTest, ODE ) {
	carl::Variable x = this->vpool.newCarlVariable( "x" );
	carl::Variable y = this->vpool.newCarlVariable( "y" );

	MultivariatePolynomial<carl::Interval<double>> deriv_x(
		  { (Term<carl::Interval<double>>)( 1 ), (carl::Interval<double>)1 * y } );
	MultivariatePolynomial<carl::Interval<double>> deriv_y( { (carl::Interval<double>)-1 * x * x } );

	PolynomialODE<double> ode;
	ode.assign( y, deriv_y );
	ode.assign( x, deriv_x );

	std::cout << ode;
}

TYPED_TEST( TaylorModelTest, Lie_Derivation ) {
	carl::Variable x = this->vpool.newCarlVariable( "x" );
	carl::Variable y = this->vpool.newCarlVariable( "y" );

	MultivariatePolynomial<carl::Interval<double>> deriv_x(
		  { (Term<carl::Interval<double>>)( 1 ), (carl::Interval<double>)1 * y } );
	MultivariatePolynomial<carl::Interval<double>> deriv_y( { (carl::Interval<double>)-1 * x * x } );

	PolynomialODE<double> ode;
	ode.assign( x, deriv_x );
	ode.assign( y, deriv_y );

	carl::Interval<double> intZero( 0 );
	TaylorModel<double> tm_x( { Term<carl::Interval<double>>( x ) }, intZero );
	TaylorModel<double> tm_y( { Term<carl::Interval<double>>( y ) }, intZero );

	std::vector<TaylorModel<double>> tm_v;
	tm_v.push_back( tm_x );
	tm_v.push_back( tm_y );

	std::cout << "1st order Lie derivative:" << std::endl;

	tm_v[0].LieDerivative_assign( ode );
	std::cout << tm_v[0] << std::endl;

	tm_v[1].LieDerivative_assign( ode );
	std::cout << tm_v[1] << std::endl;

	std::cout << std::endl << "2nd order Lie derivative:" << std::endl;

	tm_v[0].LieDerivative_assign( ode );
	std::cout << tm_v[0] << std::endl;

	tm_v[1].LieDerivative_assign( ode );
	std::cout << tm_v[1] << std::endl;

	std::cout << std::endl << "3rd order Lie derivative:" << std::endl;

	tm_v[0].LieDerivative_assign( ode );
	std::cout << tm_v[0] << std::endl;

	tm_v[1].LieDerivative_assign( ode );
	std::cout << tm_v[1] << std::endl;

	std::cout << std::endl << "4th order Lie derivative:" << std::endl;

	tm_v[0].LieDerivative_assign( ode );
	std::cout << tm_v[0] << std::endl;

	tm_v[1].LieDerivative_assign( ode );
	std::cout << tm_v[1] << std::endl;
}

TYPED_TEST( TaylorModelTest, normalize ) {
	carl::Variable x = this->vpool.newCarlVariable( "x" );

	TaylorModel<double> tm(
		  { (Term<carl::Interval<double>>)( 1 ), (carl::Interval<double>)2 * x, (carl::Interval<double>)-1 * x * x } );

	carl::Interval<double> range_of_x( 2, 4 );
	Domain<double> domain;
	domain.assign( x, range_of_x );

	std::cout << "Before normalization:" << std::endl;
	std::cout << tm << std::endl;
	std::cout << domain << std::endl;

	tm.normalize( domain );

	std::cout << "After normalization" << std::endl;
	std::cout << tm << std::endl;
}

TYPED_TEST( TaylorModelTest, Picard_Operation ) {
	carl::Variable x = this->vpool.newCarlVariable( "x" );
	carl::Variable y = this->vpool.newCarlVariable( "y" );
	carl::Variable x0 = this->vpool.newCarlVariable( "x0" );
	carl::Variable y0 = this->vpool.newCarlVariable( "y0" );
	carl::Variable t = this->vpool.newCarlVariable( "t" );

	MultivariatePolynomial<carl::Interval<double>> deriv_x(
		  { (Term<carl::Interval<double>>)( 1 ), (carl::Interval<double>)1 * y } );
	MultivariatePolynomial<carl::Interval<double>> deriv_y( { (carl::Interval<double>)-1 * x * x } );

	PolynomialODE<double> ode;
	ode.assign( x, deriv_x );
	ode.assign( y, deriv_y );

	std::cout << "The polynomial ODE is" << std::endl;

	std::cout << ode << std::endl;

	std::cout << "We compute the Picard operation on the Taylor model" << std::endl;

	carl::Interval<double> remainder_x( -0.1, 0.1 ), remainder_y( -0.1, 0.1 );
	TaylorModel<double> tm_x(
		  { (carl::Interval<double>)1 * x0, (carl::Interval<double>)1 * t, (carl::Interval<double>)1 * y0 * t },
		  remainder_x );
	TaylorModel<double> tm_y(
		  { (carl::Interval<double>)1 * y0, (carl::Interval<double>)-1 * x0 * x0 * t,
			(carl::Interval<double>)-1 * x0 * t * t, (carl::Interval<double>)-0.33333333 * t * t * t },
		  remainder_y );

	TaylorModelVec<double> tmv;
	tmv.assign( x, tm_x );
	tmv.assign( y, tm_y );

	std::cout << tmv << std::endl;

	std::cout << "wherein" << std::endl;

	carl::Interval<double> range_of_x0( -1, 1 ), range_of_y0( -0.5, 0.5 );
	carl::Interval<double> range_of_t( 0.0, 0.02 );
	Domain<double> domain;
	domain.assign( x0, range_of_x0 );
	domain.assign( y0, range_of_y0 );
	domain.assign( t, range_of_t );

	std::cout << domain << std::endl;

	std::cout << "Result:" << std::endl;

	TaylorModel<double> tm0_x( { (carl::Interval<double>)1 * x0 } );
	TaylorModel<double> tm0_y( { (carl::Interval<double>)1 * y0 } );
	TaylorModelVec<double> tmv0;

	tmv0.assign( x, tm0_x );
	tmv0.assign( y, tm0_y );

	TaylorModelVec<double> tmvResult;
	tmvResult = tmv.Picard( tmv0, ode, domain, t, range_of_t, 3 );

	std::cout << tmvResult << std::endl;
}

/*
TYPED_TEST(TaylorModelTest, Brusselator)
{
	carl::Variable x = this->vpool.newCarlVariable("x");
	carl::Variable y = this->vpool.newCarlVariable("y");
	carl::Variable x0 = this->vpool.newCarlVariable("x0");
	carl::Variable y0 = this->vpool.newCarlVariable("y0");
	carl::Variable t = this->vpool.newCarlVariable("t");

	MultivariatePolynomial<carl::Interval<FLOAT_T<mpfr_t> >> deriv_x({(Term<carl::Interval<FLOAT_T<mpfr_t>
>>)(carl::Interval<FLOAT_T<mpfr_t> >(1)), (carl::Interval<FLOAT_T<mpfr_t>>)1*x*x*y,
(carl::Interval<FLOAT_T<mpfr_t>>)-2.5*x}); MultivariatePolynomial<carl::Interval<FLOAT_T<mpfr_t>>>
deriv_y({(carl::Interval<FLOAT_T<mpfr_t>>)1.5*x, (carl::Interval<FLOAT_T<mpfr_t>>)-1*x*x*y});

	PolynomialODE<FLOAT_T<mpfr_t>> ode;
	ode.assign(x, deriv_x);
	ode.assign(y, deriv_y);

	// define the initial set which is a flowpipe
	carl::Interval<FLOAT_T<mpfr_t>> range_of_x0(-1,1), range_of_y0(-1,1);
	carl::Interval<FLOAT_T<mpfr_t>> range_of_t(0.0,0.02);
	Domain<FLOAT_T<mpfr_t>> domain;
	domain.assign(x0, range_of_x0);
	domain.assign(y0, range_of_y0);
	domain.assign(t, range_of_t);

	TaylorModel<FLOAT_T<mpfr_t>> X0_x({(Term<carl::Interval<FLOAT_T<mpfr_t>>>)(carl::Interval<FLOAT_T<mpfr_t> >(0.9)),
(carl::Interval<FLOAT_T<mpfr_t>>)0.01*x0}); TaylorModel<FLOAT_T<mpfr_t>>
X0_y({(Term<carl::Interval<FLOAT_T<mpfr_t>>>)(carl::Interval<FLOAT_T<mpfr_t> >(0.1)),
(carl::Interval<FLOAT_T<mpfr_t>>)0.01*y0});

//	TaylorModel<double> X0_x({(Term<carl::Interval<double>>)(0.9)});
//	TaylorModel<double> X0_y({(Term<carl::Interval<double>>)(0.1)});

	TaylorModelVec<FLOAT_T<mpfr_t>> tmvInitial;
	tmvInitial.assign(x, X0_x);
	tmvInitial.assign(y, X0_y);

	Flowpipe<FLOAT_T<mpfr_t>> initialSet(tmvInitial, domain);

	ContinuousSystem<FLOAT_T<mpfr_t>> system(ode, initialSet);

//	system.output(std::cout, 6);

	std::list<Flowpipe<FLOAT_T<mpfr_t>> > result;

	Range<FLOAT_T<mpfr_t>> estimation;
	carl::Interval<FLOAT_T<mpfr_t>> intEst(-1e-1,1e-1);
	estimation.assign(x, intEst);
	estimation.assign(y, intEst);

	system.reach_picard(result, t, 6.2, 0.02, 6, estimation);

	std::ofstream os;
	os.open("Brusselator.plt");

	output_2D_interval_gnuplot(result, os, std::string("Brusselator"), x, y);

	os.close();
}

TYPED_TEST(TaylorModelTest, VanDerPol)
{
	carl::Variable x = this->vpool.newCarlVariable("x");
	carl::Variable y = this->vpool.newCarlVariable("y");
	carl::Variable x0 = this->vpool.newCarlVariable("x0");
	carl::Variable y0 = this->vpool.newCarlVariable("y0");
	carl::Variable t = this->vpool.newCarlVariable("t");

	MultivariatePolynomial<carl::Interval<double>> deriv_x({(carl::Interval<double>)1*y});
	MultivariatePolynomial<carl::Interval<double>> deriv_y({(carl::Interval<double>)1*y, (carl::Interval<double>)-1*x,
(carl::Interval<double>)-1*x*x*y});

	PolynomialODE<double> ode;
	ode.assign(x, deriv_x);
	ode.assign(y, deriv_y);

	// define the initial set which is a flowpipe
	carl::Interval<double> range_of_x0(-1,1), range_of_y0(-1,1);
	carl::Interval<double> range_of_t(0.0,0.02);
	Domain<double> domain;
	domain.assign(x0, range_of_x0);
	domain.assign(y0, range_of_y0);
	domain.assign(t, range_of_t);

	TaylorModel<double> X0_x({(Term<carl::Interval<double>>)(1.4), (carl::Interval<double>)0.15*x0});
	TaylorModel<double> X0_y({(Term<carl::Interval<double>>)(2.3), (carl::Interval<double>)0.05*y0});

	TaylorModelVec<double> tmvInitial;
	tmvInitial.assign(x, X0_x);
	tmvInitial.assign(y, X0_y);

	Flowpipe<double> initialSet(tmvInitial, domain);

	ContinuousSystem<double> system(ode, initialSet);

//	system.output(std::cout, 6);

	std::list<Flowpipe<double> > result;

	Range<double> estimation;
	carl::Interval<double> intEst(-1e-2,1e-2);
	estimation.assign(x, intEst);
	estimation.assign(y, intEst);

	system.reach_picard(result, t, 7, 0.02, 6, estimation);

	std::ofstream os;
	os.open("VanDerPol.plt");

	output_2D_interval_gnuplot(result, os, std::string("VanDerPol"), x, y);

	os.close();
}

TYPED_TEST(TaylorModelTest, Roessler)
{
	carl::Variable x = this->vpool.newCarlVariable("x");
	carl::Variable y = this->vpool.newCarlVariable("y");
	carl::Variable z = this->vpool.newCarlVariable("z");
	carl::Variable x0 = this->vpool.newCarlVariable("x0");
	carl::Variable y0 = this->vpool.newCarlVariable("y0");
	carl::Variable z0 = this->vpool.newCarlVariable("z0");
	carl::Variable t = this->vpool.newCarlVariable("t");

	MultivariatePolynomial<carl::Interval<double>> deriv_x({(carl::Interval<double>)-1*y,
(carl::Interval<double>)-1*z}); MultivariatePolynomial<carl::Interval<double>> deriv_y({(carl::Interval<double>)0.2*y,
(carl::Interval<double>)1*x}); MultivariatePolynomial<carl::Interval<double>>
deriv_z({(Term<carl::Interval<double>>)(0.2), (carl::Interval<double>)-5.7*z, (carl::Interval<double>)1*x*z});

	PolynomialODE<double> ode;
	ode.assign(x, deriv_x);
	ode.assign(y, deriv_y);
	ode.assign(z, deriv_z);

	// define the initial set which is a flowpipe
	carl::Interval<double> range_of_x0(-1,1), range_of_y0(-1,1), range_of_z0(-1,1);
	carl::Interval<double> range_of_t(0.0,0.02);
	Domain<double> domain;
	domain.assign(x0, range_of_x0);
	domain.assign(y0, range_of_y0);
	domain.assign(z0, range_of_z0);
	domain.assign(t, range_of_t);

	TaylorModel<double> X0_x({(carl::Interval<double>)0.1*x0});
	TaylorModel<double> X0_y({(Term<carl::Interval<double>>)(-8.4), (carl::Interval<double>)0.1*y0});
	TaylorModel<double> X0_z({(carl::Interval<double>)0.1*z0});

	TaylorModelVec<double> tmvInitial;
	tmvInitial.assign(x, X0_x);
	tmvInitial.assign(y, X0_y);
	tmvInitial.assign(z, X0_z);

	Flowpipe<double> initialSet(tmvInitial, domain);

	ContinuousSystem<double> system(ode, initialSet);

//	system.output(std::cout, 6);

	std::list<Flowpipe<double> > result;

	Range<double> estimation;
	carl::Interval<double> intEst(-1e-2,1e-2);
	estimation.assign(x, intEst);
	estimation.assign(y, intEst);
	estimation.assign(z, intEst);

	system.reach_picard(result, t, 6, 0.02, 7, estimation);

	std::ofstream os;
	os.open("Roessler.plt");

	output_2D_interval_gnuplot(result, os, std::string("Roessler"), y, z);

	os.close();
}*/
