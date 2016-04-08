#include "ReachTreeNode.h"

namespace hypro
{
    template<typename Number, typename Representation>
    ReachTreeNode::ReachTreeNode( Location<Number>* _loc, Number _time_step, unsigned _depth, ReachTreeNode* _parent )
        : mLoc( _loc ), mTimeStep( _time_step ), mDepth( _depth ), mParent( _parent )
    {
        mChildren = std::vector< ReachTreeNode* >();    
    }
    
    template<typename Number, typename Representation>
    Location<Number>* ReachTreeNode::getLocation()
    {
        return mLast;
    }
    
    template<typename Number, typename Representation>
    Number ReachTreeNode::getTimeStep()
    {
        return mTimeStep;
    }
       
    template<typename Number, typename Representation>
    unsigned ReachTreeNode::getDepth()
    {
        return mDepth;
    }
      
    template<typename Number, typename Representation>
    Representation ReachTreeNode::getFirstSegment()
    {
        return mFirst;
    }
    
    template<typename Number, typename Representation>    
    Representation ReachTreeNode::getLastSegment()
    {
        return mLast;
    }
    
    template<typename Number, typename Representation>    
    std::map< unsigned, std::pair< Number, Number > > ReachTreeNode::getGuardSatisfiedFirstLast()
    {
        return mGuardSatisfiedFirstLast;
    }
    
    template<typename Number, typename Representation>    
    flowpipe_t ReachTreeNode::getOverapprox()
    {
        return mOverapprox;
    }
     
    template<typename Number, typename Representation>
    std::vector< ReachTreeNode* > ReachTreeNode::getChildren()
    {
        return mChildren;
    }
    
    template<typename Number, typename Representation>    
    ReachTreeNode ReachTreeNode::getParent()
    {
        return mParent;
    }    
    
    template<typename Number, typename Representation>
    void ReachTreeNode::setTimeStep(Number _time_step)
    {
        mTimeStep = _time_step;
    }
    
    template<typename Number, typename Representation>
    void ReachTreeNode::setFirstSegment( Representation _first )
    {
        mFirst = _first;
    }  
        
    template<typename Number, typename Representation>
    void ReachTreeNode::setLastSegment( Representation _last )
    {
        mLast = _last;
    } 
        
    template<typename Number, typename Representation>
    void ReachTreeNode::setGuardSatisfyingSegments( std::map<unsigned,std::pair< Number, Number > > _guard_satisfied_first_last )
    {
        mGuardSatisfiedFirstLast = _guard_satisfied_first_last;
    }
    
    template<typename Number, typename Representation>
    void ReachTreeNode::setOverapproximation( flowpipe_t overapprox )
    {
        mOverapprox = overapprox;
    }
    
    template<typename Number, typename Representation>
    void ReachTreeNode::addChild( ReachTreeNode* node_appended_on, ReachTreeNode* node_to_be_added )
    {
        node_appended_on->mChildren.push_back( node_to_be_added );
    }
}
