#pragma once

#include "Dictionary.h"

namespace hypro {

template <typename Number>
class ConstrainSet {
  private:
	// semantic: vector of variable bounds and assignment.
	// each constraint: a tuple of two pairs (bool: isInfty, number: lower, respectively upper bound) and a number (assignment).
	std::vector<std::tuple<std::pair<bool, Number>, std::pair<bool, Number>, Number>> constrainSet;

  public:
	ConstrainSet() = default;

	std::tuple<std::pair<bool, Number>, std::pair<bool, Number>, Number> get( std::size_t index ) const {
		return constrainSet[index];
	}

	std::size_t size() const {
		return constrainSet.size();
	}

	void add( std::tuple<std::pair<bool, Number>, std::pair<bool, Number>, Number> newElem ) {
		constrainSet.push_back( newElem );
	}

	/**
	 * @brief Checks if there is any variable out of bounds. The method returns the index of the next variable, which is out of bounds,
	 * diff holds the distance to the respective bound.
	 * @details [long description]
	 *
	 * @param index Index for the variable, which is out of bounds.
	 * @param diff Distance to the bound.
	 * @param baseIndices A vector of possible variable indices.
	 * @return True, if there is any variable out of bounds.
	 */
	bool outside( Eigen::Index& index, Number& diff, const std::vector<Eigen::Index>& baseIndices ) {
		index = constrainSet.size() + 1;
		diff = 0;
		for ( std::size_t i = 0; i < baseIndices.size() - 1; ++i ) {																			// iterate over the base indices
			if ( ( index == Eigen::Index( constrainSet.size() + 1 ) ||																			// if nothing found OR
				   baseIndices[i] - 1 < baseIndices[index] )																					// What does this mean?
				 && not( std::get<0>( std::get<0>( constrainSet[baseIndices[i] - 1] ) ) ||														// not ( unbounded lower bound
						 std::get<1>( std::get<0>( constrainSet[baseIndices[i] - 1] ) ) <= std::get<2>( constrainSet[baseIndices[i] - 1] ) ) )	// OR lb <= assignment)
			{
				index = Eigen::Index( i );
				diff = std::get<1>( std::get<0>( constrainSet[baseIndices[i] - 1] ) ) - std::get<2>( constrainSet[baseIndices[i] - 1] );
			} else if ( ( index == Eigen::Index( constrainSet.size() + 1 ) ||																		   // if nothing found OR
						  baseIndices[i] - 1 < baseIndices[index] )																					   // SOMETHING
						&& not( std::get<0>( std::get<1>( constrainSet[baseIndices[i] - 1] ) ) ||													   // not (upper unbounded
								std::get<1>( std::get<1>( constrainSet[baseIndices[i] - 1] ) ) >= std::get<2>( constrainSet[baseIndices[i] - 1] ) ) )  // OR ub >= assignment
			{
				index = Eigen::Index( i );
				diff = std::get<1>( std::get<1>( constrainSet[baseIndices[i] - 1] ) ) - std::get<2>( constrainSet[baseIndices[i] - 1] );
			}
		}
		return index != Eigen::Index( constrainSet.size() + 1 );
	}
	/**
	 * @brief Finds a suitable pivot to get the variable "index" to its bounds.
	 * @return True, if there is a suitable pivot.
	 */
	bool getPivot( const Eigen::Index& index, const Number& diff, Eigen::Index& pivot, const std::vector<Eigen::Index>& cobaseIndices,
				   const matrix_t<Number>& dictionary ) {
		pivot = constrainSet.size() + 1;
		for ( std::size_t i = 0; i < cobaseIndices.size() - 1; ++i ) {
			if ( pivot == Eigen::Index( constrainSet.size() + 1 ) || cobaseIndices[i] < pivot ) {
				if ( dictionary( index, i ) * diff < 0 && ( std::get<0>( std::get<0>( constrainSet[cobaseIndices[i] - 1] ) ) || std::get<1>( std::get<0>( constrainSet[cobaseIndices[i] - 1] ) ) > std::get<2>( constrainSet[cobaseIndices[i] - 1] ) ) ) {
					pivot = Eigen::Index( i );
				} else if ( dictionary( index, i ) * diff > 0 && ( std::get<0>( std::get<1>( constrainSet[cobaseIndices[i] - 1] ) ) || std::get<1>( std::get<1>( constrainSet[cobaseIndices[i] - 1] ) ) < std::get<2>( constrainSet[cobaseIndices[i] - 1] ) ) ) {
					pivot = Eigen::Index( i );
				}
			}
		}
		return ( pivot != Eigen::Index( constrainSet.size() + 1 ) );
	}

