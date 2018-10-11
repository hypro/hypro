/*
 * File:   ReachTree.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 8, 2016, 12:04 PM
 */

#include "ReachTreeNode.h"
#include "TreeStatistic.h"
#include <string>

namespace hypro
{
class ReachTree
{
  private:
    ReachTreeNode::Node_t mRoot;

  public:
    ReachTree(ReachTreeNode::Node_t _root);

    ~ReachTree(){
    	delete mRoot;
    }

    ReachTreeNode::Node_t getRoot() const;

    std::size_t getDepth() const;

	std::size_t getNumberNodes() const;

	double getAvgBranching() const;

	std::vector<std::size_t> getLevelCnt() const;

    std::string getDotRepresentation() const;

    TreeStatistic getTreeStats() const;
};
} // hypro
