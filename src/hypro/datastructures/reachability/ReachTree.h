/*
 * File:   ReachTree.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 8, 2016, 12:04 PM
 */

#pragma once
#include "ReachTreeNode.h"
#include "TreeStatistic.h"
#include <string>

namespace hypro
{
template<typename Number>
class ReachTree
{
  private:
    ReachTreeNode<Number>* mRoot;

  public:
    ReachTree(ReachTreeNode<Number>* _root);

    ~ReachTree(){
    	delete mRoot;
    }

    ReachTreeNode<Number>* getRoot() const;

    std::size_t getDepth() const;

	std::size_t getNumberNodes() const;

	double getAvgBranching() const;

	std::vector<std::size_t> getLevelCnt() const;

    std::string getDotRepresentation() const;

    TreeStatistic getTreeStats() const;
};
} // hypro

#include "ReachTree.tpp"
