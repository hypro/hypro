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
ReachabilityTree<Number>::ReachabilityTree( const NeuralNetwork<Number>& network, const HPolytope<Number>& inputSet, const std::vector<HPolytope<Number>>& safeSets )
	: mNetwork( network )
	, mInputSet( inputSet )
	, mSafeSets( safeSets )
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
std::vector<ReachabilityNode<Number>*> ReachabilityTree<Number>::leaves() const {
	return mLeaves;
}


/*
* Returns the depth of the ReachabilityTree starting at node
* depth := longest path to a leaf node
*/
template <typename Number>
unsigned short int ReachabilityTree<Number>::depth(ReachabilityNode<Number>* node) const {
	unsigned short int maxDepth = 0;
	for (int i = 0; i < node->getNumberOfChildren(); i++){
		unsigned short int depthChild = depth(node->getChild(i));
		maxDepth = maxDepth < depthChild ? depthChild : maxDepth; 	
	}
		
	return 1 + maxDepth;
}

template <typename Number>
int ReachabilityTree<Number>::sgn( Number val ) const {
	return ( Number( 0 ) <= val ) - ( val < Number( 0 ) );
}

template <typename Number>
Number ReachabilityTree<Number>::min_val( size_t dim ) const {
	return mNetwork.mins()[dim];
}

template <typename Number>
Number ReachabilityTree<Number>::max_val( size_t dim ) const {
	return mNetwork.maxes()[dim];
}

template <typename Number>
Number ReachabilityTree<Number>::mean_val( size_t dim ) const {
	if ( dim == -1 )
		return mNetwork.means()[mNetwork.means().size() - 1];
	return mNetwork.means()[dim];
}

template <typename Number>
Number ReachabilityTree<Number>::range_val( size_t dim ) const {
	if ( dim == -1 )
		return mNetwork.ranges()[mNetwork.ranges().size() - 1];
	return mNetwork.ranges()[dim];
}

template <typename Number>
Starset<Number> ReachabilityTree<Number>::prepareInput( bool normalize ) const {
	// this function should transform the input polytope (e.g. an ACAS property) into an input set to the network
	// i.e. it should transform the input polytope using min-max normalization and mean-std scaling
	// min-max normalization <=> add all upper and lower bounding halfspaces to the polytope and then remove redundant constraints
	// mean-std scaling <=> subtract mean (translation vector) and scale by std (scaling matrix)  => affine transformation
	if ( normalize ) {
		size_t dimension = mInputSet.dimension();
		matrix_t<Number> shape = mInputSet.matrix();
		vector_t<Number> offsets = mInputSet.vector();
		// std::cout << dimension << std::endl << shape << offsets << std::endl;

		vector_t<int> lowerBounds = vector_t<int>::Zero( dimension );
		vector_t<int> upperBounds = vector_t<int>::Zero( dimension );

		std::vector<Halfspace<Number>> halfplanes;

		// normalize the given constraints using the parameters of the network
		for ( size_t i = 0; i < mInputSet.size(); ++i ) {
			for ( size_t j = 0; j < dimension; ++j ) {
				if ( shape( i, j ) == +1 or shape( i, j ) == -1 ) {
					// the current constraint is a lower or an upper bound
					if ( shape( i, j ) == -1 )
						lowerBounds[j] = 1;
					if ( shape( i, j ) == +1 )
						upperBounds[j] = 1;

					vector_t<Number> normal = shape.row( i );
					Number offset = offsets[i];
					offset = sgn( normal( j ) ) * ( std::min( std::max( sgn( normal( j ) ) * offset, min_val( j ) ), max_val( j ) ) - mean_val( j ) ) / range_val( j );
					halfplanes.push_back( Halfspace<Number>( normal, offset ) );
					break;
				}
			}
		}

		// add the lower and upper bounds for missing dimensions
		for ( size_t j = 0; j < dimension; ++j ) {
			if ( lowerBounds[j] == 0 ) {
				vector_t<Number> normal = vector_t<Number>::Zero( dimension );
				normal[j] = -1;
				Number offset = -1 * ( ( min_val( j ) - mean_val( j ) ) / range_val( j ) );
				halfplanes.push_back( Halfspace<Number>( normal, offset ) );
			}
			if ( upperBounds[j] == 0 ) {
				vector_t<Number> normal = vector_t<Number>::Zero( dimension );
				normal[j] = +1;
				Number offset = +1 * ( ( max_val( j ) - mean_val( j ) ) / range_val( j ) );
				halfplanes.push_back( Halfspace<Number>( normal, offset ) );
			}
		}

		return Starset<Number>( HPolytope<Number>( halfplanes ) );

		// TODO: implement the replacement of an equality constraint in the form of two inequalities (e.g., x >= 5 AND x <= 5 replaced by x = 5)
		// vector_t<Number> center = vector_t<Number>::Zero( dimension );
		// matrix_t<Number> generator = matrix_t<Number>::Identity( dimension, dimension );
		// // eliminate pair of inequalities which would reseult as an equality
		// for(int i = 0; i < halfplanes.size() - 1; i++) {
		// 	for(int j = i + 1; j < halfplanes.size(); j++) {
		// 		vector_t<Number> normal1 = halfplanes[i].normal();
		// 		vector_t<Number> normal2 = halfplanes[j].normal();
		// 		Number offset1 = halfplanes[i].offset();
		// 		Number offset2 = halfplanes[j].offset();

		// 		if(offset1 + offset2 == 0 && (normal1 + normal2).isZero()) {
		// 			halfplanes[j] = halfplanes.back();
		// 			halfplanes.pop_back();
		// 			halfplanes[i] = halfplanes.back();
		// 			halfplanes.pop_back();

		// 			// how should the basis and center change in order to simulate the mergeing of two inequalities into one equality in the star-set?
		// 		}
		// 	}
		// }

		// return Starset<Number>( center, generator, HPolytope<Number>( new_halfplanes ) );
	}

	//causes optimizer errors using the starset constructor with mInputSet as only input
	return Starset<Number>( mInputSet.matrix(), mInputSet.vector() );
}

