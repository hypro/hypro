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
#include <map>
#include <set>

namespace hypro {
namespace reachability {

template <typename Number>
class ReachabilityTree {
  private:
	ReachabilityNode<Number>* mRoot;				 // root node of the reachability analysis tree
	std::vector<ReachabilityNode<Number>*> mLeaves;	 // the leaves of the reachability tree
	unsigned short int mDepth;						 // depth of the reachability tree

	NeuralNetwork<Number> mNetwork;			   // the analyzed neural network
	HPolytope<Number> mInputSet;			   // the input set of the network
	std::vector<HPolytope<Number>> mSafeSets;  // the safe set specified in the form of a vector of HPolytopes
	std::vector<matrix_t<Number>> mSafeSetMatrices; 
    std::vector<vector_t<Number>> mSafeSetVectors;
	bool mIsSafe;							   // true if the reachability tree is safe
	bool mIsComplete;						   // true if the  computation of the reachability tree finished

	hypro::Plotter<Number>& mPlotter;

	TRACING_STRATEGY mTracingStrategy;
	COUNTEREXAMPLE_STRATEGY mCounterExampleStrategy;
	REFINEMENT_TYPE mRefinementType; 
	bool mRemoveSafeSubtrees;
	bool mTryReusingPredicates;
	PREDICATE_TRACING_ORIGIN mPredicateTracingOrigin;

	//stores the position of counterexample
	// mPreviousCounterexampleSources[i] contains a ascending list of all nodes in layer i that were previously a counterexample source
	std::vector<std::list<int>> mPreviousCounterexampleSources; 

	// mPreviousCounterexamples: For key (layer, neuron) the reachability node (layer, neuron+1) or (layer+1,0) 
	// contains the value (counterexample or source) corresponding to the key
	std::map<std::pair<int,int>, std::set<Point<Number>>> mPreviousCounterexamples;
	
	std::map<std::pair<int,int>, std::set<std::string>> mSafeHistories;

	int mNumberOfTracings;

	/**
	 * @brief Verifies the FNN corresponding to this reachability tree by using a structure tree
	 * 
	 * @return safety of the FNN
	 */
	bool _verifyWithStructureTree(size_t max_iter = 100);

  public:
	// Default constructor
	ReachabilityTree();

	// Destructor - recursively delete all nodes from the root to the leaves
	~ReachabilityTree();

	// Initializer constructor
	ReachabilityTree( const NeuralNetwork<Number>& network, const HPolytope<Number>& inputSet, const std::vector<HPolytope<Number>>& safeSets );

	//Initializer constructor with explicit strategies
	ReachabilityTree( const NeuralNetwork<Number>& network, const HPolytope<Number>& inputSet, const std::vector<HPolytope<Number>>& safeSets, const COUNTEREXAMPLE_STRATEGY counterExampleStrategy, const REFINEMENT_TYPE refinementType, const TRACING_STRATEGY backpropagationStrategy, const bool removeSafeSubtrees = false);

	ReachabilityNode<Number>* root() const;

	std::vector<ReachabilityNode<Number>*> leaves() const;

	unsigned short int depth(ReachabilityNode<Number>* node) const;

	bool getTryReusingPredicates() const;

	void setTryReusingPredicates(const bool reusePredicates);

	PREDICATE_TRACING_ORIGIN getPredicateTracingOrigin() const;

	void setPredicateTracingOrigin(const PREDICATE_TRACING_ORIGIN strategy);

	/**
	 * @brief Find the specified ancestor in the same layer
	 * 
	 * @param[in] node: reachability node that is the start for the search
	 * @param[in] neuronNumber: neuronNumber the ancestor node is identified with
	 * @return Ancestor of node with neuron number neuronNumber
	 */
	ReachabilityNode<Number>* getAncestor(ReachabilityNode<Number>* node, const int neuronNumber) const;

	std::vector<SearchJob<Number>> checkSafeHistory(std::vector<SearchJob<Number>> newJobs);

	/**
	 * @brief Computes a full subtree starting in rootNode according to strategy
	 * 
	 * @param[in] rootNode: root node of the resulting reachabiltiy subtree
	 * @param[in] safeSets: safety specification for the checking final leaves computed
	 * @param[in] strategy: the strategy used to choose the next node to compute 
	 * @return rootNode
	 */
	ReachabilityNode<Number>* computeReachTree( ReachabilityNode<Number>* rootNode, const std::vector<HPolytope<Number>>& safeSets, SEARCH_STRATEGY strategy );

	/**
	 * @brief Computes a partial subtree starting in rootNode with at least one additional final leaf
	 * 
	 * @param[in] rootNode: root node of the resulting reachabiltiy subtree
	 * @param[in] safeSets: safety specification for the checking final leaves computed
	 * @return rootNode
	 */
	std::pair<ReachabilityNode<Number>*,std::vector<ReachabilityNode<Number>*>> computePartiallyExactReachTree( ReachabilityNode<Number>* rootNode, const std::vector<HPolytope<Number>>& safeSets );
	
