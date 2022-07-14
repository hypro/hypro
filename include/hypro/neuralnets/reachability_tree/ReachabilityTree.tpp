#include "ReachabilityTree.h"

namespace hypro {
namespace reachability {

template <typename Number>
ReachabilityTree<Number>::ReachabilityTree() {}

template <typename Number>
ReachabilityTree<Number>::~ReachabilityTree() {
	// TODO: deallocate all nodes recursively from the root to the leafs
}

template <typename Number>
ReachabilityTree<Number>::ReachabilityTree( const NeuralNetwork<Number>& network, const HPolytope<Number>& inputSet, const HPolytope<Number>& safeSet )
	: mNetwork( network )
	, mInputSet( inputSet )
	, mSafeSet( safeSet ) {}

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
	return true;
}

template <typename Number>
std::vector<Starset<Number>> ReachabilityTree<Number>::forwardPass( const Starset<Number>& inputSet, NN_REACH_METHOD method, SEARCH_STRATEGY strategy ) const {
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
void ReachabilityTree<Number>::computeReachTree( const Starset<Number>& inputSet, NN_REACH_METHOD method, SEARCH_STRATEGY strategy, int layerNumber, int neuronNumber ) {
	// create the root_job and add to the queue
	SearchJob root_job( inputSet, mNetwork.layers( layerNumber ), mNetwork.layers(), neuronNumber );
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

	switch ( method ) {
		case NN_REACH_METHOD::EXACT:
		case NN_REACH_METHOD::OVERAPPROX:
			// if we apply the EXACT or OVERAPPROX method, regardless if the computation of the reachability tree is complete or not
			// we can surely return the answer
			computeReachTree( starInput, method, strategy );
			return mIsSafe;
		case NN_REACH_METHOD::CEGAR:
			// for both the CEGAR mehtod we start with a fully overapproximate reachability analysis
			// then we refine the result of the overapproximate reachability
			computeReachTree( starInput, NN_REACH_METHOD::OVERAPPROX, strategy );
		default:
			FATAL( "hypro.neuralnets.reachability_tree", "Invalid analysis method specified" );
			break;
	}

	if ( mIsSafe )
		// if the method is CEGAR and the reachable sets are all safe then the whole network is safe
		return true;

	// else we start the refinement
	// TODO: implement the refinement algorithm

	return false;
	exit(0);

	// create the root_job and add to the queue
	SearchJob root_job( starInput, mNetwork.layers( 0 ), mNetwork.layers(), 0 );
	std::deque<SearchJob<Number>> jobQueue;
	jobQueue.push_back( root_job );

	bool networkSafe = true;

	int num_final_sets = 0;

	// perform BFS / DFS until the queue is empty
	while ( !jobQueue.empty() && networkSafe ) {
		SearchJob job = jobQueue.front();
		std::vector<SearchJob<Number>> newJobs = job.compute( method );
		jobQueue.pop_front();
		for ( auto newJob : newJobs ) {
			if ( newJob.isFinalResult() ) {
				bool isSafe = isSubResultSafe( newJob.finalResult(), safeOutput );
				if ( !isSafe ) {
					// if any of the subresults is not safe then this should be interrupted the network is not safe considering the type of reach method
					// also interrupt all the threads that are computing (in multithreading setting)
					networkSafe = false;
				}
				num_final_sets += newJob.finalResult().size();
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

	if ( method == NN_REACH_METHOD::CEGAR && !mIsSafe ) {
		// perform CEGAR refinement until it becomes safe or we can show that it is unsafe
	}

	std::cout << "In total the final number of reachable sets is " << num_final_sets << std::endl;

	return false;
}

}  // namespace reachability
}  // namespace hypro