template <typename Number>
std::vector<HPolytope<Number>> ReachabilityTree<Number>::prepareSafeSet( bool normalize ) const {
	if ( normalize ) {
		// output denormalization  y = (x - mean) / range
		std::vector<HPolytope<Number>> safeSets = std::vector<HPolytope<Number>>();
		for ( auto safeSet : mSafeSets ) {
			std::vector<Halfspace<Number>> halfplanes = std::vector<Halfspace<Number>>();
			for ( auto halfspace : safeSet.constraints() ) {
				vector_t<Number> normal = halfspace.normal();
				Number offset = halfspace.offset();

				int count_p1 = 0;
				int count_n1 = 0;
				for ( int i = 0; i < normal.size(); i++ ) {
					if ( normal[i] == +1 )
						count_p1++;
					if ( normal[i] == -1 )
						count_n1++;
				}
				if ( count_p1 != 1 || count_n1 != 1 ) {
					// if the number of +1s and -1s is not 1, then do the normalization
					// otherwise the constraint should not be normalized
					offset = ( offset - mean_val( -1 ) ) / range_val( -1 );
				}
				halfplanes.push_back( Halfspace<Number>( normal, offset ) );
			}
			safeSets.push_back( HPolytope<Number>( halfplanes ) );
		}
		return safeSets;
	}
	return mSafeSets;
}

template <typename Number>
bool ReachabilityTree<Number>::isSubResultSafe( const std::vector<Starset<Number>>& subResult, const std::vector<HPolytope<Number>>& safeSets ) const {
	// TODO: implement this method
	return true;
}

