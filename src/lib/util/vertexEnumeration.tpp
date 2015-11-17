#include "vertexEnumeration.h"

namespace hypro {

	template<typename Number>
	Dictionary<Number>::Dictionary(const Dictionary& rhs) :
		mDictionary(rhs.dictionary()),
		mF(mDictionary.rows()-1),
		mG(0),
		mB(rhs.basis()),
		mN(rhs.cobasis()),
		mSubstitution()
	{}

	template<typename Number>
	Dictionary<Number>::Dictionary (const matrix_t<Number>& A, const vector_t<Number>& b) :
		mDictionary(),
		mF(A.rows()-A.cols()),
		mG(0)
	{
		// Note: This is the constructor, which should be used, as it creates the optimal dictionary.

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

		// Gauss:
		// normalize rows for each variable and forward insertion
		for(unsigned rowIndex = 0; rowIndex < a.rows()-1; ++rowIndex)
		{
			a.row(rowIndex) = a.row(rowIndex)/a(rowIndex,rowIndex);
			a.row(rowIndex+1) = a.row(rowIndex+1) - (a.row(rowIndex)*a(rowIndex+1, rowIndex));
		}

		// backward insertion
		for(unsigned rowIndex = a.rows()-1; rowIndex > 0; --rowIndex)
		{
			if(a(rowIndex,rowIndex) != 1)
			{
				a.row(rowIndex) = a.row(rowIndex) / a(rowIndex,rowIndex);
			}
			a.row(rowIndex-1) = a.row(rowIndex-1) - (a.row(rowIndex)*a(rowIndex-1, rowIndex));
		}

		// Substitution holds the matrix which contains the solution for the last d equations,
		// required for the vertex computation.
		auto substitutionBlock = a.rightCols(dimension+1);
		mSubstitution = matrix_t<Number>(a.rows(), dimension+1);
		mSubstitution << substitutionBlock;

		// creation of the actual dictionary from the top m-d rows
		mDictionary = matrix_t<Number>(A.rows()-dimension + 1, dimension + 1);
		for(unsigned rI = 0; rI < top.rows(); ++rI)
		{
			mDictionary(rI,0) = top(rI,0);
			for(unsigned dI = 1; dI < top.cols(); ++dI)
			{
				mDictionary.row(rI) = mDictionary.row(rI) + (top(rI,dI) * substitutionBlock.row(dI-1));
			}
		}

		// Augment dictionary by a row of -1s -> the f row
		matrix_t<Number> allOnes = matrix_t<Number>::Constant(1,mDictionary.cols(), Number(-1));
		allOnes(0) = Number(0);
		mDictionary.row(mDictionary.rows()-1) = allOnes;

		//std::cout << "Optimal dictionary: " << mDictionary << std::endl;

		// create the mapping for the basic and non-basic variables (variable index maps to row/column index in the matrix).
		std::size_t colCnt = 0;
		for(unsigned index = 1; index < mDictionary.rows(); ++index) {
			mB[index] = colCnt;
			++colCnt;
		}

		std::size_t rowCnt = 1;
		for(std::size_t index = mDictionary.rows() ; index < mDictionary.rows() + dimension ; ++index) {
			mN[index] = rowCnt;
			++rowCnt;
		}
	}

	template<typename Number>
	const matrix_t<Number>& Dictionary<Number>::dictionary() const {
		return mDictionary;
	}

	template<typename Number>
	const std::map<std::size_t, std::size_t>& Dictionary<Number>::basis() const {
		return mB;
	}

	template<typename Number>
	const std::map<std::size_t, std::size_t>& Dictionary<Number>::cobasis() const {
		return mN;
	}

