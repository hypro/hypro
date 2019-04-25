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
		if(noOfSides != vec.rows()){
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
		//If all coeffs negative -> all directions point towards origin -> unbounded polyhedron not empty
		//If all coeffs positive -> all directions point away from origin -> bounded polyhedron not empty
		//bool allNegative = true;
		bool allPositive = true;
		for(int i = 0; i < mVector.rows(); i++){
			if(mVector(i) < 0){
				allPositive = false;
			} 
			//if(mVector(i) > 0){
			//	allNegative = false;
			//}
		}
		if(allPositive) return false;
		//if(allNegative){
		//	mBounded = false;
		//	return false;	
		//} 

		//If no quick check triggered: Solve LP
		std::cout << "Optimizer mat: \n" << mOptimizer.matrix() << "optimizer vec: \n" << mOptimizer.vector() << std::endl;
		bool res = !mOptimizer.checkConsistency();
		TRACE("hypro.representations.TPolytope","Optimizer result: " << res);
		return res;
	}

	//Copy from HPoly
	template<typename Number, typename Converter, typename Setting>
	Number TemplatePolyhedronT<Number,Converter,Setting>::supremum() const {
		if(mMatrixPtr){
			std::cout << "TPoly: " << *this << std::endl;	
		}
		Number max = 0;
		if(this->empty()){
			std::cout << "this was empty" << std::endl;
			return max;	
		} 
		auto tmp = this->vertices();
		if(tmp.empty()){
			std::cout << "vertices were empty" << std::endl;
		}
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
		if(this->empty()) {
			return EvaluationResult<Number>( Number(1), SOLUTION::INFTY );
		}
		return mOptimizer.evaluate(_direction, true);
	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<EvaluationResult<Number>> TemplatePolyhedronT<Number,Converter,Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
		return std::vector<EvaluationResult<Number>>();
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
		return std::pair<CONTAINMENT, TemplatePolyhedronT<Number,Converter,Setting>>();
	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<CONTAINMENT, TemplatePolyhedronT<Number,Converter,Setting>> TemplatePolyhedronT<Number,Converter,Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
		return std::pair<CONTAINMENT, TemplatePolyhedronT<Number,Converter,Setting>>();
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::project(const std::vector<std::size_t>& dimensions) const {
		return TemplatePolyhedronT<Number,Converter,Setting>();
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::linearTransformation( const matrix_t<Number>& A ) const {
		return TemplatePolyhedronT<Number,Converter,Setting>();
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
		return TemplatePolyhedronT<Number,Converter,Setting>();
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::minkowskiSum( const TemplatePolyhedronT<Number,Converter,Setting>& rhs ) const {
		assert(this->rGetMatrixPtr() == rhs.rGetMatrixPtr());
		return TemplatePolyhedronT<Number,Converter,Setting>();
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::intersect( const TemplatePolyhedronT<Number,Converter,Setting>& rhs ) const {
		assert(this->rGetMatrixPtr() == rhs.rGetMatrixPtr());
		vector_t<Number> res = mVector;
		for(int i = 0; i < mMatrixPtr->rows(); ++i){
			if(rhs.vector()(i) < res(i)){
				res(i) = rhs.vector()(i);
			} 
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(*mMatrixPtr, res);

		//THIS IS NEEDED IF TRIANGLE POINTING INSIDE COUNTS AS EMPTY - A TRIANGLE POINTING INSIDE IS EMPTY - EVEN THEN THE OPERATION WILL GET THE RIGHT ONE
		//auto tmp = TemplatePolyhedronT<Number,Converter,Setting>(*mMatrixPtr, res);
		//if(tmp.empty()){
		//	tmp = TemplatePolyhedronT<Number,Converter,Setting>();
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
		//if(this->empty()) return false; //NEEDED?
		//if(rhs.empty()) return true; //NEEDED?
		for(int i = 0; i < mVector.rows(); i++){
			if(mVector(i) < rhs.vector()(i)) return false;
		}
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::unite( const TemplatePolyhedronT<Number,Converter,Setting>& rhs ) const {
		assert(this->rGetMatrixPtr() == rhs.rGetMatrixPtr());
		if(this->empty()) return rhs; //NEEDED?
		if(rhs.empty()) return *this; //NEEDED?
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
			assert(this->rGetMatrixPtr() == elem->rGetMatrixPtr());
		}
		#endif
		vector_t<Number> res = mVector;
		for(int i = 0; i < mMatrixPtr->rows(); ++i){
			for(const auto& tpoly : templatePolyhedrones){
				if(tpoly(i) > res(i)){
					res(i) = tpoly(i);
				}
			}
		}
		auto tmp = TemplatePolyhedronT<Number,Converter,Setting>(*mMatrixPtr, res);
		//if(tmp.empty()) return TemplatePolyhedronT<Number,Converter,Setting>();
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
