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
#include "../../representations/sampling/sampling.h"
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

	NeuralNetwork<Number> mNetwork;	 // the analized neural network
	HPolytope<Number> mInputSet;	 // the input set of the network
	std::vector<HPolytope<Number>> mSafeSets;		 // the safe set specified in the form of a vector of HPolytopes
	bool mIsSafe;					 // true if the reachability tree is safe
	bool mIsComplete;				 // true if the  computation of the reachability tree finished

	hypro::Plotter<Number>& mPlotter;

  public:
	// Default constructor
	ReachabilityTree();

	// Destructor - recursively delete all nodes from the root to the leaves
	~ReachabilityTree();

	// Initializer constructor
	ReachabilityTree( const NeuralNetwork<Number>& network, const HPolytope<Number>& inputSet, const std::vector<HPolytope<Number>>& safeSets );

	ReachabilityNode<Number>* root() const;

	std::vector<ReachabilityNode<Number>*> leaves() const;

	unsigned short int depth() const;

	std::vector<Starset<Number>> forwardPass( const Starset<Number>& inputSet, NN_REACH_METHOD method, SEARCH_STRATEGY strategy ) const;
	ReachabilityNode<Number>* computeReachTree( ReachabilityNode<Number>* rootNode, const std::vector<HPolytope<Number>>& safeSets, SEARCH_STRATEGY strategy );
	bool verify( NN_REACH_METHOD method, SEARCH_STRATEGY strategy, bool createPlots = false, bool normalizeInput = false, bool normalizeOutput = false );

	bool counterExampleIsValid( Point<Number> candidate, ReachabilityNode<Number>* node ) const;

	/**
	 * @brief A method that produces a counterexample candidate for the current ReachabilityTree using sampling.
	 *
	 * @return Return a Point<Number>, the counterexample candidate
	 */
	Point<Number> produceCounterExampleCandidate( Starset<Number> set, std::vector<HPolytope<Number>> rejectionSet ) const;

	ReachabilityNode<Number>* getFirstNonEmptyLeaf() const;

	void updateLeaves( ReachabilityNode<Number>* node );

	/**
	 * @brief Find the source neuron of a countereaxmple candidate (if exists).
	 *
	 * @param[in] candidate: a counter example candidate Point<Number>
	 * @param[in] leaf: the reachability tree leaf from which we start the search
	 * @return std::pair<Point, ReachabilityNode*>: returns a pair <candidate, node> which indicates the source neuron of the countereaxmple, return <candidate, nullptr> if it is a true countereaxmple
	 */
	std::pair<Point<Number>, ReachabilityNode<Number>*> identifyCounterExampleSource( const Point<Number>& candidate, ReachabilityNode<Number>* leaf ) const;

	/**
	 * @brief Calculates the corresponding point from the previous set such that applying the previous nodes computations on it we would get back the counterexample candidate
	 *
	 * @param[in] candidate, the candidate for which we try to find the correspodning point from the previous node
	 * @param[in] parentLayer, layer of the previous node
	 * @param[in] parentNeuron, neuron number of the previous node
	 * @param[in] parentSet, the representation of the previous node
	 * @return Point<Number> the corresponding point
	 */
	Point<Number> propagateCandidateBack( const Point<Number>& candidate, int parentLayer, int parentNeuron, const Starset<Number>& parentSet ) const;

	void plotTree( ReachabilityNode<Number>* current, std::string filename ) const;

  private:
	int sgn(Number val) const;
	Number min_val(size_t dim) const;
	Number max_val(size_t dim) const;
	Number mean_val(size_t dim) const;
	Number range_val(size_t dim) const;

	Starset<Number> prepareInput( bool normalize ) const;
	std::vector<HPolytope<Number>> prepareSafeSet( bool normalize ) const;
	bool isSubResultSafe( const std::vector<Starset<Number>>& subResult, const std::vector<HPolytope<Number>>& safeSet ) const;
};

}  // namespace reachability
}  // namespace hypro

#include "ReachabilityTree.tpp"