	template<typename Number>
	Point<Number> Dictionary<Number>::vertex() const {
		vector_t<Number> valuation = vector_t<Number>(mN.size() + 1);
		valuation(0) = 1;
		for(unsigned i = 1; i < valuation.rows(); ++i) {
			unsigned varIndex = mB.size() + i ;

			if(mB.find(varIndex) != mB.end()) {
				valuation(i) = mDictionary(mB.at(varIndex),mG);
			} else {
				valuation(i) = 0;
			}
		}

		std::cout << __func__ << mSubstitution << std::endl << __func__ << valuation << std::endl;

		return Point<Number>(mSubstitution*valuation);
	}

	template<typename Number>
	std::vector<Point<Number>> Dictionary<Number>::search () {
		std::vector<Point<Number>> res;
		std::size_t i,j;
		i = 0;
		j = 1;

		std::size_t m = mDictionary.rows()-1;

#ifdef FUKUDA_VERTEX_ENUM_DEBUG
		std::size_t depth = 0;

		std::cout << "Level " << depth << ": Initial, optimal dictionary: " << std::endl;
		print(true);
		std::cout << "Corresponding computed vertex: " << vertex() << std::endl;
		std::cout << "Is lexicographic minimum: " << isLexMin() << std::endl;
#endif
		if(isLexMin())
			res.push_back(vertex());

		do {
			while(i <= m && !isReverseCrissCrossPivot(i,j)) increment(i,j);
			if(i<m) {
				pivot(i,j);
#ifdef FUKUDA_VERTEX_ENUM_DEBUG
				std::cout << "Found reverse pivot -> step one level down." << std::endl;
				++depth;
				std::cout << "Level " << depth << ": Vertex dictionary after pivot (" << i << ", " << j << "): " << std::endl;
				print(true);
				std::cout << "Corresponding computed vertex: " << vertex() << std::endl;
				std::cout << "Is lexicographic minimum: " << isLexMin() << std::endl;
#endif
				if(isLexMin()){
					res.push_back(vertex());
				}
				i = 0;
				j = 1;
			} else {
				if (selectCrissCrossPivot(i,j)) // we are at the root of the search tree and finished.
					break;
				pivot(i,j);
#ifdef FUKUDA_VERTEX_ENUM_DEBUG
				std::cout << "step one level up, consider next dictionaries." << std::endl;
				--depth;
				std::cout << "Level " << depth << ": Vertex dictionary after pivot (" << i << ", " << j << "): " << std::endl;
				print(true);
#endif
				increment(i,j);
			}
		} while ( i <= m && (mB.find(m) == mB.end() || mB.at(m) != m) );

		return res;
	}

	template<typename Number>
	bool Dictionary<Number>::isLexMin() const {
		auto basisIt = mB.begin();
		auto cobasisIt = mN.begin();

		while(cobasisIt != mN.end()){
			while(basisIt != mB.end()) {
				if(basisIt->first > cobasisIt->first && mDictionary(basisIt->second, mG) == 0 && mDictionary(basisIt->second, cobasisIt->second) != 0) {
					return false;
				} else {
					++basisIt;
				}
			}
			basisIt = mB.begin();
			++cobasisIt;
		}

		return true;
	}

