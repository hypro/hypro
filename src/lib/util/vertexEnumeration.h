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

#include "../config.h"
#include "../datastructures/Point.h"

//#define FUKUDA_VERTEX_ENUM_DEBUG

namespace hypro {

template<typename Number>
class Dictionary {
private:
	matrix_t<Number> 	mDictionary;
	std::size_t			mF;
	std::size_t			mG;
	std::map<std::size_t, std::size_t> mB;
	std::map<std::size_t, std::size_t> mN;
	matrix_t<Number> 	mSubstitution;

public:
	Dictionary() = default;
	Dictionary(const Dictionary& rhs);

	/**
	 * @brief Constructs a dictionary from a given halfspace arrangement. Note: The constructor already creates an optimal dictionary.
	 *
	 * @param A Matrix holding the constraints.
	 * @param b Vector holding the constants.
	 */
	Dictionary(const matrix_t<Number>& A, const vector_t<Number>& b);

	/**
	 * @brief Getter for the current dictionary.
	 *
	 * @return
	 */
	inline const matrix_t<Number>& dictionary() const;

	/**
	 * @brief Getter for the current basis variable map (variableIndex -> rowIndex)
	 *
	 * @return
	 */
	inline const std::map<std::size_t, std::size_t>& basis() const;

	/**
	 * @brief Getter for the current slack variable map (variableIndex -> columnIndex)
	 *
	 * @return
	 */
	inline const std::map<std::size_t, std::size_t>& cobasis() const;

	/**
	 * @brief Computes the vertex which is represented by the current dictionary.
	 * @details The computation makes use of the last d equations from the original problem.
	 * Solving these equations for the last d variables results in the "substitution block".
	 * The computation of a vertex utilizes this block as well as the current dictionary:
	 * The variables in the substitution block are set to either 0 (if the variable is a non-basic
	 * variable in the current dictionary) or to a_ig (if the variable is at row i and thus a basic
	 * variable).
	 *
	 * @return
	 */
	Point<Number> vertex() const;

	/**
	 * @brief The main loop for the vertex enumeration algorithm, which should be called on the initial, optimal dictionary.
	 * @details This loop starts at the initial optimal dictionary. It iterates over the rows and columns of the dictionary and
	 * searches for a valid reverse-pivot. Having found this, it continues the search for this valid reverse-pivot ("step one level down")
	 * and starts all over for the resulting dictionary. When all possible combinations for one dictionary are searched (thus, the
	 * algorithm implements a depth-first search), a pivoting step is performed ("step one level up"), which results in a dictionary
	 * already found (as we only search in valid reverse-pivots) or if we are at the root, there is no possible pivot as the dictionary
	 * is already optimal (the search is complete). On its way through the search tree all dictionaries, which are lexicographically minimal
	 * are used to compute a vertex of the hyperplane arrangement.
	 *
	 * @return
	 */
	std::vector<Point<Number>> search ();

	/**
	 * @brief Determines, whether the current basis variables are the lexicographic minimal basis for the vertex.
	 * This function can be used to output degenerate vertices only once.
	 *
	 * @return
	 */
	bool isLexMin() const;

	/**
	 * @brief Checks whether the proposed pivot is a valid reverse-pivot.
	 * @details Currently this check performs the pivot and checks, whether the result of the function selectCrissCrossPivot results
	 * in the original dictionary.
	 *
	 * @param i Row index.
	 * @param j Column index.
	 *
	 * @return
	 */
	bool isReverseCrissCrossPivot(std::size_t i, std::size_t j) const;

	/**
	 * @brief Selects the next possible criss cross pivot taking account of the variable order.
	 * @details The method currently (as the whole algorithm) uses criss-cross pivoting for its search strategy. Another
	 * option is to make use of Bland's rule as in the original simplex algorithm.
	 *
	 * @param i The reference for the proposed row index.
	 * @param j The reference for the proposed column index.
	 *
	 * @return True, if the dictionary is optimal, i.e. there is no valid pivot.
	 */
	bool selectCrissCrossPivot(std::size_t& i, std::size_t& j) const;

	/**
	 * @brief Performs a pivoting step with the passed row and column index. Afterwards the dictionary is sorted and the row and column
	 * index are updated accordingly.
	 *
	 * @param i Row index.
	 * @param j Column index.
	 */
	void pivot(std::size_t& i, std::size_t& j);

	inline Dictionary<Number>& operator=(const Dictionary<Number>& rhs);
	inline bool operator==(const Dictionary<Number>& rhs) const;
	inline bool operator!=(const Dictionary<Number>& rhs) const { return !(*this == rhs); };

	void print(bool pretty = false) const;
private:

	/**
	 * @brief Moves a row from originalPos to insertionPos shifting all intermediate rows accordingly.
	 *
	 * @param originalPos
	 * @param insertionPos
	 */
	void insertRowAtPosition(const std::size_t& originalPos, const std::size_t& insertionPos);

	/**
	 * @brief Moves a column from originalPos to insertionPos shifting all intermediate rows accordingly.
	 *
	 * @param originalPos
	 * @param insertionPos
	 */
	void insertColAtPosition(const std::size_t& originalPos, const std::size_t& insertionPos);

	/**
	 * @brief Rearranges the initial input to ensure that the last d rows are linearly independent.
	 */
	matrix_t<Number> rearrange(const matrix_t<Number>& A);

	/**
	 * @brief Increments the row and column indices according to the current dictionary (traverse row-wise).
	 *
	 * @param i Row index.
	 * @param j Column index.
	 */
	void increment(std::size_t& i, std::size_t& j) const;
};

template<typename Number>
std::ostream& operator<<(std::ostream& _out, const Dictionary<Number>& _dict) {
	_out << _dict.dictionary() << std::endl;
	_out << "Basis:   " <<_dict.basis() << std::endl;
	_out << "CoBasis: " << _dict.cobasis() << std::endl;
	return _out;
}

} // namespace hypro

#include "vertexEnumeration.tpp"