#include "ReachTreeNodeSimple.h"

namespace hypro
{   
    template<typename Number, typename Representation>
    ReachTreeNodeSimple::ReachTreeNodeSimple( )
    {
        mChildren = std::vector< ReachTreeNode* >();  
        mDepth = 0;
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
    
    template<typename Number, typename Representation>
    void ReachTreeNodeSimple::addChild( ReachTreeNode* node_to_be_added )
    {
        this->mChildren.push_back( node_to_be_added );        
    }
    
    
}