	template<typename Number>
	bool Dictionary<Number>::isReverseCrissCrossPivot(std::size_t i, std::size_t j) const {
		std::size_t s,r;

		if(i >= (std::size_t) mDictionary.rows()-1){
#ifdef FUKUDA_VERTEX_ENUM_DEBUG
			std::cout << "Invalid indices." << std::endl;
#endif
			return false;
		}

		if(mDictionary(i,j) == 0) {
#ifdef FUKUDA_VERTEX_ENUM_DEBUG
			std::cout << "Not usable for pivot (table entry=0)." << std::endl;
#endif
			return false;
		}

#ifdef FUKUDA_VERTEX_ENUM_DEBUG
		std::cout << __func__ << " i " << i << ", j " << j << std::endl;
#endif

		auto sIt = mB.begin();
		while(sIt->second != i) ++sIt;
		s = sIt->first;

		auto rIt = mN.begin();
		while(rIt->second != j) ++rIt;
		r = rIt->first;

		Dictionary<Number> tmp(*this);
		std::size_t tmpI = i;
		std::size_t tmpJ = j;
		tmp.pivot(tmpI,tmpJ);
		//std::cout << "Tmp after proposed pivot:" << std::endl;
		//tmp.print(true);

		std::size_t newI,newJ;
		bool optimal = tmp.selectCrissCrossPivot(newI, newJ);

#ifdef FUKUDA_VERTEX_ENUM_DEBUG
		std::cout << "i: " << i << ", j: " << j << std::endl;
		std::cout << "r: " << r << ", s: " << s << std::endl;
#endif
		if(optimal) {
			return false;
		}

		std::size_t newS,newR;

		auto nsIt = tmp.basis().begin();
		while(nsIt->second != newI) ++nsIt;
		newS = nsIt->first;

		auto nrIt = tmp.cobasis().begin();
		while(nrIt->second != newJ) ++nrIt;
		newR = nrIt->first;

		if(newS == r && newR == s) {
			return true;
		} else {
			return false;
		}
	}

	template<typename Number>
	bool Dictionary<Number>::selectCrissCrossPivot(std::size_t& i, std::size_t& j) const {
		// step 1: Find smallest index i s.th. i primal or dual infeasible
		bool primalInfeasible = false;
		bool dualInfeasible = false;
		std::size_t index = 0;
		for(; index <= (std::size_t) mDictionary.rows()+mDictionary.cols()-2; ++index) {
			if(mB.find(index) != mB.end() && mDictionary(mB.at(index), mG) < 0) {
				primalInfeasible = true;
				break;
			}

			if(mN.find(index) != mN.end() && mDictionary(mF, mN.at(index)) > 0) {
				dualInfeasible = true;
				break;
			}
		}

		// step 2: Select other variable accordingly
		if(primalInfeasible) {
			assert(mB.find(index) != mB.end());
			for(auto cobasisIt = mN.begin(); cobasisIt != mN.end(); ++cobasisIt) {
				if(mDictionary(mB.at(index), cobasisIt->second) > 0) {
					i = mB.at(index);
					j = cobasisIt->second;
					break;
				}
			}
#ifdef FUKUDA_VERTEX_ENUM_DEBUG
			std::cout << __func__ << ": " << i << ", " << j << std::endl;
#endif
			return false;
		} else if (dualInfeasible) {
			assert(mN.find(index) != mN.end());

			for(auto basisIt = mB.begin(); basisIt != mB.end(); ++basisIt) {
				if(mDictionary(basisIt->second, mN.at(index)) < 0) {
					i = basisIt->second;
					j = mN.at(index);
					break;
				}
			}
#ifdef FUKUDA_VERTEX_ENUM_DEBUG
			std::cout << __func__ << ": " << i << ", " << j << std::endl;
#endif
			return false;
		}

		// Dictionary is optimal - no feasible pivot
#ifdef FUKUDA_VERTEX_ENUM_DEBUG
		std::cout << __func__ << ": No feasible pivot." << std::endl;
#endif
		return true;
	}

