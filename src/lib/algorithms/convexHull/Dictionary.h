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
#include "../../datastructures/Point.h"
#include "../../datastructures/Halfspace.h"
#include "ConstrainSet.h"

#define FUKUDA_VERTEX_ENUM_DEBUG
#define DICT_DBG

namespace hypro {

template<typename Number>
class Dictionary {
private:
	matrix_t<Number> 	mDictionary;
	std::vector<std::size_t> mB;
	std::vector<std::size_t> mN;
	ConstrainSet<Number> mConstrains;

public:
	Dictionary() = default;
	Dictionary(const Dictionary& rhs);
	Dictionary(const matrix_t<Number>& rhs, std::vector<std::size_t> base, std::vector<std::size_t> cobase);
	Dictionary(const matrix_t<Number>& rhs, std::vector<std::size_t> base, std::vector<std::size_t> cobase, ConstrainSet<Number> constrains);
	/**
	 * @brief Build a dictionary with mDictionary=rhs, mB=base and mN=cobase.
	 */

	Dictionary(const std::vector<Halfspace<Number>>& hsv);
	/**
	 * @brief Build a dictionary based on the hyperplane set hsv.
	 */

	std::vector<std::size_t> basis() const;

	std::vector<std::size_t> cobasis() const;

	ConstrainSet<Number> constrainSet() const;

	matrix_t<Number> tableau() const;

	Number get (std::size_t i,std::size_t j) const;
	/**
	 * @return the number in the cell (i,j) of mDictionary.
	 */

	void setValue(std::size_t i, std::size_t j, Number val);
	/**
	 * @brief set mDicionary(i,j) to val.
	 */

	void printDictionary() const;

	void pivotDictionary(std::size_t i, std::size_t j);

	/**
	 * @brief Pivot expected ‘)’ before ‘<’ tokenthe dictionary, no modification made to mB and mN.
	 */

	void pivot(std::size_t i, std::size_t j);
	/**
	 * @brief The whole pivot.
	 */

	bool selectCrissCrossPivot(std::size_t& i, std::size_t& j);
	/**
	 * @brief Selects the next pivot according to CrissCross's rule.
	 *
	 * @param i The reference for the proposed row index.
	 * @param j The reference for the proposed column index.
	 *
	 * @return True, if there is a valid pivot.
	 */

	bool fixOutOfBounds();
	/**
	 * @brief Check for the satisfiability of the dictionary and finds a sutable assignement
	 */

	bool selectBlandPivot(std::size_t& i, std::size_t& j) const;
	/**
	 * @brief Puts in i and j the pivot, returns false iff none was sutable.
	 */

	bool selectDualBlandPivot(std::size_t& i, std::size_t& j, const std::vector<std::size_t> availableIndices);//
	/**
	 * @param available indices is the set of indices the pivot is allowed to pick in.
	 */

	bool isPrimalFeasible();

	bool isDualFeasible();

	bool reverse(const std::size_t i, const std::size_t j);
	bool reverse_old(const std::size_t i, const std::size_t j);//before optimization
	/**
	 * @brief is (i,j) the pivot given by the Bland's rule for the dictionary obtained by pivoting around (i,j).
	 */

	bool reverseDual(const std::size_t i, const std::size_t j, const std::vector<std::size_t>& availableIndices);
	bool reverseDual_old(const std::size_t i, const std::size_t j, const std::vector<std::size_t> availableIndices);

	bool isLexMin();

	Point<Number> toPoint() const;

	std::vector<std::size_t> findZeros();
	/**
	 * @brief gives the list of the degenerated constrains in the dictionary.
	 */
	void setOnes(const std::vector<std::size_t>& indices);
	/**
	 * @brief put 1 in the last column for the indices provided by @param indices.
	 */

	void setZeros(const std::vector<std::size_t>& indices);

	void nonSlackToBase();
	/**
	 * @brief Puts the non slack variable to the basis.
	 */
	void nonSlackToBase(std::vector<vector_t<Number>>& linealtySpace);

	std::set<std::size_t> toCobase(const std::set<std::size_t> saturatedIndices);
	/**
	 * @brief Puts the saturated variable to the cobasis.
	 */


	void pushToBounds(std::size_t colIndex);
	/**
	 * @brief Tries to push the corresponding variable to its bound, if another bound is reached before, pivot around the later.
	 */

	std::set<vector_t<Number>> findCones();

	friend bool operator==(const Dictionary<Number>& lhs, const Dictionary<Number>& rhs) {
		if(lhs.mB != rhs.mB) {
			//std::cout << __func__ << " Basis not equal." << std::endl;
 			return false;
		}

		if(lhs.mN != rhs.mN) {
			//std::cout << __func__ << " CoBasis not equal." << std::endl;
			return false;
		}

		if(lhs.mConstrains != rhs.mConstrains) {
			//std::cout << __func__ << " ConstraintSet not equal." << std::endl;
			return false;
		}

		if(lhs.mDictionary != rhs.mDictionary) {
			//std::cout << __func__ << " Tableau not equal." << std::endl;
			return false;
		}

		return true;
	}

	friend bool operator!=(const Dictionary<Number>& lhs, const Dictionary<Number>& rhs) {
		return !(lhs==rhs);
	}
};

} // namespace hypro

#include "Dictionary.tpp"
