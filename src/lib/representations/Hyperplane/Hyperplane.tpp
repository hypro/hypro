#include "Hyperplane.h"

namespace hypro {
	
	template<typename Number>
	Hyperplane<Number>::Hyperplane(const Point<Number>& _vector, const Number& _off)
	{
		mNormal = vector_t<Number>(_vector.dimension());
		for(unsigned i = 0; i != _vector.dimension(); ++i)
		{
			mNormal(i) = _vector.at(i);
		}
		mScalar = _off;
		mDimension = _vector.dimension();
	}
        
	template<typename Number>
	Hyperplane<Number>::Hyperplane(std::initializer_list<Number> _coordinates, const Number& _off)
	{
		mNormal = vector_t<Number>(_coordinates.size());
		unsigned pos = 0;
		for(auto& coordinate : _coordinates)
		{
			mNormal(pos) = coordinate;
			++pos;
		}
		mScalar = _off;
		mDimension = pos;
	}
        
	template<typename Number>
	Hyperplane<Number>::Hyperplane(const vector_t<Number>& _vec, const std::vector<vector_t<Number>>& _vectorSet)
	{
		//here: hyperplane given in parameterform is converted to normalform
		//the normal vector of the hyperplane is computed by solving a system of equations
		mNormal = computePlaneNormal(_vectorSet);
#ifdef fukuda_DEBUG
		std::cout<< "computed Plane Normal: " << mNormal << std::endl;
#endif

		//the scalar is just the scalar product of the normal vector & a point in the hyperplane
		mScalar = mNormal.dot(_vec);
#ifdef fukuda_DEBUG
		std::cout<< "computed Offset: " << mScalar << std::endl;
#endif

		mDimension = _vec.rows();
	}
	
	template<typename Number>
	Hyperplane<Number>::Hyperplane(const std::vector<vector_t<Number>>& _points) {
		// TODO: introduce consistency check to avoid degeneracy.
		vector_t<Number> origin = *_points.begin();
		std::vector<vector_t<Number>> directions;
		assert(_points.size() > 1);
		for(unsigned i = 1; i < _points.size(); ++i) {
			directions.push_back(_points(i) - origin);
		}
		*this = Hyperplane<Number>(origin, directions);
	}

	template<typename Number>
	unsigned Hyperplane<Number>::dimension() const
	{
		return mNormal.rows();
	}
        
	template<typename Number>
	vector_t<Number> Hyperplane<Number>::normal() const
	{
		return mNormal;
	}
        
	template<typename Number>
	void Hyperplane<Number>::setNormal(const vector_t<Number>& _normal)
	{
		mNormal = _normal;
		mDimension = _normal.rows();
	}
        
	template<typename Number>
	Number Hyperplane<Number>::offset() const
	{
		return mScalar;
	}
        
	template<typename Number>
	void Hyperplane<Number>::setOffset(Number _offset)
	{
		mScalar = _offset;
	}
		
	template<typename Number>
	Number Hyperplane<Number>::signedDistance(const vector_t<Number>& _point) const {
		return (_point.dot(mNormal) - mScalar);
	}
        
	template<typename Number>
	bool Hyperplane<Number>::intersection(Number& _result, const vector_t<Number>& _vector) const
	{
		bool intersect = false;
		Number factor = 0;
#ifdef fukuda_DEBUG
		std::cout << "mNormal: " << mNormal << std::endl;
#endif
		Number dotProduct = (mNormal.dot(_vector));
#ifdef fukuda_DEBUG
		std::cout << "dotProduct: " << dotProduct << std::endl;
#endif
		if (dotProduct != 0) {
			intersect = true;
			factor = mScalar / dotProduct;
		}
		_result = factor;
		//note: to get the intersection point -> _vector *= factor;
		return intersect;
	}
        
	template<typename Number>
	bool Hyperplane<Number>::intersection(Number& _result, const Point<Number>& _vector) const
	{
		// TODO
		return false;
	}

	template<typename Number>
	const Number& Hyperplane<Number>::internalOffset() const
	{
		return mScalar;
	}

	/**
	 * @author: Chris K
	 * Method to compute the normal of a plane based on two direction vectors
	 * simply computing the cross product does not work since the dimension is not necessarily 3
	 */
	template<typename Number>
	vector_t<Number> Hyperplane<Number>::computePlaneNormal(const std::vector<vector_t<Number>>& _edgeSet) {

		/*
		 * Setup LP with GLPK
		 */
		glp_prob *normal;
		normal = glp_create_prob();
		glp_set_obj_dir(normal, GLP_MAX);

		//we have one row for each edge in our set
		glp_add_rows(normal, _edgeSet.size());

		//constraints of auxiliary variables (bounds for rows)
		for (unsigned i=1; i <= _edgeSet.size(); ++i) {
			glp_set_row_bnds(normal, i, GLP_FX, 0.0, 0.0);
		}

		//each column corresponds to one dimension of a vector in our edgeSet
		//TODO consider p1 & p2 of different dimensions? (-> two edge sets)
		glp_add_cols(normal, _edgeSet.at(0).rows());

		//coefficients of objective function:
		for (unsigned i=1; i <= _edgeSet.at(0).rows(); ++i) {
			glp_set_obj_coef(normal, i, 1.0);
		}

		//constraints for structural variables
		for (unsigned i=1; i<= _edgeSet.at(0).rows(); ++i) {
			glp_set_col_bnds(normal, i, GLP_DB, -1.0, 1.0);
		}

		//setup matrix coefficients
		unsigned elements = (_edgeSet.size()) * (_edgeSet.at(0).rows());
		int ia[1+elements];
		int ja[1+elements];
		double ar[1+elements];
		unsigned pos = 1;

		//to prevent bugs
		ia[0] = 0;
		ja[0] = 0;
		ar[0] = 0;

		for (unsigned i=1; i <= _edgeSet.size(); ++i) {

			for (unsigned j=1; j <= _edgeSet.at(0).rows(); ++j) {
				ia[pos] = i;
				ja[pos] = j;
				vector_t<Number> tmpVec = _edgeSet.at(i-1);
				ar[pos] = tmpVec(j-1);
#ifdef fukuda_DEBUG
				std::cout << "Coeff. at (" << i << "," << j << "): " << ar[pos] << std::endl;
#endif
				++pos;
			}
		}
		assert(pos-1 <= elements);

		glp_load_matrix(normal, elements, ia, ja, ar);
		glp_simplex(normal, NULL);

		vector_t<Number> result = vector_t<Number>(_edgeSet.at(0).rows(),1);

		//fill the result vector based on the optimal solution returned by the LP
		for (unsigned i=1; i <= _edgeSet.at(0).rows(); ++i) {
			result(i-1) = glp_get_col_prim(normal, i);
		}

		glp_delete_prob(normal);

		return result;
	}
	
	template<typename Number>
	bool Hyperplane<Number>::changeDimension(unsigned int newDimension) {
		assert(newDimension!=0);
		unsigned int oldDim = mDimension;
		mDimension = newDimension;
		if (newDimension == oldDim) {
			return false;
		}
		else {
			mNormal.conservativeResize(newDimension,1);
			for (unsigned i=oldDim; i<newDimension; i++) {
				mNormal(i) = 0;
			}
		}
		return true;
	}

}