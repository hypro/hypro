
#pragma once

//#include "../../util/eigenTypetraits.h"
#include "../../datastructures/hybridAutomata/util.h"
#include "../../representations/Box/Box.h"
#include "carl/core/VariablePool.h"

namespace hypro
{

		/*
		 * General purpose functionality
		 */
		template<typename Number>
		bool compare(carl::FLOAT_T<Number> _lhs, carl::FLOAT_T<Number> _rhs, hypro::operator_e _op) {
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

		/*
		 * Functionality for the reachability computation
		 */

		/**
		 * based on the Hausdorff distance, constructs the box (also a polytope) that is used for bloating the initial approximation
		 */
		template<typename Number>
		hypro::valuation_t<Number> computePolytope(unsigned int _dim, Number _radius) {
			//the last variable is always a placeholder for a constant translation factor
			//no bloating in that dimension
			unsigned int correctedDim = _dim-1;

			hypro::matrix_t<Number> mat = hypro::matrix_t<Number>(2*correctedDim,correctedDim);
			hypro::vector_t<Number> vec(2*correctedDim,1);

			//initialize matrix entries with 0
			for (int k=0; k<2*correctedDim; ++k) {
				for (int l=0; l<correctedDim; ++l) {
					mat(k,l) = 0;
				}
			}

			int i = 0;

			for (int z=0; z<correctedDim; ++z) {

				vec(i) = _radius;
				vec(i+1) = _radius;

				mat(i,z) = 1;
				mat(i+1,z) = -1;

				i = i+2;

			}

			hypro::valuation_t<Number> poly = hypro::Polytope<Number>(mat,vec);
			return poly;
		}

		/**
		 * conversion of a matrix of type 'carl::FLOAT_T<Number>' to 'double'
		 */
		template<typename Number>
		Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> convertMatToDouble(hypro::matrix_t<Number>& _mat) {
			Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> resultMat(_mat.rows(),_mat.cols());

			for (int i=0; i<_mat.rows(); ++i) {
				for (int j=0; j<_mat.cols(); ++j) {
					resultMat(i,j) = _mat(i,j).toDouble();
				}
			}
			return resultMat;
		}

		/**
		 * conversion of a matrix of (templated) type 'Number' to 'carl::FLOAT_T<Number>'
		 */
		template<typename Number>
		hypro::matrix_t<Number> convertMatToFloatT(Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& _mat) {
			hypro::matrix_t<Number> resultMat(_mat.rows(),_mat.cols());

			for (int i=0; i<_mat.rows(); ++i) {
				for (int j=0; j<_mat.cols(); ++j) {
					resultMat(i,j) = carl::FLOAT_T<Number>(_mat(i,j));
				}
			}
			return resultMat;
		}
}

