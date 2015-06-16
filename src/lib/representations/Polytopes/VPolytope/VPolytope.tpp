/* 
 * @file   VPolytope.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since   2014-02-25
 * @version 2014-02-25
 */

#include "VPolytope.h"


namespace hypro
{
	template<typename Number>
	VPolytope<Number>::VPolytope() : 
		mPoints(),
		mFan(),
		mFanSet(false),
		mReduced(true),
		mInitialized(false)
	{}

	template<typename Number>
	VPolytope<Number>::VPolytope(const Point<Number>& point)
	{
		mPoints.push_back(point);
		mFan = polytope::Fan<Number>();
		mFanSet = false;
		mReduced = true;
		mInitialized = false;
	}

	template<typename Number>
	VPolytope<Number>::VPolytope(const pointVector& points)
	{
		for(const auto point : points) {
			mPoints.push_back(point);
		}
		mFan = polytope::Fan<Number>();
		mFanSet = false;
		mReduced = false;
		mInitialized = false;
	}

	template<typename Number>
	VPolytope<Number>::VPolytope(const matrix_t<Number>& _constraints, const vector_t<Number> _constants) {

		std::cout << _constraints << std::endl << _constants << std::endl;

		// calculate all possible hyperplane intersections -> TODO: dPermutation can be improved.
		std::vector<std::vector<unsigned>> permutationIndices = polytope::dPermutation(_constraints.rows(), _constraints.cols());
		matrix_t<Number> intersection = matrix_t<Number>(_constraints.cols(), _constraints.cols());
		vector_t<Number> intersectionConstants = vector_t<Number>(_constraints.cols());
		std::vector<vector_t<Number>> possibleVertices;
		for(const auto& permutation : permutationIndices) {
			unsigned rowCount = 0;
			for(const auto& rowIndex : permutation) {
				intersection.row(rowCount) = _constraints.row(rowIndex);
				intersectionConstants(rowCount) = _constants(rowIndex);
				++rowCount;
			}
			// check if rank is full
			if(intersection.colPivHouseholderQr().rank() == intersection.cols()) {
				vector_t<Number> vertex = intersection.colPivHouseholderQr().solve(intersectionConstants);
				possibleVertices.push_back(vertex);
				std::cout<< "Vertex choices: (" << permutation << ") " << vertex.transpose() << std::endl;
			}
		}
		
		// check if vertices are true vertices (i.e. they fulfill all constraints)
		for(auto vertex = possibleVertices.begin(); vertex != possibleVertices.end(); ++vertex){
		//std::cout<<__func__ << " : " <<__LINE__ << " current position : " << i << std::endl;
		//std::cout<<__func__ << " : " <<__LINE__ << "number of vertices : " << possibleVertices.size() << std::endl;
			for(unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex) {
				Number res = vertex->dot(_constraints.row(rowIndex));
				if(res > _constants(rowIndex)) 
					vertex = possibleVertices.erase(vertex) - 1;
			}
		}
		//std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
		// finish initialization
		for(const auto& point : possibleVertices) {
			mPoints.push_back(Point<Number>(point));
			std::cout << "Real vertex " << point.transpose() << std::endl;
		}
		//std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
		mFan = polytope::Fan<Number>();
		mFanSet = false;
		mReduced = false;
		mInitialized = false;
	}

	template<typename Number>
	VPolytope<Number>::VPolytope(const VPolytope& orig)
	{
		mPoints.insert(mPoints.end(), orig.begin(), orig.end());
		mFan = polytope::Fan<Number>();
		mFanSet = false; // TODO: Include getter fpr this
		mReduced = orig.reduced(); // TODO: Include getter fpr this
		mInitialized = false;
		mCone = orig.cone();
	}
	
	template<typename Number>
	VPolytope<Number> VPolytope<Number>::linearTransformation(const matrix_t<Number>& A) const
	{
		VPolytope<Number> result;
		for(const auto& vertex : mPoints) {
			result.insert(vertex.linearTransformation(A));
		}
		result.setCone(mCone.linearTransformation(A));
		return result;
	}
	
	template<typename Number>
	VPolytope<Number> VPolytope<Number>::minkowskiSum(const VPolytope<Number>& rhs) const
	{
		VPolytope<Number> result;
		// add each rhs-vertex to each vertex of this polytope.
		for(auto lhsVertex : mPoints)
		{
			for(auto rhsVertex : rhs.mPoints)
			{
				result.insert(lhsVertex+rhsVertex);
			}
		}
		result.setCone(mCone.minkowskiSum(rhs.cone()));
		return result;
	}
	
