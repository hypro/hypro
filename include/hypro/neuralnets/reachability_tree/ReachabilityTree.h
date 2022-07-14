// reachability tree should have a data member which is a Neural Network (it holds all the data for the network)
// it should have a method verify network which has an input set and safety set and also a reachability method (Exact or overapproximate)
// also it should have an option to set the tree search behavior between BFS and DFS (in the constructor)
// should have a method which decides if one output set satisfies the safety property
// this check should be made after each leaf in DFS (here early termination is possible) and also for each leaf in BFS (here we get all the output sets at the same time)
// the bfs / dfs should be layer-wise

// #include "../network/NeuralNetwork.h"
// #include "ReachabilityNode.h"
// #include "SearchJob.h"
// #include "SearchStrategy.h"

#pragma once
#include "ReachabilityNode.h"
#include "SearchJob.h"
#include "SearchStrategy.h"

#include <deque>
#include <vector>

namespace hypro {
namespace reachability {

template <typename Number>
class ReachabilityTree {
  private:
	ReachabilityNode<Number>* mRoot;				 // root node of the reachability analysis tree
	std::vector<ReachabilityNode<Number>*> mLeaves;	 // the leaves of the reachability tree
	unsigned short int mDepth;						 // depth of the reachability tree

	NeuralNetwork<Number> mNetwork;	 // the analysied neural network
	HPolytope<Number> mInputSet;	 // the input set of the network
	HPolytope<Number> mSafeSet;		 // the safe set specified in the form of a HPolytope
	bool mIsSafe;					 // true if the reachability tree is safe
	bool mISComplete;				 // true if the  computation of the reachability tree finished

  public:
	// Default constructor
	ReachabilityTree();

	// Destructor - recursively delete all nodes from the root to the leaves
	~ReachabilityTree();

	// Initializer constructor
	ReachabilityTree( const NeuralNetwork<Number>& network, const HPolytope<Number>& inputSet, const HPolytope<Number>& safeSet );

	ReachabilityNode<Number>* root() const;

	std::vector<ReachabilityNode<Number>*> leaves() const;

	unsigned short int depth() const;

	std::vector<Starset<Number>> forwardPass( NN_REACH_METHOD method, SEARCH_STRATEGY strategy ) const;
	void computeReachTree( const Starset<Number>& inputSet, NN_REACH_METHOD method, SEARCH_STRATEGY strategy );
	bool verify( NN_REACH_METHOD method, SEARCH_STRATEGY strategy );

  private:
	Starset<Number> prepareInput() const;
	HPolytope<Number> prepareSafeSet() const;
	bool isSubResultSafe( const std::vector<Starset<Number>>& subResult, const HPolytope<Number>& safeSet ) const;
};

}  // namespace reachability
}  // namespace hypro

#include "ReachabilityTree.tpp"
