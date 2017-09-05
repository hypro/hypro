#include "vertexEnumeration.h"
#define CHULL_DBG
namespace hypro {

	template<typename Number>
	void VertexEnumeration<Number>::increment(Eigen::Index& i, Eigen::Index& j, std::size_t maxJ) {
		++j; if(j>= Eigen::Index(maxJ)){j=0;++i;};
		DEBUG("hypro.vertexEnumeration" ,": i=" << i << ", j=" << j);
	}

	template<typename Number>
	VertexEnumeration<Number>::VertexEnumeration(const std::vector<Halfspace<Number>>& hsv) : mHsv(hsv) {}

	template<typename Number>
	VertexEnumeration<Number>::VertexEnumeration(const matrix_t<Number>& constraints, const vector_t<Number>& constants) {
		assert(constraints.rows() == constants.rows());
		for(unsigned i = 0; i < constraints.rows(); ++i) {
			mHsv.emplace_back(Halfspace<Number>(constraints.row(i), constants(i)));
		}
	}

	template<typename Number>
	std::vector<Halfspace<Number>> VertexEnumeration<Number>::getHsv() const {
		return mHsv;
	}

	template<typename Number>
	std::vector<Dictionary<Number>> VertexEnumeration<Number>::getDictionaries() const {
		return mDictionaries;
	}

	template<typename Number>
	std::vector<Point<Number>> VertexEnumeration<Number>::getPositivePoints() const {
		return mPositivePoints;
	}

	template<typename Number>
	void VertexEnumeration<Number>::printPositivePoints() const {
		for(const auto& p : mPositivePoints) {
			std::cout << p << std::endl;
		}
	}

	template<typename Number>
	std::vector<Point<Number>> VertexEnumeration<Number>::getPoints() const {
		return mPoints;
	}

	template<typename Number>
	void VertexEnumeration<Number>::printPoints() const {
		for(const auto& p : mPoints) {
			std::cout << p << std::endl;
		}
	}

	template<typename Number>
	std::vector<vector_t<Number>> VertexEnumeration<Number>::getLinealtySpace() const {
		return mLinealtySpace;
	}

	template<typename Number>
	void VertexEnumeration<Number>::printLinealtySpace() const {
	for(const auto& l : mLinealtySpace) {
			std::cout << l << std::endl;
		}
	}

	template<typename Number>
	std::vector<vector_t<Number>> VertexEnumeration<Number>::getPositiveCones() const {
		return mPositiveCones;
	}

	template<typename Number>
	void VertexEnumeration<Number>::printPositiveCones() const {
	for(const auto& c : mPositiveCones) {
			std::cout << c << std::endl;
		}
	}

	template<typename Number>
	std::vector<vector_t<Number>> VertexEnumeration<Number>::getCones() const {
		return mCones;
	}

	template<typename Number>
	void VertexEnumeration<Number>::printCones() const {
	for(const auto& c:mCones) {
			std::cout << c << std::endl;
		}
	}

	template<typename Number>
	void VertexEnumeration<Number>::enumerateVertices() {
		/*
		DEBUG("hypro.vertexEnumeration","Input:");
		for(const auto& plane : mHsv) {
			DEBUG("hypro.vertexEnumeration",plane);
		}
		*/

		if(findPositiveConstrains()) {//if non empty
			enumerateDictionaries();
			enumerateVerticesEachDictionary();
			toGeneralCoordinates();

			/*
			DEBUG("hypro.vertexEnumeration","Output:");
			for(const auto& vertex : mPoints) {
				DEBUG("hypro.vertexEnumeration",vertex);
			}
			*/

			#ifndef NDEBUG
			for(const auto& vertex : mPoints) {
				for(const auto& plane : mHsv) {
					if(!plane.contains(vertex)) {
						WARN("hypro.vertexEnumeration","plane " << plane << " does not contain " << vertex);
						WARN("hypro.vertexEnumeration","distance: " << (plane.normal().dot(vertex.rawCoordinates()) - plane.offset()));
					}
					assert(plane.contains(vertex));
				}
			}
			#endif
		}
	}

