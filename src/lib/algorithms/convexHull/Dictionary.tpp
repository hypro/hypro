#include "Dictionary.h"

namespace hypro {

	template<typename Number>
	Dictionary<Number>::Dictionary(const Dictionary& rhs) :
		mDictionary(rhs.tableau()),
		mB(rhs.basis()),
		mN(rhs.cobasis())
	{}

	template<typename Number>
	Dictionary<Number>::Dictionary(const matrix_t<Number>& rhs, std::vector<std::size_t> basis, std::vector<std::size_t> cobasis):
		mDictionary(rhs),
		mB(basis),
		mN(cobasis)
	{}

	template<typename Number>
	Dictionary<Number>::Dictionary(const matrix_t<Number>& rhs, std::vector<std::size_t> basis, std::vector<std::size_t> cobasis, ConstrainSet<Number> constrains):
		mDictionary(rhs),
		mB(basis),
		mN(cobasis),
		mConstrains(constrains)
	{}

	template<typename Number>
	std::vector<std::size_t> Dictionary<Number>::basis() const {
		return mB;
	}

	template<typename Number>
	std::vector<std::size_t> Dictionary<Number>::cobasis() const {
		return mN;
	}

	template<typename Number>
	ConstrainSet<Number> Dictionary<Number>::constrainSet() const {
		return mConstrains;
	}

	template<typename Number>
	Number Dictionary<Number>::get(std::size_t i,std::size_t j) const {
		return mDictionary(i,j);
	}


	template<typename Number>
	void Dictionary<Number>::setValue(std::size_t i, std::size_t j, Number val) {
		mDictionary(i,j) = val;
	}

	template<typename Number>
	matrix_t<Number> Dictionary<Number>::tableau() const {
		return mDictionary;
	}

	template<typename Number>
	Dictionary<Number>::Dictionary(const std::vector<Halfspace<Number>>& hsv) {
		int d = hsv[0].dimension();
		int n0 = hsv.size();
		int i,j;
		matrix_t<Number> Ab = matrix_t<Number>::Zero(n0+1, n0+1);

		for(i=0; i<n0; ++i){
			Ab(i, i+1) = -1;
		}
		Ab(n0,0)=-1;

		matrix_t<Number> An = matrix_t<Number>::Zero(n0+1, d+1);

		for(i=0; i<d; ++i){
			An(0, i) = 1;
		}
		An(0, d) = 0;
		for(i=1; i<n0+1; ++i){
			An(i, d) = -1*hsv[i-1].offset();
			for(j=0; j<d; ++j){
				An(i, j) = hsv[i-1].normal()[j];
			}
		}

		mDictionary = Ab * An;

		for(i=1; i<n0+1; ++i){
			mB.push_back(std::size_t(i));
		}
		mB.push_back(std::size_t(n0+d+1));
		for(i=n0+1; i<n0+d+1; ++i){
			mN.push_back(std::size_t(i));
		}
		mN.push_back(std::size_t(n0+d+2));
		//f=n0+d+1, ; g= n0+d+2

		for(i=0;i<n0;++i) {
			mConstrains.add(std::tuple<std::pair<bool,Number>,std::pair<bool,Number>,Number>(
					std::pair<bool,Number>(false,-mDictionary(i,d)),std::pair<bool,Number>(true,Number(0)),Number(0)));
		}
		for(i=0;i<d;++i) {
			mConstrains.add(
			std::tuple<std::pair<bool,Number>,std::pair<bool,Number>,Number>(
					std::pair<bool,Number>(true,Number(0)),std::pair<bool,Number>(true,Number(0)),Number(0)));
		}
	}

	template<typename Number>
	void Dictionary<Number>::printDictionary() const {
		uint32_t i,j;
		cout << "\n mB size=";
		cout << mB.size();
		cout << "\n mN size=";
		cout << mN.size();
		cout << "\n mDictionary size=";
		cout << mDictionary.size();
		cout << "\n \n";

		cout <<"mB = ";
		for(i=0; i<mB.size(); ++i){
			cout << mB[i];
			cout << ";  ";
		}
		cout <<"\nmN = ";
		for(j=0; j<mN.size(); ++j){
			cout << mN[j];
			cout << ";  ";
		}
		cout << "\n \n";

		for(i=0; i<mB.size(); ++i){
			for(j=0; j<mN.size(); ++j){
				cout << mDictionary(i,j);
				cout << " ; ";
			}
			cout << "\n";
		}
		cout.flush();
	}


