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
	, mPlotter( hypro::Plotter<Number>::getInstance() )
	, mCounterExampleStrategy( COUNTEREXAMPLE_STRATEGY::Z3_BASIC )
	, mRefinmentType( REFINEMENT_TYPE::AVOIDANT )
	, mBackpropagationStrategy( BACKPROPAGATION_STRATEGY::BINARYSEARCH ) {
	unsigned short int depth = 1;
	mPreviousCounterexampleSources = std::vector<std::list<int>>();
	for ( auto layer : mNetwork.layers() ) {
		mPreviousCounterexampleSources.push_back(std::list<int>());
		if ( layer->layerType() == NN_LAYER_TYPE::AFFINE )
			depth = depth + 1;
		else
			depth = depth + layer->layerSize();
	}
	mDepth = depth;
	assert(mPreviousCounterexampleSources.size() == network.numLayers());
}

template <typename Number>
ReachabilityTree<Number>::ReachabilityTree( const NeuralNetwork<Number>& network, const HPolytope<Number>& inputSet, const std::vector<HPolytope<Number>>& safeSets, const COUNTEREXAMPLE_STRATEGY counterExampleStrategy, const REFINEMENT_TYPE refinementType, const BACKPROPAGATION_STRATEGY backpropagationStrategy)
	: mNetwork( network )
	, mInputSet( inputSet )
	, mSafeSets( safeSets )
	, mPlotter( hypro::Plotter<Number>::getInstance())
	, mCounterExampleStrategy( counterExampleStrategy )
	, mRefinmentType( refinementType ) 
	, mBackpropagationStrategy( backpropagationStrategy ) {
	mPreviousCounterexampleSources = std::vector<std::list<int>>();
	unsigned short int depth = 1;
	for ( auto layer : mNetwork.layers() ) {
		mPreviousCounterexampleSources.push_back(std::list<int>());
		if ( layer->layerType() == NN_LAYER_TYPE::AFFINE )
			depth = depth + 1;
		else
			depth = depth + layer->layerSize();
	}
	mDepth = depth;
	assert(mPreviousCounterexampleSources.size() == network.numLayers());
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
	// TODO: confirm the following works and remove the other :: return node->getNumberOfChildren() > 0 ? 1 + depth(node.getChild(0)) : 1;
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

	return Starset<Number>( mInputSet );
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
void ReachabilityTree<Number>::rememberCounterexampleSource(int layerNumber, int neuronNumber){
	if(mPreviousCounterexampleSources[layerNumber].empty()){
		mPreviousCounterexampleSources[layerNumber].push_back(neuronNumber);
		return;
	}

	std::list<int>::iterator it;
	for ( it = mPreviousCounterexampleSources[layerNumber].begin(); *it <= neuronNumber && it != mPreviousCounterexampleSources[layerNumber].end(); it++){
		if (*it == neuronNumber){
			return;
		}
	}

	mPreviousCounterexampleSources[layerNumber].insert(it, neuronNumber);
}

template <typename Number> 
bool ReachabilityTree<Number>::isPreviousCounterexampleSource(int layerNumber, int neuronNumber ){
	if(mPreviousCounterexampleSources[layerNumber].empty()){
		return false;
	}

	std::list<int>::iterator it;
	for ( it = mPreviousCounterexampleSources[layerNumber].begin(); *it <= neuronNumber && it != mPreviousCounterexampleSources[layerNumber].end(); it++){
		if (*it == neuronNumber){
			return true;
		}
	}

	return false;
}


// This method computes the rechability tree using a specified input starset and an NN_REACH_METHOD starting from a given neuron
// It can be used just to compute a subtree from the j. neuron of the k.th layer
// the subtree then could be inserted into the search tree (replacing and deleting the old subtree)
// Note: This only computes the reachability tree until an unsafe leaf is found
template <typename Number>
ReachabilityNode<Number>* ReachabilityTree<Number>::computeReachTree( ReachabilityNode<Number>* rootNode, const std::vector<HPolytope<Number>>& safeSets, SEARCH_STRATEGY strategy ) {
	// create the root_job and add to the queue
	SearchJob<Number> root_job( rootNode, mNetwork.layers() );
	NN_REACH_METHOD rootMethod = rootNode->method();
	std::deque<SearchJob<Number>> jobQueue;
	jobQueue.push_back( root_job );

	// perform BFS / DFS until the queue is not empty and the network is still safe
	while ( !jobQueue.empty() ) {
		SearchJob<Number> job = jobQueue.front();
		std::vector<SearchJob<Number>> newJobs;
		if(BACKPROPAGATION_STRATEGY::EXACT_SOURCES == mBackpropagationStrategy && isPreviousCounterexampleSource(job.getNode()->layerNumber(),job.getNode()->neuronNumber())){
			newJobs = job.compute( NN_REACH_METHOD::EXACT );
		} else {
			newJobs = job.compute( rootMethod );
		}
		jobQueue.pop_front();

		for ( auto newJob : newJobs ) {
			if(BACKPROPAGATION_STRATEGY::EXACT_SOURCES == mBackpropagationStrategy && rootMethod != NN_REACH_METHOD::EXACT){
				newJob.getNode()->setMethod(NN_REACH_METHOD::OVERAPPRX);
			}

			if ( newJob.isFinalResult() ) {
				// check if the leaf satisfies the safety property
				// if not then early stop condition is met and the loop can be stopped
				ReachabilityNode<Number>* leafNode = newJob.getNode();
				mLeaves.push_back( leafNode );

				if ( !leafNode->checkSafe( mSafeSetMatrices, mSafeSetVectors, mCounterExampleStrategy) ) {
					mIsSafe = false;
					if(BACKPROPAGATION_STRATEGY::EXACT_SOURCES != mBackpropagationStrategy || rootMethod == NN_REACH_METHOD::EXACT){
						mIsComplete = true;
						return rootNode;
					}
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

template <typename Number>
std::pair<ReachabilityNode<Number>*,std::vector<ReachabilityNode<Number>*>> ReachabilityTree<Number>::computePartiallyExactReachTree( ReachabilityNode<Number>* rootNode, const std::vector<HPolytope<Number>>& safeSets, SEARCH_STRATEGY strategy ) {
	SearchJob<Number> job( rootNode, mNetwork.layers() );
	std::vector<ReachabilityNode<Number>*> notComputedNodes;
	
	while ( !job.isFinalResult() ) {
		std::vector<SearchJob<Number>> newJobs;
		if(isPreviousCounterexampleSource(job.getNode()->layerNumber(),job.getNode()->neuronNumber())){
			newJobs = job.compute( NN_REACH_METHOD::EXACT );
		} else {
			newJobs = job.compute( rootNode->method() );
		}
		for ( int i = 1; i < newJobs.size(); i++) {
			newJobs[i].getNode()->setMethod(NN_REACH_METHOD::OVERAPPRX);
			notComputedNodes.push_back(newJobs[i].getNode());	
		}		
		job = newJobs[0];
	}

	ReachabilityNode<Number>* leafNode = job.getNode();
	mLeaves.push_back( leafNode );
	if ( !leafNode->checkSafe( mSafeSetMatrices, mSafeSetVectors, mCounterExampleStrategy) ) {
		mIsSafe = false;
	} 
	mIsComplete = true;
	return std::make_pair(leafNode, notComputedNodes);
}

//The refinement loop for CEGAR where each new sub-tree is allways computed fully
template <typename Number>
bool ReachabilityTree<Number>::_refinementAlwaysFullComputation(SEARCH_STRATEGY strategy,  bool createPlots, size_t max_iter, const std::vector<HPolytope<Number>> safeOutput){
	// repeat until we either find a real counterexample or we can verify that the network is safe
	int ctx = 0;
	while ( !mIsSafe && ctx < max_iter ) {
		mLeaves.clear();  // TODO: do not clear the leaves that are not affected
		updateLeaves( mRoot );
		std::cout << "Number of leaves: " << mLeaves.size() << std::endl;

		ReachabilityNode<Number>* chosenLeaf = getFirstUnsafeLeaf();
			
		// generate a counterexample
		Point<Number> candidate = chosenLeaf->getCounterExample();
		std::cout << "The counterexample candidate is " << candidate << std::endl;
		
		//Otherwise chosenLeaf is safe
		assert(candidate.dimension() > 0);

		// identify the source neuron of the counterexample
		std::cout << "Previous counterexample sources: [";
		for(auto list : mPreviousCounterexampleSources){
			std::cout << "(";
			for (int neuron : list){
				std::cout << neuron << ",";
			}
			std::cout << ")";
		}
		std::cout << "]. Identifying next source..." << std::endl;
		std::pair<Point<Number>, ReachabilityNode<Number>*> candidateSource = identifyCounterExampleSource( candidate, chosenLeaf, mBackpropagationStrategy);

		//If an actual counterexample can be propagated back to the root, the the counterexample is not the result of approximation
		if ( candidateSource.first.dimension() > 0 && !candidateSource.second->hasParent()  ) {
			std::cout << "True countereaxmple found, refinement process stops" << std::endl;
			std::cout << "The true counterexample is: " << candidateSource.first << std::endl;
			mIsSafe = false;
			return false;
		}

		//source of the spurious counterexample
        ReachabilityNode<Number>* refinedNode = candidateSource.second;
		rememberCounterexampleSource(refinedNode->layerNumber(), refinedNode->neuronNumber());
		std::cout << "Known counterexample sources: [";
		for(auto list : mPreviousCounterexampleSources){
			std::cout << "(";
			for (int neuron : list){
				std::cout << neuron << ",";
			}
			std::cout << ")";
		}
		std::cout << "]" << std::endl;
        std::cout << "The source of newest counterexample candidate is: " << refinedNode->layerNumber() << " " << refinedNode->neuronNumber() << std::endl;
		
		// do the refinement step
		mIsSafe = true;
		mIsComplete = false;

		// calculate the children of the refined node using exact computation
		refinedNode->removeAllChildren();
		std::cout << "Refining the selected node" << std::endl;
		SearchJob<Number> refinedJob( refinedNode, mNetwork.layers() );
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

	if( !mIsSafe && ctx >= max_iter ){
		std::cout << "Reached maximum number of refinment steps. Safety of the NN is not known!" << std::endl;
		return false;
	}

	return true;

}


//The refinment loop for CEGAR where a subtree is only computed, when its safety is checked
template <typename Number>
bool ReachabilityTree<Number>::_refinementAvoidComputation(SEARCH_STRATEGY strategy,  bool createPlots, size_t max_iter, const std::vector<HPolytope<Number>> safeOutput){
	bool foundResult = false;
	bool foundUnsafe = true;
	assert(mLeaves.size() == 1 && "Over-approximate reachability computation did not result in 1 leaf");
    ReachabilityNode<Number>* unsafeLeaf = mLeaves[0];
	std::vector<ReachabilityNode<Number>*> notComputedLeaves;

	//Using for-loops appears to be faster somehow
	for(int count = 0; !foundResult && count < max_iter; count++){	
		// Split the unsafe leaf exists
		// Backpropagate the counterexample: Identify the source neuron of the counterexample
		std::cout << "The counterexample candidate is " << unsafeLeaf->getCounterExample() << std::endl;		
		std::pair<Point<Number>, ReachabilityNode<Number>*> candidateSource = identifyCounterExampleSource( unsafeLeaf->getCounterExample(), unsafeLeaf, mBackpropagationStrategy );

		// If the counterexample is not spurious then: return false
		if ( candidateSource.first.dimension() > 0 && !candidateSource.second->hasParent()  ) {
			std::cout << "True countereaxmple found, refinement process stops" << std::endl;
			std::cout << "The true counterexample is: " << candidateSource.first << std::endl;
			mIsSafe = false;
			foundResult = true;
			continue;
		} 
		
		// Split with exact and do NOT compute the children
		std::cout << "Previous counterexample sources: [";
		for(auto list : mPreviousCounterexampleSources){
			std::cout << "(";
			for (int neuron : list){
				std::cout << neuron << ",";
			}
			std::cout << ")";
		}
		std::cout << "]. Identifying next source..." << std::endl;
		ReachabilityNode<Number>* refinedNode = candidateSource.second;
		rememberCounterexampleSource(refinedNode->layerNumber(), refinedNode->neuronNumber());
		std::cout << "Known counterexample sources: [";
		for(auto list : mPreviousCounterexampleSources){
			std::cout << "(";
			for (int neuron : list){
				std::cout << neuron << ",";
			}
			std::cout << ")";
		}
		std::cout << "]" << std::endl;
    	std::cout << "Refining the source of the counterexample candidate: " << refinedNode->layerNumber() << " " << refinedNode->neuronNumber() << std::endl;
		refinedNode->removeAllChildren();
		SearchJob<Number> refinedJob( refinedNode, mNetwork.layers() );
		std::vector<SearchJob<Number>> newJobs = refinedJob.compute( NN_REACH_METHOD::EXACT );
		std::cout << "New jobs size: " << newJobs.size() << std::endl;
		foundUnsafe = false;
			
		//Update leaves
		notComputedLeaves.clear();	
		mLeaves.clear();
		updateLeaves( mRoot,  &notComputedLeaves);
		std::cout << "Number of not-computed leaves: " << notComputedLeaves.size()
				  << "\nNumber of all leaves: " << mLeaves.size() << std::endl;

		// Compute the reachability tree of the not-computed leaves, until an unsafe leaf is found or all leaves are computed
		int i;
		for(i = 0; i < notComputedLeaves.size() && !foundUnsafe; i++){
			std::cout << "Computing new over-approximated subtree...";
			notComputedLeaves[i]->setMethod( NN_REACH_METHOD::OVERAPPRX );
			if(BACKPROPAGATION_STRATEGY::EXACT_SOURCES == mBackpropagationStrategy){
				std::pair<ReachabilityNode<Number>*,std::vector<ReachabilityNode<Number>*>> tmp = computePartiallyExactReachTree( notComputedLeaves[i], safeOutput, strategy );
				foundUnsafe = !(tmp.first->checkSafe(mSafeSetMatrices, mSafeSetVectors, mCounterExampleStrategy));
				if(!foundUnsafe){
					for (ReachabilityNode<Number>* notComputedLeaf : tmp.second){
						notComputedLeaves.push_back(notComputedLeaf);
					}
				}
			} else {
				foundUnsafe = !computeReachTree( notComputedLeaves[i], safeOutput, strategy )->checkSafe(mSafeSetMatrices, mSafeSetVectors, mCounterExampleStrategy);
			}
			std::cout << " New subtree is " << (!foundUnsafe ? "safe" : "unsafe") << std::endl;
		}
		
		if(foundUnsafe){ //set the unsafeLeaf
			unsafeLeaf = notComputedLeaves[--i];			
			while (!unsafeLeaf->isLeaf()){
				unsafeLeaf = unsafeLeaf->getChild(0);
			}
		} else { //all leaves are safe and computed -> the tree is safe
			mIsSafe = true;
			foundResult = true;
		}			
	}
	return mIsSafe;
}

// here in the verify method just call the forwardPass method to calculate the EXACT or OVERAPPROXIMATIVE result
// if it is CEGAR countinue with the refinement, otherwise just stop and verify the "leaves"
// if the method is not CEGAR than it makes no sense to save the intermediate stars into the search tree

template <typename Number>
bool ReachabilityTree<Number>::verify( NN_REACH_METHOD method, SEARCH_STRATEGY strategy, bool createPlots, bool normalizeInput, bool normalizeOutput, size_t max_iter) {
	Starset<Number> starInput = prepareInput( normalizeInput );
	std::vector<HPolytope<Number>> safeOutput = prepareSafeSet( normalizeOutput );
	
	for (unsigned i = 0; i < safeOutput.size(); i++){
    	mSafeSetMatrices.push_back(safeOutput[i].matrix());
        mSafeSetVectors.push_back(safeOutput[i].vector());
    }
	
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
		return true;
	}

	// std::cout << "Neural network structure: " << mNetwork << std::endl;
	std::cout << "Search tree depth: " << depth(mRoot) << std::endl;

	// else we start the refinement
	if ( createPlots )
		plotTree( mRoot, "0-CEGAR_Reach_" );

	switch(mRefinmentType){
		case REFINEMENT_TYPE::AVOIDANT:
			_refinementAvoidComputation(strategy, createPlots, max_iter, safeOutput);
			break;
		case REFINEMENT_TYPE::FULL:
			_refinementAlwaysFullComputation(strategy, createPlots, max_iter, safeOutput);
			break;
		default:
			_refinementAvoidComputation(strategy, createPlots, max_iter, safeOutput);
			break;
	}

	mLeaves.clear();  // TODO: do not clear the leaves that are not affected
	updateLeaves( mRoot );
	// TODO: do not forget to delete the reachability tree when it is not used anymore

	std::cout << "The neural network is " << ( mIsSafe ? "safe" : "unsafe" ) << std::endl;
	std::cout << "The number of final sets is " << mLeaves.size() << std::endl;

	return mIsSafe;
}

// Returns the first unsafe leaf
template <typename Number>
ReachabilityNode<Number>* ReachabilityTree<Number>::getFirstUnsafeLeaf() const {
	for ( auto leaf : mLeaves ) {
		if ( !leaf->isSafe() ) {
			return leaf;
		}
	}
	//This should only be called, if the reachtree is not safe
	assert(false && "all leaves are safe");
	return mLeaves[0];
}

/*
* Adds all leaves with ancestor node to the mLeaves vector
* This does NOT clear the mLeaves vector before adding new leaves!
*/
template <typename Number>
void ReachabilityTree<Number>::updateLeaves( ReachabilityNode<Number>* node) {
	if ( node->isLeaf() || !node->isComputed()) {
		mLeaves.push_back( node );
	} else {
		for (int i = 0; i < node->getNumberOfChildren(); i++){
			updateLeaves( node->getChild(i) );		
		}
	}
}

template <typename Number>
void ReachabilityTree<Number>::updateLeaves( ReachabilityNode<Number>* node, std::vector<ReachabilityNode<Number>*>* notComputedLeaves) {
	if ( node->isLeaf() || !node->isComputed()) {
		if (!node->isComputed()){
			notComputedLeaves->push_back(node);
		}
		mLeaves.push_back( node );
	} else {
		for (int i = 0; i < node->getNumberOfChildren(); i++){
			updateLeaves( node->getChild(i), notComputedLeaves);		
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
std::pair<Point<Number>, ReachabilityNode<Number>*> ReachabilityTree<Number>::identifyCounterExampleSource( const Point<Number>& candidate, ReachabilityNode<Number>* node, BACKPROPAGATION_STRATEGY strategy) const {
	if ( !node->hasParent() ) {
		// indicates that the backpropagated counterexample originates from the very first neuron
		std::cout << "Candidate in root" << std::endl;
		return std::make_pair( candidate, node );  
	} 
    
    if ( candidate.dimension() <= 0 ){
		// if it is not included the current neuron introduces the counterexample
		return std::make_pair( candidate, node );
	}

	std::pair<Point<Number>, ReachabilityNode<Number>*> result;
	if(NN_LAYER_TYPE::AFFINE != mNetwork.layers(node->getParent()->layerNumber())->layerType()){
		switch(strategy){
			case BACKPROPAGATION_STRATEGY::BINARYSEARCH:
			case BACKPROPAGATION_STRATEGY::EXACT_SOURCES:
				result = binarySearchBackpropagation(candidate, node, 0, 0);
				return identifyCounterExampleSource(result.first, result.second, strategy);
			case BACKPROPAGATION_STRATEGY::REMEMBERING_SEARCH:
				result = rememberingSearchBackpropagation(candidate, node);
				return identifyCounterExampleSource(result.first, result.second, strategy);
			default:
				break;
		}
	}

	ReachabilityNode<Number>* parent = node->getParent();
	Point<Number> newCandidate = propagateCandidateBack( candidate, parent->layerNumber(), parent->neuronNumber(), parent->representation(), node->representation());
	return identifyCounterExampleSource( newCandidate, parent, strategy );
}


//Where we know, that we can backpropgate to:       l = node->neuronNumber()
//Where we want to try to backpropagate to:         c = nextIndex = ancestorNode->neuronNumber()
//Where we know, that we cannot backpropagate to:   u = upperIndex 
//Returns a origin of candidate and the node corresponding to the neuron with number 0 OR the source-node of the counterexample and the empty point
template <typename Number>
std::pair<Point<Number>, ReachabilityNode<Number>*> ReachabilityTree<Number>::binarySearchBackpropagation(const Point<Number>& candidate, ReachabilityNode<Number>* node,  const int upperIndex, const int nextIndex ) const {
    //For very small layers, this method is not useful, therefore the default method is used
    if(mNetwork.layers( node->getParent()->layerNumber() )->layerSize() <= 2 ){
        return identifyCounterExampleSource(candidate, node, BACKPROPAGATION_STRATEGY::SINGLESTEP);
    }

	std::cout << "Upper Index: " << upperIndex
              << "\nNext Index: " << nextIndex
              << "\nNode Index: "<< node->getParent()->neuronNumber() + 1 <<"\n";
	    
    
    //If backpropagation to the starset in node is possible, but backpropagation to the next one is not possible, the source is identified
    if(node->neuronNumber() == upperIndex + 1) {
        std::cout << "Found source in layer!" << std::endl;
        return std::make_pair(Point<Number>(), getAncestor(node, upperIndex));
    } else if(node->getParent()->neuronNumber() == upperIndex) {
		return std::make_pair(Point<Number>(), node->getParent());
	}
    
    ReachabilityNode<Number>* ancestorNode = getAncestor(node->getParent(), nextIndex);
    Point<Number> origin = propagateCandidateBack(candidate, node->getParent()->layerNumber() ,node->getParent()->neuronNumber(), nextIndex, ancestorNode->representation());
    //This is the "binary search" part
    if(origin.dimension() > 0){
        //If backpropagation to the start of the layer is possible, continue propagating through the other layers
        if(nextIndex == 0 && upperIndex == 0){
            std::cout << "Continuing with the next layer..." << std::endl;;
            return std::make_pair(origin, ancestorNode);
        }
        // Continue the search for 
        std::cout << "Changing lower index" << std::endl;
        return binarySearchBackpropagation(origin, ancestorNode, upperIndex, (upperIndex + nextIndex) / 2); //rounding of integer division is correct
    } else {
        std::cout << "Changing upper index" << std::endl;
        return binarySearchBackpropagation(candidate, node, nextIndex, (nextIndex + node->getParent()->neuronNumber() + 1) / 2); //rounding of integer division is correct
    }
}

template <typename Number>
std::pair<Point<Number>, ReachabilityNode<Number>*> ReachabilityTree<Number>::rememberingSearchBackpropagation(const Point<Number>& candidate, ReachabilityNode<Number>* node ) const {
	std::list<int> previousSources = mPreviousCounterexampleSources[node->getParent()->layerNumber()];

	if(previousSources.empty()){
		return binarySearchBackpropagation(candidate, node,  0, 0 );
	}

	//For very small layers, this method is not useful, therefore the default method is used
    if(mNetwork.layers( node->getParent()->layerNumber() )->layerSize() <= 2 ){
        return identifyCounterExampleSource(candidate, node, BACKPROPAGATION_STRATEGY::SINGLESTEP);
    }

	ReachabilityNode<Number>* ancestorNode;
	Point<Number> origin;
	int layerNumber = node->getParent()->layerNumber();
	int nodeNumber = node->getParent()->neuronNumber();

	//If backpropagation to the start of the layer is possible, continue propagating through the other layers
	ancestorNode = getAncestor(node->getParent(), 0);
    origin = propagateCandidateBack(candidate, layerNumber , nodeNumber, 0, ancestorNode->representation());
	if(0 < origin.dimension() ){
    	std::cout << "Continuing with the next layer..." << std::endl;;
        return std::make_pair(origin, ancestorNode);
    }
	
	//TODO: Figure out why an error with getAncestor could occure here (found with drones->c_1_1)
	//		Think about subsequent neurons in the previous sources list (e.g.: [..., x,x+1,...])
	for (std::list<int>::iterator it = previousSources.begin(); it != previousSources.end(); it++ ){
		ancestorNode = getAncestor(node->getParent(), *it);
		origin = propagateCandidateBack(candidate, layerNumber, nodeNumber, *it, ancestorNode->representation());
		//If backpropagation is possible, check if prev(it) is the source
		if( 0 < origin.dimension() ){
			if ( it == previousSources.begin()){
				return binarySearchBackpropagation(origin, ancestorNode, 0, (*it)/2);
			}
			ReachabilityNode<Number>* beforeSourceNode = getAncestor(ancestorNode, *std::prev(it) + 1);
			Point<Number> tmpOrigin = propagateCandidateBack(origin, layerNumber, ancestorNode->getParent()->neuronNumber(), *std::prev(it) + 1, beforeSourceNode->representation());
			if ( 0 < tmpOrigin.dimension() ){
				return std::make_pair(Point<Number>(), beforeSourceNode->getParent());
			}
			return binarySearchBackpropagation(origin, ancestorNode,*std::prev(it) + 1, ((*it) + *std::prev(it) + 1)/2);
		}
		if( next(it) == previousSources.end()){
			ReachabilityNode<Number>* beforeSourceNode = getAncestor(node->getParent(), (*it) + 1);
			Point<Number> tmpOrigin = propagateCandidateBack(candidate, layerNumber, nodeNumber, (*it) + 1, beforeSourceNode->representation());
			if ( 0 < tmpOrigin.dimension() ){
				return std::make_pair(Point<Number>(), ancestorNode);
			}
			return binarySearchBackpropagation(candidate, node,(*it) + 1, (nodeNumber + (*it))/2 + 1);
		}
	}
	return binarySearchBackpropagation(candidate, node,  (*previousSources.begin()) + 1, (nodeNumber + (*previousSources.begin()))/2 + 1 );
}

template <typename Number>
ReachabilityNode<Number>* ReachabilityTree<Number>::getAncestor(ReachabilityNode<Number>* node, const int neuronNumber) const {
    if (node->neuronNumber() == neuronNumber){
        return node;
    }
    assert(node->hasParent() && node->layerNumber() == node->getParent()->layerNumber());
    return getAncestor(node->getParent(), neuronNumber);
}


template <typename Number>
Point<Number> ReachabilityTree<Number>::propagateCandidateBack( const Point<Number>& candidate, const int parentLayer, const int parentNeuron, const Starset<Number>& parentSet, const Starset<Number>& currentSet ) const {
	std::cout << "Propagating candidate back..." << std::endl;
	std::shared_ptr<LayerBase<Number>> layer = mNetwork.layers( parentLayer );
	
	if (layer->layerType() ==  NN_LAYER_TYPE::AFFINE){
		return layer->propagateCandidateBack( candidate, parentNeuron, parentSet, currentSet);	
	}

	return layer->propagateCandidateBack( candidate, parentNeuron, parentSet );
}

// [upperIndex, lowerIndex] is inclusive
// For all dimensions in this interval (in the natural numbers) the backpropagation takes place!
// Thus if the candidate comes from neuron (n+1) and is propagated back to neuron n, the correct interval is [n,n]
template <typename Number>
Point<Number> ReachabilityTree<Number>::propagateCandidateBack(const Point<Number>& candidate, int layerNumber, int lowerIndex, int upperIndex, const Starset<Number>& ancestorSet) const {
	std::cout << "Propagating candidate back from " << lowerIndex + 1<< " to " << upperIndex << std::endl;
	std::shared_ptr<LayerBase<Number>> layer = mNetwork.layers( layerNumber );
	return layer->propagateCandidateBack( candidate, lowerIndex, upperIndex, ancestorSet );
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