#include "NodeManager.h"

namespace hypro
{   
    template<typename Number, typename Representation>
    NodeManager::NodeManager( ReachTree _tree )
        : mTree( _tree )
    {
        
    }
    
    template<typename Number, typename Representation>
    ReachTreeNode* NodeManager::getNode( std::vector<unsigned> _id )
    {
        assert( _id.size() > 0 && _id != std::vector<unsigned>( 0 ) );
        ReachTreeNode* result = mTree->getRoot();
        auto _id_iter = _id.begin();
        while( _id_iter != _id.end() )
        {
            result = ( result->getChildren() ).at( *_id_iter );
            ++_id_iter;
        }
        return result;
    }
    
    template<typename Number, typename Representation>
    void NodeManager::modifyNode(std::vector<unsigned> _id)
    {
        // TO-DO        
    }
}    