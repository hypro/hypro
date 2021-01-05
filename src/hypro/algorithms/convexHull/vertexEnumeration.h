#pragma once

#include "../../util/sequenceGeneration/SequenceGenerator.h"
#include "Dictionary.h"

#include <string>

namespace hypro {

template <typename Number>
class VertexEnumeration {
  private:
	std::vector<Halfspace<Number>> mHsv;
	std::vector<Dictionary<Number>> mDictionaries;
	std::vector<Point<Number>> mPositivePoints;
	matrix_t<Number> mPivotingMatrix;
	vector_t<Number> mOffset;
	std::vector<Point<Number>> mPoints;
	std::vector<vector_t<Number>> mLinealtySpace;
	std::set<vector_t<Number>> mPositiveCones;
	std::vector<vector_t<Number>> mCones;

  public:
	VertexEnumeration() = default;
	VertexEnumeration( const VertexEnumeration<Number>& _orig ) = default;
	VertexEnumeration( const std::vector<Halfspace<Number>>& hsv );
	VertexEnumeration( const matrix_t<Number>& constraints, const vector_t<Number>& constants );
	~VertexEnumeration() = default;

	const std::vector<Halfspace<Number>>& getHsv() const;

	const std::vector<Dictionary<Number>>& getDictionaries() const;

	const std::vector<Point<Number>>& getPositivePoints() const;
	void printPositivePoints() const;

	const std::vector<Point<Number>>& getPoints() const;
	void printPoints() const;

	const std::vector<vector_t<Number>>& getLinealtySpace() const;
	void printLinealtySpace() const;

	const std::vector<vector_t<Number>>& getPositiveCones() const;
	void printPositiveCones() const;

	const std::vector<vector_t<Number>>& getCones() const;
	void printCones() const;

	void increment( Eigen::Index& i, Eigen::Index& j, std::size_t maxJ );

	/**
		 * @brief does everything with the halfspaces in mHsv
		 */
	void enumerateVertices();

	/**
		 * @brief create vertices by permutating all d-combinations of half-spaces.
		 */
	void enumerateVerticesNaive();

	/**
		 * @brief find all the vertices obtained from a given dictionary acording to Fukuda's algorithm.
		 */
	void enumerateVertices( Dictionary<Number>& dictionary );

	/**
		 * @brief enumerate all the vertices of the dictionaries in mDictionaries.
		 */
	void enumerateVerticesEachDictionary();

	/**
		 * @brief Finds all the optimal dictionaries from the first one in mDictionaries.
		 */
	void enumerateDictionaries();

	/**
		 * @brief Finds a fist vertex, detects the linealty spaces and adds the corresponding constrains.
		 */
	Dictionary<Number> findFirstVertex();

	/**
		 * @brief If the candidate is independent from the collection, returns the smallest non nul coordinate,
		 * -1 otherwise.
		 */
	int linearIndependance( std::map<int, vector_t<Number>> collection, vector_t<Number>& candidateRef ) const;	 //not used

	/**
		 * @return A set of the index of d independent hyperplanes of mHsv.
		 */
	std::vector<std::size_t> findIndepHs() const;  //not used

	/**
		 * @return the intersection of the hyperplanes in selectionRef.
		 */
	Point<Number> findIntersection( const std::vector<std::size_t>& selectionRef ) const;  //not used

	/**
		 * @brief Transform Ax<=b into A'y<=b' & y>=0.
		 */
	bool findPositiveConstrains();

	/**
		 * @brief Converts the positive cones and points into the original system of coordinates.
		 */
	void toGeneralCoordinates();

	void findLinealtySpace();  //not used

	/**
		 * @brief Adds to halfspace set two halfspaces for each linealty direction to block it.
		 */
	void addLinealtyConstrains();
};
}  // namespace hypro

#include "vertexEnumeration.tpp"
