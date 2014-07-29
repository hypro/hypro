
#pragma once

//#include "../../util/eigenTypetraits.h"
#include "../../datastructures/hybridAutomata/util.h"
#include "../../representations/Box/Box.h"
#include "carl/core/VariablePool.h"

namespace hypro
{
		/*
		enum operator_e {
			EQ,
			GEQ,
			LEQ,
			NEQ,
			LESS,
			GREATER
		};
		*/

		//typedef std::map<carl::Variable, carl::FLOAT_T<Number> > vector_t;
		//typedef Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> matrix_t;
		//typedef std::map<carl::Variable, operator_e> operator_t;
		//typedef std::map<carl::Variable, carl::FLOAT_T<Number>> valuation_t;
		//typedef std::map<carl::Variable, carl::Interval<FLOAT_T<Number>>> valuation_t; //a valuation is simply always handled as an interval

		/**
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

		/**
		 * Functionality in context of a Location
		 */
		/*
		template<typename Number>
		bool checkInvariant(hypro::Location _loc, valuation_t _val) {
			//return mInvariant.mat * _val mInvariant.op mInvariant.vec
			//shorter? for (auto varIt : _val)

			auto vecIt = _loc.mInvariant.vec.begin();

			for (int currentRow=0; currentRow != _loc.mInvariant.mat.rows(); ++currentRow) {  //iterate over all matrix rows
				carl::FLOAT_T<Number> upperSum = 0;										// one matrix row * valuation vector = sum
				carl::FLOAT_T<Number> lowerSum = 0;
				int currentColumn = 0;

				for (auto varIt=_val.begin(); varIt !=_val.end(); ++varIt) {		// for each row iterate over all variables
					carl::FLOAT_T<Number> upperBound = varIt->second.upper();       // upper & lower bounds of the valuation interval for one variable
					carl::FLOAT_T<Number> lowerBound = varIt->second.lower();

					upperSum += _loc.mInvariant.mat(currentRow,currentColumn) * upperBound;   //add (matrix entry * var valuation) to the sums
					lowerSum += _loc.mInvariant.mat(currentRow,currentColumn) * lowerBound;

					currentColumn++; 												//next variable corresponds to next column
				}
				bool tempResult_up = compare(upperSum,vecIt->second,_loc.mInvariant.op); // compare upperSum with the value stored in the vector with respect to the operator
				bool tempResult_low = compare(lowerSum,vecIt->second,_loc.mInvariant.op);  //TODO can the vector contain intervals?

				if (!tempResult_up || !tempResult_low) {return false;}               //return false if a boundary is ever violated TODO possibly add information
			}
			return true;   // a boundary was never violated
		}
		*/

		/**
		 * Functionality in context of a Transition
		 */
		/*
		template<typename Number>
		bool checkGuard(hypro::Transition _trans, valuation_t _val) {
			//return mGuard.mat * _val mGuard.op mGuard.vec

			auto vecIt = _trans.mGuard.vec.begin();

			for (int currentRow=0; currentRow != _trans.mGuard.mat.rows(); ++currentRow) {  //iterate over all matrix rows
				carl::FLOAT_T<Number> upperSum = 0;										// one matrix row * valuation vector = sum
				carl::FLOAT_T<Number> lowerSum = 0;
				int currentColumn = 0;

				for (auto varIt=_val.begin(); varIt !=_val.end(); ++varIt) {		// for each row iterate over all variables
					carl::FLOAT_T<Number> upperBound = varIt->second.upper();       // upper & lower bounds of the valuation interval for one variable
					carl::FLOAT_T<Number> lowerBound = varIt->second.lower();

					upperSum += _trans.mGuard.mat(currentRow,currentColumn) * upperBound;   //add (matrix entry * var valuation) to the sums
					lowerSum += _trans.mGuard.mat(currentRow,currentColumn) * lowerBound;

					currentColumn++; 												//next variable corresponds to next column
				}
				bool tempResult_up = compare(upperSum,vecIt->second,_trans.mGuard.op); // compare upperSum with the value stored in the vector with respect to the operator
				bool tempResult_low = compare(lowerSum,vecIt->second,_trans.mGuard.op);  //TODO can the vector contain intervals?

				if (!tempResult_up || !tempResult_low) {return false;}               //return false if a boundary is ever violated TODO possibly add information
			}
			return true;   // a boundary was never violated
		}
		*/

		/**
		 * Functionality for the Flowpipe
		 */

		template<typename Number>
		hypro::Box<Number> computeBox(unsigned int _dim, Number _radius) {
			hypro::Box<Number> box = new hypro::Box<Number>();
		    carl::VariablePool& pool = carl::VariablePool::getInstance();
	        std::map<const carl::Variable, carl::Interval<Number> > boundaries;

			for (int i=0; i<_dim; ++i) {
				carl::Variable x = pool.getFreshVariable(std::to_string(i));
				boundaries.insert( std::make_pair(x, carl::Interval<Number>(-_radius,_radius)) );
			}
			box.insert(boundaries);
			return box;
		}

		template<typename Number>
		hypro::valuation_t<Number> computePolytope(unsigned int _dim, Number _radius) {
			//the last variable is always a placeholder for a constant translation factor
			//do not bloat into that dimension
			unsigned int correctedDim = _dim-1;
			//TODO: currently the additional row and column is just filled with 0s
			//unsigned int correctedDim = _dim;

			hypro::matrix_t<Number> mat = hypro::matrix_t<Number>(2*correctedDim,correctedDim);
			hypro::vector_t<Number> vec(2*correctedDim,1);
			//carl::VariablePool& pool = carl::VariablePool::getInstance();

			//TODO set rest of mat to 0 - necessary to do explicitly?
			for (int k=0; k<2*correctedDim; ++k) {
				for (int l=0; l<correctedDim; ++l) {
					mat(k,l) = 0;
				}
			}

			int i = 0;
			//TODO z<correctedDim
			for (int z=0; z<correctedDim; ++z) {

				vec(i) = _radius;
				vec(i+1) = _radius;

				mat(i,z) = 1;
				mat(i+1,z) = -1;

				i = i+2;

			}

			std::cout << "in computePolytope(): Vector " << std::endl;
			std::cout << vec << std::endl;
			std::cout << "------" << std::endl;

			std::cout << "in computePolytope(): Matrix " << std::endl;
			std::cout << mat << std::endl;
			std::cout << "------" << std::endl;

			hypro::valuation_t<Number> poly = hypro::Polytope<Number>(mat,vec);
			return poly;
		}

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