	template<typename Number>
	void Dictionary<Number>::pivot(std::size_t& i, std::size_t& j) {
		// update other cells
		for(unsigned colIndex = 0; colIndex < mDictionary.cols(); ++colIndex) {
			for(unsigned rowIndex = 0; rowIndex < mDictionary.rows(); ++rowIndex) {
				if(rowIndex != i && colIndex != j)
					mDictionary(rowIndex, colIndex) = mDictionary(rowIndex, colIndex) - ( mDictionary(rowIndex, j)* mDictionary(i, colIndex) ) / mDictionary(i,j);
			}
		}

		// update row
		for(unsigned colIndex = 0; colIndex < mDictionary.cols(); ++colIndex) {
			if(colIndex != j)
				mDictionary(i, colIndex) = - mDictionary(i, colIndex) / mDictionary(i,j);
		}

		// update col
		for(unsigned rowIndex = 0; rowIndex < mDictionary.rows(); ++rowIndex) {
			if(rowIndex != i)
				mDictionary(rowIndex,j) = mDictionary(rowIndex, j) / mDictionary(i,j);
		}

		// update cell
		mDictionary(i,j) = Number(1) / mDictionary(i,j);

		// update position mapping
		std::size_t r;
		std::size_t s;
		for(auto& pair : mB) {
			if(pair.second == i){
				r = pair.first;
				break;
			}
		}
		for(auto& pair : mN) {
			if(pair.second == j){
				mB.erase(r);
				mB[pair.first] = i;
				s = pair.first;
				mN.erase(pair.first);
				mN[r] = j;
				break;
			}
		}

		// rearrange dictionary (sort variable indices ascending)
		auto basisIt = mB.begin();
		std::size_t rowCnt = 0;
		while(basisIt->first != s) {++basisIt; ++rowCnt;}
		if(i != rowCnt) {
			//std::cout << "Move row " << i << " to Position " << rowCnt << std::endl;
			insertRowAtPosition(i,rowCnt);
		}

		auto cobasisIt = mN.begin();
		std::size_t colCnt = 1;
		while(cobasisIt->first != r) {++cobasisIt; ++colCnt;}
		if(j != colCnt) {
			//std::cout << "Move col " << j << " to Position " << colCnt << std::endl;
			insertColAtPosition(j,colCnt);
		}

		// update i and j
		i = rowCnt;
		j = colCnt;
	}

	template<typename Number>
	void Dictionary<Number>::insertRowAtPosition(const std::size_t& originalPos, const std::size_t& insertionPos) {
		matrix_t<Number> newDict = mDictionary;
		if(originalPos < insertionPos){
			auto tmpRow = newDict.row(originalPos);
			for(std::size_t rowIndex = 0; rowIndex < std::size_t(newDict.rows()); ++rowIndex) {
				if (rowIndex >= originalPos && rowIndex < insertionPos) {
					//std::cout << "Shift at index " << rowIndex << std::endl;
					mDictionary.row(rowIndex) = newDict.row(rowIndex + 1);
				} else if (rowIndex == insertionPos) {
					//std::cout << "Insert original row at index " << rowIndex << std::endl;
					mDictionary.row(rowIndex) = tmpRow;
				}
			}
			// update mapping
			std::map<std::size_t, std::size_t> newMap;
			for(auto basisIt = mB.begin(); basisIt != mB.end(); ++basisIt) {
				if(basisIt->second == originalPos) {
					//std::cout << "Var " << basisIt->first << " is remapped to pos " << insertionPos << std::endl;
					std::size_t var = basisIt->first;
					newMap.insert(std::make_pair(var,insertionPos)).first;
				} else if(basisIt->second > originalPos && basisIt->second <= insertionPos) {
					std::size_t var = basisIt->first;
					std::size_t pos = basisIt->second - 1;
					//std::cout << "Var " << basisIt->first << " is shifted to pos " << pos << std::endl;
					newMap.insert(std::make_pair(var,pos)).first;
				} else {
					//std::cout << "Do nothing for var " << basisIt->first << std::endl;
					newMap.insert(std::make_pair(basisIt->first, basisIt->second));
				}
			}
			mB = newMap;
		} else {
			auto tmpRow = newDict.row(originalPos);
			for(std::size_t rowIndex = newDict.rows(); rowIndex > 0; --rowIndex) {
				if (rowIndex <= originalPos && rowIndex > insertionPos) {
					//std::cout << "Shift at index " << rowIndex << std::endl;
					mDictionary.row(rowIndex) = newDict.row(rowIndex - 1);
				}
			}
			mDictionary.row(insertionPos) = tmpRow;
			// update mapping
			std::map<std::size_t, std::size_t> newMap;
			for(auto basisIt = mB.begin(); basisIt != mB.end(); ++basisIt) {
				if(basisIt->second == originalPos) {
					//std::cout << "Var " << basisIt->first << " is remapped to pos " << insertionPos << std::endl;
					std::size_t var = basisIt->first;
					newMap.insert(std::make_pair(var,insertionPos)).first;
				} else if(basisIt->second < originalPos && basisIt->second >= insertionPos) {
					std::size_t var = basisIt->first;
					std::size_t pos = basisIt->second + 1;
					//std::cout << "Var " << basisIt->first << " is shifted to pos " << pos << std::endl;
					newMap.insert(std::make_pair(var,pos)).first;
				} else {
					//std::cout << "Do nothing for var " << basisIt->first << std::endl;
					newMap.insert(std::make_pair(basisIt->first, basisIt->second));
				}
			}
			mB = newMap;
		}
	}

