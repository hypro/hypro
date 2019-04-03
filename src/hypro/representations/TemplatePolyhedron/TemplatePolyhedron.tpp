#pragma once
#include "TemplatePolyhedron.h"

namespace hypro {

	//////// Constructors & Destructors ////////

	//Empty constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT() 
		: mVector(vector_t<Number>::Zero(1)) //mMatrix is handled as its static
	{}

	//Regular template polyhedron constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT(std::size_t dimension, const Number& noOfSides) 
	{
		if(noOfSides < dimension){
			std::cout << "WARNING: Template polyhedron not a bounded object anymore!" << std::endl;
		}
		
		//compute template matrix and set it as new mMatrix
		auto templateDirs = computeTemplate(dimension, noOfSides);
		matrix_t<Number> templateMatrix = matrix_t<Number>::Zero(templateDirs.size(), templateDirs.front().cols());
		for(unsigned i = 0; i < templateDirs.size(); ++i){
			templateMatrix.row(i) = templateDirs.at(i);
		}
		setMatrix(templateMatrix);
		
		//mVector set to zero? Give offset as argument?
		mVector = vector_t<Number>::Zero(mMatrix.rows());
	}

	//Matrix-Vector-constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( const matrix_t<Number>& mat, const vector_t<Number>& vec ) 
		: mVector(vec)
	{
		setMatrix(mat);
		if(mat.rows() < dimension){
			std::cout << "WARNING: Template polyhedron not a bounded object anymore!" << std::endl;
		} 
	}

	//Copy constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( const TemplatePolyhedronT<Number,Converter,Setting>& orig ) 
		: mVector(orig.vector())
		//is that still right with a static member?
	{
		setMatrix(orig.matrix());
	}

	//Move constructor
	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT( TemplatePolyhedronT<Number,Converter,Setting>&& orig ) 
		: mVector(std::move(orig.vector()))
		//is that even right? Doess that make sense?
	{
		setMatrix(std::move(orig.matrix()));
	}

	//Settings constructor
	template<typename Number, typename Converter, typename Setting>
	template<typename SettingRhs, carl::DisableIf< std::is_same<Setting, SettingRhs> > >
	TemplatePolyhedronT<Number,Converter,Setting>::TemplatePolyhedronT(const TemplatePolyhedronT<Number,Converter,SettingRhs>& orig)
		: mVector(orig.vector())
		//is that still right with a static member?
	{
		setMatrix(orig.matrix());
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
		return TemplatePolyhedronT<Number,Converter,Setting>();
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
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	bool TemplatePolyhedronT<Number,Converter,Setting>::contains( const TemplatePolyhedronT<Number,Converter,Setting>& TemplatePolyhedron ) const {
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::unite( const TemplatePolyhedronT<Number,Converter,Setting>& rhs ) const {
		return TemplatePolyhedronT<Number,Converter,Setting>();
	}

	template<typename Number, typename Converter, typename Setting>
	TemplatePolyhedronT<Number,Converter,Setting> TemplatePolyhedronT<Number,Converter,Setting>::unite( const std::vector<TemplatePolyhedronT<Number,Converter,Setting>>& TemplatePolyhedrones ) {
		return TemplatePolyhedronT<Number,Converter,Setting>();
	}

	template<typename Number, typename Converter, typename Setting>
	void TemplatePolyhedronT<Number,Converter,Setting>::reduceRepresentation() {

	}

	template<typename Number, typename Converter, typename Setting>
	void TemplatePolyhedronT<Number,Converter,Setting>::clear() {

	}

} // namespace hypro
