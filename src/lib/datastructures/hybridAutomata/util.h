
#pragma once

#include "../../util/eigenTypetraits.h"

namespace hypro
{
	public:
		enum operator_e {
			EQ,
			GEQ,
			LEQ,
			NEQ,
			LESS,
			GREATER
		};

		typedef std::map<carl::Variable, carl::FLOAT_T<Number> > vector_t;
		typedef Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> matrix_t;
		typedef std::map<carl::Variable, operator_e> operator_t;
		typedef std::map<carl::Variable, carl::Interval<FLOAT_T<Number>>> valuation_t;

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
