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
    bool VPolytope<Number>::linearTransformation(VPolytope<Number>& result /*, ... */) const
    {
        return true;
    }
    
    template<typename Number>
    bool VPolytope<Number>::minkowskiSum(VPolytope<Number>& result, const VPolytope<Number>& rhs) const
    {
        result.clear();
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
    bool VPolytope<Number>::intersect(VPolytope<Number>& result, const VPolytope<Number>& rhs) const
    {
        result.clear();
        for(auto lhsVertex : mVertices)
        {
            for(auto rhsVertex : rhs.mVertices)
            {
                // first add the contained points, as they are always part of the intersection
                if(rhs.contains(lhsVertex))
                {
                    result.insert(lhsVertex);
                }
                if(this->contains(rhsVertex))
                {
                    result.insert(rhsVertex);
                }
                // add the points resulting from the intersection of facets
                // Todo
            }
        } 
        return true;
    }
    
    template<typename Number>
    bool VPolytope<Number>::hull(VPolytope<Number>& result) const
    {
        return true;
    }
    
    template<typename Number>
    bool VPolytope<Number>::contains(const Point<Number>& point) const
    {
        return true;
    }
    
    template<typename Number>
    bool VPolytope<Number>::unite(VPolytope<Number>& result, const VPolytope<Number>& rhs) const
    {
        result.clear();
        result.insert(this->mVertices.begin(), this->mVertices.end());
        result.insert(rhs.mVertices.begin(),rhs.mVertices.end());
        return true;
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
        unsigned elements = this->mDimension * numVectors;

        glp_add_cols(cone, numVectors);
        glp_add_rows(cone, this->mDimension);

        int ia[elements];
        int ja[elements];
        double ar[elements];
        unsigned pos = 1;

        for(unsigned i = 1; i <= this->mDimension; ++i)
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

