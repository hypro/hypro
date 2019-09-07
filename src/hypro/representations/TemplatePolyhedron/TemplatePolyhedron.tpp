#pragma once
#include "TemplatePolyhedron.h"

namespace hypro {

	//////// Constructors & Destructors ////////

	//Empty constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT() 
		: mMatrixPtr(nullptr)
		, mVector(vector_t<Number>::Zero(0))
		, mOptimizer(Optimizer<Number>()) 
	{}

	//Regular template polyhedron constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT(const std::size_t dimension, const std::size_t noOfSides, const vector_t<Number>& vec) 
		: mVector(vec)
	{
		//Check if coeff vector has the right length
		if(noOfSides != std::size_t(vec.rows())){
			throw std::invalid_argument("Template polyhedron offset vector length not fitting.");
		}

		//Check if polyhedron will be bounded
		if(noOfSides <= dimension){
			throw std::invalid_argument("Template polyhedron is unbound. Please check the amount of constraints used for building this template polyhedron.");
		}
		
		//compute template matrix and set it as new mMatrixPtr
		auto templateDirs = computeTemplate<Number>(dimension, noOfSides);
		mMatrixPtr = std::make_shared<matrix_t<Number>>(combineRows(templateDirs));
		mOptimizer = Optimizer<Number>(*mMatrixPtr, mVector);
	}

	//Matrix-Vector-constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( const matrix_t<Number>& mat, const vector_t<Number>& vec ) 
		: mMatrixPtr(std::make_shared<matrix_t<Number>>(mat))
		, mVector(vec)
		, mOptimizer(Optimizer<Number>(mat, vec))
	{
		assert(mOptimizer.matrix() == mat);
		assert(mOptimizer.vector() == vec);
		assert(vec.rows() == mMatrixPtr->rows());
	}

	//Shared-ptr-constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( const std::shared_ptr<const matrix_t<Number>>& matPtr, const vector_t<Number>& vec ) 
		: mMatrixPtr(std::shared_ptr<const matrix_t<Number>>(matPtr))
		, mVector(vec)
		, mOptimizer(Optimizer<Number>(*matPtr, vec))
	{
		assert(this->rGetMatrixPtr() == matPtr);
		assert(mOptimizer.matrix() == *matPtr);
		assert(mOptimizer.vector() == vec);
		assert(vec.rows() == mMatrixPtr->rows());
	}

	//Copy constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( const TemplatePolyhedronT<Number,Converter,Setting>& orig ) 
		: mMatrixPtr(orig.rGetMatrixPtr())
		, mVector(orig.vector())
		//, mOptimizer(Optimizer<Number>(*orig.rGetMatrixPtr(), orig.vector()))
	{
		if(orig.rGetMatrixPtr() == nullptr){
			mOptimizer = Optimizer<Number>();
			mOptimizer.setVector(orig.vector());
		} else {
			mOptimizer = Optimizer<Number>(*orig.rGetMatrixPtr(), orig.vector());	
			assert(mVector.rows() == mMatrixPtr->rows());	
		}
		//mOptimizer.setVector(mVector);
		assert(mMatrixPtr == orig.rGetMatrixPtr());
	}

	//Move constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( TemplatePolyhedronT<Number,Converter,Setting>&& orig ) 
		: mMatrixPtr(std::move(orig.rGetMatrixPtr()))
		, mVector(std::move(orig.vector()))	
		//, mOptimizer(Optimizer<Number>(*orig.rGetMatrixPtr(), orig.vector()))
	{
		if(orig.rGetMatrixPtr() == nullptr){
			mOptimizer = Optimizer<Number>();
			mOptimizer.setVector(orig.vector());
		} else {
			mOptimizer = Optimizer<Number>(*orig.rGetMatrixPtr(), orig.vector());	
			assert(mVector.rows() == mMatrixPtr->rows());	
		}
		//mOptimizer.setVector(mVector);
		orig.clear();
		//assert(mVector.rows() == mMatrixPtr->rows());		
		assert(orig.rGetMatrixPtr() == nullptr);
	}

