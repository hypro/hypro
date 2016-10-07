#include "ReachTree.h"

namespace hypro
{
    template<typename Number, typename Representation>
    ReachTree::ReachTree( ReachTreeNodeSimple* _root )
        : mRoot( _root )
    {
        
    }
    
    template<typename Number, typename Representation>
    ReachTreeNodeSimple* ReachTree::getRoot()
    {
        return mRoot;
    }
}
