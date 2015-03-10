/*
 * Test_TaylorModel.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: chen
 */

#include "../../lib/representations/TaylorModel/continuous.h"

using namespace hypro;

void TEST_Addition()
{
	VariablePool & vpool = VariablePool::getInstance();
	Variable x = vpool.getFreshVariable("x");
	Variable y = vpool.getFreshVariable("y");
	Variable z = vpool.getFreshVariable("z");
	Variable x0 = vpool.getFreshVariable("x0");
	Variable y0 = vpool.getFreshVariable("y0");

	TaylorModel<double> tmv_1_x({Term<Interval<double>>(1)});
	TaylorModel<double> tmv_1_y({Term<Interval<double>>(2), (Interval<double>)1*x0*x0});
	TaylorModel<double> tmv_1_z({(Interval<double>)1*y0, (Interval<double>)1*x0*y0});

	TaylorModelVec<double> tmv_1;
	tmv_1.assign(x, tmv_1_x);
	tmv_1.assign(y, tmv_1_y);
	tmv_1.assign(z, tmv_1_z);

	std::cout << tmv_1 << std::endl;

	TaylorModel<double> tmv_2_x({Term<Interval<double>>(3)});
	TaylorModel<double> tmv_2_y({Term<Interval<double>>(5), (Interval<double>)3*x0*x0});
	TaylorModel<double> tmv_2_z({(Interval<double>)1*x0, (Interval<double>)1*x0*y0});

	TaylorModelVec<double> tmv_2;
	tmv_2.assign(y, tmv_2_y);
	tmv_2.assign(z, tmv_2_z);
	tmv_2.assign(x, tmv_2_x);

	std::cout << '+' << std::endl;

	std::cout << tmv_2 << std::endl;

	tmv_1 += tmv_2;

	std::cout << '=' << std::endl;
	std::cout << tmv_1 << std::endl;
}

void TEST_Subtraction()
{

}

void TEST_Multiplication()
{
	VariablePool & vpool = VariablePool::getInstance();
	Variable x = vpool.getFreshVariable("x");

	Interval<double> remainder1(-0.1,0.1), remainder2(-0.1,0.1);

	TaylorModel<double> tm1({(Interval<double>)-1*x, (Interval<double>)1*x*x}, remainder1);
	TaylorModel<double> tm2({Term<Interval<double>>(1), (Interval<double>)2*x, (Interval<double>)-1*x*x}, remainder2);

	Interval<double> range_of_x(2,4);
	Domain<double> domain;
	domain.assign(x, range_of_x);

	TaylorModel<double> tmResult;
	tmResult = tm1.multiply(tm2, domain, 2);

	std::cout << "We compute the product of the Taylor models" << std::endl;

	std::cout << tm1 << std::endl;
	std::cout << "and" << std::endl;
	std::cout << tm2 << std::endl;

	std::cout << "The result is" << std::endl;
	std::cout << tmResult << std::endl;





	Variable y = vpool.getFreshVariable("y");

	TaylorModel<double> tm3({Term<Interval<double>>(6), (Interval<double>)5*y, (Interval<double>)1*y*y}, remainder1);
	TaylorModel<double> tm4({Term<Interval<double>>(-2), (Interval<double>)-4*y, (Interval<double>)-1*y*y}, remainder2);

	Interval<double> range_of_y(-1,1);
	domain.clear();
	domain.assign(y, range_of_y);

	tmResult = tm3.multiply(tm4, domain, 2);

	std::cout << "We compute the product of the Taylor models" << std::endl;

	std::cout << tm3 << std::endl;
	std::cout << "and" << std::endl;
	std::cout << tm4 << std::endl;

	std::cout << "The result is" << std::endl;
	std::cout << tmResult << std::endl;
}

