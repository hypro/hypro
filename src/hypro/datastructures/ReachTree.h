/* 
 * File:   ReachTree.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 8, 2016, 12:04 PM
 */

#include "ReachTreeNodeSimple.h"

namespace hypro
{    
    template <typename Number, typename Representation>
    class ReachTree
    {
        private:
            ReachTreeNodeSimple* mRoot;
            
        public:
            ReachTree( ReachTreeNodeSimple* _root );
            ReachTreeNodeSimple* getRoot();
    };
}    

