#pragma once

#include "Dictionary.h"

#define FUKUDA_VERTEX_ENUM_DEBUG

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
		
		std::vector<Halfspace<Number>> getHsv() const;
		
		std::vector<Dictionary<Number>> getDictionaries() const;
		
		std::vector<Point<Number>> getPositivePoints() const;
		
		std::vector<Point<Number>> getPoints() const;
		
		std::vector<vector_t<Number>> getLinealtySpace() const;
	
		std::vector<vector_t<Number>> getPositiveCones() const;
	
		std::vector<vector_t<Number>> getCones() const;
		
		void increment(unsigned& i, unsigned& j, unsigned maxJ);
		
		void enumerateVertices();
		
		VertexEnumeration(const std::vector<Halfspace<Number>>& hsv);
		/**
		 * @brief mHsv=hsv, put the associated optimal dictionary in mDictionaries.
		 */
		 
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
		
		int linearIndependance(std::map<int,vector_t<Number>> collection, vector_t<Number>& candidateRef) const;
		/**
		 * @brief If the candidate is independant from the collection, returns the smallest non nul coordinate,
		 * -1 otherwise.
		 */
		
		std::vector<unsigned> findIndepHs() const;
		/**
		 * @return A set of the iDictionary<Number>ndex of d independant hyperplanes of mHsv.
		 */
		
		Point<Number> findIntersection(const std::vector<unsigned>& selectionRef) const;
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
		
		void findLinealtySpace();
		
		void addLinealtyConstrains();
		/**
		 * @brief Adds to halfspace set two halfspaces for each linealty direction to block it.
		 */
	};
} // namespace

#include "vertexEnumeration.tpp"