	template<typename Number>
	VPolytope<Number> VPolytope<Number>::intersect(const VPolytope<Number>& rhs) const {
		// create a set of possible points via combination of all coordinates
		pointVector possibleVertices;
		for(const auto& lhsVertex : mPoints) {
			possibleVertices.push_back(lhsVertex);
			for(unsigned coordIndex = 0; coordIndex < lhsVertex.rawCoordinates().rows(); ++coordIndex) {
				for(const auto& rhsVertex : rhs.mPoints) {
					vector_t<Number> newVertex = rhsVertex.rawCoordinates();
					newVertex(coordIndex) = lhsVertex.at(coordIndex);
					possibleVertices.push_back(vector_t<Number>(newVertex));
					possibleVertices.push_back(vector_t<Number>(rhsVertex));
				}
			}
		}
		// remove all vertices, which are only contained in one of the polytopes
		for(auto vertexIt = possibleVertices.begin(); vertexIt != possibleVertices.end(); ) {
			if( !(this->contains(*vertexIt) && rhs.contains(*vertexIt)) ) {
				vertexIt = possibleVertices.erase(vertexIt);
			}
			else {
				++vertexIt;
			}
		}
		return VPolytope<Number>(possibleVertices);
	}
	
	template<typename Number>
	bool VPolytope<Number>::contains(const Point<Number>& point) const
	{
		return this->contains(point.rawCoordinates());
	}
	
	template<typename Number>
	bool VPolytope<Number>::contains(const vector_t<Number>& vec) const {
		// initialize tableau if necessary
		if(!mInitialized)
			initGLPK();
		
		glp_set_obj_dir(mLp,GLP_MAX);
		for(unsigned i = 1; i <= vec.rows(); ++i)
			glp_set_row_bnds(mLp, i, GLP_FX,double(vec(i-1)),0); // as the variable is fixed, the last parameter (upper row bound) is ignored
		
		glp_set_row_bnds(mLp, vec.rows()+1, GLP_FX,1.0,0); // the sum of the vectors equals exactly one.
		
		for(unsigned i = 1; i <= mPoints.size(); ++i){
			glp_set_col_bnds(mLp,i, GLP_DB, 0.0, 1.0);
			glp_set_obj_coef(mLp,i,1.0); // the objective function is max: v1 + v2 + v3 + ... + vn
		}
		
		// solve
		glp_simplex(mLp, &mOptions);
		bool interiorPoint = (glp_get_prim_stat(mLp) == GLP_FEAS);
		
		return interiorPoint;
	}

	template<typename Number>
	bool VPolytope<Number>::contains(const VPolytope<Number>& _other) const {
		for(const auto& vertex : _other.vertices()) {
			if(!this->contains(vertex))
				return false;
		}
		return true;
	}
	
	template<typename Number>
	VPolytope<Number> VPolytope<Number>::unite(const VPolytope<Number>& rhs) const
	{
		VPolytope<Number>::pointVector points;
		points.insert(points.end(), this->mPoints.begin(), this->mPoints.end());
		points.insert(points.end(), rhs.mPoints.begin(),rhs.mPoints.end());
		
		std::vector<Facet<Number>*> facets = convexHull(points);
		std::set<Point<Number>> preresult;
		for(unsigned i = 0; i<facets.size(); i++) {
			for(unsigned j = 0; j<facets[i]->vertices().size(); j++) {
				preresult.insert(facets[i]->vertices().at(j));			
			}			
		}
		VPolytope<Number>::pointVector res;
		for(const auto& point : preresult)
			res.push_back(point);

		return VPolytope<Number>(res);
		
		//return result;
	}

	template<typename Number>
	void VPolytope<Number>::clear()
	{
		mPoints.clear();
	}

	template<typename Number>
    Number VPolytope<Number>::supremum () const {
    	Number max = 0;
        for(auto& point : mPoints)
        {
            Number inftyNorm = hypro::Point<Number>::inftyNorm(point);
            max = max > inftyNorm ? max : inftyNorm;
        }
        return max;
    }
	
	/***************************************************************************
	 * Auxiliary functions
	 **************************************************************************/
	
	template<typename Number>
	void VPolytope<Number>::initGLPK() const {
		if(!mInitialized) {
			// create lp problem (basic options etc.) of size dimension+1 x #Points
			mLp = glp_create_prob();
			glp_init_smcp(&mOptions);
			mOptions.msg_lev = GLP_MSG_OFF;
			glp_add_rows(mLp, this->dimension()+1);
			glp_add_cols(mLp, mPoints.size());

			// prepare matrix
			unsigned size = mPoints.size()*(this->dimension()+1); // add one row to hold the constraint that all add up to one.
			mIa = new int[size+1];
			mJa = new int[size+1];
			mAr = new double[size+1];
			unsigned pos = 1;
			typename pointVector::const_iterator vertex = mPoints.begin();
			for(unsigned i = 1; i <= this->dimension()+1; ++i) {
				for(unsigned j = 1; j <= mPoints.size(); ++j) {
					mIa[pos] = i; mJa[pos] = j;
					if(i == this->dimension()+1) {
						mAr[pos] = 1.0;
						std::cout << "Setting: mIa[" << pos << "]=" << i << ", mJa[" << pos << "]=" << j << ", mAr[" << pos << "]= 1.0" << std::endl;
					}else{
						mAr[pos] = double((*vertex).at(i-1));
						std::cout << "Setting: mIa[" << pos << "]=" << i << ", mJa[" << pos << "]=" << j << ", mAr[" << pos << "]=" << double((*vertex).at(i-1)) << std::endl;
					}
					++pos;
					++vertex;
				}
				vertex = mPoints.begin();
			}
			glp_load_matrix(mLp,size, mIa, mJa, mAr);
			mInitialized = true;
		}
	}
	
