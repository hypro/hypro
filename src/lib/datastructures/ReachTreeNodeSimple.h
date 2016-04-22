/* 
 * File:   ReachTreeNodeSimple.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 15, 2016, 10:57 AM
 */
#pragma once

#include "../representations/GeometricObject.h"
#include "ReachTreeNode.h"

namespace hypro
{
    template <class Number, class Representation>
    class ReachTreeNode;

    template <typename Representation>
    using flowpipe_t = std::vector<Representation>;

    template <typename Number, typename Representation>
    class ReachTreeNodeSimple
    {
        protected:
            std::vector< unsigned > mID;
            unsigned mDepth;
            std::vector< ReachTreeNode<Number, Representation>* > mChildren;
        public:
        /**
	 * @brief Constructor 
	 *
	 * @param TO-DO
	 */
	ReachTreeNodeSimple( );
        
        std::vector< unsigned > getID();
        
        unsigned getDepth();
        
        std::vector< ReachTreeNode<Number, Representation>* > getChildren();
        
        void addChild( ReachTreeNode<Number,Representation>* node_to_be_added );
        
    };
}

