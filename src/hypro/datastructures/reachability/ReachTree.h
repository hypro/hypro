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

namespace hypro {
template <typename State>
class ReachTree {
  private:
	ReachTreeNode<State>* mRoot;

  public:
	ReachTree( ReachTreeNode<State>* _root );

	~ReachTree() {
		delete mRoot;
	}

	ReachTreeNode<State>* getRoot() const;

	std::size_t getDepth() const;

	std::size_t getNumberNodes() const;

	double getAvgBranching() const;

	std::vector<std::size_t> getLevelCnt() const;

	std::string getDotRepresentation() const;

	TreeStatistic getTreeStats() const;
};
}  // namespace hypro

#include "ReachTree.tpp"
