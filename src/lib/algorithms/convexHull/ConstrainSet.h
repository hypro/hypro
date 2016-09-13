#pragma once

#include "Dictionary.h"

namespace hypro {

template<typename Number>
class ConstrainSet {
	private:
		std::vector<std::tuple<std::pair<bool,Number>,std::pair<bool,Number>,Number>> constrainSet;

	public:
		ConstrainSet() = default;

		std::tuple<std::pair<bool,Number>,std::pair<bool,Number>,Number> get(std::size_t index) {
			return constrainSet[index];
		}

		void add(std::tuple<std::pair<bool,Number>,std::pair<bool,Number>,Number> newElem) {
			constrainSet.push_back(newElem);
		}

		bool outside(std::size_t& index, Number& diff, const std::vector<std::size_t>& baseIndices) {
			index = constrainSet.size()+1;
			diff = 0;
			for(std::size_t i=0;i<baseIndices.size()-1;++i) {
				if((index==constrainSet.size()+1||baseIndices[i]-1<baseIndices[index]) && not(std::get<0>(std::get<0>(constrainSet[baseIndices[i]-1]))||
							std::get<1>(std::get<0>(constrainSet[baseIndices[i]-1]))<=std::get<2>(constrainSet[baseIndices[i]-1]))) {
					index = i;
					diff = std::get<1>(std::get<0>(constrainSet[baseIndices[i]-1]))-std::get<2>(constrainSet[baseIndices[i]-1]);
				} else if((index==constrainSet.size()+1||baseIndices[i]-1<baseIndices[index]) && not(std::get<0>(std::get<1>(constrainSet[baseIndices[i]-1]))||
							std::get<1>(std::get<1>(constrainSet[baseIndices[i]-1]))>=std::get<2>(constrainSet[baseIndices[i]-1]))) {
					index = i;
					diff = std::get<1>(std::get<1>(constrainSet[baseIndices[i]-1]))-std::get<2>(constrainSet[baseIndices[i]-1]);
				}
			}
			return index!=constrainSet.size()+1;
		}

	/**
	 * @brief Finds the next variable that is out of its bounds among the indices of the basis.
	 * @param diff contains the distance to the bound.
	 * @return True, if there is a violated bound.
	 */

		bool getPivot(std::size_t& index, Number& diff, std::size_t& pivot, const std::vector<std::size_t>& cobaseIndices,
						const matrix_t<Number>& dictionary) {
			pivot = constrainSet.size()+1;
			for(std::size_t i=0;i<cobaseIndices.size()-1;++i) {
				if(pivot==constrainSet.size()+1 || cobaseIndices[i]<pivot) {
					if(dictionary(index,i) * diff<0 && (std::get<0>(std::get<0>(constrainSet[cobaseIndices[i]-1]))
								|| std::get<1>(std::get<0>(constrainSet[cobaseIndices[i]-1]))>std::get<2>(constrainSet[cobaseIndices[i]-1]))) {
						pivot = i;
					} else if(dictionary(index,i)*diff>0 && (std::get<0>(std::get<1>(constrainSet[cobaseIndices[i]-1]))
								|| std::get<1>(std::get<1>(constrainSet[cobaseIndices[i]-1]))<std::get<2>(constrainSet[cobaseIndices[i]-1]))) {
						pivot = i;
					}
				}
			}
			return(pivot!=constrainSet.size()+1);
		}
	/**
	 * @brief Finds a suitable pivot to get the variable "index" to its bounds.
	 * @return True, if there is a suitable pivot.
	 */

		void modifyAssignment (const std::size_t& pivot,const Number& diff,const std::vector<std::size_t>& base,
						const std::vector<std::size_t>& cobase, const matrix_t<Number>& dictionary) {
			std::get<2>(constrainSet[cobase[pivot]-1])+=diff;
			for(std::size_t rowIndex=0;rowIndex<base.size()-1;++rowIndex) {
				std::get<2>(constrainSet[base[rowIndex]-1]) = 0;
				for(std::size_t colIndex=0;colIndex<cobase.size()-1;++colIndex) {
					std::get<2>(constrainSet[base[rowIndex]-1]) += dictionary(rowIndex,colIndex)*std::get<2>(constrainSet[cobase[colIndex]-1]);
				}
			}
		}
	/**
	 * @brief modify the assignment of "pivot" by adding "diff" and recomputes the value of the variables in the basis
	 *
	 */

		void setLowerBoundToValue (const std::size_t index) {//not used
			std::get<1>(std::get<0>(constrainSet[index]))=std::get<2>(constrainSet[index]);
		}

		void print() const {
		cout <<"\n";
			for(std::size_t i=0;i<constrainSet.size();++i) {
				cout << i+1 <<": (";
				if(std::get<0>(std::get<0>(constrainSet[i]))) {cout << "-infty";} else {cout << std::get<1>(std::get<0>(constrainSet[i]));}
				cout << ",";
				if(std::get<0>(std::get<1>(constrainSet[i]))) {cout << "infty";} else {cout << std::get<1>(std::get<1>(constrainSet[i]));}
				cout << ")    value: " << std::get<2>(constrainSet[i])<<"\n";
			}
		}

		Point<Number> toPoint(std::size_t dimension) const {
			std::vector<Number> point = std::vector<Number>(dimension);
			for(std::size_t index= 0;index<dimension;++index) {
				point[index] = std::get<2>(constrainSet[constrainSet.size()-dimension+index]);
			}
			return Point<Number>(point);
		}

		bool isSaturated(std::size_t var) const {
			return (not(std::get<0>(std::get<0>(constrainSet[var])))&&std::get<1>(std::get<0>(constrainSet[var]))==std::get<2>(constrainSet[var]))
			||(not(std::get<0>(std::get<1>(constrainSet[var])))&&std::get<1>(std::get<1>(constrainSet[var]))==std::get<2>(constrainSet[var]));
		}

		bool finiteLowerBound(unsigned var) const {
			return not(std::get<0>(std::get<0>(constrainSet[var])));
		}

		Number diffToLowerBound(unsigned var) const {
			return std::get<1>(std::get<0>(constrainSet[var]))-std::get<2>(constrainSet[var]);
		}
	/**
	 * @brief returns the difference between the current assignment and the lower bound
	 */
	 friend bool operator==(const ConstrainSet<Number>& lhs, const ConstrainSet<Number>& rhs) {
	 	if(lhs.constrainSet.size() != rhs.constrainSet.size()) {
	 		return false;
	 	}
	 	for(unsigned pos = 0; pos < lhs.constrainSet.size(); ++pos) {
	 		if(lhs.constrainSet.at(pos) != rhs.constrainSet.at(pos)) {
	 			return false;
	 		}
	 	}

	 	return true;
	 }

	 friend bool operator!=(const ConstrainSet<Number>& lhs, const ConstrainSet<Number>& rhs) {
	 	return !(lhs == rhs);
	 }
};
} // namespace hypro
