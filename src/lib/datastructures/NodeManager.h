/* 
 * File:   NodeManager.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 15, 2016, 11:38 AM
 */

#include "ReachTree.h"

namespace hypro
{
    template<typename Number, typename Representation>
    using initialData = boost::tuple< Location<Number>*, Number, representation_name >;
    
    template <typename Number, typename Representation>
    class NodeManager
    {
        private:
            ReachTree mTree;
            
        public:
            // The constructor to be used when the initial states are inserted into the tree
            // Note: The default constructor must have been called before to obtain defined behavior
            NodeManager( std::vector< initialData > _init_states );
            ReachTreeNode* getNode( std::vector< unsigned > _id );
            createNode( initialData _new_node_data, ReachTreeNode* _parent );
            void addGuardIndices( std::vector< unsigned > _id, Transition<Number>* _trans, representation_name _rep, unsigned _index );
            void addOverapprox( std::vector< unsigned > _id, flowpipe_t _overapprox  );
    };
}  

