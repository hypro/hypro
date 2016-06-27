#include "vertexEnumeration.h"

namespace hypro {

	template<typename Number>
	void VertexEnumeration<Number>::increment(unsigned& i, unsigned& j, unsigned maxJ) {
		++j; if(j>=maxJ){j=0;++i;};//cout<<"\nincr  i="<<i<<",j="<<j<<"\n";
	}
	
	template<typename Number>
	VertexEnumeration<Number>::VertexEnumeration(const std::vector<Halfspace<Number>>& hsv) {
		mHsv=hsv;
	}
	
	template<typename Number>
	std::vector<Halfspace<Number>> VertexEnumeration<Number>::getHsv() const {return mHsv;}
	
	template<typename Number>
	std::vector<Dictionary<Number>> VertexEnumeration<Number>::getDictionaries() const {return mDictionaries;}
	
	template<typename Number>
	std::vector<Point<Number>> VertexEnumeration<Number>::getPositivePoints() const {return mPositivePoints;}
	
	template<typename Number>
	std::vector<Point<Number>> VertexEnumeration<Number>::getPoints() const {return mPoints;}
	
	template<typename Number>
	std::vector<vector_t<Number>> VertexEnumeration<Number>::getLinealtySpace() const {return mLinealtySpace;}
	
	template<typename Number>
	std::vector<vector_t<Number>> VertexEnumeration<Number>::getPositiveCones() const {return mPositiveCones;}
	
	template<typename Number>
	std::vector<vector_t<Number>> VertexEnumeration<Number>::getCones() const {return mCones;}
	
	template<typename Number>
	void VertexEnumeration<Number>::enumerateVertices() {
		findLinealtySpace();
		addLinealtyConstrains();
		if(findPositiveConstrains()) {
			enumerateDictionaries();
			enumerateVerticesEachDictionary();
			toGeneralCoordinates();
		}
	}
	
	template<typename Number>
	void VertexEnumeration<Number>::enumerateVertices(Dictionary<Number>& dictionary) {
		std::set<vector_t<Number>> cones =dictionary.findCones(); 
		for(const auto& cone: cones) {cout << "cone ---------------------------------------";
			mPositiveCones.insert(cone);
		}
		unsigned a=0;
		unsigned b=0;
		int depth=0;
		unsigned& i=a;
		unsigned& j=b;
		unsigned m = dictionary.basis().size()-1;//different than the article
		unsigned n = dictionary.cobasis().size()-1;
		while(i<m || depth>=0){
			while(i<m && not(dictionary.reverse(i,j))){
				VertexEnumeration<Number>::increment(i,j,n);
			}
			if(i<m){
				dictionary.pivot(i,j);
				if(dictionary.isLexMin()) {
					cout << "\n new point: ";
					//dictionary.printDictionary();
					cout << dictionary.toPoint();
					mPositivePoints.push_back(dictionary.toPoint());
				}
				std::set<vector_t<Number>> cones =dictionary.findCones(); 
				for(const auto& cone: cones) {cout << "cone ---------------------------------------";
					mPositiveCones.insert(cone);
				}
				i=0;j=0;++depth;
			} else { 
				if(depth>0) {
					dictionary.selectBlandPivot(i,j);
					dictionary.pivot(i,j);
				}
				VertexEnumeration<Number>::increment(i,j,n);
				--depth;
			} 
		}
	}
	
	template<typename Number>
	void VertexEnumeration<Number>::enumerateVerticesEachDictionary() {
		mPositivePoints.push_back(mDictionaries[0].toPoint());
		for(unsigned i = 0; i<mDictionaries.size(); ++i) {
			cout<< "\n\n Next dictionary ---------------------\n";
			mDictionaries[i].printDictionary();
			enumerateVertices(mDictionaries[i]);
		}
	}
	