	template<typename Number>
	void Dictionary<Number>::insertColAtPosition(const std::size_t& originalPos, const std::size_t& insertionPos) {
		matrix_t<Number> newDict = mDictionary;
		if(originalPos < insertionPos){
			auto tmpCol = newDict.col(originalPos);
			for(std::size_t colIndex = 0; colIndex < std::size_t(newDict.cols()); ++colIndex) {
				if (colIndex >= originalPos && colIndex < insertionPos) {
					//std::cout << "Shift at index " << colIndex << std::endl;
					mDictionary.col(colIndex) = newDict.col(colIndex + 1);
				} else if (colIndex == insertionPos) {
					//std::cout << "Insert original col at index " << colIndex << std::endl;
					mDictionary.col(colIndex) = tmpCol;
				}
			}
			// update mapping
			std::map<std::size_t, std::size_t> newMap;
			for(auto cobasisIt = mN.begin(); cobasisIt != mN.end(); ++cobasisIt) {
				if(cobasisIt->second == originalPos) {
					//std::cout << "Var " << cobasisIt->first << " is remapped to pos " << insertionPos << std::endl;
					std::size_t var = cobasisIt->first;
					newMap.insert(std::make_pair(var,insertionPos)).first;
				} else if(cobasisIt->second > originalPos && cobasisIt->second <= insertionPos) {
					std::size_t var = cobasisIt->first;
					std::size_t pos = cobasisIt->second - 1;
					//std::cout << "Var " << cobasisIt->first << " is shifted to pos " << pos << std::endl;
					newMap.insert(std::make_pair(var,pos)).first;
				} else {
					//std::cout << "Do nothing for var " << cobasisIt->first << std::endl;
					newMap.insert(std::make_pair(cobasisIt->first, cobasisIt->second));
				}
			}
			mN = newMap;
		} else {
			auto tmpCol = newDict.col(originalPos);
			for(std::size_t colIndex = newDict.cols(); colIndex > 0; --colIndex) {
				if (colIndex <= originalPos && colIndex > insertionPos) {
					//std::cout << "Shift at index " << colIndex << std::endl;
					mDictionary.col(colIndex) = newDict.col(colIndex - 1);
				}
			}
			mDictionary.col(insertionPos) = tmpCol;
			// update mapping
			std::map<std::size_t, std::size_t> newMap;
			for(auto cobasisIt = mN.begin(); cobasisIt != mN.end(); ++cobasisIt) {
				if(cobasisIt->second == originalPos) {
					//std::cout << "Var " << cobasisIt->first << " is remapped to pos " << insertionPos << std::endl;
					std::size_t var = cobasisIt->first;
					newMap.insert(std::make_pair(var,insertionPos)).first;
				} else if(cobasisIt->second < originalPos && cobasisIt->second >= insertionPos) {
					std::size_t var = cobasisIt->first;
					std::size_t pos = cobasisIt->second + 1;
					//std::cout << "Var " << cobasisIt->first << " is shifted to pos " << pos << std::endl;
					newMap.insert(std::make_pair(var,pos)).first;
				} else {
					//std::cout << "Do nothing for var " << cobasisIt->first << std::endl;
					newMap.insert(std::make_pair(cobasisIt->first, cobasisIt->second));
				}
			}
			mN = newMap;
		}
	}

