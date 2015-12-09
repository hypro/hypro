
#pragma once

#include "Dictionary.h"

#define FUKUDA_VERTEX_ENUM_DEBUG

namespace hypro {

template<typename Number>
class VertexEnumeration {
	private:
		matrix_t<Number> mSubstitution;
		std::vector<Dictionary<Number>> mDictionaries;

	public:
		VertexEnumeration() = default;
		VertexEnumeration(const VertexEnumeration<Number>& _orig) = default;

		VertexEnumeration(const matrix_t<Number>& A, const vector_t<Number>& b) {
			// initial creation of the optimal dictionary.

			matrix_t<Number> t = matrix_t<Number>(A.rows(), A.cols() + 1);
			t << b,-A;
			// rearrange to make the last d equations linear independent.
			t = rearrange(t);

			// solve the last d equations
			std::size_t dimension = A.cols();
			// Assumption: The last d equations of A are linear independent

			auto bottom = t.bottomRows(dimension);
			auto top = t.topRows(A.rows()-dimension);

			auto varBlock = bottom.rightCols(dimension);
			auto constPart = bottom.leftCols(1);

			// holds the variables we use later for the vertex computation.
			matrix_t<Number> tmp = matrix_t<Number>(varBlock);

			// a is required for solving the last d equations
			matrix_t<Number> a(tmp.rows(), 2*dimension+1);
			a << tmp, -constPart, matrix_t<Number>::Identity(dimension,dimension);

			//std::cout << "a: " << std::endl << a << std::endl;

			// Gauss:
			std::set<unsigned> usedRows;
			for(unsigned colIndex = 0; colIndex < dimension; ++colIndex)
			{
				//std::cout << "Eliminate for column " << colIndex << std::endl;
				unsigned rowIndex = 0;
				// find first row suitable for elimination
				while(rowIndex < a.rows() && (usedRows.find(rowIndex) != usedRows.end() || a(rowIndex,colIndex) == 0)) {
					++rowIndex;
				}

				//std::cout << "Use row " << rowIndex << " for elimination" << std::endl;
				if(rowIndex < a.rows() && a(rowIndex,colIndex) != 0){
					usedRows.insert(rowIndex);
					//normalize
					a.row(rowIndex) = a.row(rowIndex)/a(rowIndex,colIndex);
					for(unsigned rIt = 0; rIt < a.rows(); ++ rIt){
						if(rIt != rowIndex && a(rIt,colIndex) != 0) {
							// forward insertion
							a.row(rIt) = a.row(rIt) - (a.row(rowIndex)*a(rIt, colIndex));
						}
					}
				}
				//std::cout << a << std::endl;
			}

			// Substitution holds the matrix which contains the solution for the last d equations,
			// required for the vertex computation.
			auto substitutionBlock = a.rightCols(dimension+1);
			mSubstitution = matrix_t<Number>(a.rows(), dimension+1);
			mSubstitution << substitutionBlock;

			// creation of the actual dictionary from the top m-d rows
			matrix_t<Number> dictionaryMatrix = matrix_t<Number>(A.rows()-dimension + 1, dimension + 1);
			std::map<std::size_t, std::size_t> B;
			std::map<std::size_t, std::size_t> N;
			std::size_t F = A.rows()-A.cols();
			for(unsigned rI = 0; rI < top.rows(); ++rI)
			{
				dictionaryMatrix(rI,0) = top(rI,0);
				for(unsigned dI = 1; dI < top.cols(); ++dI)
				{
					dictionaryMatrix.row(rI) = dictionaryMatrix.row(rI) + (top(rI,dI) * substitutionBlock.row(dI-1));
				}
			}

			// Augment dictionaryMatrix by a row of -1s -> the f row
			matrix_t<Number> allOnes = matrix_t<Number>::Constant(1,dictionaryMatrix.cols(), Number(-1));
			allOnes(0) = Number(0);
			dictionaryMatrix.row(dictionaryMatrix.rows()-1) = allOnes;

			//std::cout << "Optimal dictionaryMatrix: " << dictionaryMatrix << std::endl;

			// create the mapping for the basic and non-basic variables (variable index maps to row/column index in the matrix).
			std::size_t colCnt = 0;
			for(unsigned index = 1; index < dictionaryMatrix.rows(); ++index) {
				B[index] = colCnt;
				++colCnt;
			}

			std::size_t rowCnt = 1;
			for(std::size_t index = dictionaryMatrix.rows() ; index < dictionaryMatrix.rows() + dimension ; ++index) {
				N[index] = rowCnt;
				++rowCnt;
			}

			Dictionary<Number> initial(dictionaryMatrix,B,N,F,std::size_t(0)); // G is the last parameter, which is always 0 at the moment.
			// check if the initial matrix represents a degenerate dictionary
			if(isDegenerate(initial))
				createInitialOptimalDictionaries(initial);
			else
				mDictionaries.push_back(std::move(initial));
		}