	template<typename Number>
	void VertexEnumeration<Number>::enumerateDictionaries() {
		Dictionary<Number> dictionary = mDictionaries[0];
		unsigned a=0;
		unsigned b=0;
		int depth=0;
		std::vector<unsigned> basisAux = dictionary.findZeros();//locate degenerated variables
		std::vector<Number> memory;
		unsigned& i=a;
		unsigned& j=b;
		unsigned m = basisAux.size();//different than the article
		unsigned m2 = dictionary.basis().size()-1;
		unsigned n = dictionary.cobasis().size()-1;
		for(unsigned rowIndex = 0; rowIndex <= m2; ++rowIndex) {
			memory.push_back(dictionary.get(rowIndex,n));
		}
		dictionary.setOnes(basisAux);
		while(i<m || depth>=0){
			while(i<m && not(dictionary.reverseDual(i,j,basisAux))){
				VertexEnumeration<Number>::increment(i,j,n);
			}
			if(i<m){
				dictionary.pivot(basisAux[i],j);
				Dictionary<Number> newDictionary = (Dictionary<Number>(dictionary));
				for(unsigned rowIndex = 0; rowIndex <= m2; ++rowIndex) {
					newDictionary.setValue(rowIndex,n,memory[rowIndex]);
				}
				mDictionaries.push_back(newDictionary);
				i=0;j=0;++depth;
			} else {
				if(depth>0) {
					dictionary.selectDualBlandPivot(i,j,basisAux);
					dictionary.pivot(basisAux[i],j);
				}
				VertexEnumeration<Number>::increment(i,j,n);
				--depth;
			} 
		}
		cout<<"\n nb dico = " << mDictionaries.size() <<"\n";
	}
	
	template<typename Number>
	Dictionary<Number> VertexEnumeration<Number>::findFirstVertex() {
		unsigned d = mHsv[0].dimension();
		unsigned n0 = mHsv.size();
		Dictionary<Number> dictionary = Dictionary<Number>(mHsv);
		while(dictionary.fixOutOfBounds()) {}
		dictionary.nonSlackToBase();
		std::set<unsigned> hyperplanes;
		for(unsigned index=0;index<n0;++index) {
			if(dictionary.constrainSet().isSaturated(index)) {
				hyperplanes.insert(index);
			}
		}
		std::set<unsigned> frozenCols = dictionary.toCobase(hyperplanes);
		for(unsigned colIndex=0; colIndex<d;++colIndex) {
			if(frozenCols.end()==frozenCols.find(colIndex)) {
				dictionary.pushToBounds(colIndex);
			}
		}
		return dictionary;
	}
	
	template<typename Number>
	int VertexEnumeration<Number>::linearIndependance(std::map<int,vector_t<Number>> collection, vector_t<Number>& candidateRef) const {
		for(typename std::map<int,vector_t<Number>>::iterator it=collection.begin(); it!=collection.end(); ++it) {
			Number ratio = (candidateRef[it->first])/(it->second)[it->first];
			for(int i=0;i<candidateRef.size();++i) {
				candidateRef[i] -= ratio*it->second[i];
			}
		}
		int nonNulIndex = -1;
		int i=0;
		while(nonNulIndex<0 && i<candidateRef.size()) {
			if(candidateRef[i]!=0) {
				return i;
			}
			++i;
		}
		return nonNulIndex;
	}
	
	template<typename Number>
	std::vector<unsigned> VertexEnumeration<Number>::findIndepHs() const {
		unsigned dim = mHsv[0].dimension();
		unsigned count = 0;
		unsigned index = 0;
		std::vector<unsigned> selection;
		std::map<int,vector_t<Number>> collection;
		while(count<dim) {//assuming there are enought independant halfspaces
			vector_t<Number> candidate = mHsv[index].normal();
			vector_t<Number>& candidateRef = candidate;
			int nonNulIndex = linearIndependance(collection, candidateRef);
			if(nonNulIndex!=-1) {
				collection.insert(std::pair<int,vector_t<Number>>(nonNulIndex,candidate));
				++count;
				selection.push_back(index);
			}
			++index;
		}
		return selection;
	}
	