	//Settings constructor
	template<typename Number, typename Converter, typename Setting>
	template<typename SettingRhs, carl::DisableIf< std::is_same<Setting, SettingRhs> > >
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT(const TemplatePolyhedronT<Number,Converter,SettingRhs>& orig)
		: mMatrixPtr(orig.rGetMatrixPtr())
		, mVector(orig.vector())
		//, mOptimizer(Optimizer<Number>(*orig.rGetMatrixPtr(), orig.vector()))
	{
		if(orig.rGetMatrixPtr() == nullptr){
			mOptimizer = Optimizer<Number>();
			mOptimizer.setVector(orig.vector());
		} else {
			mOptimizer = Optimizer<Number>(*orig.rGetMatrixPtr(), orig.vector());	
			assert(mVector.rows() == mMatrixPtr->rows());	
		}
		//mOptimizer.setVector(mVector);
		//assert(mVector.rows() == mMatrixPtr->rows());
		assert(mMatrixPtr == orig.rGetMatrixPtr());
	}

	//////// GeometricObject Interface ////////

	//Copy from HPoly
	template<typename Number, typename Converter, typename Setting>
	bool TemplatePolyhedronT<Number,Converter,Setting>::empty() const {
		
		//Quick checks
		if(mMatrixPtr == nullptr) return true;
		//if(mMatrixPtr->rows() <= 1) return false;

		//Linear time quick checks: 
		//If all coeffs negative -> all directions point towards origin -> unbounded polyhedron infeasible therefore empty
		//If all coeffs positive -> all directions point away from origin -> bounded polyhedron not empty
		bool allNegative = true;
		bool allPositive = true;
		for(int i = 0; i < mVector.rows(); i++){
			if(mVector(i) < 0){
				allPositive = false;
			} 
			if(mVector(i) > 0){
				allNegative = false;
			}
		}
		if(allPositive) return false;
		if(allNegative) return true;	

		//If no quick check triggered: Solve LP
		bool res = !mOptimizer.checkConsistency();
		TRACE("hypro.representations.TPolytope","Optimizer result: " << res);
		return res;
	}

	//Copy from HPoly - is also obsolete 
	template<typename Number, typename Converter, typename Setting>
	Number TemplatePolyhedronT<Number,Converter,Setting>::supremum() const {
		Number max = 0;
		if(this->empty()) return max;	
		auto tmp = this->vertices();
		//assert(!this->empty());
		//assert(!this->vertices().empty());
		for ( const auto &point : this->vertices() ) {
			Number inftyNorm = Point<Number>::inftyNorm( point );
			max = max > inftyNorm ? max : inftyNorm;
		}
		return max;
	}

	//The (slow) HPoly way
	template<typename Number, typename Converter, typename Setting>
	std::vector<Point<Number>> TemplatePolyhedronT<Number,Converter,Setting>::vertices( const matrix_t<Number>& ) const {
		if(this->empty()) return std::vector<Point<Number>>();
		typename Converter::VPolytope tmp(this->matrix(), this->vector());
		return tmp.vertices();
	}

	template<typename Number, typename Converter, typename Setting>
	EvaluationResult<Number> TemplatePolyhedronT<Number,Converter,Setting>::evaluate( const vector_t<Number>& _direction, bool ) const {
		if(this->empty()) return EvaluationResult<Number>( Number(0), SOLUTION::INFEAS );
		return mOptimizer.evaluate(_direction, true);
	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<EvaluationResult<Number>> TemplatePolyhedronT<Number,Converter,Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
		if(this->empty()) return std::vector<EvaluationResult<Number>>();
		std::vector<EvaluationResult<Number>> res;
		for(int i = 0; i < _directions.rows(); i++){
			res.emplace_back(mOptimizer.evaluate(_directions.row(i), useExact));
		}
		return res;
	}

	template<typename Number, typename Converter, typename Setting>
	std::size_t TemplatePolyhedronT<Number,Converter,Setting>::dimension() const {
		if(mMatrixPtr == nullptr) return std::size_t(0);
		return mMatrixPtr->cols();
	}