	template<typename Number>
	void VertexEnumeration<Number>::enumerateVerticesNaive() {
		if(!mHsv.empty()) {
			unsigned dim = mHsv.begin()->dimension();

			Permutator permutator(mHsv.size(), dim);
			std::vector<std::size_t> permutation;
			while(!permutator.end()) {
				permutation = permutator();

				matrix_t<Number> A( dim, dim );
				vector_t<Number> b( dim );
				unsigned pos = 0;
				for(auto planeIt = permutation.begin(); planeIt != permutation.end(); ++planeIt) {
					A.row(pos) = mHsv.at(*planeIt).normal().transpose();
					b(pos) = mHsv.at(*planeIt).offset();
					++pos;
				}

				Eigen::FullPivLU<matrix_t<Number>> lu_decomp( A );
				if ( lu_decomp.rank() < A.rows() ) {
					continue;
				}

				vector_t<Number> res = lu_decomp.solve( b );

				// Check if the computed vertex is a real vertex
				bool outside = false;
				for(unsigned planePos = 0; planePos < mHsv.size(); ++planePos) {
					bool skip = false;
					for(unsigned permPos = 0; permPos < permutation.size(); ++permPos) {
						if(planePos == permutation.at(permPos)) {
							skip = true;
							break;
						}
					}

					if(!skip) {
						if( !carl::AlmostEqual2sComplement(mHsv.at(planePos).offset(), mHsv.at(planePos).normal().dot(res), default_double_comparison_ulps) && mHsv.at(planePos).offset() - mHsv.at(planePos).normal().dot(res) < 0 ) {
							outside = true;
							break;
						}
					}
				}
				if(!outside) {
					// insert, if no duplicate
					Point<Number> tmp(res);
					if(std::find(mPoints.begin(), mPoints.end(), tmp) == mPoints.end()) {
						mPoints.push_back(tmp);
					}
				}
			}
		}
	}

	template<typename Number>
	void VertexEnumeration<Number>::enumerateVertices(Dictionary<Number>& dictionary) {
		assert(dictionary.isOptimal());
		std::set<vector_t<Number>> cones =dictionary.findCones();
		for(const auto& cone: cones) {
			mPositiveCones.insert(cone);
		}
		Eigen::Index a=0;
		Eigen::Index b=0;
		int depth=0;//used to know when to stop
		Eigen::Index& i=a;
		Eigen::Index& j=b;
		Eigen::Index m = Eigen::Index(dictionary.basis().size()-1);//different than the article
		Eigen::Index n = Eigen::Index(dictionary.cobasis().size()-1);
		while(i<m || depth>=0){
			while(i<m && not(dictionary.reverse(i,j))){
				VertexEnumeration<Number>::increment(i,j,n);
			}
			if(i<m){
				assert(dictionary.isPrimalFeasible());
				DEBUG("hypro.vertexEnumeration","Dictionary before step down:");
				dictionary.printDictionary();
				COUT("\n\n\n" << std::endl);
				dictionary.pivot(i,j);
				assert(dictionary.isPrimalFeasible());
				#ifndef NDEBUG
				//size_t tmpI,tmpJ;
				Eigen::Index tmpI,tmpJ;
				dictionary.selectBlandPivot(tmpI,tmpJ);
				if(!(tmpI == i && tmpJ == j)) {
					WARN("hypro.vertexEnumeration","Chosen pivot: " << tmpI << ", " << tmpJ << ", assumed was: " << i << ", " << j  << ", dict after pivot: ");
					dictionary.printDictionary();
					COUT("\n\n\n" << std::endl);
				}
				assert(tmpI == i && tmpJ == j);
				#endif
				DEBUG("hypro.vertexEnumeration","(Step down) Pivot " << i << ", " << j << " is a valid reverse pivot.");
				if(dictionary.isLexMin()) {
					DEBUG("hypro.vertexEnumeration","new point:");
					DEBUG("hypro.vertexEnumeration",dictionary);
					DEBUG("hypro.vertexEnumeration",dictionary.toPoint());
					mPositivePoints.push_back(dictionary.toPoint());
				}
				std::set<vector_t<Number>> cones =dictionary.findCones();
				for(const auto& cone: cones) {
					DEBUG("hypro.vertexEnumeration","cone found");
					mPositiveCones.insert(cone);
				}
				i=0;j=0;++depth;
			} else {
				if(depth>0) {
					assert(dictionary.isPrimalFeasible());
					dictionary.selectBlandPivot(i,j);
					dictionary.pivot(i,j);
					DEBUG("hypro.vertexEnumeration","(Step up) Pivot " << i << ", " << j << " is a valid Bland pivot.");
					assert(dictionary.isPrimalFeasible());
				}
				VertexEnumeration<Number>::increment(i,j,n);
				--depth;
			}
		}
	}

