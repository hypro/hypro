#include "NodeManager.h"
#include "ReachTreeNode.h"

namespace hypro
{
    
    template<typename Number, typename Representation>
    NodeManager::NodeManager()
    {
        ReachTreeNodeSimple* root = new ReachTreeNodeSimple( );  
        *root = ReachTreeNodeSimple();
        mTree = ReachTree( root );
    }    
    
    template<typename Number, typename Representation>
    NodeManager::NodeManager( std::vector< initialData > _init_states )
    {
        assert( mTree->getRoot() != nullptr ); 
        auto iter_init = _init_states.begin();
        unsigned i = 0;
        while( iter_init != _init_states.end() )
        {
            ReachTreeNode* temp = new ReachTreeNode();
            std::vector< unsigned > id = std::vector< unsigned >( 0 );
            id.push_back( i );
            *temp = ReachTreeNode( id, boost::get<0>( *iter_init ), boost::get<1>( *iter_init ), 1, boost::get<2>( *iter_init ), mTree->getRoot() );
            mTree->getRoot()->addChild( temp );
            ++i
            ++iter_init;
        }
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
    void NodeManager::createNode( initialData _new_node_data, ReachTreeNode* _parent )
    {
        ReachTreeNode* newNode = new ReachTreeNode();
        std::vector< unsigned > id = _parent->getID();
        assert( id.size() > 0 );
        id.push_back( id.size() );
        *newNode = ReachTreeNode( id, boost::get<0>( _new_node_data ), boost::get<1>( _new_node_data ), boost::get<2>( _new_node_data ), 1, boost::get<2>( _new_node_data ), _parent );
        _parent->addChild( newNode );              
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