	template<typename Number>
	Point<Number> VertexEnumeration<Number>::findIntersection(const std::vector<unsigned>& selectionRef) const {
		unsigned dimension = selectionRef.size();
		matrix_t<Number> mat = matrix_t<Number>(dimension, dimension);
		vector_t<Number> vect = vector_t<Number>(dimension);
		for(unsigned rowIndex=0; rowIndex<dimension; ++rowIndex) {
			for(unsigned colIndex=0; colIndex<dimension; ++colIndex) {
				mat(rowIndex,colIndex) = (mHsv[selectionRef[rowIndex]]).normal()[colIndex];
			}
		vect[rowIndex] = (mHsv[selectionRef[rowIndex]]).offset();
		}
		return Point<Number>(mat.fullPivLu().solve(vect));
	}
	
	
	template<typename Number>
	bool VertexEnumeration<Number>::findPositiveConstrains() {
		try{	
			Dictionary<Number>dictionary(findFirstVertex());
			unsigned dimension = dictionary.cobasis().size()-1;
			unsigned constrainsCount = dictionary.basis().size()-1;
			matrix_t<Number> A1 = matrix_t<Number>(dimension, dimension);
			matrix_t<Number> A2 = matrix_t<Number>(mHsv.size()-dimension, dimension);
			vector_t<Number> b1 = vector_t<Number>(dimension);
			std::vector<std::size_t> mB;
			std::vector<std::size_t> mN;
			for(unsigned rowIndex=0; rowIndex<dimension; ++rowIndex) {
				for(unsigned colIndex=0; colIndex<dimension; ++colIndex) {
				mHsv[dictionary.cobasis()[rowIndex]-1];
				(mHsv[dictionary.cobasis()[rowIndex]-1]).normal();
					A1(rowIndex,colIndex) = (mHsv[dictionary.cobasis()[rowIndex]-1]).normal()[colIndex];
				}
				b1[rowIndex] = (mHsv[dictionary.cobasis()[rowIndex]-1]).offset();
			}
			matrix_t<Number> invA1 = A1.inverse();
			unsigned skiped = 0;
			for(unsigned rowIndex=0; rowIndex<constrainsCount; ++rowIndex) {
				if(dictionary.basis()[rowIndex]-1<constrainsCount) {
					for(unsigned colIndex=0; colIndex<dimension; ++colIndex) {
						A2(rowIndex-skiped,colIndex) = (mHsv[dictionary.basis()[rowIndex]-1]).normal()[colIndex];
					} 
				} else {++skiped;}
			}
			matrix_t<Number> newDictionary = matrix_t<Number>(constrainsCount-dimension+1, dimension+1);//faire la derniere ligne
			skiped = 0;
			for(unsigned rowIndex=0; rowIndex<constrainsCount; ++rowIndex) {
				if(dictionary.basis()[rowIndex]-1<constrainsCount) {
					for(unsigned colIndex=0; colIndex<dimension; ++colIndex) {
					newDictionary(rowIndex-skiped,colIndex)=0;
						for(unsigned index=0; index<dimension; ++index) {
							newDictionary(rowIndex-skiped,colIndex)+=A2(rowIndex-skiped,index)*invA1(index,colIndex);
						}
					}
					newDictionary(rowIndex-skiped,dimension)= (mHsv[dictionary.basis()[rowIndex]-1]).offset();
					for(unsigned colIndex=0; colIndex<dimension; ++colIndex) {
						newDictionary(rowIndex-skiped,dimension)-=newDictionary(rowIndex-skiped,colIndex)*b1[colIndex];
					}
				} else {++skiped;}
			}
		
			for(unsigned colIndex=0; colIndex<dimension; ++colIndex) {
				newDictionary(constrainsCount-dimension,colIndex)=Number(-1);
			}
		
			for(unsigned i=1; i<constrainsCount-dimension+1; ++i){
				mB.push_back(std::size_t(i));
			}
			mB.push_back(std::size_t(constrainsCount+1));
			for(unsigned i=constrainsCount-dimension+1; i<constrainsCount+1; ++i){
				mN.push_back(std::size_t(i));
			}
			mN.push_back(std::size_t(constrainsCount+2));
		
			mDictionaries.push_back(Dictionary<Number>(newDictionary,mB,mN));
		
			mPivotingMatrix = invA1;
			mOffset = b1;
		} 
		catch(string const& message) {
			cout << message;
			return false;
		}
		return true;
	}
	
