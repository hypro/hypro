
#pragma once

//#include "../../util/eigenTypetraits.h"
#include "../../datastructures/hybridAutomata/util.h"
#include "../../representations/Box/Box.h"
#include "../../representations/SupportFunction/SupportFunction.h"
#include "carl/core/VariablePool.h"

namespace hypro
{

		/*
		 * General purpose functionality
		 */
		template<typename Number>
		bool compare(Number _lhs, Number _rhs, hypro::operator_e _op) {
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

		template<typename Number>
	    Number hausdorffError(const Number& delta, const matrix_t<Number>& matrix, const Number& _supremum)
	    {
	        using namespace Eigen;
	        // TODO: Can we omit conversion to Number and use Number instead?
	        Number result;
	        Number d = delta;
	        //TODO: What about the constant factor?
	        //Eigen::Matrix<Number, Dynamic, Dynamic> matrix = Eigen::Matrix<Number, Dynamic, Dynamic>(polytope::csSize(mPolyhedron.constraints()), polytope::pplDimension(mPolyhedron));
	        //matrix = hypro::polytope::polytopeToMatrix<Number>(this->mPolyhedron);
	    	//std::cout << "in hausdorffError() - matrix: " << std::endl;
	    	//std::cout << matrix << std::endl;

	        // TODO: Matrix lpNorm function of Eigen does not work ...
	        //Number t = matrix.lpNorm<Infinity>();

	        // calculate matrix infinity norm by hand
	        Number norm = 0;
	        for(unsigned rowCnt = 0; rowCnt < matrix.rows(); ++rowCnt)
	        {
	            for(unsigned colCnt = 0; colCnt < matrix.cols(); ++colCnt)
	            {
	                Number value = matrix(rowCnt, colCnt);
	                value.abs_assign();
	                norm = norm < value ? value : norm;
	            }
	        }

	        //Number tmp = d * t;
	        Number tmp = d * norm;
	        tmp.exp(result);
	        result = result - 1 - tmp;

	        result *= _supremum;

	        return result;
	    }

		/**
		 * based on the Hausdorff distance, constructs the box (also a polytope) that is used for bloating the initial approximation
		 */
		template<typename Number, typename Representation>
		Representation computePolytope(unsigned int _dim, Number _radius) {
			//the last variable is always a placeholder for a constant translation factor
			//no bloating in that dimension
			//unsigned int correctedDim = _dim;

			hypro::matrix_t<Number> mat = hypro::matrix_t<Number>::Zero(2*_dim,_dim);
			hypro::vector_t<Number> vec(2*_dim,1);

			int i = 0;
			for (unsigned z=0; z<_dim; ++z) {

				vec(i) = _radius;
				vec(i+1) = _radius;

				mat(i,z) = 1;
				mat(i+1,z) = -1;

				i = i+2;

			}
			//mat(2*_dim-2,_dim-1) = 1;
			//mat(2*_dim-1,_dim-1) = 1;
			//mat(2*_dim-1,_dim-1) = -1; -> this does not work, as the dimension of the result is too low.
			//vec(2*_dim-2) = 0;
			//vec(2*_dim-1) = 0;

			//std::cout << "Hausdorff matrix: " << mat << ", Hausdorff vector " << vec << std::endl;

			Representation poly = Representation(mat,vec);
			return poly;
		}

		/*
		template<typename Number>
		SupportFunction<Number> computePolytope(unsigned int _dim, Number _radius) {
			return SupportFunction<Number>(SF_TYPE::INFTY_BALL, _radius );
		}
		*/
		/**
		 * conversion of a matrix of type 'Number' to 'double'
		 */
		template<typename Number>
		Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> convertMatToDouble(hypro::matrix_t<Number>& _mat) {
			Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> resultMat(_mat.rows(),_mat.cols());

			for (int i=0; i<_mat.rows(); ++i) {
				for (int j=0; j<_mat.cols(); ++j) {
					resultMat(i,j) = _mat(i,j).toDouble();
				}
			}
			return resultMat;
		}

                /**
		 * conversion of a vector of type 'Number' to 'double'
		 */
                template<typename Number>
		Eigen::Matrix<Number, Eigen::Dynamic, 1> convertVecToDouble(hypro::vector_t<Number>& _vec) {
			Eigen::Matrix<Number, Eigen::Dynamic, 1> resultMat(_vec.rows(),1);

			for (int i=0; i<_vec.rows(); ++i) {
                            resultMat(i) = _vec(i).toDouble();
			}
			return resultMat;
		}

		/**
		 * conversion of a matrix of (templated) type 'Number' to 'Number'
		 */
		template<typename Number>
		hypro::matrix_t<Number> convertMatToFloatT(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& _mat) {
			hypro::matrix_t<Number> resultMat(_mat.rows(),_mat.cols());

			for (int i=0; i<_mat.rows(); ++i) {
				for (int j=0; j<_mat.cols(); ++j) {
					resultMat(i,j) = Number(_mat(i,j));
				}
			}
			return resultMat;
		}
}
