/* 
 * @file   VPolytope.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since   2014-02-25
 * @version 2014-02-25
 */

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
        return true;
    }

    template<typename Number>
    void VPolytope<Number>::clear()
    {
        mVertices.clear();
    }
}//namespace

