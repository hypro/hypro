#include "vertexEnumeration.h"

namespace hypro {

	template<typename Number>
	Dictionary<Number>::Dictionary(const Dictionary& rhs) :
		mDictionary(rhs.dictionary()),
		mF(mDictionary.rows()-1),
		mG(0),
		mB(rhs.basis()),
		mN(rhs.cobasis())
	{}

	template<typename Number>
	Dictionary<Number>::Dictionary (const matrix_t<Number>& A, const vector_t<Number>& b) :
		mDictionary(),
		mF(A.rows()-A.cols()),
		mG(0)
	{
		matrix_t<Number> t = matrix_t<Number>(A.rows(), A.cols() + 1);
		t << b,-A;
		// rearrange to make the last d equations linear independent.
		rearrange();

		// solve the last d equations
		std::size_t dimension = A.cols();
		// Assumption: The last d equations of A are linear independent

		auto bottom = t.bottomRows(dimension);
		auto top = t.topRows(A.rows()-dimension);

		auto varBlock = bottom.rightCols(dimension);
		auto constPart = bottom.leftCols(1);

		matrix_t<Number> tmp = matrix_t<Number>(varBlock);

		matrix_t<Number> a(tmp.rows(), 2*dimension+1);
		a << tmp, -constPart, matrix_t<Number>::Identity(dimension,dimension);

		//normalize rows for each variable and forward insertion
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

		auto substitutionBlock = a.rightCols(dimension+1);

		mDictionary = matrix_t<Number>(A.rows()-dimension + 1, dimension + 1);

		for(unsigned rI = 0; rI < top.rows(); ++rI)
		{
			mDictionary(rI,0) = top(rI,0);

			for(unsigned dI = 1; dI < top.cols(); ++dI)
			{
				mDictionary.row(rI) = mDictionary.row(rI) + (top(rI,dI) * substitutionBlock.row(dI-1));
			}
		}

		// Augment dictionary by a row of -1s
		//mDictionary.conservativeResize(mDictionary.rows()+1,Eigen::NoChange_t());

		matrix_t<Number> allOnes = matrix_t<Number>::Constant(1,mDictionary.cols(), Number(-1));
		allOnes(0) = Number(0);
		mDictionary.row(mDictionary.rows()-1) = allOnes;

		//std::cout << "Optimal dictionary: " << mDictionary << std::endl;
		std::size_t colCnt = 0;
		for(unsigned index = 1; index < mDictionary.rows(); ++index) {
			mB[index] = colCnt;
			++colCnt;
		}

		std::size_t rowCnt = 1;
		for(std::size_t index = mDictionary.rows() ; index < A.rows() + dimension - 1 ; ++index) {
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

	}

	template<typename Number>
	void Dictionary<Number>::search () {
		std::size_t i,j;
		i = 0;
		j = 1;

		std::size_t m = mDictionary.rows(); // TODO: check!

		std::cout << "Initial, optimal dictionary: " << std::endl;
		std::cout << *this << std::endl;

		do {
			while(i <= m && !isReverseCrissCrossPivot(i,j)) increment(i,j);
			if(i<m) {
				pivot(i,j);
				std::cout << "dictionary after pivot (" << i << ", " << j << "): " << std::endl;
				std::cout << *this << std::endl;
				std::cout << "Vertex-Dictionary: " << mB << std::endl;
				i = 0;
				j = 1;
			} else {
				selectCrissCrossPivot(i,j);
				pivot(i,j);
				increment(i,j);
			}
		} while ( i < m && mB[m-1] != m-1);
	}

	template<typename Number>
	bool Dictionary<Number>::isReverseCrissCrossPivot(std::size_t i, std::size_t j) {
		std::size_t s,r;

		std::cout << "i " << i << ", j " << j << std::endl;

		auto sIt = mB.begin();
		while(sIt->second != i) ++sIt;
		s = sIt->first;

		auto rIt = mN.begin();
		while(rIt->second != j) ++rIt;
		r = rIt->first;

		std::cout << "r " << r << ", s " << s << std::endl;

		// TODO: Not optimal - it is sufficient to check rows f,s and cols g,r -> only compute those.
		bool firstCondition = true;
		bool secondCondition = true;

		if(mDictionary(i,mG) > 0 && mDictionary(i,j) > 0) {

			for(auto basisIt = mB.begin(); basisIt != mB.end(); ++basisIt) {
				if( basisIt->first < s) {
					if( mDictionary(i,basisIt->first) < 0 )
						firstCondition = false;
				} else {
					break;
				}
			}
		} else {
			firstCondition = false;
		}

		if(firstCondition) {
			if(mDictionary(mF, j) < 0 && mDictionary(i,j) < 0) {

				for(auto cobasisIt = mN.begin(); cobasisIt != mN.end(); ++cobasisIt) {
					if( cobasisIt->first < r) {
						if( mDictionary(cobasisIt->first,j) > 0 )
							secondCondition = false;
					}
				}
			}
		}
		return (firstCondition || secondCondition);
	}

	template<typename Number>
	bool Dictionary<Number>::selectCrissCrossPivot(std::size_t& i, std::size_t& j) {
		// step 1: Find smallest index i s.th. i primal or dual infeasible
		bool primalInfeasible = false;
		bool dualInfeasible = false;
		std::size_t index = 0;
		for(; index < mF; ++index) {
			if(mB.find(index) != mB.end() && mDictionary(mB[index], mG) < 0) {
				primalInfeasible = true;
				break;
			}

			if(mN.find(index) != mN.end() && mDictionary(mF, mN[index]) > 0) {
				dualInfeasible = true;
				break;
			}
		}

		// step 2: Select other variable accordingly
		if(primalInfeasible) {
			assert(mB.find(index) != mB.end());
			for(auto cobasisIt = mN.begin(); cobasisIt != mN.end(); ++cobasisIt) {
				if(mDictionary(mB[index], cobasisIt->second) > 0) {
					i = mB[index];
					j = cobasisIt->second;
					break;
				}
			}
			std::cout << __func__ << ": " << i << ", " << j << std::endl;
			return true;
		} else if (dualInfeasible) {
			assert(mN.find(index) != mN.end());

			for(auto basisIt = mB.begin(); basisIt != mB.end(); ++basisIt) {
				if(mDictionary(basisIt->second, mN[index]) < 0) {
					i = basisIt->second;
					j = mN[index];
					break;
				}
			}
			std::cout << __func__ << ": " << i << ", " << j << std::endl;
			return true;
		}

		// Dictionary is optimal - no feasible pivot
		std::cout << __func__ << ": No feasible pivot." << std::endl;
		return false;
	}

	template<typename Number>
	void Dictionary<Number>::pivot(std::size_t& i, std::size_t& j) {

		std::cout << __func__ << " (" << i << ", " << j << ")" << std::endl;
		//std::cout << "sPos: " << mN[s] << std::endl;
		//std::cout << "rPos: " << mB[r] << std::endl;

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
			std::cout << "Move row " << j << " to Position " << rowCnt << std::endl;
			insertRowAtPosition(i,rowCnt);
		}

		auto cobasisIt = mN.begin();
		std::size_t colCnt = 1;
		while(cobasisIt->first != r) {++cobasisIt; ++colCnt;}
		if(j != colCnt) {
			std::cout << "Move col " << j << " to Position " << colCnt << std::endl;
			insertColAtPosition(j,colCnt);
		}

		// update i and j
		std::size_t tmp = i;
		i = j;
		j = tmp;
	}

