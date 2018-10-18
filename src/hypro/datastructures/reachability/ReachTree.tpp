#include "ReachTree.h"

namespace hypro
{
template<typename Number>
ReachTree<Number>::ReachTree(ReachTreeNode<Number>* _root) : mRoot(_root)
{
}

template<typename Number>
ReachTreeNode<Number>* ReachTree<Number>::getRoot() const {
    return mRoot;
}

template<typename Number>
std::size_t ReachTree<Number>::getDepth() const {
	return mRoot->getSubtreeDepth();
}

template<typename Number>
std::size_t ReachTree<Number>::getNumberNodes() const {
	return mRoot->getSubtreeSize();
}

template<typename Number>
double ReachTree<Number>::getAvgBranching() const {
	return mRoot->getAvgSubtreeBranching();
}

template<typename Number>
std::vector<std::size_t> ReachTree<Number>::getLevelCnt() const {
	std::vector<std::size_t> res;
	mRoot->getLevelCnt(res);
	return res;
}

template<typename Number>
std::string ReachTree<Number>::getDotRepresentation() const {
	std::string nodes = "digraph structs \n { node [shape=record];\n";
	std::string transitions = "";
	std::string endDelimiter = "}\n";
	std::vector<unsigned> levels;
	mRoot->getDotRepresentation(0,nodes,transitions,levels);

	std::string levelCounts = "//";
	for(std::size_t i = 0; i < levels.size(); ++i){
		levelCounts += std::to_string(i);
		levelCounts += ": ";
		levelCounts += std::to_string(levels[i]);
		levelCounts += ", ";
	}

	levelCounts += "\n";

	return nodes + transitions + endDelimiter + levelCounts;

}

template<typename Number>
TreeStatistic ReachTree<Number>::getTreeStats() const {
	TreeStatistic res;
	res.nodeCnt = this->getNumberNodes();
	res.depth = this->getDepth();
	res.avgBranching = this->getAvgBranching();
	res.levelCnt = this->getLevelCnt();

	return res;
}

} // hypro