	template<typename Number>
	void VertexEnumeration<Number>::enumerateVerticesEachDictionary() {
		mPositivePoints.push_back(mDictionaries[0].toPoint());
		for(std::size_t i = 0; i<mDictionaries.size(); ++i) {
			DEBUG("hypro.vertexEnumeration","Next dictionary ---------------------");
			DEBUG("hypro.vertexEnumeration",mDictionaries[i]);
			enumerateVertices(mDictionaries[i]);
		}
	}

	template<typename Number>
	void VertexEnumeration<Number>::enumerateDictionaries() {
		Dictionary<Number> dictionary = mDictionaries[0];
		assert(dictionary.isOptimal());
		Eigen::Index a=0;
		Eigen::Index b=0;
		int depth=0;
		std::vector<Eigen::Index> basisAux = dictionary.findZeros();//locate degenerated variables
		std::vector<Number> memory;
		Eigen::Index& i=a;
		Eigen::Index& j=b;
		Eigen::Index m = Eigen::Index(basisAux.size());//different than the article
		Eigen::Index m2 = Eigen::Index(dictionary.basis().size()-1);
		Eigen::Index n = Eigen::Index(dictionary.cobasis().size()-1);
		for(Eigen::Index rowIndex = 0; rowIndex <= m2; ++rowIndex) {
			memory.push_back(dictionary.get(rowIndex,n));// to restore the constant column
		}
		dictionary.setOnes(basisAux);
		while(i<m || depth>=0){
			while(i<m){
				if(!dictionary.reverseDual(i,j,basisAux)) {
					VertexEnumeration<Number>::increment(i,j,n);
				} else {break;}
			}
			if(i<m){
				assert(dictionary.isDualFeasible());
				DEBUG("hypro.vertexEnumeration","(Step down) Pivot " << basisAux[i] << ", " << j << " is a valid reverse pivot.");
				dictionary.pivot(basisAux[i],j);
				assert(dictionary.isDualFeasible());
				//dictionary.printDictionary();
				Dictionary<Number> newDictionary = (Dictionary<Number>(dictionary));
				for(Eigen::Index rowIndex = 0; rowIndex <= m2; ++rowIndex) {
					newDictionary.setValue(rowIndex,n,memory[rowIndex]);
				}
				mDictionaries.push_back(newDictionary);
				i=0;j=0;++depth;
			} else {
				if(depth>0) {
					assert(dictionary.isDualFeasible());
					dictionary.selectDualBlandPivot(i,j,basisAux);
					DEBUG("hypro.vertexEnumeration","(Step up) Pivot " << basisAux[i] << ", " << j << " is a valid pivot.");
					assert(dictionary.selectDualBlandPivot(i,j,basisAux));
					assert(i < basisAux.size());
					dictionary.pivot(basisAux[i],j);
					assert(dictionary.isDualFeasible());
					//dictionary.printDictionary();
				}
				VertexEnumeration<Number>::increment(i,j,n);
				--depth;
			}
		}
		DEBUG("hypro.vertexEnumeration","nb dico = " << mDictionaries.size());
	}

