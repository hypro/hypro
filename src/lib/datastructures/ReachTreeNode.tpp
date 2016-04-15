#include "ReachTreeNode.h"

namespace hypro
{
    template<typename Number, typename Representation>
    ReachTreeNode::ReachTreeNode( std::vector< unsigned > _id, Location<Number>* _loc, Number _time_step, unsigned _depth, representation_name _rep, ReachTreeNode* _parent )
        : mID( _id ), mLoc( _loc ), mTimeStep( _time_step ), mDepth( _depth ), mRep( _rep ), mParent( _parent )
    {
        mChildren = std::vector< ReachTreeNode* >(); 
        mGuardSatisfiedIndices = guard_map();
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
    representation_name ReachTreeNode::getRep()
    {   
        return mRep;  
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
    std::map< Transition<Number>*, std::vector< unsigned > > ReachTreeNode::getGuardSatisfiedIndices()
    {
        return mGuardSatisfiedIndices;
    }
    
    template<typename Number, typename Representation>    
    flowpipe_t ReachTreeNode::getOverapprox()
    {
        return mOverapprox;
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
    void ReachTreeNode::setRepresentation( representation_name _rep )
    {
        mRep = _rep;
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
    void ReachTreeNode::setOverapproximation( flowpipe_t overapprox )
    {
        mOverapprox = overapprox;
    }
    
    template<typename Number, typename Representation>
    void ReachTreeNode::addGuardSatisfyingSegment( Transition<Number>* _trans, representation_name _rep, unsigned _index )
    {
        mGuardSatisfiedIndices[ std::pair( _trans, _rep ) ] = _index;       
    }
}
