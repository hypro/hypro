#include "ReachabilityTree.h"

namespace hypro {
namespace reachability {

template <typename Number>
ReachabilityTree<Number>::ReachabilityTree()
	: mPlotter( hypro::Plotter<Number>::getInstance() ) {}

template <typename Number>
ReachabilityTree<Number>::~ReachabilityTree() {
	mLeaves.clear();
	delete mRoot;
}

template <typename Number>
ReachabilityTree<Number>::ReachabilityTree( const NeuralNetwork<Number>& network, const HPolytope<Number>& inputSet, const std::vector<HPolytope<Number>>& safeSets )
	: mNetwork( network )
	, mInputSet( inputSet )
	, mSafeSets( safeSets )
	, mPlotter( hypro::Plotter<Number>::getInstance() )
	, mCounterExampleStrategy( COUNTEREXAMPLE_STRATEGY::Z3_BASIC )
	, mRefinmentType( REFINEMENT_TYPE::EXACT_SOURCES )
	, mTracingStrategy( TRACING_STRATEGY::BINARYSEARCH )
	, mRemoveSafeSubtrees( false )
	, mNumberOfTracings( 0 ) {
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
ReachabilityTree<Number>::ReachabilityTree( const NeuralNetwork<Number>& network, const HPolytope<Number>& inputSet, const std::vector<HPolytope<Number>>& safeSets, const COUNTEREXAMPLE_STRATEGY counterExampleStrategy, const REFINEMENT_TYPE refinementType, const TRACING_STRATEGY backpropagationStrategy, const bool removeSafeSubtrees )
	: mNetwork( network )
	, mInputSet( inputSet )
	, mSafeSets( safeSets )
	, mPlotter( hypro::Plotter<Number>::getInstance() )
	, mCounterExampleStrategy( counterExampleStrategy )
	, mRefinmentType( refinementType )
	, mTracingStrategy( backpropagationStrategy )
	, mRemoveSafeSubtrees( removeSafeSubtrees )
	, mNumberOfTracings( 0 ) {
	mPreviousCounterexampleSources = std::vector<std::list<int>>();
	unsigned short int depth = 1;
	for ( auto layer : mNetwork.layers() ) {
		mPreviousCounterexampleSources.push_back( std::list<int>() );
		if ( layer->layerType() == NN_LAYER_TYPE::AFFINE )
			depth = depth + 1;
		else
			depth = depth + layer->layerSize();
	}
	mDepth = depth;
	assert( mPreviousCounterexampleSources.size() == network.numLayers() );
	mPreviousCounterexamples[std::make_pair( network.numLayers() - 1, 0 )] = std::set<Point<Number>>();
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
unsigned short int ReachabilityTree<Number>::depth( ReachabilityNode<Number>* node ) const {
	unsigned short int maxDepth = 0;
	for ( int i = 0; i < node->getNumberOfChildren(); i++ ) {
		// std::cout << "Depth child" << std::endl;
		unsigned short int depthChild = depth( node->getChild( i ) );
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
void ReachabilityTree<Number>::rememberCounterexampleSource( int layerNumber, int neuronNumber ) {
	if ( mPreviousCounterexampleSources[layerNumber].empty() ) {
		mPreviousCounterexampleSources[layerNumber].push_back( neuronNumber );
		return;
	}

	std::list<int>::iterator it;
	for ( it = mPreviousCounterexampleSources[layerNumber].begin(); *it <= neuronNumber && it != mPreviousCounterexampleSources[layerNumber].end(); it++ ) {
		if ( *it == neuronNumber ) {
			return;
		}
	}

	mPreviousCounterexampleSources[layerNumber].insert( it, neuronNumber );
}

template <typename Number>
bool ReachabilityTree<Number>::isPreviousCounterexampleSource( int layerNumber, int neuronNumber ) {
	if ( mPreviousCounterexampleSources[layerNumber].empty() ) {
		return false;
	}

	std::list<int>::iterator it;
	for ( it = mPreviousCounterexampleSources[layerNumber].begin(); *it <= neuronNumber && it != mPreviousCounterexampleSources[layerNumber].end(); it++ ) {
		if ( *it == neuronNumber ) {
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
	if ( rootNode->isLeaf() ) {
		if ( !rootNode->checkSafe( mSafeSetMatrices, mSafeSetVectors, mCounterExampleStrategy, mPreviousCounterexamples[std::make_pair( mPreviousCounterexampleSources.size() - 1, 0 )] ) ) {
			mPreviousCounterexamples[std::make_pair( mPreviousCounterexampleSources.size() - 1, 0 )].insert( rootNode->getCounterExample() );
			mIsSafe = false;
		} else if ( mRemoveSafeSubtrees ) {
			removeSafeSubtree( rootNode );
		}
		mIsComplete = true;
		return rootNode;
	}

	// create the root_job and add to the queue
	SearchJob<Number> root_job( rootNode, mNetwork.layers() );
	NN_REACH_METHOD rootMethod = mRoot->method();
	std::deque<SearchJob<Number>> jobQueue;
	jobQueue.push_back( root_job );

	// perform BFS / DFS until the queue is not empty and the network is still safe
	while ( !jobQueue.empty() ) {
		SearchJob<Number> job = jobQueue.front();
		std::vector<SearchJob<Number>> newJobs;
		if ( REFINEMENT_TYPE::EXACT_SOURCES == mRefinmentType && isPreviousCounterexampleSource( job.getNode()->layerNumber(), job.getNode()->neuronNumber() ) ) {
			newJobs = job.compute( NN_REACH_METHOD::EXACT );
		} else {
			newJobs = job.compute( rootMethod );
		}
		jobQueue.pop_front();

		for ( auto newJob : newJobs ) {
			if ( newJob.isFinalResult() ) {
				// check if the leaf satisfies the safety property
				// if not then early stop condition is met and the loop can be stopped
				ReachabilityNode<Number>* leafNode = newJob.getNode();
				if ( !leafNode->checkSafe( mSafeSetMatrices, mSafeSetVectors, mCounterExampleStrategy, mPreviousCounterexamples[std::make_pair( mPreviousCounterexampleSources.size() - 1, 0 )] ) ) {
					mIsSafe = false;
					mPreviousCounterexamples[std::make_pair( mPreviousCounterexampleSources.size() - 1, 0 )].insert( leafNode->getCounterExample() );
					if ( rootMethod == NN_REACH_METHOD::EXACT ) {
						mIsComplete = true;
						return rootNode;
					}
					mLeaves.push_back( leafNode );
				} else if ( mRemoveSafeSubtrees ) {
					newJob.setNode( nullptr );
					removeSafeSubtree( leafNode );
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
void ReachabilityTree<Number>::removeSafeSubtree( ReachabilityNode<Number>* safeLeaf ) {
	if ( !mRemoveSafeSubtrees ) {
		return;
	}

	ReachabilityNode<Number>* node = safeLeaf;

	while ( true ) {
		node->setSafe( true );
		switch ( node->method() ) {
			case NN_REACH_METHOD::OVERAPPRX:
				if ( node->hasParent() ) {
					node = node->getParent();
				} else {
					return;	 // root has been reached and is thus safe
				}
				break;
			case NN_REACH_METHOD::EXACT: {
				if ( node->hasParent() ) {
					ReachabilityNode<Number>* parent = node->getParent();

					// This could add save sets for a safe history implemenation
					// std::pair<int,int> key = std::make_pair(parent->layerNumber(), parent->neuronNumber());
					// mPreviousSaveSets[key].push_back(node->representation());

					for ( int i = 0; i < parent->getNumberOfChildren(); i++ ) {
						// std::cout << "Remove child" << std::endl;
						if ( !parent->getChild( i )->isSafe() ) {
							parent->removeChild( node );
							return;	 // the parent is the root of an "uncomputed" subtree
						}
					}
					node = node->getParent();
					break;
				} else {
					return;	 // root has been reached and is thus safe
				}
			}
			case NN_REACH_METHOD::CEGAR:  // nodes can only be computed via EXACT or OVERAPPRX activation function application
			default:
				assert( false && "This should not be reachable!" );
				break;
		}
	}
}

template <typename Number>
std::pair<ReachabilityNode<Number>*, std::vector<ReachabilityNode<Number>*>> ReachabilityTree<Number>::computePartiallyExactReachTree( ReachabilityNode<Number>* rootNode, const std::vector<HPolytope<Number>>& safeSets ) {
	std::vector<ReachabilityNode<Number>*> notComputedNodes;

	// This is a special case, where an activation function is computed producing final leaves
	if ( rootNode->isLeaf() ) {
		if ( !rootNode->checkSafe( mSafeSetMatrices, mSafeSetVectors, mCounterExampleStrategy, mPreviousCounterexamples[std::make_pair( mPreviousCounterexampleSources.size() - 1, 0 )] ) ) {
			mPreviousCounterexamples[std::make_pair( mPreviousCounterexampleSources.size() - 1, 0 )].insert( rootNode->getCounterExample() );
			mIsSafe = false;
		}
		mIsComplete = true;
		return std::make_pair( rootNode, notComputedNodes );
	}

	SearchJob<Number> job( rootNode, mNetwork.layers() );

	while ( !job.isFinalResult() ) {
		std::vector<SearchJob<Number>> newJobs;
		if ( isPreviousCounterexampleSource( job.getNode()->layerNumber(), job.getNode()->neuronNumber() ) ) {
			switch ( mRefinmentType ) {
				case REFINEMENT_TYPE::EXACT_SOURCES:
					newJobs = job.compute( NN_REACH_METHOD::EXACT );
					break;
				case REFINEMENT_TYPE::REMEMBERING_SOURCES: {
					newJobs = job.compute( NN_REACH_METHOD::OVERAPPRX );
					assert( newJobs.size() == 1 );
					bool useExact = false;
					for ( Point<Number> prevCounterexample : mPreviousCounterexamples[std::make_pair( job.getNode()->layerNumber(), job.getNode()->neuronNumber() )] ) {
						if ( newJobs[0].getNode()->representation().contains( prevCounterexample ) ) {
							useExact = true;
							break;
						}
					}
					if ( useExact ) {
						job.getNode()->removeAllChildren();
						newJobs = job.compute( NN_REACH_METHOD::EXACT );
					}
					break;
				}
				default:  // This defaults to EXACT_SOURCES and should not be reachable
					newJobs = job.compute( NN_REACH_METHOD::EXACT );
					break;
			}
			/* Part of the unsuable implementation for safe history: The containment checks take segnificantly to long
				if(mUseSafeHistory){
					std::vector<SearchJob<Number>> tmp;
					for (int i = 0; i < newJobs.size(); i++){
						ReachabilityNode<Number>* newNode = newJobs[i].getNode();
						std::pair<int,int> key = std::make_pair(newNode->getParent()->layerNumber(), newNode->getParent()->neuronNumber());
						for (Starset<Number> safeSet : mPreviousSaveSets[key]){
							std::cout << "Checking safe history"<< std::endl;
							if ( safeSet.contains(newNode->representation()) ) {
								std::cout << "Safe history helped!" << std::endl;
								newJobs[i].setNode(nullptr);
								newNode->getParent()->removeChild(newNode);
								break;
							}
						}
						if ( newJobs[i].getNode() != nullptr ){
							tmp.push_back(newJobs[i]);
						}
					}
					newJobs = tmp;
			}
			*/
		} else {
			newJobs = job.compute( mRoot->method() );
		}
		for ( int i = 1; i < newJobs.size(); i++ ) {
			notComputedNodes.push_back( newJobs[i].getNode() );
		}
		job = newJobs[0];
	}

	ReachabilityNode<Number>* leafNode = job.getNode();
	mLeaves.push_back( leafNode );
	if ( !leafNode->checkSafe( mSafeSetMatrices, mSafeSetVectors, mCounterExampleStrategy, mPreviousCounterexamples[std::make_pair( mPreviousCounterexampleSources.size() - 1, 0 )] ) ) {
		mPreviousCounterexamples[std::make_pair( mPreviousCounterexampleSources.size() - 1, 0 )].insert( leafNode->getCounterExample() );
		mIsSafe = false;
	}
	mIsComplete = true;
	return std::make_pair( leafNode, notComputedNodes );
}

// The refinement loop for CEGAR where each new sub-tree is allways computed fully
template <typename Number>
bool ReachabilityTree<Number>::fullRefinement( SEARCH_STRATEGY strategy, bool createPlots, size_t max_iter, const std::vector<HPolytope<Number>> safeOutput ) {
	// repeat until we either find a real counterexample or we can verify that the network is safe
	int ctx = 0;
	while ( !mIsSafe && ctx < max_iter ) {
		mLeaves.clear();
		updateLeaves( mRoot );
		ReachabilityNode<Number>* chosenLeaf = getFirstUnsafeLeaf();

		if ( chosenLeaf == mRoot ) {
			mIsSafe = true;
			return true;
		}

		// generate a counterexample
		Point<Number> candidate = chosenLeaf->getCounterExample();
		Point<Number> candidateAlpha = chosenLeaf->getCounterExampleAlpha();

		// Otherwise chosenLeaf is safe
		assert( candidate.dimension() > 0 );
		std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> candidateSource = identifyCounterExampleOrigin( candidate, candidateAlpha, chosenLeaf, mTracingStrategy );

		// If an actual counterexample can be propagated back to the root, the the counterexample is not the result of approximation
		if ( std::get<0>( candidateSource ).dimension() > 0 && !( std::get<2>( candidateSource )->hasParent() ) ) {
			mIsSafe = false;
			return false;
		}

		// source of the spurious counterexample
		ReachabilityNode<Number>* refinedNode = std::get<2>( candidateSource );
		rememberCounterexampleSource( refinedNode->layerNumber(), refinedNode->neuronNumber() );

		// do the refinement step
		mIsComplete = false;

		// calculate the children of the refined node using exact computation
		refinedNode->removeAllChildren();
		SearchJob<Number> refinedJob( refinedNode, mNetwork.layers() );
		std::vector<SearchJob<Number>> newJobs = refinedJob.compute( NN_REACH_METHOD::EXACT );

		for ( int i = 0; i < newJobs.size(); i++ ) {
			// use the compute reach tree function to compute the subtrees of the children
			computeReachTree( newJobs[i].getNode(), safeOutput, strategy );
		}

		ctx++;
		if ( createPlots )
			plotTree( mRoot, std::to_string( ctx ) + "-CEGAR_Reach_" );
	}

	if ( !mIsSafe && ctx >= max_iter ) {
		std::cout << "Reached maximum number of refinment steps. Safety of the NN is not known!" << std::endl;
		return false;
	}

	return true;
}

// The refinment loop for CEGAR where a subtree is only computed, when its safety is checked
template <typename Number>
bool ReachabilityTree<Number>::avoidentRefinement( SEARCH_STRATEGY strategy, bool createPlots, size_t max_iter, const std::vector<HPolytope<Number>> safeOutput ) {
	bool foundResult = false;
	bool foundUnsafe = true;
	assert( mLeaves.size() == 1 && "Over-approximate reachability computation did not result in 1 leaf" );
	ReachabilityNode<Number>* unsafeLeaf = mLeaves[0];
	std::vector<ReachabilityNode<Number>*> notComputedLeaves;

	// Using for-loops appears to be faster somehow
	for ( int count = 0; !foundResult && count < max_iter; count++ ) {
		// Split the unsafe leaf exists
		// Backpropagate the counterexample: Identify the source neuron of the counterexample
		std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> candidateSource = identifyCounterExampleOrigin( unsafeLeaf->getCounterExample(), unsafeLeaf->getCounterExampleAlpha(), unsafeLeaf, mTracingStrategy );

		// If the counterexample is not spurious then: return false
		if ( std::get<0>( candidateSource ).dimension() > 0 && !( std::get<2>( candidateSource )->hasParent() ) ) {
			mIsSafe = false;
			foundResult = true;
			continue;
		}

		// Split with exact and do NOT compute the children
		ReachabilityNode<Number>* refinedNode = std::get<2>( candidateSource );
		rememberCounterexampleSource( refinedNode->layerNumber(), refinedNode->neuronNumber() );
		refinedNode->removeAllChildren();
		SearchJob<Number> refinedJob( refinedNode, mNetwork.layers() );
		std::vector<SearchJob<Number>> newJobs = refinedJob.compute( NN_REACH_METHOD::EXACT );
		foundUnsafe = false;

		// Update leaves
		notComputedLeaves.clear();
		mLeaves.clear();
		updateLeaves( mRoot, &notComputedLeaves );

		// Compute the reachability tree of the not-computed leaves, until an unsafe leaf is found or all leaves are computed
		int i;
		for ( i = 0; i < notComputedLeaves.size() && !foundUnsafe; i++ ) {
			switch ( mRefinmentType ) {
				case REFINEMENT_TYPE::REMEMBERING_SOURCES:
				case REFINEMENT_TYPE::EXACT_SOURCES: {
					std::pair<ReachabilityNode<Number>*, std::vector<ReachabilityNode<Number>*>> tmp = computePartiallyExactReachTree( notComputedLeaves[i], safeOutput );
					foundUnsafe = !( tmp.first->checkSafe( mSafeSetMatrices, mSafeSetVectors, mCounterExampleStrategy, mPreviousCounterexamples[std::make_pair( mPreviousCounterexampleSources.size() - 1, 0 )] ) );
					if ( !foundUnsafe ) {
						for ( ReachabilityNode<Number>* notComputedLeaf : tmp.second ) {
							notComputedLeaves.push_back( notComputedLeaf );
						}
						removeSafeSubtree( tmp.first );
					} else {
						mPreviousCounterexamples[std::make_pair( mPreviousCounterexampleSources.size() - 1, 0 )].insert( tmp.first->getCounterExample() );
					}
					break;
				}
				default: {
					ReachabilityNode<Number>* leaf = computeReachTree( notComputedLeaves[i], safeOutput, strategy );
					foundUnsafe = !leaf->checkSafe( mSafeSetMatrices, mSafeSetVectors, mCounterExampleStrategy, mPreviousCounterexamples[std::make_pair( mPreviousCounterexampleSources.size() - 1, 0 )] );
					if ( foundUnsafe ) {
						mPreviousCounterexamples[std::make_pair( mPreviousCounterexampleSources.size() - 1, 0 )].insert( leaf->getCounterExample() );
					} else {
						removeSafeSubtree( leaf );
					}
					break;
				}
			}
		}

		if ( foundUnsafe ) {  // set the unsafeLeaf
			unsafeLeaf = notComputedLeaves[--i];
			while ( !unsafeLeaf->isLeaf() ) {
				// std::cout << "unsafe leaf child" << std::endl;
				unsafeLeaf = unsafeLeaf->getChild( 0 );
			}
		} else {  // all leaves are safe and computed -> the tree is safe
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
bool ReachabilityTree<Number>::verify( NN_REACH_METHOD method, SEARCH_STRATEGY strategy, bool createPlots, bool normalizeInput, bool normalizeOutput, size_t max_iter ) {
	Starset<Number> starInput = prepareInput( normalizeInput );
	std::vector<HPolytope<Number>> safeOutput = prepareSafeSet( normalizeOutput );

	for ( unsigned i = 0; i < safeOutput.size(); i++ ) {
		mSafeSetMatrices.push_back( safeOutput[i].matrix() );
		mSafeSetVectors.push_back( safeOutput[i].vector() );
	}

	mLeaves.clear();
	mIsSafe = true;
	mIsComplete = false;

	// create the root node of the reachability tree
	mRoot = new ReachabilityNode<Number>( starInput, method, 0, 0 );
	switch ( method ) {
		case NN_REACH_METHOD::EXACT:
		case NN_REACH_METHOD::OVERAPPRX:
			// if we apply the EXACT or OVERAPPROX method, regardless if the computation of the reachability tree is complete or not
			// we can surely return the answer
			computeReachTree( mRoot, safeOutput, strategy );
			if ( createPlots )
				plotTree( mRoot, method._to_string() );
			std::cout << "The neural network is " << ( mIsSafe ? "safe" : "unsafe" ) << std::endl;
			std::cout << "The number of final sets is " << mLeaves.size() << std::endl;
			return mIsSafe;
		case NN_REACH_METHOD::CEGAR:
			// for the CEGAR mehtod we start with a fully overapproximate reachability analysis
			// then we refine the result of the overapproximate reachability
			mRoot->setMethod( NN_REACH_METHOD::OVERAPPRX );
			computeReachTree( mRoot, safeOutput, strategy );
			std::cout << "CEGAR first forward pass finished, the result is " << ( mIsSafe ? "safe" : "unsafe" ) << std::endl;
			break;
		default:
			FATAL( "hypro.neuralnets.reachability_tree", "Invalid analysis method specified" );
	}

	if ( mIsSafe ) {
		// if the method is CEGAR and the reachable set is safe then the whole network is safe
		return true;
	}

	// std::cout << "Neural network structure: " << mNetwork << std::endl;
	// std::cout << "Search tree depth: " << depth(mRoot) << std::endl;

	// else we start the refinement
	if ( createPlots )
		plotTree( mRoot, "0-CEGAR_Reach_" );

	switch ( mRefinmentType ) {
		case REFINEMENT_TYPE::AVOIDANT:
		case REFINEMENT_TYPE::EXACT_SOURCES:
		case REFINEMENT_TYPE::REMEMBERING_SOURCES:
			avoidentRefinement( strategy, createPlots, max_iter, safeOutput );
			break;
		case REFINEMENT_TYPE::FULL:
			fullRefinement( strategy, createPlots, max_iter, safeOutput );
			break;
		default:
			FATAL( "hypro.neuralnets.reachability_tree", "Invalid refinement method specified" );
	}

	mLeaves.clear();
	updateLeaves( mRoot );

	std::cout << "The neural network is " << ( mIsSafe ? "safe" : "unsafe" ) << std::endl;
	std::cout << "The number of final sets is " << mLeaves.size() << std::endl;
	std::cout << "Number of Tracings performed is " << mNumberOfTracings << std::endl;
	return mIsSafe;
}

// Returns the first unsafe leaf or root
template <typename Number>
ReachabilityNode<Number>* ReachabilityTree<Number>::getFirstUnsafeLeaf() const {
	for ( auto leaf : mLeaves ) {
		if ( !leaf->isSafe() ) {
			return leaf;
		}
	}
	return mRoot;
}

/*
 * Adds all leaves with ancestor node to the mLeaves vector
 * This does NOT clear the mLeaves vector before adding new leaves!
 */
template <typename Number>
void ReachabilityTree<Number>::updateLeaves( ReachabilityNode<Number>* node ) {
	if ( node->isLeaf() || !node->isComputed() ) {
		mLeaves.push_back( node );
	} else {
		for ( int i = 0; i < node->getNumberOfChildren(); i++ ) {
			// std::cout << "Update leaves 1 child" << std::endl;
			updateLeaves( node->getChild( i ) );
		}
	}
}

template <typename Number>
void ReachabilityTree<Number>::updateLeaves( ReachabilityNode<Number>* node, std::vector<ReachabilityNode<Number>*>* notComputedLeaves ) {
	if ( node->isLeaf() || !node->isComputed() ) {
		if ( ( !node->isComputed() ) || ( !node->hasCounterExample() ) ) {
			notComputedLeaves->push_back( node );
		}
		mLeaves.push_back( node );
	} else {
		for ( int i = 0; i < node->getNumberOfChildren(); i++ ) {
			// std::cout << "Update leaves 2 child" << std::endl;
			updateLeaves( node->getChild( i ), notComputedLeaves );
		}
	}
}

/*
 * If node is the root, then return pair of inputs
 * Else if source is non-empty, then propagate the source back and return a call of this method on the parent of node and the backpropagated source
 * Else if source is empty, return pair of inputs
 *
 * Returns:
 *	a) a node (including the root) and the empty point (indicates that the node is the sources of the original counterexample)
 *	b) the root and a non-empty point (indicates a true counterexample)
 */

template <typename Number>
std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> ReachabilityTree<Number>::identifyCounterExampleOrigin( const Point<Number>& source, const Point<Number>& sourceAlpha, ReachabilityNode<Number>* node, TRACING_STRATEGY strategy ) {
	if ( !node->hasParent() ) {
		// indicates that the backpropagated counterexample originates from the very first neuron
		return std::make_tuple( source, sourceAlpha, node );
	}

	if ( source.dimension() <= 0 ) {
		// if it is not included the operation performed on the current neuron introduces the counterexample
		return std::make_tuple( source, sourceAlpha, node );
	}

	std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> result;
	if ( NN_LAYER_TYPE::AFFINE != mNetwork.layers( node->getParent()->layerNumber() )->layerType() ) {
		switch ( strategy ) {
			case TRACING_STRATEGY::BINARYSEARCH:
				result = binarySearchTracing( source, sourceAlpha, node, 0, 0 );
				return identifyCounterExampleOrigin( std::get<0>( result ), std::get<1>( result ), std::get<2>( result ), strategy );
			case TRACING_STRATEGY::REMEMBERING_SEARCH:
				result = rememberingSearchTracing( source, sourceAlpha, node );
				return identifyCounterExampleOrigin( std::get<0>( result ), std::get<1>( result ), std::get<2>( result ), strategy );
			case TRACING_STRATEGY::UNSAT_CORE:
				result = unsatCoreTracing( source, sourceAlpha, node );
				return identifyCounterExampleOrigin( std::get<0>( result ), std::get<1>( result ), std::get<2>( result ), strategy );
			default:
				break;
		}
	}

	ReachabilityNode<Number>* parent = node->getParent();
	std::pair<Point<Number>, Point<Number>> newSource = traceSourceBack( source, sourceAlpha, parent->layerNumber(), parent->neuronNumber(), parent->representation(), node->representation() );
	if ( newSource.first.dimension() <= 0 ) {
		std::pair<int, int> key = std::make_pair( node->layerNumber(), node->neuronNumber() );
		mPreviousCounterexamples[key].insert( source );
	}
	return identifyCounterExampleOrigin( newSource.first, newSource.second, parent, mTracingStrategy );
}

// Where we know, that we can backpropgate to:       l = node->neuronNumber()
// Where we want to try to backpropagate to:         c = nextIndex = ancestorNode->neuronNumber()
// Where we know, that we cannot backpropagate to:   u = upperIndex
// Returns a origin of source and the node corresponding to the neuron with number 0 OR the source-node of the counterexample and the empty point
template <typename Number>
std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> ReachabilityTree<Number>::binarySearchTracing( const Point<Number>& source, const Point<Number>& sourceAlpha, ReachabilityNode<Number>* node, const int upperIndex, const int nextIndex ) {
	// For very small layers, this method is not useful, therefore the default method is used
	//  first: neuronNumber == 0 -> layer size = 0 -> very small activation function sequence with subsequent affine mapping (thus parent has layersize = 1)
	//                                             or a node resulting form the last dimension of activation function application -> parent layer needs to be checked for size
	//  second: neuronNumber > 0 -> node is in a sequence of activation functions and can thus be directly checked
	if ( ( node->neuronNumber() == 0 && mNetwork.layers( node->getParent()->layerNumber() )->layerSize() <= 2 ) || ( node->neuronNumber() > 0 && mNetwork.layers( node->layerNumber() )->layerSize() <= 2 ) ) {
		return identifyCounterExampleOrigin( source, sourceAlpha, node, TRACING_STRATEGY::SINGLESTEP );
	}

	ReachabilityNode<Number>* ancestorNode = getAncestor( node->getParent(), nextIndex );
	std::pair<Point<Number>, Point<Number>> origin = traceSourceBack( source, sourceAlpha, node->getParent()->layerNumber(), node->getParent()->neuronNumber(), nextIndex, ancestorNode->representation() );

	int u;
	int c;
	ReachabilityNode<Number>* newNode;
	Point<Number> newSource;
	Point<Number> newSourceAlpha;

	// This is the "binary search" part
	if ( origin.first.dimension() > 0 ) {
		// If backpropagation to the start of the layer is possible, continue propagating through the other layers
		if ( nextIndex == 0 && upperIndex == 0 ) {
			return std::make_tuple( origin.first, origin.second, ancestorNode );
		}

		newSource = origin.first;
		newSourceAlpha = origin.second;
		newNode = ancestorNode;
		u = upperIndex;
		c = ( upperIndex + nextIndex ) / 2;

	} else {
		newSource = source;
		newSourceAlpha = sourceAlpha;
		newNode = node;
		u = nextIndex;
		c = ( nextIndex + node->getParent()->neuronNumber() + 1 ) / 2;
	}

	// At this point newNode->neuronNumber() != 0 thus the parent has the next lower neuron number
	// If backpropagation to the starset in node is possible, but backpropagation to the next one is not possible, the source is identified
	if ( newNode->getParent()->neuronNumber() == u ) {
		std::pair<int, int> key = std::make_pair( newNode->getParent()->layerNumber(), u );
		mPreviousCounterexamples[key].insert( newSource );
		return std::make_tuple( Point<Number>(), Point<Number>(), newNode->getParent() );
	}

	return binarySearchTracing( newSource, newSourceAlpha, newNode, u, c );	 // rounding of integer division is correct
}

template <typename Number>
std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> ReachabilityTree<Number>::rememberingSearchTracing( const Point<Number>& source, const Point<Number>& sourceAlpha, ReachabilityNode<Number>* node ) {
	std::list<int> previousSources = mPreviousCounterexampleSources[node->getParent()->layerNumber()];

	if ( previousSources.empty() ) {
		return binarySearchTracing( source, sourceAlpha, node, 0, 0 );
	}

	// For very small layers, this method is not useful, therefore the default method is used
	if ( mNetwork.layers( node->getParent()->layerNumber() )->layerSize() <= 2 ) {
		return identifyCounterExampleOrigin( source, sourceAlpha, node, TRACING_STRATEGY::SINGLESTEP );
	}

	ReachabilityNode<Number>* ancestorNode;
	std::pair<Point<Number>, Point<Number>> origin;
	int layerNumber = node->getParent()->layerNumber();
	int nodeNumber = node->getParent()->neuronNumber();

	// If backpropagation to the start of the layer is possible, continue propagating through the other layers
	ancestorNode = getAncestor( node->getParent(), 0 );
	origin = traceSourceBack( source, sourceAlpha, layerNumber, nodeNumber, 0, ancestorNode->representation() );
	if ( 0 < origin.first.dimension() ) {
		return std::make_tuple( origin.first, origin.second, ancestorNode );
	}

	for ( std::list<int>::iterator it = previousSources.begin(); it != previousSources.end(); it++ ) {
		ancestorNode = getAncestor( node->getParent(), *it );
		origin = traceSourceBack( source, sourceAlpha, layerNumber, nodeNumber, *it, ancestorNode->representation() );
		// If backpropagation is possible, check if prev(it) is the source
		if ( 0 < origin.first.dimension() ) {
			if ( it == previousSources.begin() ) {
				return binarySearchTracing( origin.first, origin.second, ancestorNode, 0, ( *it ) / 2 );
			}
			ReachabilityNode<Number>* beforeSourceNode = getAncestor( ancestorNode, *std::prev( it ) + 1 );
			std::pair<Point<Number>, Point<Number>> tmpOrigin = traceSourceBack( origin.first, origin.second, layerNumber, ancestorNode->getParent()->neuronNumber(), *std::prev( it ) + 1, beforeSourceNode->representation() );
			if ( 0 < tmpOrigin.first.dimension() ) {
				return std::make_tuple( Point<Number>(), Point<Number>(), beforeSourceNode->getParent() );
			}
			return binarySearchTracing( origin.first, origin.second, ancestorNode, *std::prev( it ) + 1, ( ( *it ) + *std::prev( it ) + 1 ) / 2 );
		}
		if ( next( it ) == previousSources.end() ) {
			ReachabilityNode<Number>* beforeSourceNode = getAncestor( node->getParent(), ( *it ) + 1 );
			std::pair<Point<Number>, Point<Number>> tmpOrigin = traceSourceBack( source, sourceAlpha, layerNumber, nodeNumber, ( *it ) + 1, beforeSourceNode->representation() );
			if ( 0 < tmpOrigin.first.dimension() ) {
				return std::make_tuple( Point<Number>(), Point<Number>(), ancestorNode );
			}
			return binarySearchTracing( source, sourceAlpha, node, ( *it ) + 1, ( nodeNumber + ( *it ) ) / 2 + 1 );
		}
	}
	return binarySearchTracing( source, sourceAlpha, node, ( *previousSources.begin() ) + 1, ( nodeNumber + ( *previousSources.begin() ) ) / 2 + 1 );
}

template <typename Number>
std::tuple<Point<Number>, Point<Number>, ReachabilityNode<Number>*> ReachabilityTree<Number>::unsatCoreTracing( const Point<Number>& source, const Point<Number>& sourceAlpha, ReachabilityNode<Number>* node ) {
	if ( ( node->neuronNumber() == 0 && mNetwork.layers( node->getParent()->layerNumber() )->layerSize() <= 2 ) || ( node->neuronNumber() > 0 && mNetwork.layers( node->layerNumber() )->layerSize() <= 2 ) ) {
		return identifyCounterExampleOrigin( source, sourceAlpha, node, TRACING_STRATEGY::SINGLESTEP );
	}

	// attempt to trace through the whole layer
	std::shared_ptr<LayerBase<Number>> layer = mNetwork.layers( node->getParent()->layerNumber() );
	ReachabilityNode<Number>* newSourceNode = getAncestor( node->getParent(), 0 );
	std::tuple<int, Point<Number>, Point<Number>> result = layer->traceUnsatCore( source, sourceAlpha, node->getParent()->neuronNumber() + 1, 0, newSourceNode->representation() );
	if ( std::get<0>( result ) < 0 ) {
		return std::make_tuple( std::get<1>( result ), std::get<2>( result ), newSourceNode );
	}

	// use unsat cores to find an origin in the activation function sequence
	int upper = 0;
	int next = std::get<0>( result );
	Point<Number> newSource = source;
	Point<Number> newSourceAlpha = sourceAlpha;
	assert( node->getParent()->neuronNumber() + 1 > next && next >= upper );
	while ( node->getParent()->neuronNumber() + 1 > upper ) {
		newSourceNode = getAncestor( node->getParent(), next );
		mNumberOfTracings += 1;
		result = layer->traceUnsatCore( newSource, newSourceAlpha, node->getParent()->neuronNumber() + 1, next, newSourceNode->representation() );
		if ( std::get<0>( result ) < 0 ) {
			node = newSourceNode;
			next = upper;
			newSource = std::get<1>( result );
			newSourceAlpha = std::get<2>( result );
		} else if ( node->getParent()->neuronNumber() == next ) {
			std::pair<int, int> key = std::make_pair( node->getParent()->layerNumber(), next );
			mPreviousCounterexamples[key].insert( newSource );
			return std::make_tuple( Point<Number>(), Point<Number>(), newSourceNode );
		} else {
			upper = next;
			next = std::get<0>( result );
		}
	}

	return std::make_tuple( Point<Number>(), Point<Number>(), newSourceNode );
}

template <typename Number>
ReachabilityNode<Number>* ReachabilityTree<Number>::getAncestor( ReachabilityNode<Number>* node, const int neuronNumber ) const {
	if ( node->neuronNumber() == neuronNumber ) {
		return node;
	}
	assert( node->hasParent() && node->layerNumber() == node->getParent()->layerNumber() );
	return getAncestor( node->getParent(), neuronNumber );
}

template <typename Number>
std::pair<Point<Number>, Point<Number>> ReachabilityTree<Number>::traceSourceBack( const Point<Number>& source, const Point<Number>& sourceAlpha, const int parentLayer, const int parentNeuron, const Starset<Number>& parentSet, const Starset<Number>& currentSet ) {
	mNumberOfTracings += 1;
	std::shared_ptr<LayerBase<Number>> layer = mNetwork.layers( parentLayer );

	if ( layer->layerType() == NN_LAYER_TYPE::AFFINE ) {
		return layer->traceSourceBack( source, sourceAlpha, parentNeuron, parentSet, currentSet );
	}
	return layer->traceSourceBack( source, sourceAlpha, parentNeuron, parentSet );
}

// [upperIndex, lowerIndex] is inclusive
// For all dimensions in this interval (in the natural numbers) the backpropagation takes place!
// Thus if the source comes from neuron (n+1) and is propagated back to neuron n, the correct interval is [n,n]
template <typename Number>
std::pair<Point<Number>, Point<Number>> ReachabilityTree<Number>::traceSourceBack( const Point<Number>& source, const Point<Number>& sourceAlpha, int layerNumber, int lowerIndex, int upperIndex, const Starset<Number>& ancestorSet ) {
	mNumberOfTracings += 1;
	std::shared_ptr<LayerBase<Number>> layer = mNetwork.layers( layerNumber );
	return layer->traceSourceBack( source, sourceAlpha, lowerIndex, upperIndex, ancestorSet );
}

template <typename Number>
void ReachabilityTree<Number>::plotTree( ReachabilityNode<Number>* current, std::string filename ) const {
	mPlotter.clear();
	mPlotter.setFilename( filename + "_pdf.plt" );
	current->plot();

	for ( int i = 0; i < current->getNumberOfChildren(); i++ ) {
		// std::cout << "Plot child" << std::endl;
		plotTree( current->getChild( i ), filename + "." + std::to_string( i ) );
	}
}

}  // namespace reachability
}  // namespace hypro