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
#include "ReachabilitySettings.h"

#include <deque>
#include <vector>
#include <list>

namespace hypro {
namespace reachability {

template <typename Number>
class ReachabilityTree {
  private:
	ReachabilityNode<Number>* mRoot;				 // root node of the reachability analysis tree
	std::vector<ReachabilityNode<Number>*> mLeaves;	 // the leaves of the reachability tree
	unsigned short int mDepth;						 // depth of the reachability tree (actually the depth of the NN)

	NeuralNetwork<Number> mNetwork;			   // the analized neural network
	HPolytope<Number> mInputSet;			   // the input set of the network
	std::vector<HPolytope<Number>> mSafeSets;  // the safe set specified in the form of a vector of HPolytopes
	std::vector<matrix_t<Number>> mSafeSetMatrices; 
    std::vector<vector_t<Number>> mSafeSetVectors;
	bool mIsSafe;							   // true if the reachability tree is safe
	bool mIsComplete;						   // true if the  computation of the reachability tree finished

	hypro::Plotter<Number>& mPlotter;

	BACKPROPAGATION_STRATEGY mBackpropagationStrategy;
	COUNTEREXAMPLE_STRATEGY mCounterExampleStrategy;
	REFINEMENT_TYPE mRefinmentType; 

	//stores the position of counterexample
	// mPreviousCounterexampleSources[i] contains a ascending list of all nodes in layer i that were previously a counterexample source
	std::vector<std::list<int>> mPreviousCounterexampleSources; 

  public:
	// Default constructor
	ReachabilityTree();

	// Destructor - recursively delete all nodes from the root to the leaves
	~ReachabilityTree();

	// Initializer constructor
	ReachabilityTree( const NeuralNetwork<Number>& network, const HPolytope<Number>& inputSet, const std::vector<HPolytope<Number>>& safeSets );

	//Initializer constructor with explicit counterexample strategy and refinement type
	ReachabilityTree( const NeuralNetwork<Number>& network, const HPolytope<Number>& inputSet, const std::vector<HPolytope<Number>>& safeSets, const COUNTEREXAMPLE_STRATEGY counterExampleStrategy, const REFINEMENT_TYPE refinementType, const BACKPROPAGATION_STRATEGY backpropagationStrategy);

	ReachabilityNode<Number>* root() const;

	std::vector<ReachabilityNode<Number>*> leaves() const;

	unsigned short int depth(ReachabilityNode<Number>* node) const;

	/**
	 * @return Ancestor of node with neuron number neuronNumber
	 */
	ReachabilityNode<Number>* getAncestor(ReachabilityNode<Number>* node, const int neuronNumber) const;

	ReachabilityNode<Number>* computeReachTree( ReachabilityNode<Number>* rootNode, const std::vector<HPolytope<Number>>& safeSets, SEARCH_STRATEGY strategy );
	std::pair<ReachabilityNode<Number>*,std::vector<ReachabilityNode<Number>*>> computePartiallyExactReachTree( ReachabilityNode<Number>* rootNode, const std::vector<HPolytope<Number>>& safeSets, SEARCH_STRATEGY strategy );
	bool verify( NN_REACH_METHOD method, SEARCH_STRATEGY strategy, bool createPlots = false, bool normalizeInput = false, bool normalizeOutput = false, size_t max_iter= 100 );

	ReachabilityNode<Number>* getFirstUnsafeLeaf() const;

	void updateLeaves( ReachabilityNode<Number>* node );
	void updateLeaves( ReachabilityNode<Number>* node, std::vector<ReachabilityNode<Number>*>* notComputedLeaves);

	/**
	 * @brief Find the source neuron of a countereaxmple candidate (if exists).
	 *
	 * @param[in] candidate: a counter example candidate Point<Number>
	 * @param[in] node: the reachability tree leaf from which we start the search
	 * @param[in] strategy: Strategy used for finding the origin of candidate
	 * @return std::pair<Point, ReachabilityNode*>: returns a pair <EmptyPoint, node> which indicates the source neuron of the countereaxmple, return <source, root> if it is a true countereaxmple
	 */
	std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> identifyCounterExampleSource( const Point<Number>& candidate, const Point<Number>& candidateAlpha, ReachabilityNode<Number>* node, BACKPROPAGATION_STRATEGY strategy) const;