	template<typename Number>
	const typename VPolytope<Number>::Fan& VPolytope<Number>::calculateFan() const
	{
		if(!mFanSet) {
			std::vector<Facet<Number>> facets = convexHull(mPoints);
			std::set<Point<Number>> preresult;
			for(unsigned i = 0; i<facets.size(); i++) {
				for(unsigned j = 0; j<facets[i].vertices().size(); j++) {
					preresult.insert(facets[i].vertices().at(j));							
				}				
			} 
			polytope::Fan<Number> fan;
			for(auto& point : preresult) {
				polytope::Cone<Number>* cone = new polytope::Cone<Number>();
				for(unsigned i = 0; i<facets.size(); i++) {
					for(unsigned j = 0; j<facets[i].vertices().size(); j++) {
						if(point == facets[i].vertices().at(j))	{
						std::vector<Ridge<Number>> ridges = getRidges(facets[i]);
							for(unsigned m = 0; m<ridges.size(); m++) { 
								if(checkInsideRidge(ridges[m], point)) {						
									std::vector<Facet<Number>> conefacets = shareRidge(facets, ridges[m]);
							
									matrix_t<Number> matrix = matrix_t<Number>(conefacets.size(),point.size());
									for(unsigned k = 1; k < conefacets.size(); k++) {
										for(unsigned l = 0; l < conefacets[k].getNormal().size(); l++) {
											matrix(k,l) = conefacets[k].getNormal()(l);
										}
									}
							
									for(unsigned j = 0; j < point.size(); j++) {
										matrix(0,j) = 1;
	
										if(matrix.fullPivLu().rank()==point.size()){
											break;
										} else {
											matrix(0,j) = 0;
										}
									}
									vector_t<Number> b = vector_t<Number>::Zero(conefacets.size());
									b(0) = 1;
									vector_t<Number> result = matrix.fullPivHouseholderQr().solve(b);
								
									cone->add(std::shared_ptr<Hyperplane<Number>>( new Hyperplane<Number>(result, result.dot(point.rawCoordinates()))));
									//cone->add(std::make_shared<Hyperplane<Number>>(Hyperplane<Number>(result, result.dot(point.rawCoordinates()))));	
								}	
							}	
						}					
					}			
				}
			fan.add(cone);	
			}
		mFanSet = true;
		mFan = fan;
	}
}

	template<typename Number>
	const typename VPolytope<Number>::Cone& VPolytope<Number>::calculateCone(const Point<Number>& vertex)
	{
		// set up glpk
		glp_prob *cone;
		cone = glp_create_prob();
		glp_set_obj_dir(cone, GLP_MIN);

		typename polytope::Cone<Number>::vectors vectors;
		for(auto& cone : mFan.get())
		{
			vectors.insert(vectors.end(), cone.begin(), cone.end());
		}             
		unsigned numVectors = vectors.size();
		unsigned elements = this->dimension() * numVectors;

		glp_add_cols(cone, numVectors);
		glp_add_rows(cone, this->dimension());

		int ia[elements];
		int ja[elements];
		double ar[elements];
		unsigned pos = 1;

		for(unsigned i = 1; i <= this->dimension(); ++i)
		{
			for(unsigned j = 1; j <= numVectors; ++j)
			{
				ia[pos] = i;
				ja[pos] = j;
				ar[pos] = vectors.at(j).at(i);
				++pos;
			}
		}
		assert(pos <= elements);

		glp_load_matrix(cone, elements, ia, ja, ar);
		glp_simplex(cone, NULL);

		// TODO output & result interpretation

		//glp_delete_prob(cone);
	}
	
	template<typename Number>
	VPolytope<Number>& VPolytope<Number>::operator=(const VPolytope<Number>& rhs)
	{
		if( this != &rhs )
		{
			VPolytope<Number> tmp(rhs);
			std::swap(*this,tmp);
		}
		return *this;
	}
	
	template<typename Number>
	bool VPolytope<Number>::operator==(const VPolytope<Number>& rhs)
	{
		if(this->dimension() != rhs.dimension())
			return false;

		// TODO: Highly inefficient!!!
		for(auto& lPoint : this->vertices())
		{
			if(!rhs.hasVertex(lPoint))
				return false;
		}
		for(auto& rPoint : rhs.vertices())
		{
			if(!this->hasVertex(rPoint))
				return false;
		}
		return true;
	}
	
}//namespace

