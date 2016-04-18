#include "NodeManager.h"
#include "ReachTreeNode.h"

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
        ReachTreeNode* result;
        ReachTreeNodeSimple* temp = mTree->getRoot();
        auto _id_iter = _id.begin();
        // Do one iteration 'manually' due to the fact that the root is
        // a supertype of the childrens' nodes
        result = ( temp->getChildren() ).at( *_id_iter );
        ++_id_iter;
        while( _id_iter != _id.end() )
        {
            result = ( result->getChildren() ).at( *_id_iter );
            ++_id_iter;
        }
        return result;
    }
    
    template<typename Number, typename Representation>
    void NodeManager::addGuardIndices( std::vector< unsigned > _id, Transition<Number>* _trans, representation_name _rep, unsigned _index )
    {
        ReachTreeNode* aim = getNode( _id );
        aim->addGuardSatisfyingSegment( _trans, _rep, _index );
    }
    
    template<typename Number, typename Representation>
    void NodeManager::addOverapprox( std::vector<unsigned> _id, flowpipe_t _overapprox )
    {
        ReachTreeNode* aim = getNode( _id );
        aim->setOverapproximation( _overapprox );
    }
}    