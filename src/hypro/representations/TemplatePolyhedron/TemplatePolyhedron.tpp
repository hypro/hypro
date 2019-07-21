#pragma once
#include "TemplatePolyhedron.h"

namespace hypro {

	//////// Constructors & Destructors ////////

	//Empty constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT() 
		: mVector(vector_t<Number>::Zero(0)), mOptimizer(Optimizer<Number>()) 
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
		matrix_t<Number> templateMatrix = matrix_t<Number>::Zero(templateDirs.size(), templateDirs.front().rows());
		for(unsigned i = 0; i < templateDirs.size(); ++i){
			templateMatrix.row(i) = templateDirs.at(i);
		}
		mMatrixPtr = std::make_shared<matrix_t<Number>>(templateMatrix);
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
		//assert(mOptimizer.getRelations().size() == std::size_t(mat.rows()));
		assert(vec.rows() == mMatrixPtr->rows());
	}

	//Copy constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( const TemplatePolyhedronT<Number,Converter,Setting>& orig ) 
		: mMatrixPtr(orig.rGetMatrixPtr())
		, mVector(orig.vector())
		, mOptimizer(Optimizer<Number>(*orig.rGetMatrixPtr(), orig.vector()))
	{
		mOptimizer.setVector(mVector);
		assert(mVector.rows() == mMatrixPtr->rows());	
		assert(mMatrixPtr == orig.rGetMatrixPtr());
	}

	//Move constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( TemplatePolyhedronT<Number,Converter,Setting>&& orig ) 
		: mMatrixPtr(std::move(orig.rGetMatrixPtr()))
		, mVector(std::move(orig.vector()))	
		, mOptimizer(Optimizer<Number>(*orig.rGetMatrixPtr(), orig.vector()))
	{
		mOptimizer.setVector(mVector);
		orig.clear();
		assert(mVector.rows() == mMatrixPtr->rows());		
		assert(orig.rGetMatrixPtr() == nullptr);
	}

	//Settings constructor
	template<typename Number, typename Converter, typename Setting>
	template<typename SettingRhs, carl::DisableIf< std::is_same<Setting, SettingRhs> > >
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT(const TemplatePolyhedronT<Number,Converter,SettingRhs>& orig)
		: mMatrixPtr(orig.rGetMatrixPtr())
		, mVector(orig.vector())
		, mOptimizer(Optimizer<Number>(*orig.rGetMatrixPtr(), orig.vector()))
	{
		mOptimizer.setVector(mVector);
		assert(mVector.rows() == mMatrixPtr->rows());
		assert(mMatrixPtr == orig.rGetMatrixPtr());
	}

	//////// GeometricObject Interface ////////

	//Copy from HPoly
	template<typename Number, typename Converter, typename Setting>
	bool TemplatePolyhedronT<Number,Converter,Setting>::empty() const {
		
		//Quick checks
		if(mMatrixPtr == nullptr) return true;
		if(mMatrixPtr->rows() <= 1) return false;

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

	//Copy from HPoly
	template<typename Number, typename Converter, typename Setting>
	Number TemplatePolyhedronT<Number,Converter,Setting>::supremum() const {
		Number max = 0;
		if(this->empty()){
			return max;	
		} 
		auto tmp = this->vertices();
		//assert(!this->empty());
		//assert(!this->vertices().empty());
		for ( const auto &point : this->vertices() ) {
			Number inftyNorm = Point<Number>::inftyNorm( point );
			max = max > inftyNorm ? max : inftyNorm;
		}
		return max;
	}

	//The HPoly way
	template<typename Number, typename Converter, typename Setting>
	std::vector<Point<Number>> TemplatePolyhedronT<Number,Converter,Setting>::vertices( const matrix_t<Number>& ) const {
		if(this->empty()) return std::vector<Point<Number>>();
		typename Converter::VPolytope tmp(this->matrix(), this->vector());
		return tmp.vertices();
	}

	template<typename Number, typename Converter, typename Setting>
	EvaluationResult<Number> TemplatePolyhedronT<Number,Converter,Setting>::evaluate( const vector_t<Number>& _direction, bool ) const {
		if(this->empty()) return EvaluationResult<Number>( Number(0), SOLUTION::INFTY );
		return mOptimizer.evaluate(_direction, true);
	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<EvaluationResult<Number>> TemplatePolyhedronT<Number,Converter,Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
		//assert(_directions.rows() == mMatrixPtr->rows());
		//assert(_directions.cols() == mMatrixPtr->cols());
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
	std::pair<CONTAINMENT, TemplatePolyhedronT<Number,Converter,Setting>> TemplatePolyhedronT<Number,Converter,Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
		//will be done if intersectHalfspaces ready
		return std::pair<CONTAINMENT, TemplatePolyhedronT<Number,Converter,Setting>>();
	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<CONTAINMENT, TemplatePolyhedronT<Number,Converter,Setting>> TemplatePolyhedronT<Number,Converter,Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
		//will be done if intersectHalfspaces ready
		return std::pair<CONTAINMENT, TemplatePolyhedronT<Number,Converter,Setting>>();
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::project(const std::vector<std::size_t>& dimensions) const {
		//TODO: Will be done if linear Transformation ready
		return TemplatePolyhedronT<Number,Converter,Setting>();
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::linearTransformation( const matrix_t<Number>& A ) const {
		//Other Idea: Effectively, a linear transformation is only a scaling of the coeff vector, but how to find scaling factors?
		//Until then: Convert into VPoly and transform each point, then evaluate in template directions to match a point to the fitting halfspace
		if(empty()) return TemplatePolyhedronT<Number,Converter,Setting>();
		auto tmp = typename Converter::VPolytope(*mMatrixPtr, mVector);
		tmp = tmp.linearTransformation(A);
		//auto tmpAsHpoly = typename Converter::HPolytope(tmp.vertices());
		vector_t<Number> newVector = vector_t<Number>::Zero(dimension());
		for(int i = 0; i < mMatrixPtr->rows(); i++){
			EvaluationResult<Number> res = tmp.evaluate(mMatrixPtr->row(i));
			if(std::find(tmp.vertices().begin(), tmp.vertices().end(), Point<Number>(res.optimumValue)) != tmp.vertices().end()){
				newVector(i) = res.supportValue;
			}
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(*mMatrixPtr, newVector);
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
		if(empty()) return TemplatePolyhedronT<Number,Converter,Setting>();
		auto tmp = typename Converter::VPolytope(*mMatrixPtr, mVector);
		tmp = tmp.affineTransformation(A,b);
		vector_t<Number> newVector = vector_t<Number>::Zero(dimension());
		for(int i = 0; i < mMatrixPtr->rows(); i++){
			EvaluationResult<Number> res = tmp.evaluate(mMatrixPtr->row(i));
			if(std::find(tmp.vertices().begin(), tmp.vertices().end(), Point<Number>(res.optimumValue)) != tmp.vertices().end()){
				newVector(i) = res.supportValue;
			}
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(*mMatrixPtr, newVector);
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::minkowskiSum( const TemplatePolyhedronT<Number,Converter,Setting>& rhs ) const {
		//This only works if both TPolys have the same; if MinkowskiSum with a box, use smth else
		assert(this->matrix() == rhs.matrix());
		vector_t<Number> newVector = vector_t<Number>::Zero(mMatrixPtr->rows());
		for(int i = 0; i < mMatrixPtr->rows(); i++){
			newVector(i) = this->vector()(i) + rhs.vector()(i);
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(*mMatrixPtr, newVector);
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::intersect( const TemplatePolyhedronT<Number,Converter,Setting>& rhs ) const {
		//assert(this->matrix() == rhs.matrix());
		if(rhs.empty()) return *this;
		if(this->empty()) return rhs;
		vector_t<Number> res = mVector;
		for(int i = 0; i < mMatrixPtr->rows(); ++i){
			if(rhs.vector()(i) < res(i)){
				res(i) = rhs.vector()(i);
			} 
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(*mMatrixPtr, res);
		//Since intersecting with an empty / unfeasible Tpoly always results in smth unfeasible, 
		//check emptiness only once after the computation instead of two times before the computation
		//auto tmp = TemplatePolyhedronT<Number,Converter,Setting>(*mMatrixPtr, res);
		//if(tmp.empty()){
		//	if(this->empty()){
		//		tmp = TemplatePolyhedronT<Number,Converter,Setting>();
		//	} else {
		//		tmp = *this;	
		//	}
		//}
		//return tmp;
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {
		return TemplatePolyhedronT<Number,Converter,Setting>();
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
		return TemplatePolyhedronT<Number,Converter,Setting>();
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
		//assert(this->matrix() == rhs.matrix());
		//Since uniting with a empty / unfeasible TPoly can result in a feasible TPoly, check beforehand whether one of the arguments is empty.
		if(this->empty()) return rhs; 
		if(rhs.empty()) return *this; 
		vector_t<Number> res = mVector;
		for(int i = 0; i < mMatrixPtr->rows(); ++i){
			if(rhs.vector()(i) > res(i)){
				res(i) = rhs.vector()(i);
			}
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(*mMatrixPtr, res);
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::unite( const std::vector<TemplatePolyhedronT<Number,Converter,Setting>>& templatePolyhedrones ) {
		#ifndef NDEBUG
		//All tpolys we unite with must have the same matrices
		for(const auto& elem : templatePolyhedrones){
			assert(this->matrix() == elem.matrix());
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
		auto tmp = TemplatePolyhedronT<Number,Converter,Setting>(*mMatrixPtr, res);
		return tmp;
	}

	template<typename Number, typename Converter, typename Setting>
	void TemplatePolyhedronT<Number,Converter,Setting>::reduceRepresentation() {

	}

	template<typename Number, typename Converter, typename Setting>
	void TemplatePolyhedronT<Number,Converter,Setting>::clear() {
		mMatrixPtr = nullptr;
		mVector = vector_t<Number>::Zero(0);
		mOptimizer.cleanGLPInstance();
	}

} // namespace hypro
