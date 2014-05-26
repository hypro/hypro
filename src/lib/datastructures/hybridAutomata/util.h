
#pragma once

#include "../../util/eigenTypetraits.h"
#include "carl/interval/Interval.h"
#include "carl/numbers/FLOAT_T.h"
//#include "../../numbers/FLOAT_T.h"
#include "../../representations/Polytope/Polytope.h"


namespace hypro
{
		enum operator_e {
			EQ,
			GEQ,
			LEQ,
			NEQ,
			LESS,
			GREATER
		};

		template<typename Number>
		using valuation_t = hypro::Polytope<Number>;

		template<typename Number>
		using vector_t = std::map<carl::Variable, Number>;

		template<typename Number>
		using matrix_t = Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>;

		typedef std::map<carl::Variable, operator_e> operator_t;

		//typedef std::map<carl::Variable, carl::FLOAT_T<number> > vector_t;
		//typedef Eigen::Matrix<carl::FLOAT_T<number>, Eigen::Dynamic, Eigen::Dynamic> matrix_t;
		//typedef std::map<carl::Variable, carl::Interval<hypro::FLOAT_T<number>> valuation_t;
		//typedef std::map<carl::Variable, hypro::Polytope<number>> valuation_t;
		//typedef hypro::Polytope<carl::FLOAT_T<number>> valuation_t;

		/*
		template<typename Number>
		bool compare(carl::FLOAT_T<Number> _lhs, carl::FLOAT_T<Number> _rhs, operator_t _op) {
			bool result = false;

			switch (_op) {
			case EQ:
				if (_lhs == _rhs) {result = true;}
				break;
			case NEQ:
				if (_lhs != _rhs) {result = true;}
				break;
			case GEQ:
				if (_lhs >= _rhs) {result = true;}
				break;
			case LEQ:
				if (_lhs <= _rhs) {result = true;}
				break;
			case LESS:
				if (_lhs < _rhs) {result = true;}
				break;
			case GREATER:
				if (_lhs > _rhs) {result = true;}
				break;
			default:
				result = false;
			}
			return result;
		}
		*/

}