	template<typename Number, typename Converter, typename Setting>
	void TemplatePolyhedronT<Number,Converter,Setting>::removeRedundancy() {
		//TODO: is that even permitted to remove constraints from the matrix?
		//HPoly method: optimize, then get redundant constraints, then remove the redundant constraints
		//Time: LP + LP + linear
		if(!mNonRedundant){
			std::vector<std::size_t> redundant = mOptimizer.redundantConstraints();
			std::sort(redundant.begin(), redundant.end());
			if(!redundant.empty()){
				matrix_t<Number> nonRedundantMatrix = matrix_t<Number>::Zero(mMatrixPtr->rows() - redundant.size(), mMatrixPtr->cols());
				vector_t<Number> nonRedundantVector = vector_t<Number>::Zero(mMatrixPtr->rows() - redundant.size());
				int lastUnfilledRow = nonRedundantMatrix.rows()-1;
				for(std::size_t i = mMatrixPtr->rows()-1; i >= 0; i--){
					std::size_t redundantRow = redundant.back();
					if(i != redundantRow){
						nonRedundantMatrix.row(lastUnfilledRow) = mMatrixPtr->row(i);
						nonRedundantVector(lastUnfilledRow) = mVector(i);
						lastUnfilledRow--;
					} else {
						redundant.pop_back();
					}
					if(redundant.empty()) break;
				}
				assert(redundant.empty());
				mMatrixPtr = std::move(std::make_shared<matrix_t<Number>>(nonRedundantMatrix));
				mVector = std::move(nonRedundantVector);
			}
			mNonRedundant = true;
		}
		//If a plane has the same offset as another plane & normal is linearly dependent -> plane redundant
		//Time: 
		//If a plane is only a tangent plane to a point, then it is redundant either
		//Assume polytope is convex and bounded: For each plane, shift it only a bit away, if point defined by intersection of three planes still inside, then plane redundant
		//But there are still redundant planes left
	}

	template<typename Number, typename Converter, typename Setting>
	std::size_t TemplatePolyhedronT<Number,Converter,Setting>::size() const {
		return sizeof(*mMatrixPtr) + sizeof(mVector);
	}

