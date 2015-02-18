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
		mVertices(),
		mFan(),
		mFanSet(false),
		mReduced(true)
	{}

	template<typename Number>
	VPolytope<Number>::VPolytope(const Point<Number>& point)
	{
		mVertices.insert(point);
		mFan = polytope::Fan<Number>();
		mFanSet = false;
		mReduced = true;
	}

	template<typename Number>
	VPolytope<Number>::VPolytope(const vertexSet& points)
	{
		mVertices.insert(points.begin(), points.end());
		mFan = polytope::Fan<Number>();
		mFanSet = false;
		mReduced = true;
	}

	template<typename Number>
	VPolytope<Number>::VPolytope(const VPolytope& orig)
	{
		mVertices.insert(orig.begin(), orig.end());
		mFan = polytope::Fan<Number>();
		mFanSet = false; // TODO: Include getter fpr this
		mReduced = true; // TODO: Include getter fpr this
	}
	
    template<typename Number>
    VPolytope<Number> VPolytope<Number>::linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b) const
    {
		VPolytope<Number> result;
		for(const auto& vertex : mVertices) {
			result.insert(vertex*A + b);
		}
        return result;
    }
    
    template<typename Number>
    VPolytope<Number> VPolytope<Number>::minkowskiSum(const VPolytope<Number>& rhs) const
    {
        VPolytope<Number> result;
        // add each rhs-vertex to each vertex of this polytope.
        for(auto lhsVertex : mVertices)
        {
            for(auto rhsVertex : rhs.mVertices)
            {
                result.insert(lhsVertex+rhsVertex);
            }
        }
        return true;
    }
    
    template<typename Number>
    VPolytope<Number> VPolytope<Number>::intersect(const VPolytope<Number>& rhs) const {
		// create a set of possible points via combination of all coordinates
		vertexSet possibleVertices;
        for(const auto& lhsVertex : mVertices) {
			possibleVertices.insert(lhsVertex);
			std::cout << __func__ << ": possible Vertex: " << lhsVertex << std::endl;
			for(unsigned coordIndex = 0; coordIndex < lhsVertex.rows(); ++coordIndex) {
				for(const auto& rhsVertex : rhs.mVertices) {
					vector_t<Number> newVertex = rhsVertex;
					newVertex(coordIndex) = lhsVertex(coordIndex);
					possibleVertices.insert(vector_t<Number>(newVertex));
					std::cout << __func__ << ": possible Vertex: " << newVertex << std::endl;
					possibleVertices.insert(vector_t<Number>(rhsVertex));
					std::cout << __func__ << ": possible Vertex: " << rhsVertex << std::endl;
				}
			}
        } 
		
		for(auto& vertex : possibleVertices) {
			std::cout << __func__ << " : " << __LINE__ << std::endl;
			if( !(this->contains(vertex) && rhs.contains(vertex)) ) {
				std::cout << __func__ << " : " << __LINE__ << std::endl;
				std::cout << __func__ << ": vertex not in intersection: " << vertex << std::endl;
				possibleVertices.erase(vertex);
				std::cout << __func__ << " : " << __LINE__ << std::endl;
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
		
		std::cout << __func__ << " : " << vec << std::endl;
		
		glp_prob* lp;
		lp = glp_create_prob();
		glp_set_obj_dir(lp,GLP_MAX);
		glp_add_rows(lp, this->dimension()+1);
		glp_add_cols(lp, mVertices.size());
		glp_smcp* options = new glp_smcp;
		glp_init_smcp(options);
		//options->msg_lev = GLP_MSG_ALL;
		
		for(unsigned i = 1; i <= vec.rows(); ++i)
			glp_set_row_bnds(lp, i, GLP_FX,double(vec(i-1)),0); // as the variable is fixed, the last parameter (upper row bound) is ignored
		glp_set_row_bnds(lp, vec.rows()+1, GLP_FX,1.0,0); // the sum of the vectors equals exactly one.
		
		for(unsigned i = 1; i <= mVertices.size(); ++i){
			glp_set_col_bnds(lp,i, GLP_DB, 0.0, 1.0);
			glp_set_obj_coef(lp,i,1.0); // the objective function is max: v1 + v2 + v3 + ... + vn
		}
		
		// prepare matrix
		unsigned size = mVertices.size()*(this->dimension()+1); // add one row to hold the constraint that all add up to one.
		int* ia = new int[size];
		int* ja = new int[size];
		double* ar = new double[size];
		unsigned pos = 1;
		typename vertexSet::iterator vertex = mVertices.begin();
		for(unsigned i = 1; i <= vec.rows()+1; ++i) {
			for(unsigned j = 1; j <= mVertices.size(); ++j) {
				ia[pos] = i; ja[pos] = j;
				if(i == vec.rows()+1) {
					ar[pos] = 1.0;
				}else{
					ar[pos] = double((*vertex)(i-1));
				}
//				std::cout << "Setting: ia[" << pos << "]=" << i << ", ja[" << pos << "]=" << j << ", ar[" << pos << "]=" << double((*vertex)(i-1)) << std::endl;
				++pos;
				++vertex;
			}
			vertex = mVertices.begin();
		}
		
		// solve
		glp_load_matrix(lp,size, ia, ja, ar);
		int result = glp_simplex(lp,options);
		std::cout << "GLP_RESULT: " << result << std::endl;
		std::cout << "Problem state: " << glp_get_prim_stat(lp) << std::endl;
		bool interiorPoint = (glp_get_prim_stat(lp) == GLP_FEAS);
		
		// cleanup
		glp_delete_prob(lp);
		delete ia;
		delete ja;
		delete ar;
		delete options;
		
		return interiorPoint;
	}
    
    template<typename Number>
    VPolytope<Number> VPolytope<Number>::unite(const VPolytope<Number>& rhs) const
    {
        VPolytope<Number> result;
        result.insert(this->mVertices.begin(), this->mVertices.end());
        result.insert(rhs.mVertices.begin(),rhs.mVertices.end());
        return result;
    }

    template<typename Number>
    void VPolytope<Number>::clear()
    {
        mVertices.clear();
    }
    
    /***************************************************************************
     * Auxiliary functions
     **************************************************************************/
    
    template<typename Number>
    const typename VPolytope<Number>::Fan& VPolytope<Number>::calculateFan() const
    {
        // Todo: ensure ordering of the points
        
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

        glp_delete_prob(cone);
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

