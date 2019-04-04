#pragma once
#include "TemplatePolyhedron.h"

namespace hypro {

	//////// Constructors & Destructors ////////

	//Empty constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT() 
		: mVector(vector_t<Number>::Zero(0)) 
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
		
		//compute template matrix and set it as new mMatrix
		auto templateDirs = computeTemplate<Number>(dimension, noOfSides);
		matrix_t<Number> templateMatrix = matrix_t<Number>::Zero(templateDirs.size(), templateDirs.front().rows());
		for(unsigned i = 0; i < templateDirs.size(); ++i){
			templateMatrix.row(i) = templateDirs.at(i);
		}
		setMatrix(templateMatrix);
	}

	//Matrix-Vector-constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( const matrix_t<Number>& mat, const vector_t<Number>& vec ) 
	{
		setMatrix(mat); 
		if(vec.rows() == mMatrix.rows()){
			mVector = vec;
		}
	}

	//Vector constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( const vector_t<Number>& vec ) : mVector(vec) {}	

	//Copy constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( const TemplatePolyhedronT<Number,Converter,Setting>& orig ) 
	{
		setMatrix(orig.matrix());
		if(vec.rows() == mMatrix.rows()){
			mVector = orig.vector();
		}
	}

	//Move constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( TemplatePolyhedronT<Number,Converter,Setting>&& orig ) 
	{
		setMatrix(std::move(orig.matrix()));
		if(vec.rows() == mMatrix.rows()){
			mVector = std::move(orig.vector());
		}
	}

	//Settings constructor
	template<typename Number, typename Converter, typename Setting>
	template<typename SettingRhs, carl::DisableIf< std::is_same<Setting, SettingRhs> > >
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT(const TemplatePolyhedronT<Number,Converter,SettingRhs>& orig)
	{
		setMatrix(orig.matrix());
		if(vec.rows() == mMatrix.rows()){
			mVector = orig.vector();
		}
	}

	//////// GeometricObject Interface ////////

	template<typename Number, typename Converter, typename Setting>
	bool TemplatePolyhedronT<Number,Converter,Setting>::empty() const {
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	Number TemplatePolyhedronT<Number,Converter,Setting>::supremum() const {
		return Number(0);
	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<Point<Number>> TemplatePolyhedronT<Number,Converter,Setting>::vertices( const matrix_t<Number>& m ) const {
		return std::vector<Point<Number>>();
	}

	template<typename Number, typename Converter, typename Setting>
	EvaluationResult<Number> TemplatePolyhedronT<Number,Converter,Setting>::evaluate( const vector_t<Number>& _direction, bool ) const {
		return EvaluationResult<Number>();
	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<EvaluationResult<Number>> TemplatePolyhedronT<Number,Converter,Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
		return std::vector<EvaluationResult<Number>>();
	}

	template<typename Number, typename Converter, typename Setting>
	std::size_t TemplatePolyhedronT<Number,Converter,Setting>::dimension() const {
		return mMatrix.cols();
	}

	template<typename Number, typename Converter, typename Setting>
	void TemplatePolyhedronT<Number,Converter,Setting>::removeRedundancy() {

	}

	template<typename Number, typename Converter, typename Setting>
	std::size_t TemplatePolyhedronT<Number,Converter,Setting>::size() const {
		return std::size_t(0);
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
		std::pair<CONTAINMENT, TemplatePolyhedronT<Number,Converter,Setting>>();
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
		return TemplatePolyhedronT<Number,Converter,Setting>();
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::intersect( const TemplatePolyhedronT<Number,Converter,Setting>& rhs ) const {
		vector_t<Number> res = mVector;
		for(int i = 0; i < mMatrix.rows(); ++i){
			if(rhs.vector()(i) < res(i)){
				res(i) = rhs.vector()(i);
			}
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(mMatrix, res);
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
		if(point.dimension() != mMatrix.cols()){
			throw std::invalid_argument("Template polyhedron cannot contain point of different dimension.");
		}
		if(mMatrix*point.rawCoordinates() <= mVector) return true;
		return false;
	}

	template<typename Number, typename Converter, typename Setting>
	bool TemplatePolyhedronT<Number,Converter,Setting>::contains( const TemplatePolyhedronT<Number,Converter,Setting>& templatePolyhedron ) const {
		for(int i = 0; mVector.rows(); ++i){
			if(mVector(i) < templatePolyhedron.vector()(i)) return false;
		}
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::unite( const TemplatePolyhedronT<Number,Converter,Setting>& rhs ) const {
		vector_t<Number> res = mVector;
		for(int i = 0; i < mMatrix.rows(); ++i){
			if(rhs.vector()(i) > res(i)){
				res(i) = rhs.vector()(i);
			}
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(mMatrix, res);
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::unite( const std::vector<TemplatePolyhedronT<Number,Converter,Setting>>& templatePolyhedrones ) {
		vector_t<Number> res = mVector;
		for(int i = 0; i < mMatrix.rows(); ++i){
			for(const auto& tpoly : templatePolyhedrones){
				if(tpoly(i) > res(i)){
					res(i) = tpoly(i);
				}
			}
		}
		return TemplatePolyhedronT<Number,Converter,Setting>(mMatrix, res);
	}

	template<typename Number, typename Converter, typename Setting>
	void TemplatePolyhedronT<Number,Converter,Setting>::reduceRepresentation() {

	}

	template<typename Number, typename Converter, typename Setting>
	void TemplatePolyhedronT<Number,Converter,Setting>::clear() {

	}

} // namespace hypro
