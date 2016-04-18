/* 
 * File:   ReachTreeNodeSimple.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 15, 2016, 10:57 AM
 */

#include "../representations/GeometricObject.h"

namespace hypro
{
    template <typename Representation>
    using flowpipe_t = std::vector<Representation>;
    
    template <typename Number, typename Representation>
    class ReachTreeNodeSimple
    {
        protected:
            std::vector< unsigned > mID;
            unsigned mDepth;
            std::vector< ReachTreeNode* > mChildren;
        public:
        /**
	 * @brief Constructor 
	 *
	 * @param TO-DO
	 */
	ReachTreeNodeSimple( );
        
        std::vector< unsigned > getID();
        
        unsigned getDepth();
        
        std::vector< ReachTreeNode* > getChildren();
        
        void addChild( ReachTreeNode* node_to_be_added );
        
    };
}