	template<typename Number>
	Dictionary<Number> VertexEnumeration<Number>::findFirstVertex() {
		Eigen::Index d = Eigen::Index(mHsv[0].dimension());
		Eigen::Index n0 = Eigen::Index(mHsv.size());
		Dictionary<Number> dictionary = Dictionary<Number>(mHsv);
		DEBUG("hypro.vertexEnumeration","first dictionary");
		DEBUG("hypro.vertexEnumeration",dictionary);
		DEBUG("hypro.vertexEnumeration",dictionary.constrainSet());
		while(dictionary.fixOutOfBounds()) {}//tries to reach the feasible area, may throw empty exeption
		DEBUG("hypro.vertexEnumeration","fixOutOfBounds");
		DEBUG("hypro.vertexEnumeration",dictionary);
		DEBUG("hypro.vertexEnumeration",dictionary.constrainSet());
		dictionary.nonSlackToBase(mLinealtySpace);//finds linealty
		DEBUG("hypro.vertexEnumeration","nonSlackToBase");
		DEBUG("hypro.vertexEnumeration",dictionary);
		DEBUG("hypro.vertexEnumeration",dictionary.constrainSet());
		DEBUG("hypro.vertexEnumeration","lineality space size: " << mLinealtySpace.size());
		addLinealtyConstrains();

		// At this point we need to start over again, as we added artificial constraints for the lineality space.

		matrix_t<Number> dictio = matrix_t<Number>::Zero(mHsv.size()+1, d+1);
		for(Eigen::Index colIndex=0;colIndex<=d;++colIndex) {//copy
			for(Eigen::Index rowIndex=0;rowIndex<n0;++rowIndex) {
				dictio(rowIndex,colIndex) = dictionary.get(rowIndex,colIndex);
			}
			dictio(mHsv.size(),colIndex) = dictionary.get(n0,colIndex);
		}
		for(Eigen::Index rowIndex=0;rowIndex < n0;++rowIndex) {//build the linealty constrains, the part with the var in the basis
			if(std::size_t(dictionary.basis()[rowIndex]) >= dictionary.basis().size()) {
				for(Eigen::Index colIndex=0;colIndex<d;++colIndex) {
					for(std::size_t rowIndexLinealty=0;rowIndexLinealty<mLinealtySpace.size();++rowIndexLinealty) {
						dictio(n0+2*rowIndexLinealty,colIndex)-=
								dictionary.get(rowIndex,colIndex)*mLinealtySpace[rowIndexLinealty][dictionary.basis()[rowIndex]-dictionary.basis().size()];
					}
				}
			}
		}
		for(Eigen::Index colIndex=0;colIndex<d;++colIndex) {//build the linealty constrains, the part with the var in the cobasis
			for(std::size_t rowIndexLinealty=0;rowIndexLinealty<mLinealtySpace.size();++rowIndexLinealty) {
				if( std::size_t(dictionary.cobasis()[colIndex]) >= dictionary.basis().size()) {
					dictio(n0+2*rowIndexLinealty,colIndex)-=mLinealtySpace[rowIndexLinealty][colIndex];
				}
				dictio(n0+2*rowIndexLinealty+1,colIndex) = -dictio(n0+2*rowIndexLinealty,colIndex);
			}
		}
		std::vector<Eigen::Index> basis = dictionary.basis();
		std::vector<Eigen::Index> cobasis = dictionary.cobasis();
		for(auto& index: basis) {
			if(index>n0) {index+= Eigen::Index(2*mLinealtySpace.size());};
		}
		for(auto& index: cobasis) {
			if(index>n0) {index+= Eigen::Index(2*mLinealtySpace.size());};
		}
		Eigen::Index back = basis.back();
		basis.pop_back();

		for(std::size_t index = n0+1;index<=mHsv.size();++index) {basis.push_back(Eigen::Index(index));}
		basis.push_back(back);
		ConstrainSet<Number> constrains;
		for(Eigen::Index index=0; index<n0;++index) {
			constrains.add(dictionary.constrainSet().get(index));
		}
		for(std::size_t index=0; index<2*mLinealtySpace.size();++index) {
			constrains.add(std::tuple<std::pair<bool,Number>,std::pair<bool,Number>,Number>(
					std::pair<bool,Number>(false,Number(0)),std::pair<bool,Number>(true,Number(0)),Number(0)));//fix
		}
		for(Eigen::Index index=n0; index<n0+d;++index) {
			constrains.add(dictionary.constrainSet().get(index));
		}
		Dictionary<Number> newDictionary = Dictionary<Number>(dictio,basis,cobasis,constrains);//creation of a new dictionary with the linealty constrains
		while(newDictionary.fixOutOfBounds()) {}
		DEBUG("hypro.vertexEnumeration","the new dico");
		DEBUG("hypro.vertexEnumeration",dictionary);
		DEBUG("hypro.vertexEnumeration",dictionary.constrainSet());
		newDictionary.nonSlackToBase();
		std::set<Eigen::Index> hyperplanes;
		for(std::size_t index=0;index<basis.size();++index) {//search for already saturated constrains
			if(newDictionary.constrainSet().isSaturated(index)) {
				hyperplanes.insert(Eigen::Index(index));
			}
		}
		std::set<Eigen::Index> frozenCols = newDictionary.toCobase(hyperplanes);
		DEBUG("hypro.vertexEnumeration","frozen cols:");
		DEBUG("hypro.vertexEnumeration",frozenCols);
		for(Eigen::Index colIndex=0; colIndex < Eigen::Index(d);++colIndex) {
			if(frozenCols.end()==frozenCols.find(colIndex)) {
				newDictionary.pushToBounds(colIndex);
			}
		}
		return newDictionary;
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
	std::vector<std::size_t> VertexEnumeration<Number>::findIndepHs() const {
		std::size_t dim = mHsv[0].dimension();
		std::size_t count = 0;
		std::size_t index = 0;
		std::vector<std::size_t> selection;
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
	Point<Number> VertexEnumeration<Number>::findIntersection(const std::vector<std::size_t>& selectionRef) const {
		std::size_t dimension = selectionRef.size();
		matrix_t<Number> mat = matrix_t<Number>(dimension, dimension);
		vector_t<Number> vect = vector_t<Number>(dimension);
		for(std::size_t rowIndex=0; rowIndex<dimension; ++rowIndex) {
			for(std::size_t colIndex=0; colIndex<dimension; ++colIndex) {
				mat(rowIndex,colIndex) = (mHsv[selectionRef[rowIndex]]).normal()[colIndex];
			}
		vect[rowIndex] = (mHsv[selectionRef[rowIndex]]).offset();
		}
		return Point<Number>(mat.fullPivLu().solve(vect));
	}


	template<typename Number>
	bool VertexEnumeration<Number>::findPositiveConstrains() {
		try{
			if(mHsv.size()==0) {
				vector_t<Number> one = vector_t<Number>(1);
				one[0]=1;
				mLinealtySpace.push_back(one);
				throw string("\n WARNING: no constrains. \n");
			}
			Dictionary<Number> dictionary(findFirstVertex());
			DEBUG("hypro.vertexEnumeration","findFirstVertex");
			DEBUG("hypro.vertexEnumeration",dictionary);
			DEBUG("hypro.vertexEnumeration",dictionary.constrainSet());
			std::size_t dimension = dictionary.cobasis().size()-1;
			Eigen::Index constrainsCount = dictionary.basis().size()-1;
			matrix_t<Number> A1 = matrix_t<Number>(dimension, dimension);
			matrix_t<Number> A2 = matrix_t<Number>(mHsv.size()-dimension, dimension);
			vector_t<Number> b1 = vector_t<Number>(dimension);
			std::vector<Eigen::Index> mB;
			std::vector<Eigen::Index> mN;
			for(std::size_t rowIndex=0; rowIndex<dimension; ++rowIndex) {
				for(std::size_t colIndex=0; colIndex<dimension; ++colIndex) {
					A1(rowIndex,colIndex) = (mHsv.at(dictionary.cobasis()[rowIndex]-1)).normal()[colIndex];
				}
				b1[rowIndex] = (mHsv.at(dictionary.cobasis()[rowIndex]-1)).offset();
			}

			// A1*y <= b1 describes the first vertex y? -> during find first vertex, non-original variables are guaranteed to be in the co-basis (nonSlackToBase).

			matrix_t<Number> invA1 = A1.inverse();
			std::size_t skipped = 0;
			for(Eigen::Index rowIndex=0; rowIndex<constrainsCount; ++rowIndex) {
				if(dictionary.basis()[rowIndex]-1<constrainsCount) { // pick indices, which correspond to an original constraint in mHsv and skip original variables.
					for(std::size_t colIndex=0; colIndex<dimension; ++colIndex) {
						A2(rowIndex-skipped,colIndex) = (mHsv.at(dictionary.basis()[rowIndex]-1)).normal()[colIndex];
					}
				} else {++skipped;}
			}

			// Original A is now split into A1 and A2, where A1 defines the initial vertex and A2 contains the rest of constraints.

			DEBUG("hypro.vertexEnumeration","A1: " << A1);
			DEBUG("hypro.vertexEnumeration","b1: " << b1);
			DEBUG("hypro.vertexEnumeration","A2: " << A2);

			matrix_t<Number> newDictionary = matrix_t<Number>::Zero(constrainsCount-dimension+1, dimension+1);//faire la derniere ligne
			skipped = 0;
			for(Eigen::Index rowIndex=0; rowIndex<constrainsCount; ++rowIndex) {
				if(dictionary.basis()[rowIndex]-1<constrainsCount) { // again only pick those indices, which correspond to original constraints.
					for(std::size_t colIndex=0; colIndex<dimension; ++colIndex) {
						//newDictionary(rowIndex-skipped,colIndex)=0; // Set all zero? -> removed by initiating all to zero in the creation of the matrix.
						for(std::size_t index=0; index<dimension; ++index) {
							newDictionary(rowIndex-skipped,colIndex)+=A2(rowIndex-skipped,index)*invA1(index,colIndex);
						}
					}
					newDictionary(rowIndex-skipped,dimension)= (mHsv.at(dictionary.basis()[rowIndex]-1)).offset();
					for(std::size_t colIndex=0; colIndex<dimension; ++colIndex) {
						newDictionary(rowIndex-skipped,dimension)-=newDictionary(rowIndex-skipped,colIndex)*b1[colIndex];
					}
				} else {++skipped;}
			}

			// augment a row of all -1 as the optimization function
			for(std::size_t colIndex=0; colIndex<dimension; ++colIndex) {
				newDictionary(constrainsCount-dimension,colIndex)=Number(-1);
			}

			for(Eigen::Index i=1; i<constrainsCount-Eigen::Index(dimension)+1; ++i){
				mB.push_back(i);
			}
			mB.push_back(std::size_t(constrainsCount+1));
			for(Eigen::Index i=constrainsCount-Eigen::Index(dimension)+1; i<constrainsCount+1; ++i){
				mN.push_back(i);
			}
			mN.push_back(constrainsCount+2);

			mDictionaries.push_back(Dictionary<Number>(newDictionary,mB,mN));
			DEBUG("hypro.vertexEnumeration","The newly added dictionary: ");
			DEBUG("hypro.vertexEnumeration",mDictionaries.back());
			assert(mDictionaries.back().isOptimal());

			mPivotingMatrix = invA1;
			mOffset = b1;
		}
		catch(string const& message) {
			cout << message;
			return false;
		}
		DEBUG("hypro.vertexEnumeration","positive constrains");
		DEBUG("hypro.vertexEnumeration",mDictionaries[0]);
		DEBUG("hypro.vertexEnumeration",mDictionaries[0].constrainSet());
		return true;
	}

	template<typename Number>
	void VertexEnumeration<Number>::toGeneralCoordinates() {
		assert(mPoints.empty());
		for(std::size_t index=0; index<mPositivePoints.size(); ++index) {
			mPoints.push_back(Point<Number>(mPivotingMatrix*(mOffset-mPositivePoints.at(index).rawCoordinates())));
		}
		assert(mCones.empty());
		for(const auto& cone: mPositiveCones) {
			mCones.push_back((mPivotingMatrix*(-cone)));
		}
	}

	template<typename Number>
	void VertexEnumeration<Number>::findLinealtySpace() {
		std::size_t dim = mHsv[0].dimension();
		std::size_t count = 0;
		std::size_t index = 0;
		std::vector<Number> norms;
		std::vector<vector_t<Number>> collection;
		while(count<dim&&index<mHsv.size()) {
			vector_t<Number> candidate = mHsv[index].normal();
			for(std::size_t vectorIndex=0;vectorIndex<count;++vectorIndex){
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
		std::size_t linealtySpaceSize = dim-count;
		while(count<dim) {
			vector_t<Number> baseVector = vector_t<Number>::Zero(dim);
			baseVector[index]=Number(-1);
			for(std::size_t vectorIndex=0;vectorIndex<count;++vectorIndex){
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
		for(std::size_t linealtyIndex=0;linealtyIndex<mLinealtySpace.size();++linealtyIndex) {
			mHsv.push_back(Halfspace<Number>(mLinealtySpace[linealtyIndex],Number(0)));
			mHsv.push_back(Halfspace<Number>(Number(-1)*mLinealtySpace[linealtyIndex],Number(0)));
		}
	}

} // namespace hypro