	template<typename Number>
	void Dictionary<Number>::insertRowAtPosition(const std::size_t& originalPos, const std::size_t& insertionPos) {
		matrix_t<Number> newDict = mDictionary;
		if(originalPos < insertionPos){
			auto tmpRow = newDict.row(originalPos);
			for(std::size_t rowIndex = 0; rowIndex < std::size_t(newDict.rows()); ++rowIndex) {
				if(rowIndex < originalPos || rowIndex > insertionPos) {
					std::cout << "Do nothing for index " << rowIndex << std::endl;
					//mDictionary.row(rowIndex) = newDict.row(rowIndex);
				} else if (rowIndex >= originalPos && rowIndex < insertionPos) {
					std::cout << "Shift at index " << rowIndex << std::endl;
					mDictionary.row(rowIndex) = newDict.row(rowIndex + 1);
				} else if (rowIndex == insertionPos) {
					std::cout << "Insert original row at index " << rowIndex << std::endl;
					mDictionary.row(rowIndex) = tmpRow;
				}
			}
			// update mapping
			std::cout << "Update mapping " << std::endl;
			std::map<std::size_t, std::size_t> newMap;
			for(auto basisIt = mB.begin(); basisIt != mB.end(); ++basisIt) {
				if(basisIt->second == originalPos) {
					std::cout << "Var " << basisIt->first << " is remapped to pos " << insertionPos << std::endl;
					std::size_t var = basisIt->first;
					newMap.insert(std::make_pair(var,insertionPos)).first;
				} else if(basisIt->second > originalPos && basisIt->second <= insertionPos) {
					std::size_t var = basisIt->first;
					std::size_t pos = basisIt->second - 1;
					std::cout << "Var " << basisIt->first << " is shifted to pos " << pos << std::endl;
					newMap.insert(std::make_pair(var,pos)).first;
				} else {
					std::cout << "Do nothing for var " << basisIt->first << std::endl;
					newMap.insert(std::make_pair(basisIt->first, basisIt->second));
				}
			}
			mB = newMap;
		} else {
			auto tmpRow = newDict.row(originalPos);
			for(std::size_t rowIndex = newDict.rows(); rowIndex != 0; --rowIndex) {
				if(rowIndex > originalPos || rowIndex < insertionPos) {
					std::cout << "Do nothing for index " << rowIndex << std::endl;
					//mDictionary.row(rowIndex) = newDict.row(rowIndex);
				} else if (rowIndex <= originalPos && rowIndex > insertionPos) {
					std::cout << "Shift at index " << rowIndex << std::endl;
					mDictionary.row(rowIndex) = newDict.row(rowIndex - 1);
				} else if (rowIndex == insertionPos) {
					std::cout << "Insert original row at index " << rowIndex << std::endl;
					mDictionary.row(rowIndex) = tmpRow;
				}
			}
			// update mapping
			std::cout << "Update mapping " << std::endl;
			std::map<std::size_t, std::size_t> newMap;
			for(auto basisIt = mB.begin(); basisIt != mB.end(); ++basisIt) {
				if(basisIt->second == originalPos) {
					std::cout << "Var " << basisIt->first << " is remapped to pos " << insertionPos << std::endl;
					std::size_t var = basisIt->first;
					newMap.insert(std::make_pair(var,insertionPos)).first;
				} else if(basisIt->second < originalPos && basisIt->second >= insertionPos) {
					std::size_t var = basisIt->first;
					std::size_t pos = basisIt->second + 1;
					std::cout << "Var " << basisIt->first << " is shifted to pos " << pos << std::endl;
					newMap.insert(std::make_pair(var,pos)).first;
				} else {
					std::cout << "Do nothing for var " << basisIt->first << std::endl;
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
				if(colIndex < originalPos || colIndex > insertionPos) {
					std::cout << "Do nothing for index " << colIndex << std::endl;
					//mDictionary.col(colIndex) = newDict.col(colIndex);
				} else if (colIndex >= originalPos && colIndex < insertionPos) {
					std::cout << "Shift at index " << colIndex << std::endl;
					mDictionary.col(colIndex) = newDict.col(colIndex + 1);
				} else if (colIndex == insertionPos) {
					std::cout << "Insert original col at index " << colIndex << std::endl;
					mDictionary.col(colIndex) = tmpCol;
				}
			}
			// update mapping
			std::cout << "Update mapping " << std::endl;
			std::map<std::size_t, std::size_t> newMap;
			for(auto cobasisIt = mN.begin(); cobasisIt != mN.end(); ++cobasisIt) {
				if(cobasisIt->second == originalPos) {
					std::cout << "Var " << cobasisIt->first << " is remapped to pos " << insertionPos << std::endl;
					std::size_t var = cobasisIt->first;
					newMap.insert(std::make_pair(var,insertionPos)).first;
				} else if(cobasisIt->second > originalPos && cobasisIt->second <= insertionPos) {
					std::size_t var = cobasisIt->first;
					std::size_t pos = cobasisIt->second - 1;
					std::cout << "Var " << cobasisIt->first << " is shifted to pos " << pos << std::endl;
					newMap.insert(std::make_pair(var,pos)).first;
				} else {
					std::cout << "Do nothing for var " << cobasisIt->first << std::endl;
					newMap.insert(std::make_pair(cobasisIt->first, cobasisIt->second));
				}
			}
			mN = newMap;
		} else {
			auto tmpCol = newDict.col(originalPos);
			for(std::size_t colIndex = newDict.cols(); colIndex != 0; --colIndex) {
				if(colIndex > originalPos || colIndex < insertionPos) {
					std::cout << "Do nothing for index " << colIndex << std::endl;
					//mDictionary.col(colIndex) = newDict.col(colIndex);
				} else if (colIndex <= originalPos && colIndex > insertionPos) {
					std::cout << "Shift at index " << colIndex << std::endl;
					mDictionary.col(colIndex) = newDict.col(colIndex - 1);
				} else if (colIndex == insertionPos) {
					std::cout << "Insert original row at index " << colIndex << std::endl;
					mDictionary.col(colIndex) = tmpCol;
				}
			}
			// update mapping
			std::cout << "Update mapping " << std::endl;
			std::map<std::size_t, std::size_t> newMap;
			for(auto cobasisIt = mN.begin(); cobasisIt != mN.end(); ++cobasisIt) {
				if(cobasisIt->second == originalPos) {
					std::cout << "Var " << cobasisIt->first << " is remapped to pos " << insertionPos << std::endl;
					std::size_t var = cobasisIt->first;
					newMap.insert(std::make_pair(var,insertionPos)).first;
				} else if(cobasisIt->second < originalPos && cobasisIt->second >= insertionPos) {
					std::size_t var = cobasisIt->first;
					std::size_t pos = cobasisIt->second + 1;
					std::cout << "Var " << cobasisIt->first << " is shifted to pos " << pos << std::endl;
					newMap.insert(std::make_pair(var,pos)).first;
				} else {
					std::cout << "Do nothing for var " << cobasisIt->first << std::endl;
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
	void Dictionary<Number>::rearrange() {
	}

	template<typename Number>
	void Dictionary<Number>::increment(std::size_t& i, std::size_t& j) const {
		std::cout << __func__ << std::endl;
		++j;
		if( j == std::size_t(mDictionary.cols()-1)) {
			j = 1;
			++i;
		}
	}

} // namespace hypro