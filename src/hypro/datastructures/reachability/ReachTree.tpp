#include "ReachTree.h"

namespace hypro {
template <typename State>
ReachTree<State>::ReachTree( ReachTreeNode<State>* _root )
	: mRoot( _root ) {
	mRoot->setDepth( -1 );
}

template <typename State>
ReachTreeNode<State>* ReachTree<State>::getRoot() const {
	return mRoot;
}

template <typename State>
std::size_t ReachTree<State>::getDepth() const {
	return mRoot->getSubtreeDepth();
}

template <typename State>
std::size_t ReachTree<State>::getNumberNodes() const {
	return mRoot->getSubtreeSize();
}

template <typename State>
double ReachTree<State>::getAvgBranching() const {
	return mRoot->getAvgSubtreeBranching();
}

template <typename State>
std::vector<std::size_t> ReachTree<State>::getLevelCnt() const {
	std::vector<std::size_t> res;
	mRoot->getLevelCnt( res );
	return res;
}

template <typename State>
std::string ReachTree<State>::getDotRepresentation() const {
	std::string nodes = "digraph structs \n { node [shape=record];\n";
	std::string transitions = "";
	std::string endDelimiter = "}\n";
	std::vector<unsigned> levels;
	mRoot->getDotRepresentation( 0, nodes, transitions, levels );

	std::string levelCounts = "//";
	for ( std::size_t i = 0; i < levels.size(); ++i ) {
		levelCounts += std::to_string( i );
		levelCounts += ": ";
		levelCounts += std::to_string( levels[i] );
		levelCounts += ", ";
	}

	levelCounts += "\n";

	return nodes + transitions + endDelimiter + levelCounts;
}

template <typename State>
TreeStatistic ReachTree<State>::getTreeStats() const {
	TreeStatistic res;
	res.nodeCnt = this->getNumberNodes();
	res.depth = this->getDepth();
	res.avgBranching = this->getAvgBranching();
	res.levelCnt = this->getLevelCnt();

	return res;
}

}  // namespace hypro
