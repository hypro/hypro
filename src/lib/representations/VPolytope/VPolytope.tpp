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
    bool VPolytope<Number>::linear_transformation(VPolytope<Number>& result /*, ... */) const
    {
        
    }
    
    template<typename Number>
    bool VPolytope<Number>::minkowski_sum(VPolytope<Number>& result, const VPolytope<Number>& rhs) const
    {
        
    }
    
    template<typename Number>
    bool VPolytope<Number>::intersect(VPolytope<Number>& result, const VPolytope<Number>& rhs) const
    {
        
    }
    
    template<typename Number>
    bool VPolytope<Number>::hull(VPolytope<Number>& result) const
    {
        
    }
    
    template<typename Number>
    bool VPolytope<Number>::contains(const Point<Number>& point) const
    {
        
    }
    
    template<typename Number>
    bool VPolytope<Number>::unite(VPolytope<Number>& result, const VPolytope<Number>& rhs) const
    {
        
    }

    template<typename Number>
    void VPolytope<Number>::clear()
    {
        mVertices.clear();
    }
}//namespace