void TEST_Polynomial_Substitution()
{
	VariablePool & vpool = VariablePool::getInstance();
	Variable x = vpool.getFreshVariable("x");
	Variable y = vpool.getFreshVariable("y");

	MultivariatePolynomial<Interval<double>> poly({Term<Interval<double>>(Interval<double>(1)), Interval<double>(-2)*x*x });

	std::cout << "We substitute x for y in the following polynomial:" << std::endl;

	std::cout << poly << std::endl;

	MultivariatePolynomial<Interval<double>> poly_y_to_x({(Interval<double>)1*x});
	MultivariatePolynomial<Interval<double>> poly_x_to_y({(Interval<double>)1*y});
	std::map<Variable, MultivariatePolynomial<Interval<double>>> substitution;
	std::pair<const Variable, MultivariatePolynomial<Interval<double>>> y_to_x(y, poly_y_to_x);
	std::pair<const Variable, MultivariatePolynomial<Interval<double>>> x_to_y(x, poly_x_to_y);

	substitution.insert(x_to_y);
	substitution.insert(y_to_x);

	MultivariatePolynomial<Interval<double>> result;
	result = poly.substitute(substitution);

	std::cout << "The result is" << std::endl;

	std::cout << result << std::endl;
}

void TEST_Substitution()
{
    VariablePool & vpool = VariablePool::getInstance();
    Variable x = vpool.getFreshVariable("x");
	Variable x0 = vpool.getFreshVariable("x0");
	Variable t = vpool.getFreshVariable("t");

	Interval<double> remainder1(-0.1,0.1), remainder2(-0.5,0.5), T(0.2,0.2), remainder_zero(0);

	TaylorModel<double> tm1({Term<Interval<double>>(1), (Interval<double>)2*x*t*t, (Interval<double>)-0.2*x*x*t}, remainder1);

	TaylorModel<double> tm2({Term<Interval<double>>(0.1), Interval<double>(-1)*x0*x0}, remainder2);
	TaylorModel<double> tmT(T);

	std::cout << "We substitute" << std::endl;

	std::cout << tm2 << std::endl;

	std::cout << "for the variable x in" << std::endl;

	std::cout << tm1 << std::endl;

	std::cout << "and substitute 0.5 for t." << std::endl;

	std::cout << "The ranges of the variables are" << std::endl;

	Interval<double> range_of_x0(-1,1), range_of_t(0.2,0.2);
	Domain<double> domain;
	domain.assign(x0, range_of_x0);
	domain.assign(t, range_of_t);

	std::cout << domain << std::endl;

	std::map<Variable, TaylorModel<double>> substitution;
	std::pair<const Variable, TaylorModel<double>> x_to_tm2(x, tm2);
	std::pair<const Variable, TaylorModel<double>> t_to_tmT(t, tmT);

	substitution.insert(x_to_tm2);
	substitution.insert(t_to_tmT);

	TaylorModel<double> result;
	result = tm1.substitute(substitution, domain, 2);

	std::cout << "The result is" << std::endl;

	std::cout << result << std::endl;
}

void TEST_Integration()
{
    VariablePool & vpool = VariablePool::getInstance();
    Variable x = vpool.getFreshVariable("x");
	Variable y = vpool.getFreshVariable("y");

	Interval<double> remainder(1,2);
	TaylorModel<double> tm({Term<Interval<double>>(x), (Interval<double>)-2*x*y, Term<Interval<double>>(5)}, remainder);

	std::cout << "Before integration on y in [2,3]:" << std::endl;
	std::cout << tm << std::endl;

	Interval<double> range_of_y(2,3);
	tm.integration_assign(y, range_of_y);

	std::cout << "After integration on y in [2,3]:" << std::endl;
	std::cout << tm << std::endl;
}

void TEST_ODE()
{
    VariablePool & vpool = VariablePool::getInstance();
    Variable x = vpool.getFreshVariable("x");
	Variable y = vpool.getFreshVariable("y");

	MultivariatePolynomial<Interval<double>> deriv_x({(Term<Interval<double>>)(1), (Interval<double>)1*y});
	MultivariatePolynomial<Interval<double>> deriv_y({(Interval<double>)-1*x*x});

	PolynomialODE<double> ode;
	ode.assign(y, deriv_y);
	ode.assign(x, deriv_x);

	std::cout << ode;
}

