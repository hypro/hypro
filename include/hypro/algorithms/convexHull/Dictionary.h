/**
 * This file holds the vertex enumeration algorithm presented by Avis and Fukuda.
 * @file vertexEnumeration.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-10-29
 * @version	2015-11-18
 */

#pragma once

#include "../../config.h"
#include "../../datastructures/Halfspace.h"
#include "../../datastructures/Point.h"
#include "ConstrainSet.h"

#include <string>

#define FUKUDA_VERTEX_ENUM_DEBUG
#define DICT_DBG

namespace hypro {

template <typename Number>
class Dictionary {
  private:
	matrix_t<Number> mDictionary;	   // table
	std::vector<Eigen::Index> mB;	   // basis
	std::vector<Eigen::Index> mN;	   // co-basis
	ConstrainSet<Number> mConstrains;  // original constraints

  public:
	Dictionary() = default;
	Dictionary( const Dictionary& rhs );
	Dictionary( const matrix_t<Number>& rhs, std::vector<Eigen::Index> base, std::vector<Eigen::Index> cobase );
	Dictionary( const matrix_t<Number>& rhs, std::vector<Eigen::Index> base, std::vector<Eigen::Index> cobase, ConstrainSet<Number> constrains );
	/**
	 * @brief Build a dictionary with mDictionary=rhs, mB=base and mN=cobase.
	 */

	Dictionary( const std::vector<Halfspace<Number>>& hsv );
	/**
	 * @brief Build a dictionary based on the hyperplane set hsv.
	 */

	std::vector<Eigen::Index> basis() const;

	std::vector<Eigen::Index> cobasis() const;

	ConstrainSet<Number> constrainSet() const;

	matrix_t<Number> tableau() const;

	/**
	 * @return the number in the cell (i,j) of mDictionary.
	 */
	Number get( Eigen::Index i, Eigen::Index j ) const;

	/**
	 * @brief set mDicionary(i,j) to val.
	 */
	void setValue( Eigen::Index i, Eigen::Index j, Number val );

	void printDictionary() const;

	/**
	 * @brief Pivot expected ‘)’ before ‘<’ tokenthe dictionary, no modification made to mB and mN.
	 */
	void pivotDictionary( Eigen::Index i, Eigen::Index j );

	/**
	 * @brief The whole pivot.
	 */
	void pivot( Eigen::Index i, Eigen::Index j );

	/**
	 * @brief Selects the next pivot according to CrissCross's rule.
	 *
	 * @param i The reference for the proposed row index.
	 * @param j The reference for the proposed column index.
	 *
	 * @return True, if there is a valid pivot.
	 */
	bool selectCrissCrossPivot( Eigen::Index& i, Eigen::Index& j );

	/**
	 * @brief Check for the satisfiability of the dictionary and finds a suitable assignment.
	 * @details Checks if variables are out of bound. If yes, tries to find a suitable pivot to fix this. If there is none throws exception (empty set).
	 * If a suitable pivot is found, apply pivot step and update assignment.
	 * @returns True, if assignment has been updated.
	 */
	bool fixOutOfBounds();

	/**
	 * @brief Puts in i and j the pivot, returns false iff none was sutable.
	 */
	bool selectBlandPivot( Eigen::Index& i, Eigen::Index& j ) const;

	/**
	 * @param available indices is the set of indices the pivot is allowed to pick in.
	 */
	bool selectDualBlandPivot( Eigen::Index& i, Eigen::Index& j, const std::vector<Eigen::Index> availableIndices );  //

	bool isPrimalFeasible() const;

	bool isDualFeasible() const;

	bool isOptimal() const;

	/**
	 * @brief is (i,j) the pivot given by the Bland's rule for the dictionary obtained by pivoting around (i,j).
	 */
	bool reverse( const Eigen::Index i, const Eigen::Index j );
	bool reverse_old( const Eigen::Index i, const Eigen::Index j );	 // before optimization

	bool reverseDual( const Eigen::Index i, const Eigen::Index j, const std::vector<Eigen::Index>& availableIndices );
	bool reverseDual_old( const Eigen::Index i, const Eigen::Index j, const std::vector<Eigen::Index> availableIndices );

	bool isLexMin();

	Point<Number> toPoint() const;

	/**
	 * @brief gives the list of the degenerated constrains in the dictionary.
	 */
	std::vector<Eigen::Index> findZeros();

	/**
	 * @brief put 1 in the last column for the indices provided by @param indices.
	 */
	void setOnes( const std::vector<Eigen::Index>& indices );

	void setZeros( const std::vector<Eigen::Index>& indices );

	/**
	 * @brief Puts the non slack variable to the basis.
	 */
	void nonSlackToBase();

	void nonSlackToBase( std::vector<vector_t<Number>>& linealtySpace );

	/**
	 * @brief Puts the saturated variable to the cobasis.
	 */
	std::set<Eigen::Index> toCobase( const std::set<Eigen::Index>& saturatedIndices );

	/**
	 * @brief Tries to push the corresponding variable to its bound, if another bound is reached before, pivot around the later.
	 */
	void pushToBounds( Eigen::Index colIndex );

	std::set<vector_t<Number>> findCones();

	friend bool operator==( const Dictionary<Number>& lhs, const Dictionary<Number>& rhs ) {
		if ( lhs.mB != rhs.mB ) {
			// std::cout << __func__ << " Basis not equal." << std::endl;
			return false;
		}

		if ( lhs.mN != rhs.mN ) {
			// std::cout << __func__ << " CoBasis not equal." << std::endl;
			return false;
		}

		if ( lhs.mConstrains != rhs.mConstrains ) {
			// std::cout << __func__ << " ConstraintSet not equal." << std::endl;
			return false;
		}

		if ( lhs.mDictionary != rhs.mDictionary ) {
			// std::cout << __func__ << " Tableau not equal." << std::endl;
			return false;
		}

		return true;
	}

	friend bool operator!=( const Dictionary<Number>& lhs, const Dictionary<Number>& rhs ) {
		return !( lhs == rhs );
	}

	friend std::ostream& operator<<( std::ostream& _ostr, const Dictionary<Number>& d ) {
		uint32_t i, j;
		_ostr << "\n mB size=";
		_ostr << d.basis().size();
		_ostr << "\n mN size=";
		_ostr << d.cobasis().size();
		_ostr << "\n mDictionary size=";
		_ostr << d.tableau().size();
		_ostr << "\n \n";

		_ostr << "mB = ";
		for ( i = 0; i < d.basis().size(); ++i ) {
			_ostr << d.basis()[i];
			_ostr << ";  ";
		}
		_ostr << "\nmN = ";
		for ( j = 0; j < d.cobasis().size(); ++j ) {
			_ostr << d.cobasis()[j];
			_ostr << ";  ";
		}
		_ostr << "\n \n";

		for ( i = 0; i < d.basis().size(); ++i ) {
			for ( j = 0; j < d.cobasis().size(); ++j ) {
				_ostr << d.tableau()( i, j );
				_ostr << " ; ";
			}
			_ostr << "\n";
		}
		_ostr.flush();
		return _ostr;
	}
};

}  // namespace hypro

#include "Dictionary.tpp"