	/**
	 * @brief modify the assignment of "pivot" by adding "diff" and recomputes the value of the variables in the basis
	 */
	void modifyAssignment( const Eigen::Index& pivot, const Number& diff, const std::vector<Eigen::Index>& base,
						   const std::vector<Eigen::Index>& cobase, const matrix_t<Number>& dictionary ) {
		std::get<2>( constrainSet[cobase[pivot] - 1] ) += diff;
		// re-compute assignment
		for ( std::size_t rowIndex = 0; rowIndex < base.size() - 1; ++rowIndex ) {
			// re-set to zero
			std::get<2>( constrainSet[base[rowIndex] - 1] ) = 0;
			// compute new value iteratively
			for ( std::size_t colIndex = 0; colIndex < cobase.size() - 1; ++colIndex ) {
				std::get<2>( constrainSet[base[rowIndex] - 1] ) += dictionary( rowIndex, colIndex ) * std::get<2>( constrainSet[cobase[colIndex] - 1] );
			}
		}
	}

	void setLowerBoundToValue( const std::size_t index ) {	// not used
		std::get<1>( std::get<0>( constrainSet[index] ) ) = std::get<2>( constrainSet[index] );
	}

	void print() const {
		std::cout << "\n";
		for ( std::size_t i = 0; i < constrainSet.size(); ++i ) {
			std::cout << i + 1 << ": (";
			if ( std::get<0>( std::get<0>( constrainSet[i] ) ) ) {
				std::cout << "-infty";
			} else {
				std::cout << std::get<1>( std::get<0>( constrainSet[i] ) );
			}
			std::cout << ",";
			if ( std::get<0>( std::get<1>( constrainSet[i] ) ) ) {
				std::cout << "infty";
			} else {
				std::cout << std::get<1>( std::get<1>( constrainSet[i] ) );
			}
			std::cout << ")    value: " << std::get<2>( constrainSet[i] ) << "\n";
		}
	}

	Point<Number> toPoint( std::size_t dimension ) const {
		std::vector<Number> point = std::vector<Number>( dimension );
		for ( std::size_t index = 0; index < dimension; ++index ) {
			point[index] = std::get<2>( constrainSet[constrainSet.size() - dimension + index] );
		}
		return Point<Number>( point );
	}

	bool isSaturated( std::size_t var ) const {
		return ( not( std::get<0>( std::get<0>( constrainSet[var] ) ) ) && std::get<1>( std::get<0>( constrainSet[var] ) ) == std::get<2>( constrainSet[var] ) ) || ( not( std::get<0>( std::get<1>( constrainSet[var] ) ) ) && std::get<1>( std::get<1>( constrainSet[var] ) ) == std::get<2>( constrainSet[var] ) );
	}

	bool finiteLowerBound( std::size_t var ) const {
		return not( std::get<0>( std::get<0>( constrainSet[var] ) ) );
	}

	/**
	 * @brief returns the difference between the current assignment and the lower bound
	 */
	Number diffToLowerBound( std::size_t var ) const {
		return std::get<1>( std::get<0>( constrainSet[var] ) ) - std::get<2>( constrainSet[var] );
	}

	friend bool operator==( const ConstrainSet<Number>& lhs, const ConstrainSet<Number>& rhs ) {
		if ( lhs.constrainSet.size() != rhs.constrainSet.size() ) {
			return false;
		}
		for ( unsigned pos = 0; pos < lhs.constrainSet.size(); ++pos ) {
			if ( lhs.constrainSet.at( pos ) != rhs.constrainSet.at( pos ) ) {
				return false;
			}
		}

		return true;
	}

	friend bool operator!=( const ConstrainSet<Number>& lhs, const ConstrainSet<Number>& rhs ) {
		return !( lhs == rhs );
	}

	friend std::ostream& operator<<( std::ostream& _ostr, const ConstrainSet<Number>& cs ) {
		for ( std::size_t i = 0; i < cs.size(); ++i ) {
			_ostr << i + 1 << ": (";
			if ( std::get<0>( std::get<0>( cs.get( i ) ) ) ) {
				_ostr << "-infty";
			} else {
				_ostr << std::get<1>( std::get<0>( cs.get( i ) ) );
			}
			_ostr << ",";
			if ( std::get<0>( std::get<1>( cs.get( i ) ) ) ) {
				_ostr << "infty";
			} else {
				_ostr << std::get<1>( std::get<1>( cs.get( i ) ) );
			}
			_ostr << ")    value: " << std::get<2>( cs.get( i ) ) << "\n";
		}
		return _ostr;
	}
};
}  // namespace hypro