void TEST_Lie_Derivation()
{
    VariablePool & vpool = VariablePool::getInstance();
    Variable x = vpool.getFreshVariable("x");
	Variable y = vpool.getFreshVariable("y");

	MultivariatePolynomial<Interval<double>> deriv_x({(Term<Interval<double>>)(1), (Interval<double>)1*y});
	MultivariatePolynomial<Interval<double>> deriv_y({(Interval<double>)-1*x*x});

	PolynomialODE<double> ode;
	ode.assign(x, deriv_x);
	ode.assign(y, deriv_y);

	Interval<double> intZero(0);
	TaylorModel<double> tm_x({Term<Interval<double>>(x)}, intZero);
	TaylorModel<double> tm_y({Term<Interval<double>>(y)}, intZero);

	std::vector<TaylorModel<double> > tm_v;
	tm_v.push_back(tm_x);
	tm_v.push_back(tm_y);

	std::cout << "1st order Lie derivative:" << std::endl;

	tm_v[0].LieDerivative_assign(ode);
	std::cout << tm_v[0] << std::endl;

	tm_v[1].LieDerivative_assign(ode);
	std::cout << tm_v[1] << std::endl;

	std::cout << std::endl << "2nd order Lie derivative:" << std::endl;

	tm_v[0].LieDerivative_assign(ode);
	std::cout << tm_v[0] << std::endl;

	tm_v[1].LieDerivative_assign(ode);
	std::cout << tm_v[1] << std::endl;

	std::cout << std::endl << "3rd order Lie derivative:" << std::endl;

	tm_v[0].LieDerivative_assign(ode);
	std::cout << tm_v[0] << std::endl;

	tm_v[1].LieDerivative_assign(ode);
	std::cout << tm_v[1] << std::endl;

	std::cout << std::endl << "4th order Lie derivative:" << std::endl;

	tm_v[0].LieDerivative_assign(ode);
	std::cout << tm_v[0] << std::endl;

	tm_v[1].LieDerivative_assign(ode);
	std::cout << tm_v[1] << std::endl;
}

void TEST_normalize()
{
	VariablePool & vpool = VariablePool::getInstance();
	Variable x = vpool.getFreshVariable("x");

	TaylorModel<double> tm({(Term<Interval<double>>)(1), (Interval<double>)2*x, (Interval<double>)-1*x*x});

	Interval<double> range_of_x(2,4);
	Domain<double> domain;
	domain.assign(x, range_of_x);

	std::cout << "Before normalization:" << std::endl;
	std::cout << tm << std::endl;
	std::cout << domain << std::endl;

	tm.normalize(domain);

	std::cout << "After normalization" << std::endl;
	std::cout << tm << std::endl;
}

void TEST_Picard_Operation()
{
    VariablePool & vpool = VariablePool::getInstance();

    Variable x = vpool.getFreshVariable("x");
	Variable y = vpool.getFreshVariable("y");
    Variable x0 = vpool.getFreshVariable("x0");
	Variable y0 = vpool.getFreshVariable("y0");
	Variable t = vpool.getFreshVariable("t");

	MultivariatePolynomial<Interval<double>> deriv_x({(Term<Interval<double>>)(1), (Interval<double>)1*y});
	MultivariatePolynomial<Interval<double>> deriv_y({(Interval<double>)-1*x*x});

	PolynomialODE<double> ode;
	ode.assign(x, deriv_x);
	ode.assign(y, deriv_y);

	std::cout << "The polynomial ODE is" << std::endl;

	std::cout << ode << std::endl;

	std::cout << "We compute the Picard operation on the Taylor model" << std::endl;

	Interval<double> remainder_x(-0.1,0.1), remainder_y(-0.1,0.1);
	TaylorModel<double> tm_x({(Interval<double>)1*x0, (Interval<double>)1*t, (Interval<double>)1*y0*t}, remainder_x);
	TaylorModel<double> tm_y({(Interval<double>)1*y0, (Interval<double>)-1*x0*x0*t, (Interval<double>)-1*x0*t*t, (Interval<double>)-0.33333333*t*t*t}, remainder_y);

	TaylorModelVec<double> tmv;
	tmv.assign(x, tm_x);
	tmv.assign(y, tm_y);

	std::cout << tmv << std::endl;

	std::cout << "wherein" << std::endl;

	Interval<double> range_of_x0(-1,1), range_of_y0(-0.5,0.5);
	Interval<double> range_of_t(0.0,0.02);
	Domain<double> domain;
	domain.assign(x0, range_of_x0);
	domain.assign(y0, range_of_y0);
	domain.assign(t, range_of_t);

	std::cout << domain << std::endl;

	std::cout << "Result:" << std::endl;

	TaylorModel<double> tm0_x({(Interval<double>)1*x0});
	TaylorModel<double> tm0_y({(Interval<double>)1*y0});
	TaylorModelVec<double> tmv0;

	tmv0.assign(x, tm0_x);
	tmv0.assign(y, tm0_y);

	TaylorModelVec<double> tmvResult;
	tmvResult = tmv.Picard(tmv0, ode, domain, t, range_of_t, 3);

	std::cout << tmvResult << std::endl;
}