	/**
	 * @brief Verifies the FNN corresponding to this reachability tree
	 * 
	 * @param[in] method: method used for reachability analysis
	 * @param[in] strategy: method used to compute full reachability trees
	 * @param[in] createPlots: whether plots should be create for all reachability nodes in the computed reachability trees
	 * @return safety of the FNN
	 */
	bool verify( NN_REACH_METHOD method, SEARCH_STRATEGY strategy, bool createPlots = false, bool normalizeInput = false, bool normalizeOutput = false, size_t max_iter= 100 );

	/**
	 * @brief Finds an unsafe final leaf
	 * 
	 * @return the first unsafe final leaf contained in mLeaves
	 */
	ReachabilityNode<Number>* getFirstUnsafeLeaf() const;

	/**
	 * @brief Adds all leaves descending from node to mLeaves
	 * 
	 * @param[in] node: root of the subtree of which the leaves are added
	 */
	void updateLeaves( ReachabilityNode<Number>* node );
	
	/**
	 * @brief Adds all leaves descending from node to mLeaves and all non-final leaves to notComputedLeaves
	 * 
	 * @param[in] node: root of the subtree of which the leaves are added
	 * @param[in] notComputedLeaves: reference to a list if non-final leaves
	 */
	void updateLeaves( ReachabilityNode<Number>* node, std::vector<ReachabilityNode<Number>*>* notComputedLeaves);

	/**
	 * @brief Find the neuron containing an origin of a countereaxmple (if exists).
	 *
	 * @param[in] source: a source of a counter example
	 * @param[in] sourceAplha: the predicate value corresponding to source
	 * @param[in] node: the reachability node from which we start the search
	 * @param[in] strategy: Strategy used for finding the origin of source
	 * @return a reachability node corresponding to the origin and the origin if it is a counter input
	 */
	std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> identifyCounterExampleOrigin( const Point<Number>& source, const Point<Number>& sourceAlpha, ReachabilityNode<Number>* node, TRACING_STRATEGY strategy);

	/**
	 * @brief Find the origin neuron of a source inside a activation function layer using binar search or allow further tracing
	 *
	 * @param[in] source: a counter example source Point<Number>
	 * @param[in] sourceAplha: the predicate value corresponding to source
	 * @param[in] node: the reachability tree leaf from which we start the search
	 * @param[in] upperIndex: The highest index (lowest number) that is known not to be the source of the counterexample or the start of the layer
	 * @param[in] nextIndex: The index of the neuron to which backpropagation is tried next
	 * @return a reachability node corresponding to the origin and the origin if it is a counter input
	 */
	std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> binarySearchTracing(const Point<Number>& source, const Point<Number>& sourceAlpha, ReachabilityNode<Number>* node,  const int upperIndex, const int nextIndex );

	
	/**
	 * @brief Find the origin neuron of a source inside a activation function layer based on previous origins or allow further tracing
	 *
	 * @param[in] source: a counter example source Point<Number>
	 * @param[in] sourceAplha: the predicate value corresponding to source
	 * @param[in] node: the reachability tree leaf from which we start the search
	 * @return a reachability node corresponding to the origin and the origin if it is a counter input
	 */
	std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> rememberingSearchTracing(const Point<Number>& source, const Point<Number>& sourceAlpha, ReachabilityNode<Number>* node );
	
	/**
	 * @brief Find the origin neuron of a source inside a activation function layer using the UNSAT core of prior tracing attemtps or allow further tracing
	 *
	 * @param[in] source: a counter example source Point<Number>
	 * @param[in] sourceAplha: the predicate value corresponding to source
	 * @param[in] node: the reachability tree leaf from which we start the search
	 * @return a reachability node corresponding to the origin and the origin if it is a counter input
	 */
	std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> unsatCoreTracing(const Point<Number>& source, const Point<Number>& sourceAlpha, ReachabilityNode<Number>* node);
	
	/**
	 * @brief Find a potential origin neuron of a source inside an activation function layer reusing the predicate corresponding to the source
	 *
	 * @param[in] source: a counter example source Point<Number>
	 * @param[in] sourceAplha: the predicate value corresponding to source
	 * @param[in] node: the reachability tree leaf from which we start the search
	 * @return a reachability node corresponding to the origin and the origin if it is a counter input
	 */
	std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> reusedPredicateTracing( const Point<Number>& source, const Point<Number>& sourceAlpha, ReachabilityNode<Number>* node );