	/**
	 * @brief Find the source neuron of a countereaxmple candidate inside a activation function layer or allow further backpropagation
	 *
	 * @param[in] candidate: a counter example candidate Point<Number>
	 * @param[in] node: the reachability tree leaf from which we start the search
	 * @param[in] upperIndex: The highest index (lowest number) that is known not to be the source of the counterexample or the start of the layer
	 * @param[in] nextIndex: The index of the neuron to which backpropagation is tried next
	 * @return std::pair<Point, ReachabilityNode*>: returns a pair <candidate, node> which indicates the source neuron of the countereaxmple, return <candidate, nullptr> if it is a true countereaxmple
	 */
	std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*>  binarySearchBackpropagation(const Point<Number>& candidate, const Point<Number>& candidateAlpha, ReachabilityNode<Number>* node,  const int upperIndex, const int nextIndex ) const;
	std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*>  rememberingSearchBackpropagation(const Point<Number>& candidate, const Point<Number>& candidateAlpha, ReachabilityNode<Number>* node ) const;

	/**
	 * @brief Calculates the corresponding point from the previous set such that applying the previous nodes computations on it we would get back the counterexample candidate
	 *
	 * @param[in] candidate, the candidate for which we try to find the correspodning point from the previous node
	 * @param[in] parentLayer, layer of the previous node
	 * @param[in] parentNeuron, neuron number of the previous node
	 * @param[in] parentSet, the representation of the previous node
	 * @return Point<Number> the corresponding point
	 */
	std::pair<Point<Number>,Point<Number>> propagateCandidateBack( const Point<Number>& candidate, const Point<Number>& candidateAlpha, int parentLayer, int parentNeuron, const Starset<Number>& parentSet, const Starset<Number>& currentSet ) const;
	
	/**
	 * @brief Calculates a point in ancestorSet which results in candidate after passing it through to the neuron with lowerIndex. Only works inside an activation-function layer
	 *
	 * @param[in] candidate the candidate for which we try to find a origin
	 * @param[in] layerNumber the number of the current layer
	 * @param[in] lowerIndex start of backpropagation
	 * @param[in] upperIndex end of backpropagation; corresponds to the node of ancestorSet
	 * @param[in] ancestorSet the representation of the ancestor node
	 * @return Point<Number> the corresponding point if possible, and the empty point otherwise
	 */
	std::pair<Point<Number>,Point<Number>> propagateCandidateBack( const Point<Number>& candidate, const Point<Number>& candidateAlpha, int layerNumber, int lowerIndex, int upperIndex, const Starset<Number>& ancestorSet ) const;

	void plotTree( ReachabilityNode<Number>* current, std::string filename ) const;

	Starset<Number> prepareInput( bool normalize ) const;
	std::vector<HPolytope<Number>> prepareSafeSet( bool normalize ) const;


	void rememberCounterexampleSource(int layerNumber, int neuronNumber);
  private:
	int sgn( Number val ) const;
	Number min_val( size_t dim ) const;
	Number max_val( size_t dim ) const;
	Number mean_val( size_t dim ) const;
	Number range_val( size_t dim ) const;

	bool _refinementAlwaysFullComputation(SEARCH_STRATEGY strategy,  bool createPlots, size_t max_iter, const std::vector<HPolytope<Number>> safeOutput);
	bool _refinementAvoidComputation(SEARCH_STRATEGY strategy,  bool createPlots, size_t max_iter, const std::vector<HPolytope<Number>> safeOutput);

	
	bool isPreviousCounterexampleSource(int layerNumber, int neuronNumber );
};

}  // namespace reachability
}  // namespace hypro

#include "ReachabilityTree.tpp"