void TEST_Brusselator()
{
    VariablePool & vpool = VariablePool::getInstance();

    Variable x = vpool.getFreshVariable("x");
	Variable y = vpool.getFreshVariable("y");
    Variable x0 = vpool.getFreshVariable("x0");
	Variable y0 = vpool.getFreshVariable("y0");
	Variable t = vpool.getFreshVariable("t");

	MultivariatePolynomial<Interval<FLOAT_T<mpfr_t> >> deriv_x({(Term<Interval<FLOAT_T<mpfr_t> >>)(Interval<FLOAT_T<mpfr_t> >(1)), (Interval<FLOAT_T<mpfr_t>>)1*x*x*y, (Interval<FLOAT_T<mpfr_t>>)-2.5*x});
	MultivariatePolynomial<Interval<FLOAT_T<mpfr_t>>> deriv_y({(Interval<FLOAT_T<mpfr_t>>)1.5*x, (Interval<FLOAT_T<mpfr_t>>)-1*x*x*y});

	PolynomialODE<FLOAT_T<mpfr_t>> ode;
	ode.assign(x, deriv_x);
	ode.assign(y, deriv_y);

	// define the initial set which is a flowpipe
	Interval<FLOAT_T<mpfr_t>> range_of_x0(-1,1), range_of_y0(-1,1);
	Interval<FLOAT_T<mpfr_t>> range_of_t(0.0,0.02);
	Domain<FLOAT_T<mpfr_t>> domain;
	domain.assign(x0, range_of_x0);
	domain.assign(y0, range_of_y0);
	domain.assign(t, range_of_t);

	TaylorModel<FLOAT_T<mpfr_t>> X0_x({(Term<Interval<FLOAT_T<mpfr_t>>>)(Interval<FLOAT_T<mpfr_t> >(0.9)), (Interval<FLOAT_T<mpfr_t>>)0.01*x0});
	TaylorModel<FLOAT_T<mpfr_t>> X0_y({(Term<Interval<FLOAT_T<mpfr_t>>>)(Interval<FLOAT_T<mpfr_t> >(0.1)), (Interval<FLOAT_T<mpfr_t>>)0.01*y0});

//	TaylorModel<double> X0_x({(Term<Interval<double>>)(0.9)});
//	TaylorModel<double> X0_y({(Term<Interval<double>>)(0.1)});

	TaylorModelVec<FLOAT_T<mpfr_t>> tmvInitial;
	tmvInitial.assign(x, X0_x);
	tmvInitial.assign(y, X0_y);

	Flowpipe<FLOAT_T<mpfr_t>> initialSet(tmvInitial, domain);

	ContinuousSystem<FLOAT_T<mpfr_t>> system(ode, initialSet);

//	system.output(std::cout, 6);

	std::list<Flowpipe<FLOAT_T<mpfr_t>> > result;

	Range<FLOAT_T<mpfr_t>> estimation;
	Interval<FLOAT_T<mpfr_t>> intEst(-1e-1,1e-1);
	estimation.assign(x, intEst);
	estimation.assign(y, intEst);

	system.reach_picard(result, t, 6.2, 0.02, 6, estimation);

	std::ofstream os;
	os.open("Brusselator.plt");

	output_2D_interval_gnuplot(result, os, std::string("Brusselator"), x, y);

	os.close();
}