	template<typename Number, typename Converter, typename Setting>
	const TemplatePolyhedronT<Number,Converter,Setting>& TemplatePolyhedronT<Number,Converter,Setting>::reduceNumberRepresentation() {
		return this;
	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<bool,bool> TemplatePolyhedronT<Number,Converter,Setting>::checkFullInsideFullOutside(const vector_t<Number>& normal, const Number& offset) const {
		//Quick check: 
		//If all coefficients of directions similar to hspace normal smaller than hspace offset, then current obj completely in hspace
		//If all coefficients of directions not similar to hspace normal bigger than hspace offset, then current obj completely not in hspace
		bool fullyInside = true;
		bool fullyOutside = true;
		for(int i = 0; i < mMatrixPtr->rows(); ++i){
			if(normal.dot(mMatrixPtr->row(i)) > 0){
				if(mVector(i) > offset){
					fullyInside = false;
				} 
			} else {
				if(-mVector(i) < offset){
					fullyOutside = false;
				}
			}
			if(!fullyInside && !fullyOutside) break;
		}
		assert(!(fullyInside && fullyOutside));
		return std::make_pair(fullyInside,fullyOutside);
	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<CONTAINMENT, TemplatePolyhedronT<Number,Converter,Setting>> TemplatePolyhedronT<Number,Converter,Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
		
		if(empty()){
			return std::make_pair(CONTAINMENT::NO, *this);	
		}

		//Quick check
		auto fullInfullOut = checkFullInsideFullOutside(rhs.normal(), rhs.offset());
		if(fullInfullOut.first)
			return std::make_pair(CONTAINMENT::FULL, *this);
		if(fullInfullOut.second)
			return std::make_pair(CONTAINMENT::NO, *this);

		//Expensive part
		auto tmp = this->intersectHalfspace(rhs);
		if(tmp.empty()){
			return std::make_pair(CONTAINMENT::NO, std::move(tmp));
		} else {
			return std::make_pair(CONTAINMENT::PARTIAL, std::move(tmp));
		}
	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<CONTAINMENT, TemplatePolyhedronT<Number,Converter,Setting>> TemplatePolyhedronT<Number,Converter,Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
		
		if(empty()){
			return std::make_pair(CONTAINMENT::NO, *this);
		} 

		//Not so quick check:
		bool fullyInside = true;
		bool fullyOutside = true;
		for(int i = 0; i < _mat.rows(); ++i){
			auto fullInfullOut = checkFullInsideFullOutside(_mat.row(i), _vec(i));
			if(!fullInfullOut.first) fullyInside = false;
			if(!fullInfullOut.second) fullyOutside = false;
			if(!fullyInside && !fullyOutside) break;
		}

		assert(!(fullyInside && fullyOutside));
		if(fullyInside)
			return std::make_pair(CONTAINMENT::FULL, *this);
		if(fullyOutside){
			return std::make_pair(CONTAINMENT::NO, *this);
		}
			
		//Even more expensive part
		auto tmp = this->intersectHalfspaces(_mat,_vec);
		if(tmp.empty()){
			return std::make_pair(CONTAINMENT::NO, *this);
		} else {
			return std::make_pair(CONTAINMENT::PARTIAL, std::move(tmp));
		}
	}

	//NOTE: This returns a different tpoly with different constraints
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::project(const std::vector<std::size_t>& dimensions) const {
		
		if(dimensions.empty()) return Empty();
		if(empty()) return *this;	
		if(dimensions.size() > this->dimension()){
			throw(std::invalid_argument("TPoly::project, too many dimensions given"));
		}

		//All coeffs not in a mentioned dimension will be projected to zero.
		std::set<std::size_t> dimsAsSet(dimensions.begin(), dimensions.end());
		std::vector<std::size_t> dimsOrdered(dimsAsSet.begin(), dimsAsSet.end());
		auto it = dimsOrdered.begin();
		matrix_t<Number> projectedMat = matrix_t<Number>::Zero(mMatrixPtr->rows(), mMatrixPtr->cols());		
		vector_t<Number> projectedVec = mVector;
		for(unsigned j = 0; j < mMatrixPtr->cols(); ++j){
			if(j == *it){
				assert(it != dimsOrdered.end());
				projectedMat.col(j) = mMatrixPtr->col(j);
				++it;
			} else {
				//Collect all row indices where we would set the coeffs to 0
				for(int i = 0; i < mMatrixPtr->rows(); ++i){
					if((*mMatrixPtr)(i,j) != 0){
						projectedVec(i) = 0;
					}
				}
			}
		}
		assert(it == dimsOrdered.end());
		auto res = TemplatePolyhedronT<Number,Converter,Setting>(projectedMat,projectedVec);
		//res.removeRedundancy();
		//std::cout << "res after removeRedundancy is: " << res << std::endl;
		return res;
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::linearTransformation( const matrix_t<Number>& A ) const {
		//Other Idea: Effectively, a linear transformation is only a scaling of the coeff vector, but how to find scaling factors?
		//Until then: Convert into VPoly and transform each point, then evaluate in template directions to match a point to the fitting halfspace		
		//if(empty()){
		//	return TemplatePolyhedronT<Number,Converter,Setting>();
		//} 
		assert(mMatrixPtr != nullptr);
		assert(A.cols() == (int)dimension());
		assert(A.cols() == mMatrixPtr->cols());
		assert(A.rows() == mMatrixPtr->cols());

		//Scale all coefficients by the greatest scaling factor, which are the coordinates on the diagonal of A
		//assert(A.rows() == A.cols());
		//Number maxScaleFactor = A(0,0);
		//for(int i = 0; i < A.cols(); ++i){
		//	if(A(i,i) > maxScaleFactor){
		//		maxScaleFactor = A(i,i);
		//	}
		//}
		//vector_t<Number> newVector = mVector;
		//for(int i = 0; i < mVector.rows(); ++i){
		//	newVector(i) = maxScaleFactor * newVector(i);
		//}
		////To find rotation matrix, find the individual scaling factors by getting the length of the columns
		////Rotation matrix is A with each col divided its scaling factor
		//matrix_t<Number> rotMat = matrix_t<Number>::Zero(A.rows(), A.cols());
		//for(int i = 0; i < A.cols(); ++i){
		//	rotMat.col(i) = A.col(i) / norm(vector_t<Number>(A.col(i)));
		//}
		////We rotate our template directions by the inverse direction and evaluate in these directions
		//matrix_t<Number> dirsRotatedInverse = (rotMat.transpose())*(*mMatrixPtr);
		//TemplatePolyhedronT<Number,Converter,Setting> res(mMatrixPtr, newVector);
		//auto evalInInvRotatedDirs = res.multiEvaluate(dirsRotatedInverse, true);
		//assert(evalInInvRotatedDirs.size() == newVector.rows());
		//for(int i = 0; i < evalInInvRotatedDirs.size(); ++i){
		//	assert(evalInInvRotatedDirs.at(i).errorCode == SOLUTION::FEAS);
		//	newVector(i) = evalInInvRotatedDirs.at(i).supportValue;
		//}
		//res = TemplatePolyhedronT<Number,Converter,Setting>(mMatrixPtr, newVector);
		//return res;

		//Get singular value decomposition which decomposes every matrix into 3 matrices: rotation, scaling and another rotation matrix
		//TODO: Why does that not work? Maybe testwise convert to double matrix
/*
		//Convert A into double (Since eigen svd does not work with mpq_class)
		matrix_t<double> doubleA = convert<Number,double>(A);
		
		//Convert mMatrixPtr into double (Since eigen svd does not work with mpq_class)
		matrix_t<double> doublemMatrixPtr = convert<Number,double>(*mMatrixPtr);
		
		//Compute SVD and put singularValues into a matrix 
		Eigen::BDCSVD<matrix_t<double>> svd(doubleA, Eigen::ComputeFullU | Eigen::ComputeFullV);
		matrix_t<double> singularVals(doubleA.rows(), doubleA.cols());
		for(int i = 0; i < doubleA.rows(); ++i){
			singularVals(i,i) = svd.singularValues()(i);
		}
		
		//Compute transformed dirs and convert it back to Number
		std::cout << "TPoly::linearTransformation, singularVals: \n" << singularVals << "V: \n" << svd.matrixV() << "U: \n" << svd.matrixU() << "doublemMatrixPtr: \n" << doublemMatrixPtr << std::endl;
		matrix_t<double> dirsRotatedInv = doublemMatrixPtr*(singularVals.transpose()*svd.matrixU().transpose());
		//matrix_t<double> dirsRotatedInv = singularVals.transpose()*(svd.matrixV().transpose()*doublemMatrixPtr.transpose());
		//matrix_t<double> dirsRotatedInv = doublemMatrixPtr*(singularVals*svd.matrixV().transpose());
		std::cout << "TPoly::linearTransformation, dirsRotatedInv: \n" << dirsRotatedInv << std::endl;
		matrix_t<Number> dirsRotatedInverse = convert<double,Number>(dirsRotatedInv);
		assert(dirsRotatedInverse.rows() == mMatrixPtr->rows());
		assert(dirsRotatedInverse.cols() == mMatrixPtr->cols());
*/
		//Evaluate in the transformed directions
		matrix_t<Number> dirsRotatedInverse = (*mMatrixPtr)*A;
		assert(dirsRotatedInverse.rows() == mMatrixPtr->rows());
		assert(dirsRotatedInverse.cols() == mMatrixPtr->cols());
		auto evalInInvRotatedDirs = multiEvaluate(dirsRotatedInverse, true);
		vector_t<Number> newVector(mVector.rows());
		assert(evalInInvRotatedDirs.size() == std::size_t(newVector.rows()));
		for(std::size_t i = 0; i < evalInInvRotatedDirs.size(); ++i){
			assert(evalInInvRotatedDirs.at(i).errorCode == SOLUTION::FEAS);
			newVector(i) = evalInInvRotatedDirs.at(i).supportValue;
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(mMatrixPtr, newVector);
		
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
		
		/* TODO: Add affineTransformation after Sankranayanan as Setting
			For each mMatrixPtr row i:
			1. Compute Taylor series approx upto m+1-th term (how to determine m? -> set as setting)
			2. Sum first m approximations, this is first coeff vec g
			3. m+1-th approximation is second coeff vec r
			4. Compute this->evaluate(g) = g_max
			5. Compute TPoly(mMatrixPtr,InvariantCoeffs).evaluate(r) = r_max
			6. return TPoly(mMatrixPtr, g_max + r_max)
		*/

		if(empty()){
			return TemplatePolyhedronT<Number,Converter,Setting>();	
		} 
		assert(A.rows() == b.rows());
		assert(A.cols() == (int)dimension());

		TemplatePolyhedronT<Number,Converter,Setting> res = linearTransformation(A);

		//Translate res
		vector_t<Number> tmp = res.vector() + vector_t<Number>((*(mMatrixPtr) * b));
		res.setVector(tmp);

		return res;
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::minkowskiSum( const TemplatePolyhedronT<Number,Converter,Setting>& rhs ) const {
		
		//In case rhs has a different matrix than this, overapproximate the minkowskisum of both via template directions
		//Costly, but shouldn't happen too often
		if(!this->matrix().isApprox(rhs.matrix())){
			auto rhsHPoly = typename Converter::HPolytope(rhs.matrix(), rhs.vector());
			auto thisHPoly = typename Converter::HPolytope(this->matrix(), this->vector());
			auto summed = thisHPoly.minkowskiSum(rhsHPoly);
			auto evalInDirs = summed.multiEvaluate(combineRows(computeTemplate<Number>(dimension(), 8)));
			vector_t<Number> newVector = vector_t<Number>::Zero(evalInDirs.size());
			for(std::size_t i = 0; i < evalInDirs.size(); ++i){
				if(evalInDirs.at(i).errorCode == SOLUTION::FEAS){
					newVector(i) = evalInDirs.at(i).supportValue;
				} else {
					//INFTY should not be possible since minkowskiSum of convex objects is also convex and therefore evaluable in all directions.
					//An infeasible set could occur from minkowskiSum when both sets are empty, in which case we just return Empty()
					assert(evalInDirs.at(i).errorCode == SOLUTION::INFEAS);
					return TemplatePolyhedronT<Number,Converter,Setting>::Empty();
				}
			}
		}

		//This only works if both TPolys have the same; if MinkowskiSum with a box, use smth else
		vector_t<Number> newVector = vector_t<Number>::Zero(mMatrixPtr->rows());
		for(int i = 0; i < mMatrixPtr->rows(); i++){
			newVector(i) = this->vector()(i) + rhs.vector()(i);
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(mMatrixPtr, newVector);
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::intersect( const TemplatePolyhedronT<Number,Converter,Setting>& rhs ) const {
		//assert(this->matrix() == rhs.matrix());
		if(rhs.empty()){
			return *this;	
		} 
		if(this->empty()) return rhs;
		vector_t<Number> res = mVector;
		for(int i = 0; i < mMatrixPtr->rows(); ++i){
			if(rhs.vector()(i) < res(i)){
				res(i) = rhs.vector()(i);
			} 
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(mMatrixPtr, res);
		//Since intersecting with an empty / unfeasible Tpoly always results in smth unfeasible, 
		//check emptiness only once after the computation instead of two times before the computation
		//auto tmp = TemplatePolyhedronT<Number,Converter,Setting>(*mMatrixPtr, res);
		//if(tmp.empty()){
		//	if(this->empty()) //		tmp = TemplatePolyhedronT<Number,Converter,Setting>();
		//		tmp = *this;	
		//	}
		//}
		//return tmp;
	}

	//TODO: Is there a cheaper way? 
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {

		//Quick check whether fully inside halfspace or fully outside
		auto fullInfullOut = checkFullInsideFullOutside(hspace.normal(), hspace.offset());
		assert(!(fullInfullOut.first && fullInfullOut.second));
		if(fullInfullOut.first) return *this;
		if(fullInfullOut.second) return Empty();

		//If partially inside halfspace
		assert(hspace.normal().rows() == mMatrixPtr->cols());
		matrix_t<Number> mat = matrix_t<Number>::Zero(1,hspace.normal().rows());
		mat.row(0) = hspace.normal().transpose();
		vector_t<Number> vec = vector_t<Number>::Zero(1);
		vec(0) = hspace.offset();

		return intersectHalfspaces(mat,vec);
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
		
		//Emptiness check
		if(this->empty()) return *this;

		//Extend a copy of the matrix to contain the extra halfspaces
		assert(_mat.rows() == _vec.rows());
		assert(_mat.cols() == mMatrixPtr->cols());
		matrix_t<Number> extendedMatrix = matrix_t<Number>::Zero(mMatrixPtr->rows()+_mat.rows(),mMatrixPtr->cols());
		extendedMatrix.block(0,0,mMatrixPtr->rows(),mMatrixPtr->cols()) = *mMatrixPtr;
		extendedMatrix.block(mMatrixPtr->rows(),0,_mat.rows(),_mat.cols()) = _mat;

		//Extend a copy of mVector to contain the halfspace offset
		vector_t<Number> extendedVector = vector_t<Number>::Zero(mVector.rows()+_vec.rows());
		for(int i = 0; i < mVector.rows(); ++i){
			extendedVector(i) = mVector(i);
		}
		for(int i = mVector.rows(); i < mVector.rows()+_vec.rows(); ++i){
			extendedVector(i) = _vec(i-mVector.rows());
		}

		//TODO: Maybe use rotation to parallel line to acquire distance

		//Build hpoly from the extended matrix and vector, then evaluate in the original directions and build overapproximating tpoly
		auto tpolyWithHSpace = typename Converter::HPolytope(extendedMatrix, extendedVector);
		tpolyWithHSpace.removeRedundancy();
		auto evalInOrigDirs = tpolyWithHSpace.multiEvaluate(*mMatrixPtr);
		vector_t<Number> newOffsetVec = vector_t<Number>::Zero(evalInOrigDirs.size());
		for(int i = 0; i < newOffsetVec.rows(); ++i){
			if(evalInOrigDirs.at(i).errorCode == SOLUTION::INFEAS){
				return TemplatePolyhedronT<Number,Converter,Setting>();
			}
			newOffsetVec(i) = evalInOrigDirs.at(i).supportValue;
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(mMatrixPtr, newOffsetVec);
	}

	template<typename Number, typename Converter, typename Setting>
	bool TemplatePolyhedronT<Number,Converter,Setting>::contains( const Point<Number>& point ) const {
		if(this->empty()) return false;
		if(point.dimension() != mMatrixPtr->cols()){
			throw std::invalid_argument("Template polyhedron cannot contain point of different dimension.");
		}
		for(int i = 0; i < mMatrixPtr->rows(); ++i){
			if(!carl::AlmostEqual2sComplement(mMatrixPtr->row(i).dot(point.rawCoordinates()), mVector(i), 128) && mMatrixPtr->row(i).dot(point.rawCoordinates()) > mVector(i)){
				return false;
			}
		}
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	bool TemplatePolyhedronT<Number,Converter,Setting>::contains( const TemplatePolyhedronT<Number,Converter,Setting>& rhs ) const {
		if(this->matrix() != rhs.matrix()){
			throw std::invalid_argument("Template polyhedron containment only checked for template polyhedra with same matrix.");
		}
		if(rhs.dimension() != std::size_t(mMatrixPtr->cols())){
			throw std::invalid_argument("Template polyhedron cannot contain another template polyhedron of different dimension.");
		}
		if(this->empty()) return false;
		if(rhs.empty()) return true;
		for(int i = 0; i < mVector.rows(); i++){
			if(mVector(i) < rhs.vector()(i)) return false;
		}
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::unite( const TemplatePolyhedronT<Number,Converter,Setting>& rhs ) const {
		//Since uniting with a empty / unfeasible TPoly can result in a feasible TPoly, check beforehand whether one of the arguments is empty.
		//TODO: What about union of two not connected sets?
		if(this->empty()) return rhs; 
		if(rhs.empty()) return *this; 
		assert(*mMatrixPtr == rhs.matrix());
		vector_t<Number> res = mVector;
		for(int i = 0; i < mMatrixPtr->rows(); ++i){
			if(rhs.vector()(i) > res(i)){
				res(i) = rhs.vector()(i);
			}
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(mMatrixPtr, res);
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::unite( const std::vector<TemplatePolyhedronT<Number,Converter,Setting>>& templatePolyhedrones ) {
		#ifndef NDEBUG
		//All tpolys we unite with must have the same matrices
		for(const auto& elem : templatePolyhedrones){
			assert(this->matrix().isApprox(elem.matrix()));
		}
		#endif
		//Since uniting with a empty / unfeasible TPoly can result in a feasible TPoly, check for each TPoly beforehand whether it is empty, and if it is, ignore it.
		vector_t<Number> res(mMatrixPtr->rows());
		if(this->empty()){
			res = -10000000*vector_t<Number>::Ones(mMatrixPtr->rows());	
		} else {
			res = mVector;
		}
		for(int i = 0; i < mMatrixPtr->rows(); ++i){
			for(const auto& tpoly : templatePolyhedrones){
				if(!tpoly.empty()){
					if(tpoly.vector()(i) > res(i)){
						res(i) = tpoly.vector()(i);
					}
				}
			}
		}
		auto tmp = TemplatePolyhedronT<Number,Converter,Setting>(mMatrixPtr, res);
		return tmp;
	}

	template<typename Number, typename Converter, typename Setting>
	void TemplatePolyhedronT<Number,Converter,Setting>::reduceRepresentation() {
		removeRedundancy();
	}

	template<typename Number, typename Converter, typename Setting>
	void TemplatePolyhedronT<Number,Converter,Setting>::clear() {
		mMatrixPtr = nullptr;
		mVector = vector_t<Number>::Zero(0);
		mOptimizer.cleanGLPInstance();
	}

} // namespace hypro