	/**
	 * @brief Find an origin neuron of a source inside an activation function layer reusing the predicate and checking with LP
	 *
	 * @param[in] source: a counter example source Point<Number>
	 * @param[in] sourceAplha: the predicate value corresponding to source
	 * @param[in] node: the reachability tree leaf from which we start the search
	 * @return a reachability node corresponding to the origin and the origin if it is a counter input
	 */
	std::tuple<Point<Number> , Point<Number>, ReachabilityNode<Number>*> reusedPredicateLPTracing( const Point<Number>& source, const Point<Number>& alpha, ReachabilityNode<Number>* node);

	/**
	 * @brief Calculates the corresponding point from the previous set such that applying the previous nodes computations on it we would get back the counterexample source
	 *
	 * @param[in] source the source for which we try to find the correspodning point from the previous node
	 * @param[in] sourceAplha: the predicate value corresponding to source
	 * @param[in] parentLayer layer of the previous node
	 * @param[in] parentNeuron neuron number of the previous node
	 * @param[in] parentSet the representation of the previous node
	 * @return a Point<Number> the corresponding source
	 */
	std::pair<Point<Number>,Point<Number>> traceSourceBack( const Point<Number>& source, const Point<Number>& sourceAlpha, int parentLayer, int parentNeuron, const Starset<Number>& parentSet, const Starset<Number>& currentSet );
	
	/**
	 * @brief Calculates a point in ancestorSet which results in source after passing it through to the neuron with lowerIndex. Only works inside an activation-function layer
	 *
	 * @param[in] source the source for which we try to find a origin
	 * @param[in] sourceAplha: the predicate value corresponding to source
	 * @param[in] layerNumber the number of the current layer
	 * @param[in] lowerIndex start of backpropagation
	 * @param[in] upperIndex end of backpropagation; corresponds to the node of ancestorSet
	 * @param[in] ancestorSet the representation of the ancestor node
	 * @return Point<Number> the corresponding point if possible, and the empty point otherwise
	 */
	std::pair<Point<Number>,Point<Number>> traceSourceBack( const Point<Number>& source, const Point<Number>& sourceAlpha, int layerNumber, int lowerIndex, int upperIndex, const Starset<Number>& ancestorSet );


	void plotTree( ReachabilityNode<Number>* current, std::string filename ) const;

	/** 
	 * @brief Normalizes the input polytope
	 * @param normalize do nothing if false
	 * @return The normalized input polytope
	 */ 
	Starset<Number> prepareInput( bool normalize ) const;

	/** 
	 * @brief Normalizes the saftey specifcation
	 * @param normalize do nothing if false
	 * @return The normalized safety specfication
	 */ 
	std::vector<HPolytope<Number>> prepareSafeSet( bool normalize ) const;

	/** 
	 * @brief Adds to mPreviousCounterexampleSources
	 * @param[in] layerNumber layer number of the source
	 * @param[in] neuronNumber neuron number of the source
	 */ 
	void rememberCounterexampleSource(int layerNumber, int neuronNumber);

  private:
	int sgn( Number val ) const;
	Number min_val( size_t dim ) const;
	Number max_val( size_t dim ) const;
	Number mean_val( size_t dim ) const;
	Number range_val( size_t dim ) const;

	/** 
	 * @brief Deletes a safe subtree 
	 * @param[in] safeLeaf leaf of the delete safe subtree
	 */ 
	void removeSafeSubtree(ReachabilityNode<Number>* safeLeaf);
	
	/** 
	 * @brief Performs refinment allways constructing full reachability trees
	 * @param[in] strategy specifices how the reachability tree is constructed
	 * @param[in] createPlots whether plots of the reachable sets are created
	 * @param[in] max_iter maximium amount of refinement iterations before termination
	 * @param[in] safeOutput safety specification used for verification
	 */ 
	bool fullRefinement(SEARCH_STRATEGY strategy,  bool createPlots, size_t max_iter, const std::vector<HPolytope<Number>> safeOutput);

	/** 
	 * @brief Performs refinment constucting partial reachability trees if possible
	 * @param[in] strategy specifices how the reachability tree is constructed
	 * @param[in] createPlots whether plots of the reachable sets are created
	 * @param[in] max_iter maximium amount of refinement iterations before termination
	 * @param[in] safeOutput safety specification used for verification
	 */ 
	bool avoidentRefinement(SEARCH_STRATEGY strategy,  bool createPlots, size_t max_iter, const std::vector<HPolytope<Number>> safeOutput);

	/** 
	 * @brief Checks if the input is in mPreviousCounterexampleSources
	 * @param[in] layerNumber layer number of the source
	 * @param[in] neuronNumber neuron number of the source
	 */
	bool isPreviousCounterexampleSource(int layerNumber, int neuronNumber );
};

}  // namespace reachability
}  // namespace hypro

#include "ReachabilityTree.tpp"