void TEST_VanDerPol()
{
    VariablePool & vpool = VariablePool::getInstance();

    Variable x = vpool.getFreshVariable("x");
	Variable y = vpool.getFreshVariable("y");
    Variable x0 = vpool.getFreshVariable("x0");
	Variable y0 = vpool.getFreshVariable("y0");
	Variable t = vpool.getFreshVariable("t");

	MultivariatePolynomial<Interval<double>> deriv_x({(Interval<double>)1*y});
	MultivariatePolynomial<Interval<double>> deriv_y({(Interval<double>)1*y, (Interval<double>)-1*x, (Interval<double>)-1*x*x*y});

	PolynomialODE<double> ode;
	ode.assign(x, deriv_x);
	ode.assign(y, deriv_y);

	// define the initial set which is a flowpipe
	Interval<double> range_of_x0(-1,1), range_of_y0(-1,1);
	Interval<double> range_of_t(0.0,0.02);
	Domain<double> domain;
	domain.assign(x0, range_of_x0);
	domain.assign(y0, range_of_y0);
	domain.assign(t, range_of_t);

	TaylorModel<double> X0_x({(Term<Interval<double>>)(1.4), (Interval<double>)0.15*x0});
	TaylorModel<double> X0_y({(Term<Interval<double>>)(2.3), (Interval<double>)0.05*y0});

	TaylorModelVec<double> tmvInitial;
	tmvInitial.assign(x, X0_x);
	tmvInitial.assign(y, X0_y);

	Flowpipe<double> initialSet(tmvInitial, domain);

	ContinuousSystem<double> system(ode, initialSet);

//	system.output(std::cout, 6);

	std::list<Flowpipe<double> > result;

	Range<double> estimation;
	Interval<double> intEst(-1e-2,1e-2);
	estimation.assign(x, intEst);
	estimation.assign(y, intEst);

	system.reach_picard(result, t, 7, 0.02, 6, estimation);

	std::ofstream os;
	os.open("VanDerPol.plt");

	output_2D_interval_gnuplot(result, os, std::string("VanDerPol"), x, y);

	os.close();
}

void TEST_Roessler()
{
    VariablePool & vpool = VariablePool::getInstance();

    Variable x = vpool.getFreshVariable("x");
	Variable y = vpool.getFreshVariable("y");
	Variable z = vpool.getFreshVariable("z");
    Variable x0 = vpool.getFreshVariable("x0");
	Variable y0 = vpool.getFreshVariable("y0");
	Variable z0 = vpool.getFreshVariable("z0");
	Variable t = vpool.getFreshVariable("t");

	MultivariatePolynomial<Interval<double>> deriv_x({(Interval<double>)-1*y, (Interval<double>)-1*z});
	MultivariatePolynomial<Interval<double>> deriv_y({(Interval<double>)0.2*y, (Interval<double>)1*x});
	MultivariatePolynomial<Interval<double>> deriv_z({(Term<Interval<double>>)(0.2), (Interval<double>)-5.7*z, (Interval<double>)1*x*z});

	PolynomialODE<double> ode;
	ode.assign(x, deriv_x);
	ode.assign(y, deriv_y);
	ode.assign(z, deriv_z);

	// define the initial set which is a flowpipe
	Interval<double> range_of_x0(-1,1), range_of_y0(-1,1), range_of_z0(-1,1);
	Interval<double> range_of_t(0.0,0.02);
	Domain<double> domain;
	domain.assign(x0, range_of_x0);
	domain.assign(y0, range_of_y0);
	domain.assign(z0, range_of_z0);
	domain.assign(t, range_of_t);

	TaylorModel<double> X0_x({(Interval<double>)0.1*x0});
	TaylorModel<double> X0_y({(Term<Interval<double>>)(-8.4), (Interval<double>)0.1*y0});
	TaylorModel<double> X0_z({(Interval<double>)0.1*z0});

	TaylorModelVec<double> tmvInitial;
	tmvInitial.assign(x, X0_x);
	tmvInitial.assign(y, X0_y);
	tmvInitial.assign(z, X0_z);

	Flowpipe<double> initialSet(tmvInitial, domain);

	ContinuousSystem<double> system(ode, initialSet);

//	system.output(std::cout, 6);

	std::list<Flowpipe<double> > result;

	Range<double> estimation;
	Interval<double> intEst(-1e-2,1e-2);
	estimation.assign(x, intEst);
	estimation.assign(y, intEst);
	estimation.assign(z, intEst);

	system.reach_picard(result, t, 6, 0.02, 7, estimation);

	std::ofstream os;
	os.open("Roessler.plt");

	output_2D_interval_gnuplot(result, os, std::string("Roessler"), y, z);

	os.close();
}


int main()
{
//	TEST_Multiplication();
//	TEST_Integration();
//	TEST_Lie_Derivation();
//	TEST_Picard_Operation();
//	TEST_Substitution();
//	TEST_Polynomial_Substitution();
//	TEST_normalize();
//	TEST_Addition();

	TEST_Brusselator();
//	TEST_VanDerPol();
//	TEST_Roessler();
	return 0;
}


