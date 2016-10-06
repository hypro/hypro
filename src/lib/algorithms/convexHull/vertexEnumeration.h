#pragma once

#include "Dictionary.h"
#include "util/Permutator.h"

namespace hypro {

template<typename Number>
class VertexEnumeration {
	private:
		std::vector<Halfspace<Number>> mHsv;
		std::vector<Dictionary<Number>> mDictionaries;
		std::vector<Point<Number>> mPositivePoints;
		matrix_t<Number> 	mPivotingMatrix;
		vector_t<Number> 	mOffset;
		std::vector<Point<Number>> mPoints;
		std::vector<vector_t<Number>> mLinealtySpace;
		std::set<vector_t<Number>> mPositiveCones;
		std::vector<vector_t<Number>> mCones;

	public:
		VertexEnumeration() = default;
		VertexEnumeration(const VertexEnumeration<Number>& _orig) = default;
		~VertexEnumeration() = default;

		std::vector<Halfspace<Number>> getHsv() const;

		std::vector<Dictionary<Number>> getDictionaries() const;

		std::vector<Point<Number>> getPositivePoints() const;
		void printPositivePoints() const;

		std::vector<Point<Number>> getPoints() const;
		void printPoints() const;

		std::vector<vector_t<Number>> getLinealtySpace() const;
		void printLinealtySpace() const;

		std::vector<vector_t<Number>> getPositiveCones() const;
		void printPositiveCones() const;

		std::vector<vector_t<Number>> getCones() const;
		void printCones() const;

		void increment(std::size_t& i, std::size_t& j, std::size_t maxJ);

		void enumerateVertices();
		/**
		 * @brief does everything with the halfspaces in mHsv
		 *
		 */

		void enumerateVerticesNaive();

		VertexEnumeration(const std::vector<Halfspace<Number>>& hsv);
		/**
		 * @brief mHsv:=hsv
		 */

		VertexEnumeration(const matrix_t<Number>& constraints, const vector_t<Number>& constants);

		void enumerateVertices(Dictionary<Number>& dictionary);
		/**
		 * @brief find all the vertices obtained from a given dictionary acording to Fukuda's algorithm.
		 */

		void enumerateVerticesEachDictionary();
		/**
		 * @brief enumerate all the vertices of the dictionaries in mDictionaries.
		 */

		void enumerateDictionaries();
		/**
		 * @brief Finds all the optimal dictionaries from the first one in mDictionaries.
		 */

		Dictionary<Number> findFirstVertex();
		/**
		 * @brief Finds a fist vertex, detects the linealty spaces and adds the corresponding constrains.
		 */

		int linearIndependance(std::map<int,vector_t<Number>> collection, vector_t<Number>& candidateRef) const;//not used
		/**
		 * @brief If the candidate is independent from the collection, returns the smallest non nul coordinate,
		 * -1 otherwise.
		 */

		std::vector<std::size_t> findIndepHs() const;//not used
		/**
		 * @return A set of the index of d independent hyperplanes of mHsv.
		 */

		Point<Number> findIntersection(const std::vector<std::size_t>& selectionRef) const;//not used
		/**
		 * @return the intersection of the hyperplanes in selectionRef.
		 */

		bool findPositiveConstrains();
		/**
		 * @brief Transform Ax<=b into A'y<=b' & y>=0.
		 */

		void toGeneralCoordinates();
		/**
		 * @brief Converts the positive cones and points into the original system of coordinates.
		 */

		void findLinealtySpace();//not used

		void addLinealtyConstrains();
		/**
		 * @brief Adds to halfspace set two halfspaces for each linealty direction to block it.
		 */
	};
} // namespace hypro

#include "vertexEnumeration.tpp"