	template<typename Number>
	Dictionary<Number>& Dictionary<Number>::operator=(const Dictionary<Number>& rhs) {
		if(rhs != *this) {
			mDictionary = rhs.dictionary();
			mF = mDictionary.rows()-1;
			mG = 0;
			mB = rhs.basis();
			mN = rhs.cobasis();
		}
		return *this;
	}

	template<typename Number>
	inline bool Dictionary<Number>::operator==(const Dictionary<Number>& rhs) const {
		return (mDictionary == rhs.mDictionary &&
		mF == rhs.mF &&
		mG == rhs.mG &&
		mB == rhs.mB &&
		mN == rhs.mN);
	}

	template<typename Number>
	void Dictionary<Number>::print(bool pretty) const {
		if(pretty) {
			// create temporary opposite variable mapping
			std::map<std::size_t, std::size_t> NMap;
			for(const auto& pair : mN)
				NMap[pair.second] = pair.first;

			assert(NMap.size() == mN.size());

			std::map<std::size_t, std::size_t> BMap;
			for(const auto& pair : mB) {
				BMap[pair.second] = pair.first;
			}

			assert(BMap.size() == mB.size());

			std::cout << "\t g \t";
			for(const auto& pair : NMap)
				std::cout << pair.second << "\t";
			std::cout << std::endl;

			for(unsigned rowIndex = 0; rowIndex < mDictionary.rows(); ++rowIndex) {
				if(BMap.find(rowIndex) != BMap.end()){
					std::cout << BMap.at(rowIndex) << "\t";
				} else {
					std::cout << "f \t";
				}
				for(unsigned colIndex = 0; colIndex < mDictionary.cols(); ++colIndex) {
					std::cout << mDictionary(rowIndex,colIndex) << "\t";
				}
				std::cout << std::endl;
			}
		} else {
			std::cout << *this << std::endl;
		}
	}

	template<typename Number>
	matrix_t<Number> Dictionary<Number>::rearrange(const matrix_t<Number>& A) {
		if(A.rows() <= A.cols()) {
			// This should not happen.
			return A;
		}

		matrix_t<Number> copy(A);
		matrix_t<Number> res(A);
		std::size_t dimension = copy.cols();

		// perform Gauss on A to get the linear independent rows
		// normalize rows for each variable and forward insertion

		std::cout << "Original: " << std::endl << A << std::endl << std::endl;

		std::set<unsigned> linearIndependent;
		std::set<unsigned> linearDependent;
		for(unsigned colIndex = 0; colIndex < dimension; ++colIndex)
		{
			std::cout << "Eliminate for column " << colIndex << std::endl;
			unsigned rowIndex = 0;
			// find first row suitable for elimination
			std::cout << linearIndependent << std::endl;
			while(rowIndex < copy.rows() && (linearIndependent.find(rowIndex) != linearIndependent.end() || copy(rowIndex,colIndex) == 0)) {
				++rowIndex;
			}

			std::cout << "Use row " << rowIndex << " for elimination" << std::endl;
			if(copy(rowIndex,colIndex) != 0){
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
			std::cout << copy << std::endl;
		}

		std::cout << "Forward insertion result: " << std::endl;
		std::cout << copy << std::endl;

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

	template<typename Number>
	void Dictionary<Number>::increment(std::size_t& i, std::size_t& j) const {
#ifdef FUKUDA_VERTEX_ENUM_DEBUG
		std::cout << __func__ << " i=" << i << ", j=" << j;
#endif
		++j;
		if( j == std::size_t(mDictionary.cols())) {
			j = 1;
			++i;
		}
#ifdef FUKUDA_VERTEX_ENUM_DEBUG
		std::cout << " to i'=" << i << ", j'=" << j << std::endl;
#endif
	}

} // namespace hypro