	template<typename Number>
	void VertexEnumeration<Number>::toGeneralCoordinates() {
		for(unsigned index=0; index<mPositivePoints.size(); ++index) {
			mPoints.push_back(Point<Number>(mPivotingMatrix*(mOffset-mPositivePoints[index].rawCoordinates())));
		}
		for(const auto& cone: mPositiveCones) {
			mCones.push_back((mPivotingMatrix*(-cone)));
		}
	}
	
	template<typename Number>
	void VertexEnumeration<Number>::findLinealtySpace() {
		unsigned dim = mHsv[0].dimension();
		unsigned count = 0;
		unsigned index = 0;
		std::vector<Number> norms;
		std::vector<vector_t<Number>> collection;
		while(count<dim&&index<mHsv.size()) {
			vector_t<Number> candidate = mHsv[index].normal();
			for(unsigned vectorIndex=0;vectorIndex<count;++vectorIndex){
				candidate=candidate-collection[vectorIndex]*((collection[vectorIndex].dot(candidate)/norms[vectorIndex]));
			}
			int i=0;
			while(i<candidate.size()) {
				if(candidate[i]!=0) {break;}
				++i;
			}
			if(i<candidate.size()) {
				collection.push_back(candidate);
				norms.push_back(candidate.dot(candidate));
				++count;
			}
			++index;
		}
		index = 0;
		unsigned linealtySpaceSize = dim-count;		
		while(count<dim) {
			vector_t<Number> baseVector = vector_t<Number>::Zero(dim);
			baseVector[index]=Number(-1);
			for(unsigned vectorIndex=0;vectorIndex<count;++vectorIndex){
				baseVector=baseVector-collection[vectorIndex]*(collection[vectorIndex].dot(baseVector)/norms[vectorIndex]);
			}
			int i=0;
			while(i<baseVector.size()) {
				if(baseVector[i]!=0) {break;}
				++i;
			}
			if(i<baseVector.size()) {
				collection.push_back(baseVector);
				norms.push_back(baseVector.dot(baseVector));
				++count;
			}
			++index;
		}
		for(index = 0; index<linealtySpaceSize; ++index) {
			mLinealtySpace.push_back(collection[dim-index-1]);
		}
	}
	
