//
// Created by stefan on 30.06.16.
//

#pragma once
#ifdef USE_Z3
#include "z3++.h"
#include "z3Context.h"

template<typename Number>
static z3::expr_vector createFormula(const hypro::matrix_t<Number>& _constraints, const hypro::vector_t<Number> _constants, carl::Relation _rel = carl::Relation::LEQ) {

	// TODO: Relation is ignored here.

	std::cout << __func__ << _constraints << " \n\n " << _constants << std::endl;

	z3::context c;
	z3::expr_vector constraints(c);
	z3::expr_vector variables(c);
	std::cout << "Variables.size() " << variables.size() << std::endl;
	for(unsigned i = 0; i < _constraints.cols(); ++i){
		z3::expr var(c);
		const char* varName = ("x_" + std::to_string(i)).c_str();
		var=c.real_const(varName);
		variables.push_back(var);
		std::cout << "Created z3 Variable " << var << std::endl;
		std::cout << "Variables.size() " << variables.size() << std::endl;
	}

	std::cout << "Variables.size() " << variables.size() << std::endl;

	for(unsigned i = 0; i < _constraints.rows(); ++i){
		z3::expr polynomial(c);
		polynomial = c.int_val(0);
		for(unsigned j = 0; j < _constraints.cols(); ++j){
			const char* coefficient(_constraints(i,j).toString().c_str());
			z3::expr coeff(c);
			coeff=c.real_val(coefficient);

			std::cout << "Coefficient is " << coeff << std::endl;

			z3::expr term(c);

			std::cout << "Variable is " << variables[j] << std::endl;

			term=variables[j]*coeff;
			polynomial = polynomial + term ;
		}
		const char* constantPart(_constants(i).toString().c_str());
		z3::expr constant = c.real_val(constantPart);
		z3::expr constraint(polynomial < constant);
		constraints.push_back(constraint);
	}

	return constraints;
}

template<typename Number>
static std::pair<z3::expr, z3::expr> createFormula(const hypro::matrix_t<Number>& _constraints, const hypro::vector_t<Number> _constants, const hypro::vector_t<Number>& _objective, carl::Relation _rel = carl::Relation::LEQ) {

	// TODO: Relation is ignored here.

	z3::context c;
	z3::expr formula(c);
	z3::expr objective(c);
	objective = c.int_val(0);
	formula = c.bool_val(true);
	std::vector<z3::expr> variables;
	for(unsigned i = 0; i < _constraints.cols(); ++i){
		variables.push_back(c.real_const("x_"+ i));
	}

	for(unsigned colIndex = 0; colIndex < _constraints.cols(); ++colIndex) {
		objective = objective + c.real_val(carl::toString(carl::convert<Number,hypro::Rational>(_objective(colIndex))).c_str())*variables.at(colIndex);
	}

	for(unsigned i = 0; i < _constraints.rows(); ++i){
		z3::expr constraint(c);
		constraint = c.int_val(0);
		for(unsigned j = 0; j < _constraints.cols(); ++j){
			const char* coefficient(_constraints(i,j).toString().c_str());
			constraint = constraint + variables.at(j)*(c.real_val(coefficient));
		}
		const char* constantPart(_constants(i).toString().c_str());
		z3::expr constant = c.real_val(constantPart);
		constraint = constraint < constant;
		formula = formula && constraint;
	}

	return std::make_pair(formula,objective);
}
#endif