		std::vector<Point<Number>> search() {
			std::vector<Point<Number>> result;

			for(auto& dictionary : mDictionaries){
				#ifdef FUKUDA_VERTEX_ENUM_DEBUG
				std::cout << "Start search for dictionary " << std::endl;
				dictionary.print(true);
				#endif
				std::vector<Point<Number>> tmp = searchDictionary(dictionary);
				result.insert(result.end(), tmp.begin(), tmp.end());
			}

			return result;
		}

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
		std::vector<Point<Number>> searchDictionary (Dictionary<Number>& dict) {
			std::vector<Point<Number>> res;
			std::size_t i,j;
			i = 0;
			j = 1;

			std::size_t m = dict.tableau().rows()-1;

	#ifdef FUKUDA_VERTEX_ENUM_DEBUG
			std::size_t depth = 0;

			std::cout << "Level " << depth << ": Initial, optimal dictionary: " << std::endl;
			dict.print(true);
			std::cout << "Corresponding computed vertex: " << dict.vertex(mSubstitution) << std::endl;
			std::cout << "Is lexicographic minimum: " << dict.isLexMin() << std::endl;
	#endif
			if(dict.isLexMin())
				res.push_back(dict.vertex(mSubstitution));

			do {
				while(i <= m && !dict.isReverseCrissCrossPivot(i,j)) increment(i,j,dict.tableau().cols());
				if(i<m) {
					dict.pivot(i,j);
	#ifdef FUKUDA_VERTEX_ENUM_DEBUG
					std::cout << "Found reverse pivot -> step one level down." << std::endl;
					++depth;
					std::cout << "Level " << depth << ": Vertex dictionary after pivot (" << i << ", " << j << "): " << std::endl;
					dict.print(true);
					std::cout << "Corresponding computed vertex: " << dict.vertex(mSubstitution) << std::endl;
					std::cout << "Is lexicographic minimum: " << dict.isLexMin() << std::endl;
	#endif
					if(dict.isLexMin()){
						res.push_back(dict.vertex(mSubstitution));
					}
					i = 0;
					j = 1;
				} else {
					if (dict.selectCrissCrossPivot(i,j)) // we are at the root of the search tree and finished.
						break;
					dict.pivot(i,j);
	#ifdef FUKUDA_VERTEX_ENUM_DEBUG
					std::cout << "step one level up, consider next dictionaries." << std::endl;
					--depth;
					std::cout << "Level " << depth << ": Vertex dictionary after pivot (" << i << ", " << j << "): " << std::endl;
					dict.print(true);
	#endif
					increment(i,j,dict.tableau().cols());
				}
			} while ( i <= m && (dict.basis().find(m) == dict.basis().end() || dict.basis().at(m) != m) );

			return res;
		}


		~VertexEnumeration(){}

		const std::vector<Dictionary<Number>>& dictionaries() const {
			return mDictionaries;
		}

		bool isDegenerate(const Dictionary<Number>& dict) const {
			for(unsigned row = 0; row < dict.tableau().rows(); ++row){
				if(dict.tableau()(row, 0) == 0)
					return true;
			}
			return false;
		}

	private:

		void createInitialOptimalDictionaries(Dictionary<Number>& init) {

			// modify initial dictionary -> replace g by g' of all ones.

			// enumerate all dictionaries and emplace in search vector.
			std::size_t i,j;
			i = 0;
			j = 1;

			std::size_t m = init.tableau().rows()-1;

	#ifdef FUKUDA_VERTEX_ENUM_DEBUG
			std::size_t depth = 0;

			std::cout << "Level " << depth << ": Initial, optimal dictionary: " << std::endl;
			init.print(true);
			std::cout << "Is lexicographic minimum: " << init.isLexMin() << std::endl;
	#endif
			if(init.isLexMin())
				mDictionaries.push_back(init);

			do {
				while(i <= m && !init.isReverseDualBlandPivot(i,j)) increment(i,j,init.tableau().cols());
				if(i<m) {
					init.pivot(i,j);
	#ifdef FUKUDA_VERTEX_ENUM_DEBUG
					std::cout << "Found reverse pivot -> step one level down." << std::endl;
					++depth;
					std::cout << "Level " << depth << ": Vertex dictionary after pivot (" << i << ", " << j << "): " << std::endl;
					init.print(true);
					std::cout << "Is lexicographic minimum: " << init.isLexMin() << std::endl;
	#endif
					if(init.isLexMin()){
						mDictionaries.push_back(init);
					}
					i = 0;
					j = 1;
				} else {
					if (init.selectDualBlandPivot(i,j)) // we are at the root of the search tree and finished.
						break;
					init.pivot(i,j);
	#ifdef FUKUDA_VERTEX_ENUM_DEBUG
					std::cout << "step one level up, consider next dictionaries." << std::endl;
					--depth;
					std::cout << "Level " << depth << ": Vertex dictionary after pivot (" << i << ", " << j << "): " << std::endl;
					init.print(true);
	#endif
					increment(i,j,init.tableau().cols());
				}
			} while ( i <= m && (init.basis().find(m) == init.basis().end() || init.basis().at(m) != m) );
		}

		/**
		 * @brief Increments the row and column indices according to the current dictionary (traverse row-wise).
		 *
		 * @param i Row index.
		 * @param j Column index.
		 */
		void increment(std::size_t& i, std::size_t& j, std::size_t cols) const {
			++j;
			if( j == cols) {
				j = 1;
				++i;
			}
		}

		matrix_t<Number> rearrange(const matrix_t<Number>& A) {
			if(A.rows() <= A.cols()) {
				// This should not happen.
				return A;
			}

			matrix_t<Number> copy(A);
			matrix_t<Number> res(A);
			std::size_t dimension = copy.cols();

			// perform Gauss on A to get the linear independent rows

			std::set<unsigned> linearIndependent;
			std::set<unsigned> linearDependent;
			for(unsigned colIndex = 0; colIndex < dimension; ++colIndex)
			{
				//std::cout << "Eliminate for column " << colIndex << std::endl;
				unsigned rowIndex = 0;
				// find first row suitable for elimination
				//std::cout << linearIndependent << std::endl;
				while(rowIndex < copy.rows() && (linearIndependent.find(rowIndex) != linearIndependent.end() || copy(rowIndex,colIndex) == 0)) {
					++rowIndex;
				}

				//std::cout << "Use row " << rowIndex << " for elimination" << std::endl;
				if(rowIndex < copy.rows() && copy(rowIndex,colIndex) != 0){
					linearIndependent.insert(rowIndex);
					//normalize
					copy.row(rowIndex) = copy.row(rowIndex)/copy(rowIndex,colIndex);
					for(unsigned rIt = 0; rIt < copy.rows(); ++ rIt){

						if(rIt != rowIndex && copy(rIt,colIndex) != 0) {
							// forward insertion
							copy.row(rIt) = copy.row(rIt) - (copy.row(rowIndex)*copy(rIt, colIndex));
						}
					}
				}
			}

			//std::cout << "Copy: " << std::endl << copy << std::endl;

			// collect linear dependent rows
			for(unsigned rIt = 0; rIt < copy.rows(); ++rIt){
				if(linearIndependent.find(rIt) == linearIndependent.end()) {
					linearDependent.insert(rIt);
				}
			}

			assert(linearIndependent.size() == dimension);
			assert(linearDependent.size() == A.rows() - dimension);
			if(linearIndependent.size() != dimension) {
				// no proper dimension! WHAT TO DO?
			} else {
				// move the linearly independent columns to the bottom of the matrix
				for(unsigned row = 0; row < res.rows(); ++row){
					if(row >= A.rows()-dimension) {
						res.row(row) = A.row(*linearIndependent.begin());
						linearIndependent.erase(linearIndependent.begin());
					} else {
						res.row(row) = A.row(*linearDependent.begin());
						linearDependent.erase(linearDependent.begin());
					}
				}
			}

			return res;
		}

	};

} // namespace