// This method computes the rechability tree using a specified input starset and an NN_REACH_METHOD starting from a given neuron
// It can be used just to compute a subtree from the j. neuron of the k.th layer
// the subtree then could be inserted into the search tree (replacing and deleting the old subtree)
template <typename Number>
ReachabilityNode<Number>* ReachabilityTree<Number>::computeReachTree( ReachabilityNode<Number>* rootNode, const std::vector<HPolytope<Number>>& safeSets, SEARCH_STRATEGY strategy ) {
	// create the root_job and add to the queue
	SearchJob<Number> root_job( rootNode, mNetwork.layers() );
	std::deque<SearchJob<Number>> jobQueue;
	jobQueue.push_back( root_job );

	// perform BFS / DFS until the queue is not empty and the network is still safe
	while ( !jobQueue.empty() ) {  // TODO: && mIsSafe  do not forget to break the search erlier if tree is not safe
		SearchJob<Number> job = jobQueue.front();
		// std::cout << job.getNode()->layerNumber() << " " << job.getNode()->neuronNumber() << std::endl;
		// std::cout << job.getNode()->representation() << std::endl;
		std::vector<SearchJob<Number>> newJobs = job.compute( rootNode->method() );
		jobQueue.pop_front();
		for ( auto newJob : newJobs ) {
			if ( newJob.isFinalResult() ) {
				// check if the leaf satisfies the safety property
				// if not then early stop condition is met and the loop can be stopped
				// std::cout << newJob.getNode()->layerNumber() << " " << newJob.getNode()->neuronNumber() << std::endl;
				// std::cout << newJob.getNode()->representation() << std::endl;
				ReachabilityNode<Number>* leafNode = newJob.getNode();
				mLeaves.push_back( leafNode );   // maybe this is not needed

				if ( !leafNode->checkSafe( safeSets ) ) {
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
bool ReachabilityTree<Number>::verify( NN_REACH_METHOD method, SEARCH_STRATEGY strategy, bool createPlots, bool normalizeInput, bool normalizeOutput, size_t max_iter) {
	Starset<Number> starInput = prepareInput( normalizeInput );
	std::vector<HPolytope<Number>> safeOutput = prepareSafeSet( normalizeOutput );
	// let's assume for now that the safeSet could only be a conjunction of halfspaces and it describes the set of all safe output vectors
	// TODO: later add some generalization to it
	// TODO: make the safe set an arbitrary number of conjunctions and/or disjunctions of halfspaces, i.e. it is a vector of HPolytopes (DNF)

	std::cout << "Normalized input set:\n" << starInput << std::endl;
	std::cout << "Denormalized output set:\n" << safeOutput << std::endl;

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
			if ( createPlots )
				plotTree( mRoot, method._to_string() );
			std::cout << "The neural network is " << ( mIsSafe ? "safe" : "unsafe" ) << std::endl;
			std::cout << "The number of final sets is " << mLeaves.size() << std::endl;
			return mIsSafe;
		case NN_REACH_METHOD::CEGAR:
			// for the CEGAR mehtod we start with a fully overapproximate reachability analysis
			// then we refine the result of the overapproximate reachability
			rootNode->setMethod( NN_REACH_METHOD::OVERAPPRX );
			mRoot = computeReachTree( rootNode, safeOutput, strategy );
			std::cout << "CEGAR first forward pass finished, the result is " << ( mIsSafe ? "safe" : "unsafe" ) << std::endl;
			break;
		default:
			FATAL( "hypro.neuralnets.reachability_tree", "Invalid analysis method specified" );
	}

	if ( mIsSafe ) {
		// if the method is CEGAR and the reachable sets are all safe then the whole network is safe
		std::cout << "The neural network is safe" << std::endl;
		return true;
	}

	// std::cout << "Neural network structure: " << mNetwork << std::endl;
	std::cout << "Search tree depth: " << depth(mRoot) << std::endl;

	// else we start the refinement
	int ctx = 0;
	if ( createPlots )
		plotTree( mRoot, std::to_string( ctx ) + "-CEGAR_Reach_" );

	// repeat until we either find a real counterexample or we can verify that the network is safe
	while ( !mIsSafe && ctx < max_iter ) {
		mLeaves.clear();  // TODO: do not clear the leaves that are not affected
		updateLeaves( mRoot );
		std::cout << "Number of leaves: " << mLeaves.size() << std::endl;

		ReachabilityNode<Number>* refinedNode = nullptr;

		bool counterExampleFound = false;
		while ( !counterExampleFound ) {
			ReachabilityNode<Number>* chosenLeaf = getFirstNonEmptyLeaf();
			
			// generate a potential counterexample candidate
			std::cout << "Generating a counterexample..." << std::endl;
			Point<Number> candidate = produceCounterExampleCandidate( chosenLeaf->representation(), safeOutput );
			std::cout << "The counterexample candidate is " << candidate << std::endl;

			//Otherwise chosenLeaf is safe
			assert(candidate.dimension() > 0);

			// identify the source neuron of the counterexample
			std::cout << "Identifying the source of the counterexample..." << std::endl;
			std::pair<Point<Number>, ReachabilityNode<Number>*> candidateSource = identifyCounterExampleSource( candidate, chosenLeaf );

			// TODO: check if the source is the last neuron we get a segmentation fault

			// do not forget to test if the backpropagated counterexample candidate is still a valid counterexample !!!
			if ( counterExampleIsValid( candidateSource.first, candidateSource.second ) ) {
				if ( candidateSource.first.dimension() > 0 && !candidateSource.second->hasParent()  ) {
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

		// calculate the childrens of the refined node using exact computation
		refinedNode->removeAllChildren();
		std::cout << "Refining the selected node" << std::endl;
		SearchJob<Number> refinedJob( refinedNode, mNetwork.layers() );
		std::cout << "refinedJob created" << std::endl;
		std::vector<SearchJob<Number>> newJobs = refinedJob.compute( NN_REACH_METHOD::EXACT );
		std::cout << "New jobs size: " << newJobs.size() << std::endl;

		
		for (int i = 0; i < newJobs.size(); i++){
			std::cout << "Computing "<< i << ". subtree" << std::endl;
			// set the children of the refined node
			newJobs[i].getNode()->setMethod( NN_REACH_METHOD::OVERAPPRX );
			// use the compute reach tree function to compute the subtrees of the children
			computeReachTree( newJobs[i].getNode(), safeOutput, strategy );
		}

		ctx++;
		if ( createPlots )
			plotTree( mRoot, std::to_string( ctx ) + "-CEGAR_Reach_" );
	}

	mLeaves.clear();  // TODO: do not clear the leaves that are not affected
	updateLeaves( mRoot );
	std::cout << "Number of leaves: " << mLeaves.size() << std::endl;

	// TODO: do not forget to delete the reachability tree when it is not used anymore

	std::cout << "The neural network is " << ( mIsSafe ? "safe" : "unsafe" ) << std::endl;
	std::cout << "The number of final sets is " << mLeaves.size() << std::endl;

	return mIsSafe;
}

//Currently allways returns true
template <typename Number>
bool ReachabilityTree<Number>::counterExampleIsValid( Point<Number> candidate, ReachabilityNode<Number>* node ) const {
	// TODO: consider here using exact arithmetic instead floating point (you can use for this purpose the representation converter class)

	return true;
}


/*
* Returns a counterexample in set and not in any element of rejectionSets
* If no counterexample exists, the empty point is returned
*/
template <typename Number>
Point<Number> ReachabilityTree<Number>::produceCounterExampleCandidate( Starset<Number> set, std::vector<HPolytope<Number>> rejectionSets ) const {
	
	// prepare rejectionSets for z3
	std::vector<matrix_t<Number>> rejectionMatrices = {};
    std::vector<vector_t<Number>> rejectionVectors = {};
    for (unsigned i = 0; i < rejectionSets.size(); i++){
    	rejectionMatrices.push_back(rejectionSets[i].matrix());
        rejectionVectors.push_back(rejectionSets[i].vector());
    }

	// if a counterexample exists, result contains an element in the predicate of set
	// this predicate corresponds to a point in set that is not element of any HPolytope in rejectionSets
	EvaluationResult<Number> result = z3GetCounterexample( set.shape(), set.limits(), set.generator(), set.center(), rejectionMatrices, rejectionVectors);

	switch ( result.errorCode ) {
		// A counterexample exists
		case SOLUTION::FEAS:
			{			
				Point<Number> counterexample( set.generator() * result.optimumValue + set.center());
				//TODO: Find a solution to generate a counterexaple as far from the bounds as possible
				//This is a hack to remove the rounding errors that sometimes appears in computation
				counterexample = counterexample*Number(0.99);				
				assert(set.contains(counterexample));
				return counterexample;
			}
			break;	
		case SOLUTION::INFEAS:
			//The set is safe
			std::cout << "produceCounterExampleCandidate was called on a safe set" << std::endl;
			return Point<Number>(); 
		default:
			assert(false && "Counterexample candidate neither found nor confirmed non-existence");
			break;
	}
	// This is not reachable
	return Point<Number>();
}

// Returns the first unsafe leaf (unsafe leaves are non-empty)
template <typename Number>
ReachabilityNode<Number>* ReachabilityTree<Number>::getFirstNonEmptyLeaf() const {
	for ( auto leaf : mLeaves ) {
		if ( !leaf->representation().empty() && !leaf->isSafe() ) {
			return leaf;
		}
	}
	//This should only be called, if the reachtree is not safe
	assert(false && "all leaves are empty or safe");
	return mLeaves[0];
}

/*
* Adds all leaves with ancestor node to the mLeaves vector
* This does NOT clear the mLeaves vector before adding new leaves!
*/
template <typename Number>
void ReachabilityTree<Number>::updateLeaves( ReachabilityNode<Number>* node ) {
	if ( node->isLeaf() ) {
		mLeaves.push_back( node );
	} else {
		for (int i = 0; i < node->getNumberOfChildren(); i++){
			updateLeaves( node->getChild(i) );		
		}
	}
}

/*
* If node is the root, then return pair of inputs
* Else if candidate is non-empty, then propagate the candidate back and return a call of this method on the parent of node and the backpropagated candidate
* Else if candidate is empty, return pair of inputs
* 
* Returns:
*	a) a node (including the root) and the empty point (indicates that the node is the sources of the original counterexample)
*	b) the root and a non-empty point (indicates a true counterexample)
*/

template <typename Number>
std::pair<Point<Number>, ReachabilityNode<Number>*> ReachabilityTree<Number>::identifyCounterExampleSource( const Point<Number>& candidate, ReachabilityNode<Number>* node ) const {
	if ( !node->hasParent() ) {
		std::cout << "Node does not have parent" << std::endl;
		std::cout << "Candiate in root:" << candidate << std::endl;
		return std::make_pair( candidate, node );  // indicates that the backpropagated counterexample originates from the very first neuron
	}

	std::cout << "Checking containment" << std::endl;
	std::cout << "Representation is: " << node->representation() << std::endl;
	std::cout << "Candidate is: " << candidate << std::endl;
	if (  candidate.dimension() > 0) {
		// if the counterexample candidate is still included in the current node go back to the previous node
		ReachabilityNode<Number>* parent = node->getParent();
		Point<Number> newCandidate = propagateCandidateBack( candidate, parent->layerNumber(), parent->neuronNumber(), parent->representation(), node->representation());
		std::cout << "newCandidate: " << newCandidate << std::endl;
		return identifyCounterExampleSource( newCandidate, parent );
	} else {
		// if it is not included the current neuron introduces the counterexample
		return std::make_pair( candidate, node );
	}
}

template <typename Number>
Point<Number> ReachabilityTree<Number>::propagateCandidateBack( const Point<Number>& candidate, int parentLayer, int parentNeuron, const Starset<Number>& parentSet, const Starset<Number>& currentSet ) const {
	std::cout << "Propagating candidate back..." << std::endl;
	std::shared_ptr<LayerBase<Number>> layer = mNetwork.layers( parentLayer );
	
	if (layer->layerType() ==  NN_LAYER_TYPE::AFFINE){
		return layer->propagateCandidateBack( candidate, parentNeuron, parentSet, currentSet);	
	}

	return layer->propagateCandidateBack( candidate, parentNeuron, parentSet );
}

template <typename Number>
void ReachabilityTree<Number>::plotTree( ReachabilityNode<Number>* current, std::string filename ) const {
	mPlotter.clear();
	mPlotter.setFilename( filename + "_pdf.plt" );
	current->plot();

	for (int i = 0; i < current->getNumberOfChildren(); i++){
		plotTree( current->getChild(i), filename + "." + std::to_string(i) );
	}
}

}  // namespace reachability
}  // namespace hypro