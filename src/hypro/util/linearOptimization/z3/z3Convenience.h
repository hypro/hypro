//
// Created by stefan on 30.06.16.
//
// TODO Johannes: clean me up!
//

#pragma once
#include "../../../flags.h"
#ifdef HYPRO_USE_Z3
#include <carl/util/Singleton.h>
#include <carl/core/Relation.h>
#include <thread>
#include "z3Context.h"

namespace hypro {

	template<typename Number>
	static z3::expr_vector createFormula(const matrix_t<Number>& _constraints, const vector_t<Number> _constants, z3Context& c, carl::Relation = carl::Relation::LEQ) {
		// TODO: Relation is ignored here.

		//std::cout << __func__ << _constraints << " \n\n " << _constants << std::endl;

		z3::expr_vector constraints(c);
		z3::expr_vector variables(c);
		//std::cout << "Variables.size() " << variables.size() << std::endl;
		for(unsigned i = 0; i < _constraints.cols(); ++i){
			z3::expr var(c);
			const char* varName = ("x_" + std::to_string(i)).c_str();
			var=c.real_const(varName);
			variables.push_back(var);
			//std::cout << "Created z3 Variable " << var << std::endl;
			//std::cout << "Variables.size() " << variables.size() << std::endl;
		}

		//std::cout << "Variables.size() " << variables.size() << std::endl;

		for(unsigned i = 0; i < _constraints.rows(); ++i){
			z3::expr polynomial(c);
			polynomial = c.int_val(0);
			for(unsigned j = 0; j < _constraints.cols(); ++j){
				z3::expr coeff(c);
				coeff=c.real_val((carl::convert<Number,mpq_class>(_constraints(i,j))));

				//std::cout << "Coefficient is " << coeff << std::endl;

				z3::expr term(c);

				//std::cout << "Variable is " << variables[j] << std::endl;

				term=variables[j]*coeff;
				polynomial = polynomial + term ;
			}
			z3::expr constant = c.real_val(carl::convert<Number,mpq_class>(_constants(i)));
			z3::expr constraint(polynomial <= constant);
			constraints.push_back(constraint);
		}

		return constraints;
	}

	template<typename Number>
	static z3::expr createFormula(const Point<Number>& _point, const matrix_t<Number>& _constraints, const vector_t<Number> _constants, z3Context& c ) {
		z3::expr formula(c);
		formula = c.bool_val(true);
		z3::expr pointConstraint(c);
		pointConstraint = c.int_val(0);

		std::vector<z3::expr> variables;
		for(unsigned i = 1; i <= _constraints.cols(); ++i){
			std::string name = "x_" + std::to_string(i);
			variables.push_back(c.real_const(name.c_str()));
		}

		for(unsigned d = 0; d < _point.dimension(); ++d) {
			if(_point.at(d) != carl::constant_zero<Number>::get()){
				pointConstraint = pointConstraint + c.real_val(carl::convert<Number,mpq_class>(-_point.at(d))) + variables.at(d);
			}
		}

		formula = formula && (pointConstraint == 0);

		for(unsigned i = 0; i < _constraints.rows(); ++i){
			z3::expr constraint(c);
			constraint = c.int_val(0);
			for(unsigned j = 0; j < _constraints.cols(); ++j){
				if(_constraints(i,j) != carl::constant_zero<Number>::get()){
					constraint = constraint + variables.at(j)*(c.real_val(carl::convert<Number,mpq_class>(_constraints(i,j))));
				}
			}
			z3::expr constant = c.real_val(carl::convert<Number,mpq_class>(_constants(i)));
			constraint = constraint <= constant;
			formula = formula && constraint;
		}

		return formula;
	}

	template<typename Number>
	static std::pair<z3::expr, z3::expr> createFormula(const matrix_t<Number>& _constraints, const vector_t<Number> _constants, const vector_t<Number>& _objective, z3Context& c, std::vector<z3::expr>& variables, carl::Relation = carl::Relation::LEQ) {

		// TODO: Relation is ignored here.

		z3::expr formula(c);
		z3::expr objective(c);
		objective = c.int_val(0);
		formula = c.bool_val(true);
		for(unsigned i = 1; i <= _constraints.cols(); ++i){
			std::string name = "x_" + std::to_string(i);
			variables.push_back(c.real_const(name.c_str()));
		}

		for(unsigned colIndex = 0; colIndex < _constraints.cols(); ++colIndex) {
			if(_objective(colIndex) != carl::constant_zero<Number>::get()){
				z3::expr var = variables.at(colIndex);
				z3::expr coeff = c.real_val(carl::convert<Number,mpq_class>(_objective(colIndex)));
				assert(coeff.is_arith());
				z3::expr tmp = var * coeff;
				objective = objective + tmp;
			}
		}

		for(unsigned i = 0; i < _constraints.rows(); ++i){
			z3::expr constraint(c);
			constraint = c.int_val(0);
			for(unsigned j = 0; j < _constraints.cols(); ++j){
				if(_constraints(i,j) != carl::constant_zero<Number>::get()){
					constraint = constraint + variables.at(j)*(c.real_val(carl::convert<Number,mpq_class>(_constraints(i,j))));
				}
			}
			z3::expr constant = c.real_val(carl::convert<Number,mpq_class>(_constants(i)));
			constraint = constraint <= constant;
			formula = formula && constraint;
		}

		return std::make_pair(formula,objective);
	}


	// This has been a Test and should not be needed.
	/*
	class ContextProvider : public carl::Singleton<ContextProvider> {
	    friend carl::Singleton<ContextProvider>;

	    public:
            ContextProvider () : mContextCollection(100), mFreeContextsBitmap(100, true) {}

            z3::context& getFreeContext() {
                lock.lock();
                for (unsigned i = 0; i < mFreeContextsBitmap.size(); i++) {
                    if (mFreeContextsBitmap[i] == true) {
                        // found free
                        mFreeContextsBitmap[i] = false; // mark as in use
                        lock.unlock();
                        return mContextCollection[i];
                    }
                }
                lock.unlock();
                std::cout << "WARN - You use more threads than concurrenty supported!" << std::endl;
                assert(false);
            }

            void returnContext (z3::context& context) {
                lock.lock();
                for (unsigned i = 0; i < mContextCollection.size(); i++) {
                    if (&context == &(mContextCollection[i])) {
                        mFreeContextsBitmap[i] = true;
                        break;
                    }
                }
                lock.unlock();
            }

	    private:

	        std::vector<z3::context> mContextCollection;
	        std::vector<bool> mFreeContextsBitmap;
	        unsigned mLastReturnedContext;
	        mutable std::mutex lock;
	};*/

} // namespace hypro

#endif