	template<typename Number>
	void Dictionary<Number>::pivotDictionary(std::size_t i, std::size_t j) {
		//std::cout << "Cols: " << mDictionary.cols() << ", rows: " << mDictionary.rows() << ", i: " << i << ", j: " << j << std::endl;
		// update other cells
		for(unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols()); ++colIndex) {
			for(unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()); ++rowIndex) {
				if(rowIndex != i && colIndex != j)
					mDictionary(rowIndex, colIndex) = mDictionary(rowIndex, colIndex) - ( mDictionary(rowIndex, j)* mDictionary(i, colIndex) ) / mDictionary(i,j);
			}
		}

		// update row
		for(unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols()); ++colIndex) {
			if(colIndex != j)
				mDictionary(i, colIndex) = - mDictionary(i, colIndex) / mDictionary(i,j);
		}

		// update col
		for(unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()); ++rowIndex) {
			if(rowIndex != i)
				mDictionary(rowIndex,j) = mDictionary(rowIndex, j) / mDictionary(i,j);
		}

		// update cell
		mDictionary(i,j) = Number(1) / mDictionary(i,j);
	}

	template<typename Number>
	void Dictionary<Number>::pivot(const std::size_t i, const std::size_t j) {
		pivotDictionary(i, j);

		int tmp = mB[i];
		mB[i] = mN[j];
		mN[j] = tmp;
	}

	template<typename Number>
	bool Dictionary<Number>::fixOutOfBounds() {
		Number diff = 0;
		Number diffRef = diff;
		std::size_t index = 0;
		std::size_t indexRef = index;
		std::size_t pivot = 0;
		std::size_t pivotRef = pivot;
		if(not(mConstrains.outside(indexRef,diff,mB))) {return false;}//is there any variable out of its bounds
		if(not(mConstrains.getPivot(indexRef,diff,pivotRef,mN,mDictionary))) {throw string("\n WARNING: empty set. \n");}//is there a suitable pivot
		this->pivot(indexRef,pivotRef);
		mConstrains.modifyAssignment(pivotRef, diff, mB, mN, mDictionary);
		return true;
	}

	template<typename Number>
	bool Dictionary<Number>::selectBlandPivot(std::size_t& i, std::size_t& j) {
		unsigned minIndex = mDictionary.size()+1;
		unsigned indexMin = mDictionary.size()+1;
		std::vector<std::size_t> goodIndices;

		for(unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols()-1); ++colIndex) {//select the col
			if(mDictionary(mDictionary.rows()-1,colIndex)> 0 && mN[colIndex] < minIndex)	{
				minIndex = mN[colIndex];
				indexMin = colIndex;
			}
		}
		if(minIndex == unsigned(mDictionary.size()+1)){return false;}
		j = indexMin;
		for(unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()-1); ++rowIndex) {
			if(mDictionary(rowIndex,j) < 0)	{
				goodIndices.push_back(rowIndex);
			}
		}
		if(goodIndices.size() == 0){return false;}
		i = goodIndices[0];
		minIndex = mB[goodIndices[0]];
		Number currentLambda = mDictionary(i,mDictionary.cols()-1)/mDictionary(i,j);
		for(unsigned rowIndex = 1; rowIndex < unsigned(goodIndices.size()); ++rowIndex) {//select the row
			if(mDictionary(goodIndices[rowIndex],mDictionary.cols()-1)/mDictionary(goodIndices[rowIndex],j)	> currentLambda)	{
				i = goodIndices[rowIndex];
				currentLambda = mDictionary(i,mDictionary.cols()-1)/mDictionary(i,j);
				minIndex = mB[goodIndices[rowIndex]];
			}
			if(mDictionary(goodIndices[rowIndex],mDictionary.cols()-1)/mDictionary(goodIndices[rowIndex],j)	== currentLambda
						&& minIndex > mB[goodIndices[rowIndex]])	{
				i = goodIndices[rowIndex];
				currentLambda = mDictionary(i,mDictionary.cols()-1)/mDictionary(i,j);
				minIndex = mB[goodIndices[rowIndex]];
			}

		}
		return true;
	}

	template<typename Number>
	bool Dictionary<Number>::selectDualBlandPivot(std::size_t& i, std::size_t& j, const std::vector<std::size_t> availableIndices) {
		unsigned minIndex = mDictionary.size();
		unsigned indexMin = mDictionary.size();
		std::vector<std::size_t> goodIndices;
		for(unsigned rowIndex = 0; rowIndex < unsigned(availableIndices.size()); ++rowIndex) {
			if(mDictionary(availableIndices[rowIndex],mDictionary.cols()-1)< 0 && mB[availableIndices[rowIndex]] < minIndex)	{
				minIndex = mB[availableIndices[rowIndex]];
				indexMin = rowIndex;
			}
		}
		if(minIndex == unsigned(mDictionary.size())){return false;}
		i = indexMin;
		for(unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols()-1); ++colIndex) {
			if(mDictionary(availableIndices[i],colIndex) > 0)	{
				goodIndices.push_back(colIndex);
			}
		}
		minIndex = mN[goodIndices[0]];
		j = goodIndices[0];
		Number currentLambda = mDictionary(mDictionary.rows()-1,j)/mDictionary(availableIndices[i],j);
		for(unsigned colIndex = 1; colIndex < unsigned(goodIndices.size()); ++colIndex) {
			if(mDictionary(mDictionary.rows()-1,goodIndices[colIndex])/mDictionary(availableIndices[i],goodIndices[colIndex])	> currentLambda)	{
				j = goodIndices[colIndex];
				currentLambda = mDictionary(mDictionary.rows()-1,j)/mDictionary(availableIndices[i],j);
				minIndex = mN[goodIndices[colIndex]];
			}
			if(mDictionary(mDictionary.rows()-1,goodIndices[colIndex])/mDictionary(availableIndices[i],goodIndices[colIndex])	== currentLambda
						&& minIndex > mN[goodIndices[colIndex]]) {
				minIndex = mN[goodIndices[colIndex]];
				j = goodIndices[colIndex];
				currentLambda = mDictionary(mDictionary.rows()-1,j)/mDictionary(availableIndices[i],j);
			}
		}
		return true;
	}

	template<typename Number>
	bool Dictionary<Number>::selectCrissCrossPivot(std::size_t& i, std::size_t& j) {
		unsigned minIndex = mDictionary.size();
		unsigned indexMin = mDictionary.size();
		bool b = true;
		for(unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()-1); ++rowIndex) {
			if(mDictionary(rowIndex,mDictionary.cols()-1)< 0 && mB[rowIndex] < minIndex)	{
				minIndex = mB[rowIndex];
				indexMin = rowIndex;
			}
		}
		for(unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols()-1); ++colIndex) {
			if(mDictionary(mDictionary.rows()-1,colIndex)> 0 && mN[colIndex] < minIndex)	{
				minIndex = mN[colIndex];
				indexMin = colIndex;
				b=false;
			}
		}
		if(minIndex == unsigned(mDictionary.size())){return false;}
		if(b) {
			i = indexMin;
			minIndex = mDictionary.size();
			for(unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols()); ++colIndex) {
				if(mDictionary(i,colIndex) > 0 && mN[colIndex] < minIndex)	{
					minIndex = mN[colIndex];
					j = colIndex;
				}
			}
		} else {
			j = indexMin;
			minIndex = mDictionary.size();
			for(unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()); ++rowIndex) {
				if(mDictionary(rowIndex,j) < 0 && mB[rowIndex] < minIndex)	{
					minIndex = mB[rowIndex];
					i = rowIndex;
				}
			}
		}
		return true;
	}

	template<typename Number>
	bool Dictionary<Number>::isPrimalFeasible() {
		bool b=true;
		for(unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()-1); ++rowIndex) {
			b=b&&(mDictionary(rowIndex,mDictionary.cols()-1)>=0);
		}
		return b;
	}

	template<typename Number>
	bool Dictionary<Number>::isDualFeasible() {
		bool b=true;
		for(unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols()-1); ++colIndex) {
			b=b&&(mDictionary(mDictionary.rows()-1,colIndex)<=0);
		}
		return b;
	}

	template<typename Number>
	bool Dictionary<Number>::reverse_old(const std::size_t i, const std::size_t j) {
		std::size_t a = std::size_t(0);
		std::size_t b = std::size_t(0);
		std::size_t& i3 = a;
		std::size_t& j3 = b;
		if(mDictionary(i,j)==0){return false;};
		pivot(i,j);
		bool primal = isPrimalFeasible();
		bool existingPivot = selectBlandPivot(i3,j3);
		pivot(i,j);
		return (i==i3)&&(j==j3)&&existingPivot&&primal;
	}

	template<typename Number>
	bool Dictionary<Number>::reverse(const std::size_t i, const std::size_t j) {
		if(mDictionary(mDictionary.rows()-1,j)>=0||mDictionary(i,j)>=0) {return false;}
		Number maxRatio = mDictionary(i,mDictionary.cols()-1)/mDictionary(i,j);
		for(int rowIndex=0;rowIndex<mDictionary.rows()-1;++rowIndex) {
			if(mDictionary(rowIndex,j)<0&&maxRatio<mDictionary(rowIndex,mDictionary.cols()-1)/mDictionary(rowIndex,j)) {return false;}
		}
		for(int rowIndex=0;rowIndex<mDictionary.rows()-1;++rowIndex) {
			if(rowIndex!=int(i)&&mB[rowIndex]<mN[j]&&(mDictionary(rowIndex,mDictionary.cols()-1)==0 && mDictionary(rowIndex,j)>0 )) {return false;}
		}
		for(int colIndex=0;colIndex<mDictionary.cols()-1;++colIndex) {
			if(mN[colIndex]<mB[i]&&colIndex!=int(j)) {
				if(mDictionary(mDictionary.rows()-1,colIndex)>mDictionary(mDictionary.rows()-1,j)*mDictionary(i,colIndex)/mDictionary(i,j)) {
					return false;
				}
			}
		}
		return true;
	}


	template<typename Number>
	bool Dictionary<Number>::reverseDual_old(const std::size_t i, const std::size_t j, const std::vector<std::size_t> availableIndices) {
		std::size_t a = std::size_t(0);
		std::size_t b = std::size_t(0);
		std::size_t& i3 = a;
		std::size_t& j3 = b;
		if(mDictionary(availableIndices[i],j)==0){return false;};
		pivot(availableIndices[i],j);
		bool dual = isDualFeasible();
		bool existingPivot = selectDualBlandPivot(i3,j3,availableIndices);
		pivot(availableIndices[i],j);
		return (i==i3)&&(j==j3)&&existingPivot&&dual;
	}

	template<typename Number>
	bool Dictionary<Number>::reverseDual(const std::size_t i, const std::size_t j, const std::vector<std::size_t>& availableIndices) {
		if(mDictionary(availableIndices[i],mDictionary.cols()-1)<=0||mDictionary(availableIndices[i],j)<=0) {return false;}
		Number maxRatio = mDictionary(mDictionary.rows()-1,j)/mDictionary(availableIndices[i],j);
		for(std::size_t colIndex=0;colIndex<std::size_t(mDictionary.cols()-1);++colIndex) {
			if(mDictionary(availableIndices[i],colIndex)>0&&maxRatio<mDictionary(mDictionary.rows()-1,colIndex)/mDictionary(availableIndices[i],colIndex)) {return false;}
		}
		for(std::size_t colIndex=0;colIndex<std::size_t(mDictionary.cols()-1);++colIndex) {
			if(colIndex!=j&&mN[colIndex]<mB[i]&&(mDictionary(mDictionary.rows()-1,colIndex)==0 && mDictionary(availableIndices[i],colIndex)<0 )) {return false;}
		}
		for(std::size_t rowIndex=0;rowIndex<availableIndices.size();++rowIndex) {
			if(mB[availableIndices[rowIndex]]<mN[j]&&availableIndices[rowIndex]!=i) {
				if(mDictionary(availableIndices[rowIndex],mDictionary.cols()-1)>mDictionary(availableIndices[i],mDictionary.cols()-1)*mDictionary(availableIndices[rowIndex],j)/mDictionary(availableIndices[i],j)) {
					return false;
				}
			}
		}
		return true;
	}

	template<typename Number>
	bool Dictionary<Number>::isLexMin() {
		for(unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()-1); ++rowIndex) {
			if(mDictionary(rowIndex,mDictionary.cols()-1)==0) {
				for(unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols()-1); ++colIndex) {
					if(mDictionary(rowIndex,colIndex) != 0 && mB[rowIndex]>mN[colIndex]) {
						return false;
					}
				}
			}
		}
		return true;
	}

	template<typename Number>
	Point<Number> Dictionary<Number>::toPoint () const {
		std::vector<Number> point = std::vector<Number>(mDictionary.cols()-1);
		for(unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols()-1); ++colIndex) {
			point[colIndex] = 0;
		}
		for(unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()-1); ++rowIndex) {//to optimize, not looking at every row
			if(mB[rowIndex] >= mB.size()) {
			point[mB[rowIndex]-mB.size()] = mDictionary(rowIndex,mDictionary.cols()-1);}
		}
		return Point<Number>(point);
	}

	template<typename Number>
	std::vector<std::size_t> Dictionary<Number>::findZeros() {
		std::vector<std::size_t> indexList;
		for(unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()-1); ++rowIndex) {
			if(mDictionary(rowIndex,mDictionary.cols()-1)==0) {
				indexList.push_back(rowIndex);
			}
		}
		return indexList;
	}

	template<typename Number>
	void Dictionary<Number>::setOnes(const std::vector<std::size_t>& indices) {
		for(unsigned rowIndex = 0; rowIndex < unsigned(indices.size()); ++rowIndex) {
			mDictionary(indices[rowIndex],mDictionary.cols()-1) = 1;
		}
	}

	template<typename Number>
	void Dictionary<Number>::setZeros(const std::vector<std::size_t>& indices) {
		for(unsigned rowIndex = 0; rowIndex < unsigned(indices.size()); ++rowIndex) {
			mDictionary(indices[rowIndex],mDictionary.cols()-1) = 0;
		}
	}

	template<typename Number>
	void Dictionary<Number>::nonSlackToBase(std::vector<vector_t<Number>>& linealtySpace) {
		for(unsigned colIndex=0; colIndex<mN.size()-1;++colIndex) {
			if(mN[colIndex]>=mB.size()) {
				unsigned rowIndex=0;
				for(rowIndex=0; rowIndex<mB.size()-1;++rowIndex) {
					if(mDictionary(rowIndex,colIndex)!=0&&mB[rowIndex]<mB.size()) {
						this->pivot(rowIndex,colIndex);
						break;
					}
				}
				if(rowIndex==mB.size()-1) {
					vector_t<Number> newLinealty = vector_t<Number>::Zero(mN.size()-1);
					newLinealty[mN[colIndex]-mB.size()] = 1;
					for(rowIndex=0; rowIndex<mB.size()-1;++rowIndex) {
						if(mDictionary(rowIndex,colIndex)!=0&&mB[rowIndex]>=mB.size()) {
							newLinealty[mB[rowIndex]-mB.size()] += mDictionary(rowIndex,colIndex);
						}
					}
					linealtySpace.push_back(newLinealty);
				}
			}
		}
	}

	template<typename Number>
	void Dictionary<Number>::nonSlackToBase() {
		for(unsigned colIndex=0; colIndex<mN.size()-1;++colIndex) {
			if(mN[colIndex]>=mB.size()) {
				unsigned rowIndex=0;
				for(rowIndex=0; rowIndex<mB.size()-1;++rowIndex) {
					if(mDictionary(rowIndex,colIndex)!=0&&mB[rowIndex]<mB.size()) {
						this->pivot(rowIndex,colIndex);
						break;
					}
				}
				if(rowIndex==mB.size()-1) {throw(string("WARNING: linealty space found"));}
			}
		}
	}



	template<typename Number>
	std::set<std::size_t> Dictionary<Number>::toCobase(const std::set<std::size_t> saturatedIndices) {
		std::set<std::size_t> frozenCols;
		for(std::size_t colIndex=0; colIndex<mN.size()-1;++colIndex) {
			if(saturatedIndices.end()!=saturatedIndices.find(mN[colIndex]-1)) {
				frozenCols.insert(colIndex);
			}
		}
		for(std::size_t rowIndex=0; rowIndex<mB.size()-1;++rowIndex) {
			if(saturatedIndices.end()!=saturatedIndices.find(mB[rowIndex]-1)) {
				for(std::size_t colIndex=0; colIndex<mN.size()-1;++colIndex) {
					if(frozenCols.end()==frozenCols.find(colIndex)&&mDictionary(rowIndex,colIndex)!=0) {
						this->pivot(rowIndex,colIndex);
						frozenCols.insert(colIndex);
						break;
					}
				}
			}
		}
		return frozenCols;
	}

	template<typename Number>
	void Dictionary<Number>::pushToBounds(std::size_t colIndex) {
		Number diff = mConstrains.diffToLowerBound(mN[colIndex]-1);//diff<0
		unsigned minDiffIndex = mDictionary.size();
		for(unsigned rowIndex=0; rowIndex<unsigned(mDictionary.rows())-1;++rowIndex) {
			if(mConstrains.finiteLowerBound(mB[rowIndex]-1)&&mDictionary(rowIndex,colIndex)>0) {
				if(diff< (mConstrains.diffToLowerBound(mB[rowIndex]-1)/mDictionary(rowIndex,colIndex)) ) {
					minDiffIndex = rowIndex;
					diff = mConstrains.diffToLowerBound(mB[rowIndex]-1)/mDictionary(rowIndex,colIndex);
				}
			}
		}
		if(minDiffIndex != unsigned(mDictionary.size())) {
			this->pivot(minDiffIndex,colIndex);
			mConstrains.modifyAssignment(colIndex, mConstrains.diffToLowerBound(mB[minDiffIndex]-1), mB, mN, mDictionary);
		} else {mConstrains.modifyAssignment(colIndex, diff, mB, mN, mDictionary);}
	}

	template<typename Number>
	std::set<vector_t<Number>> Dictionary<Number>::findCones() {
		std::set<vector_t<Number>> coneList;
		for(unsigned colIndex=0; colIndex<unsigned(mDictionary.cols()-1);++colIndex) {
			if(mDictionary(mDictionary.rows()-1,colIndex)<0) {
				unsigned rowIndex=0;
				while(rowIndex<unsigned(mDictionary.rows()-1) &&  mDictionary(rowIndex,colIndex)>=0) {
					++rowIndex;
				}
				if(rowIndex==unsigned(mDictionary.rows()-1)) {
					vector_t<Number> cone = vector_t<Number>::Zero(mDictionary.cols()-1);
					if(mN[colIndex]>=mB.size()) {cone[mN[colIndex]-mB.size()]=Number(1);}
					for(rowIndex=0; rowIndex<unsigned(mDictionary.rows()-1);++rowIndex) {
						if(mB[rowIndex]>=mB.size()) {
							cone[mB[rowIndex]-mB.size()]=mDictionary(rowIndex,colIndex);
						}
					}
					for(int index=0; index<cone.size();++index) {
						if(cone[index]!=0) {
							cone=cone/carl::abs(cone[index]);
							break;
						}
					}
					coneList.insert(cone);
				}
			}
		}
		return coneList;
	}



} // namespace hypro