	template<typename Number>
	void VertexEnumeration<Number>::addLinealtyConstrains() {
		for(unsigned linealtyIndex=0;linealtyIndex<mLinealtySpace.size();++linealtyIndex) {
			mHsv.push_back(Halfspace<Number>(mLinealtySpace[linealtyIndex],Number(0)));
			mHsv.push_back(Halfspace<Number>(Number(-1)*mLinealtySpace[linealtyIndex],Number(0)));
		}
	}
	
	
	/*		pices of the first findFirstVertex
	template<typename Number>
	Point<Number> VertexEnumeration<Number>::findFirstVertex() {
		unsigned d = mHsv[0].dimension();
		unsigned n0 = mHsv.size();
		std::vector<unsigned> violated;
		unsigned indexViolated=0;
		std::vector<unsigned> IndependantHalfspaces = findIndepHs();
		std::vector<unsigned>& IndependantHalfspacesRef = IndependantHalfspaces;
		Point<Number> externalPoint = findIntersection(IndependantHalfspacesRef);
		cout << "\nexternalPoint:" << externalPoint <<"\n\n";
		for(unsigned i=0;i<n0;++i) {
			if(not(mHsv[i].holds(externalPoint.rawCoordinates()))) {
				violated.push_back(i);
			}
		}
		cout << "\nviolated:" << violated.size() <<"\n\n";
		cout << "violated[0]:" << violated[0] <<"\n";
		cout << "violated[1]:" << violated[1] <<"\n";
		if(violated.size()==0) {
			return externalPoint;
		}
		
		matrix_t<Number> tab = matrix_t<Number>::Zero(n0+1, d*2+1+violated.size());
		//coef
		for(unsigned i=0;i<n0;++i) {
			if(mHsv[i].holds(externalPoint.rawCoordinates())) {
				tab(i,d*2+violated.size()) = mHsv[i].offset();
				for(unsigned j=0;j<d;++j) {			
					tab(i,j*2) = -mHsv[i].normal()[j];
					tab(i,j*2+1) = mHsv[i].normal()[j]; 
					tab(i,d*2+violated.size()) -= mHsv[i].normal()[j]*externalPoint.rawCoordinates()[j];
				}

			} else {
				tab(i,d*2+violated.size()) = -mHsv[i].offset();
				tab(i,d*2+indexViolated++) = 1;
				for(unsigned j=0;j<d;++j) {
					tab(i,j*2) = mHsv[i].normal()[j];
					tab(i,j*2+1) = -mHsv[i].normal()[j];
					tab(i,d*2+violated.size()) += mHsv[i].normal()[j]*externalPoint.rawCoordinates()[j]; 
				}
			}
		}
		
		//cost function
		for(unsigned j=0;j<d*2+violated.size();++j) {
			for(unsigned i=0;i<violated.size();++i) {
				tab(n0,j) -= tab(violated[i],j);
			}
		}
	
		for(unsigned i=0; i<unsigned(tab.rows()); ++i) {
			for(unsigned j=0; j<unsigned(tab.cols()); ++j) {
				cout << tab(i,j);
				cout << ";";
			}
			cout << "\n";
		}

		std::vector<std::size_t> B;
		std::vector<std::size_t> N;
		
		for(unsigned i=1; i<n0+1; ++i){
			B.push_back(std::size_t(i));
		}
		B.push_back(std::size_t(n0+violated.size()+d*2+1));
		for(unsigned i=n0+1; i<n0+violated.size()+d*2+1; ++i){
			N.push_back(std::size_t(i));
		}
		N.push_back(std::size_t(n0+violated.size()+d*2+2));
		Dictionary<Number> dictionary = Dictionary<Number>(tab, B, N);
		
		cout << "\nfirst dictionary:";
		dictionary.printDictionary();
		cout << "\n\n";
		std::size_t a = std::size_t(0);
		std::size_t b = std::size_t(0);
		std::size_t& i = a;
		std::size_t& j = b;
		
		cout << "\n ------------------------\n";
		cout << "\n select\n";
		while(dictionary.selectBlandPivot(i,j)) {
			cout << "\n pivot\n";
			dictionary.pivot(i,j);
			dictionary.printDictionary();cout << "\n select\n";
		}
		cout << "\n ------------------------\n";
		std::vector<Number> finalCoordinates;
		for(unsigned coord = 0; coord<d; ++coord) {
			finalCoordinates.push_back(dictionary.toPoint().rawCoordinates()[coord*2]-dictionary.toPoint().rawCoordinates()[coord*2+1]
																		+ externalPoint.rawCoordinates()[coord]);
		}
		cout << "\nresulting point: " << Point<Number>(finalCoordinates) <<"\n";
		return Point<Number>(finalCoordinates);
	}*/
	
	
	
	
} // namespace
