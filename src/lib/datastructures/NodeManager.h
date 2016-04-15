/* 
 * File:   NodeManager.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 15, 2016, 11:38 AM
 */

#include "ReachTree.h"

namespace hypro
{    
    template <typename Number, typename Representation>
    class NodeManager
    {
        private:
            ReachTree mTree;
            
        public:
            NodeManager( ReachTree _tree );
            ReachTreeNode* getNode( std::vector< unsigned > _id );
            // TO-DO createNode( ... );
            void addGuardIndices( std::vector< unsigned > _id, Transition<Number>* _trans, representation_name _rep, unsigned _index );
            void addOverapprox( std::vector< unsigned > _id, flowpipe_t _overapprox  );
    };
}  

