#include "ReachabilityTree.h"

namespace hypro {
namespace reachability {

template <typename Number>
ReachabilityTree<Number>::ReachabilityTree()
	: mPlotter( hypro::Plotter<Number>::getInstance() ) {}

template <typename Number>
ReachabilityTree<Number>::~ReachabilityTree() {
	// TODO: deallocate all nodes recursively from the root to the leafs
}

template <typename Number>
ReachabilityTree<Number>::ReachabilityTree( const NeuralNetwork<Number>& network, const HPolytope<Number>& inputSet, const HPolytope<Number>& safeSet )
	: mNetwork( network )
	, mInputSet( inputSet )
	, mSafeSet( safeSet )
	, mPlotter( hypro::Plotter<Number>::getInstance() ) {
	unsigned short int depth = 1;
	for ( auto layer : mNetwork.layers() ) {
		if ( layer->layerType() == NN_LAYER_TYPE::AFFINE )
			depth = depth + 1;
		else
			depth = depth + layer->layerSize();
	}
	mDepth = depth;
}

template <typename Number>
ReachabilityNode<Number>* ReachabilityTree<Number>::root() const {
	return mRoot;
}

template <typename Number>
std::vector<ReachabilityNode<Number>*> ReachabilityTree<Number>::leaves() const {}

template <typename Number>
unsigned short int ReachabilityTree<Number>::depth() const {
	return 0;
}

template <typename Number>
Starset<Number> ReachabilityTree<Number>::prepareInput() const {
	// this function should transform the input polytope (e.g. an ACAS property) into an input set to the network
	// i.e. it should transform the input polytope using min-max normalization and mean-std scaling
	// min-max normalization <=> add all upper and lower bounding halfspaces to the polytope and then remove redundant constraints
	// mean-std scaling <=> subtract mean (translation vector) and scale by std (scaling matrix)  => affine transformation
	return Starset<Number>( mInputSet );
}

template <typename Number>
HPolytope<Number> ReachabilityTree<Number>::prepareSafeSet() const {
	// TODO: implement de-normalization
	return mSafeSet;
}

template <typename Number>
bool ReachabilityTree<Number>::isSubResultSafe( const std::vector<Starset<Number>>& subResult, const HPolytope<Number>& safeSet ) const {
	// TODO: implement this method
	return true;
}

template <typename Number>
std::vector<Starset<Number>> ReachabilityTree<Number>::forwardPass( const Starset<Number>& inputSet, NN_REACH_METHOD method, SEARCH_STRATEGY strategy ) const {
	// TODO: update this method accordingly to the new implementation
	std::vector<Starset<Number>> outputSets;

	// BFS -> we always push to the end and we pop the first
	// DFS -> we always push to the beginning and we pop the first

	// create the root_job and add to the queue
	SearchJob root_job( inputSet, mNetwork.layers( 0 ), mNetwork.layers(), 0 );
	std::deque<SearchJob<Number>> jobQueue;
	jobQueue.push_back( root_job );

	// perform BFS / DFS until the queue is empty
	while ( !jobQueue.empty() ) {
		SearchJob job = jobQueue.front();
		std::vector<SearchJob<Number>> newJobs = job.compute( method );
		jobQueue.pop_front();
		for ( auto newJob : newJobs ) {
			if ( newJob.isFinalResult() ) {
				for ( auto finalResult : newJob.finalResult() ) {
					outputSets.push_back( finalResult );
				}
			} else {
				switch ( strategy ) {
					case SEARCH_STRATEGY::BFS:
						jobQueue.push_back( newJob );
						break;
					case SEARCH_STRATEGY::DFS:
						jobQueue.push_front( newJob );
						break;
					default:
						FATAL( "hypro.neuralnets.reachability_tree.ReachabilityTree", "Unknown search strategy" << strategy );
				}
			}
		}
	}

	std::cout << "In total the final number of reachable sets is " << outputSets.size() << std::endl;

	return outputSets;
}

// This method computes the rechability tree using a specified input starset and an NN_REACH_METHOD starting from a given neuron
// It can be used just to compute a subtree from the j. neuron of the k.th layer
// the subtree then could be inserted into the search tree (replacing and deleting the old subtree)
template <typename Number>
ReachabilityNode<Number>* ReachabilityTree<Number>::computeReachTree( ReachabilityNode<Number>* rootNode, const HPolytope<Number>& safeSet, SEARCH_STRATEGY strategy ) {
	// create the root_job and add to the queue
	SearchJob<Number> root_job( rootNode, mNetwork.layers() );
	std::deque<SearchJob<Number>> jobQueue;
	jobQueue.push_back( root_job );

	// perform BFS / DFS until the queue is not empty and the network is still safe
	while ( !jobQueue.empty() ) {  // TODO: && mIsSafe  do not forget to break the search erlier if tree is not safe
		SearchJob<Number> job = jobQueue.front();
		// std::cout << job.getNode()->layerNumber() << " " << job.getNode()->neuronNumber() << std::endl;
		std::cout << job.getNode()->representation() << std::endl;
		std::vector<SearchJob<Number>> newJobs = job.compute( rootNode->method() );
		jobQueue.pop_front();
		for ( auto newJob : newJobs ) {
			if ( newJob.isFinalResult() ) {
				// check if the leaf satisfies the safety property
				// if not then early stop condition is met and the loop can be stopped
				// std::cout << newJob.getNode()->layerNumber() << " " << newJob.getNode()->neuronNumber() << std::endl;
				std::cout << newJob.getNode()->representation() << std::endl;
				ReachabilityNode<Number>* leafNode = newJob.getNode();
				mLeaves.push_back( leafNode );
				if ( !leafNode->checkSafe( safeSet ) ) {
					leafNode->setSafe( false );
					mIsSafe = false;
				} else {
					leafNode->setSafe( true );
				}
			} else {
				switch ( strategy ) {
					case SEARCH_STRATEGY::BFS:
						jobQueue.push_back( newJob );
						break;
					case SEARCH_STRATEGY::DFS:
						jobQueue.push_front( newJob );
						break;
					default:
						FATAL( "hypro.neuralnets.reachability_tree.ReachabilityTree", "Unknown search strategy" << strategy );
				}
			}
		}
	}

	mIsComplete = true;
	return rootNode;
}

// here in the verify method just call the forwardPass method to calculate the EXACT or OVERAPPROXIMATIVE result
// if it is CEGAR countinue with the refinement, otherwise just stop and verify the "leaves"
// if the method is not CEGAR than it makes no sense to save the intermediate stars into the search tree

template <typename Number>
bool ReachabilityTree<Number>::verify( NN_REACH_METHOD method, SEARCH_STRATEGY strategy ) {
	// TODO: introduce two boolean parameters for input and output normalization
	Starset<Number> starInput = prepareInput();
	HPolytope<Number> safeOutput = prepareSafeSet();
	// let's assume for now that the safeSet could only be a conjunction of halfspaces and it describes the set of all safe output vectors
	// TODO: later add some generalization to it
	// TODO: make the safe set an arbitrary number of conjunctions and/or disjunctions of halfspaces, i.e. it is a vector of HPolytopes (DNF)

	mLeaves.clear();
	mIsSafe = true;
	mIsComplete = false;

	// create the root node of the reachability tree
	ReachabilityNode<Number>* rootNode = new ReachabilityNode<Number>( starInput, method, 0, 0 );
	switch ( method ) {
		case NN_REACH_METHOD::EXACT:
		case NN_REACH_METHOD::OVERAPPRX:
			// if we apply the EXACT or OVERAPPROX method, regardless if the computation of the reachability tree is complete or not
			// we can surely return the answer
			mRoot = computeReachTree( rootNode, safeOutput, strategy );
			std::cout << "The neural network is " << ( mIsSafe ? "safe" : "unsafe" ) << std::endl;
			std::cout << "The number of final sets is " << mLeaves.size() << std::endl;
			return mIsSafe;
		case NN_REACH_METHOD::CEGAR:
			// for the CEGAR mehtod we start with a fully overapproximate reachability analysis
			// then we refine the result of the overapproximate reachability
			rootNode->setMethod( NN_REACH_METHOD::OVERAPPRX );
			mRoot = computeReachTree( rootNode, safeOutput, strategy );
			break;
		default:
			FATAL( "hypro.neuralnets.reachability_tree", "Invalid analysis method specified" );
	}

	if ( mIsSafe ) {
		// if the method is CEGAR and the reachable sets are all safe then the whole network is safe
		std::cout << "The neural network is safe" << std::endl;
		return true;
	}
	// else we start the refinement
	// TODO: implement the refinement algorithm

	int ctx = 0;
	plotTree( mRoot, std::to_string( ctx ) + "-CEGAR_Reach_" );

	// repeat until we either find a real counterexample or we can verify that the network is safe
	// TODO: introduce a max number of iterations
	while ( !mIsSafe ) {
		mLeaves.clear();  // TODO: do not clear the leaves that are not affected
		updateLeaves( mRoot );
		std::cout << "Number of leaves: " << mLeaves.size() << std::endl;

		ReachabilityNode<Number>* refinedNode = nullptr;

		bool counterExampleFound = false;
		while ( !counterExampleFound ) {
			// generate a potential counterexample candidate
			std::cout << "Generating a counterexample..." << std::endl;
			Point<Number> candidate = produceCounterExampleCandidate( getFirstNonEmptyLeaf(), safeOutput );
			std::cout << "The counterexample candidate is " << candidate << std::endl;

			// identify the source neuron of the counterexample
			std::pair<Point<Number>, ReachabilityNode<Number>*> candidateSource = identifyCounterExampleSource( candidate, mLeaves[0] );

			// do not forget to test if the backpropagated counterexample candidate is still a valid counterexample !!!
			if ( counterExampleIsValid( candidateSource.first, candidateSource.second ) ) {
				if ( candidateSource.second->representation().contains( candidateSource.first ) ) {
					std::cout << "True countereaxmple found, refinement process stops" << std::endl;
					std::cout << "The true counterexample is: " << candidateSource.first << std::endl;
					mIsSafe = false;
					return false;
				}

				refinedNode = candidateSource.second;
				counterExampleFound = true;
				std::cout << "The source of the counterexample candidate is: " << refinedNode->layerNumber() << " " << refinedNode->neuronNumber() << std::endl;
			}
		}

		// do the refinement step
		mIsSafe = true;
		mIsComplete = false;

		// if ( refinedNode->hasPosChild() ) {
		// 	delete refinedNode->getPosChild();
		// }
		// if ( refinedNode->hasNegChild() ) {
		// 	delete refinedNode->getNegChild();
		// }
		refinedNode->setHasPosChild( false );
		refinedNode->setPosChild( nullptr );
		refinedNode->setHasNegChild( false );
		refinedNode->setNegChild( nullptr );

		// calculate the childs of the refined node using exact computation
		std::cout << "Refining the selected node" << std::endl;
		SearchJob<Number> refinedJob( refinedNode, mNetwork.layers() );
		std::vector<SearchJob<Number>> newJobs = refinedJob.compute( NN_REACH_METHOD::EXACT );
		std::cout << "New jobs size: " << newJobs.size() << std::endl;

		// set the childs of the refined node
		newJobs[0].getNode()->setMethod( NN_REACH_METHOD::OVERAPPRX );
		newJobs[1].getNode()->setMethod( NN_REACH_METHOD::OVERAPPRX );

		// use the compute reach tree function to compute the subtrees of the childs
		std::cout << "Computing positive subtree" << std::endl;
		ReachabilityNode<Number>* posSubTree = computeReachTree( newJobs[0].getNode(), safeOutput, strategy );
		std::cout << "Computing negative subtree" << std::endl;
		ReachabilityNode<Number>* negSubTree = computeReachTree( newJobs[1].getNode(), safeOutput, strategy );

		// TODO: are these even necessary?  std::vector<SearchJob<Number>> newJobs = refinedJob.compute( NN_REACH_METHOD::EXACT ); ... should already handle
		refinedNode->setPosChild( posSubTree );
		refinedNode->setNegChild( negSubTree );

		ctx++;
		plotTree( mRoot, std::to_string( ctx ) + "-CEGAR_Reach_" );
	}

	mLeaves.clear();  // TODO: do not clear the leaves that are not affected
	updateLeaves( mRoot );
	std::cout << "Number of leaves: " << mLeaves.size() << std::endl;

	// TODO: do not forget to delete the reachability tree when it is not used anymore

	// candidate = Point<Number>( { 0.25, 1.0 } );
	// candidateSource = identifyCounterExampleSource( candidate, mLeaves[0] );
	// std::cout << "The source of the counterexample candidate is: " << candidateSource.first << " " << candidateSource.second << std::endl;

	// candidate = Point<Number>( { 0.35, 0.75 } );
	// candidateSource = identifyCounterExampleSource( candidate, mLeaves[0] );
	// std::cout << "The source of the counterexample candidate is: " << candidateSource.first << " " << candidateSource.second << std::endl;

	std::cout << "The neural network is " << ( mIsSafe ? "safe" : "unsafe" ) << std::endl;
	std::cout << "The number of final sets is " << mLeaves.size() << std::endl;

	return false;
}

template <typename Number>
bool ReachabilityTree<Number>::counterExampleIsValid( Point<Number> candidate, ReachabilityNode<Number>* node ) const {
	// TODO: consider here using exact arithmetic instead floating point (you can use for this purpose the representation converter class)
	
	return true;
}

template <typename Number>
Point<Number> ReachabilityTree<Number>::produceCounterExampleCandidate( Starset<Number> set, HPolytope<Number> rejectionSet ) const {
	// TODO: this should be with random sampling (with the preference of picking the counterexample close or far away from the safe set but in the first (?) output set)
	// TODO: the sampling becomes very slow when the rejectionSet covers a high portion of the sampling set in this case some other algorithm for sampling should be used

	int sampling_trials = 10;

	// try to find a counterexmaple with MC sampling
	std::set<Point<Number>> samples = uniform_constrained_sampling( set, rejectionSet, 1, sampling_trials );
	if ( samples.size() > 0 )
		return *( samples.begin() );

	// if the sampling does not work out for the whole set try to reduce it to multiple smaller sets
	for ( auto constraint : rejectionSet.constraints() ) {
		Starset<Number> intermediateSet = set.intersectHalfspace( Halfspace<Number>( -1 * constraint.normal(), -constraint.offset() ) );
		if ( !intermediateSet.empty() ) {
			std::set<Point<Number>> newSamples = uniform_constrained_sampling( intermediateSet, rejectionSet, 1, sampling_trials );
			if ( newSamples.size() > 0 ) {
				return *( newSamples.begin() );
			}
		}
	}

	// if sampling does not work at all, just try LP solving
	for ( auto constraint : rejectionSet.constraints() ) {
		// add the reversed constraint (with a little bloating)
		Starset<Number> intermediateSet = set.intersectHalfspace( Halfspace<Number>( -1 * constraint.normal(), -constraint.offset() ) );
		std::vector<Point<Number>> vertices = intermediateSet.vertices();
		if ( vertices.size() > 0 ) {
			vector_t<Number> middle_point = vertices[0].rawCoordinates();
			for ( int i = 1; i < vertices.size(); i++ ) {
				middle_point += vertices[i].rawCoordinates();
			}
			middle_point /= vertices.size();
			return Point<Number>( middle_point );
		}
	}

	// this line means that the sampling failed (should return a pair <bool, point> instead)
	return Point<Number>( { 0, 0 } );
}

template <typename Number>
Starset<Number> ReachabilityTree<Number>::getFirstNonEmptyLeaf() const {
	// TODO: if a leaf is empty then it should be safe (?)
	// TODO: what if there is no leaf which is not empty, then the whole tree should be safe (?) -> return pair <bool, Starset<Number>>
	for ( auto leaf : mLeaves ) {
		if ( !leaf->representation().empty() ) {
			return leaf->representation();
		}
	}
	return mLeaves[0]->representation();
}

template <typename Number>
void ReachabilityTree<Number>::updateLeaves( ReachabilityNode<Number>* node ) {
	// std::cout << "preorder: " << node->layerNumber() << " " << node->neuronNumber() << std::endl;
	if ( node->isLeaf() ) {
		mLeaves.push_back( node );
	} else {
		if ( node->hasPosChild() ) {
			updateLeaves( node->getPosChild() );
		}
		if ( node->hasNegChild() ) {
			updateLeaves( node->getNegChild() );
		}
	}
}

template <typename Number>
std::pair<Point<Number>, ReachabilityNode<Number>*> ReachabilityTree<Number>::identifyCounterExampleSource( const Point<Number>& candidate, ReachabilityNode<Number>* node ) const {
	if ( !node->hasParent() ) {
		return std::make_pair( candidate, node );  // indicates that the backpropagated counterexample originates from the very first neuron
	}

	// here: should I check if the candidate is contained in the current set or would the backpropagated candidate be in in the parent set?
	// if ( checkForwardContainment( candidate, parentLayer, parentNeuron, parentSet ) ) {	 // TODO: do not forget to check also the exact result of the relu function
	if ( node->representation().contains( candidate ) ) {
		// if the counterexample candidate is still included in the current node go back to the previous node
		ReachabilityNode<Number>* parent = node->getParent();
		Point<Number> newCandidate = propagateCandidateBack( candidate, parent->layerNumber(), parent->neuronNumber(), parent->representation() );
		// std::cout << "newCandidate: " << newCandidate << std::endl;
		return identifyCounterExampleSource( newCandidate, parent );
	} else {
		// if it is not included the current neuron introduces the counterexample
		return std::make_pair( candidate, node );  // the source of the counterexample
	}
}

template <typename Number>
Point<Number> ReachabilityTree<Number>::propagateCandidateBack( const Point<Number>& candidate, int parentLayer, int parentNeuron, const Starset<Number>& parentSet ) const {
	std::shared_ptr<LayerBase<Number>> layer = mNetwork.layers( parentLayer );
	return layer->propagateCandidateBack( candidate, parentNeuron, parentSet );
}

template <typename Number>
void ReachabilityTree<Number>::plotTree( ReachabilityNode<Number>* current, std::string filename ) const {
	mPlotter.clear();
	mPlotter.setFilename( filename + "_pdf.plt" );
	current->plot();

	if ( current->hasPosChild() ) {
		plotTree( current->getPosChild(), filename + "+" );
	}
	if ( current->hasNegChild() ) {
		plotTree( current->getNegChild(), filename + "-" );
	}
}

}  // namespace reachability
}  // namespace hypro