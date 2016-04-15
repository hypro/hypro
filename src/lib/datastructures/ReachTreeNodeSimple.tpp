#include "ReachTreeNodeSimple.h"

namespace hypro
{   
    template<typename Number, typename Representation>
    ReachTreeNodeSimple::ReachTreeNodeSimple( unsigned _depth )
        : mDepth( _depth )
    {
        mChildren = std::vector< ReachTreeNode* >();  
        mID = std::vector< unsigned >( 0 );
    }
    
    template<typename Number, typename Representation>
    unsigned ReachTreeNodeSimple::getDepth()
    {
        return mDepth;
    }
    
    template<typename Number, typename Representation>
    std::vector< unsigned > ReachTreeNodeSimple::getID()
    {
        return mID;
    }
    
    template<typename Number, typename Representation>
    std::vector< ReachTreeNode* > ReachTreeNodeSimple::getChildren()
    {
        return mChildren;
    }
}