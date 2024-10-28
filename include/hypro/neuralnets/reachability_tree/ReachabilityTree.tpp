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
std::vector<ReachabilityNode<Number>*> ReachabilityTree<Number>::leaves() const {}

template <typename Number>
unsigned short int ReachabilityTree<Number>::depth() const {
	unsigned short int depth = 1;
	ReachabilityNode<Number>* node = mRoot;
	while ( node->hasPosChild() || node->hasNegChild() ) {
		depth++;
		if ( node->hasPosChild() ) {
			node = node->getPosChild();
			continue;
		}
		if ( node->hasNegChild() ) {
			node = node->getNegChild();
			continue;
		}
	}
	return depth;
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
bool ReachabilityTree<Number>::isSubResultSafe( const std::vector<Starset<Number>>& subResult, const std::vector<HPolytope<Number>>& safeSets ) const {
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
	std::cout << "Search tree depth: " << this->depth() << std::endl;

	// else we start the refinement
	int ctx = 0;
	if ( createPlots )
		plotTree( mRoot, std::to_string( ctx ) + "-CEGAR_Reach_" );

	// repeat until we either find a real counterexample or we can verify that the network is safe
	// TODO: introduce a max number of iterations
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

			// // ================== FOR TESTING =================
			// std::cout << "Counterexample contained in the reachable set: " << chosenLeaf->representation().contains( candidate ) << std::endl;
			// for ( int i = 0; i < safeOutput.size(); i++ ) {
			// 	std::cout << "Countexample contained in safe set " << i << ": " << safeOutput[i].contains( candidate ) << std::endl;
			// }
			// // ================================================

			// identify the source neuron of the counterexample
			std::cout << "Identifying the source of the counterexample..." << std::endl;
			std::pair<Point<Number>, ReachabilityNode<Number>*> candidateSource = identifyCounterExampleSource( candidate, chosenLeaf );

			// TODO: check if the source is the last neuron we get a segmentation fault

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
		std::cout << "refinedJob created" << std::endl;
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
		if ( createPlots )
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
Point<Number> ReachabilityTree<Number>::produceCounterExampleCandidate( Starset<Number> set, std::vector<HPolytope<Number>> rejectionSets ) const {
	// TODO: this should be with random sampling (with the preference of picking the counterexample close or far away from the safe set but in the first (?) output set)
	// TODO: the sampling becomes very slow when the rejectionSet covers a high portion of the sampling set in this case some other algorithm for sampling should be used

	std::cout << "Trying to generate a counterexample candidate" << std::endl;

	// int sampling_trials = 10;

	// // try to find a counterexmaple with MC sampling
	// std::set<Point<Number>> samples = uniform_constrained_sampling( set, rejectionSets, 1, sampling_trials );
	// if ( samples.size() > 0 )
	// 	return *( samples.begin() );

	// // if the sampling does not work out for the whole set try to reduce it to multiple smaller sets
	// for ( auto rejectionSet : rejectionSets ) {
	// 	for ( auto constraint : rejectionSet.constraints() ) {
	// 		Starset<Number> intermediateSet = set.intersectHalfspace( Halfspace<Number>( -1 * constraint.normal(), -constraint.offset() ) );
	// 		if ( !intermediateSet.empty() ) {
	// 			std::set<Point<Number>> newSamples = uniform_constrained_sampling( intermediateSet, rejectionSets, 1, sampling_trials );
	// 			if ( newSamples.size() > 0 ) {
	// 				return *( newSamples.begin() );
	// 			}
	// 		}
	// 	}
	// }

	// // if sampling does not work at all, just try LP solving
	// for ( auto rejectionSet : rejectionSets ) {
	// 	for ( auto constraint : rejectionSet.constraints() ) {
	// 		// add the reversed constraint (with a little bloating)
	// 		Starset<Number> intermediateSet = set.intersectHalfspace( Halfspace<Number>( -1 * constraint.normal(), -constraint.offset() ) );
	// 		std::vector<Point<Number>> vertices = intermediateSet.vertices();
	// 		if ( vertices.size() > 0 ) {
	// 			vector_t<Number> middle_point = vertices[0].rawCoordinates();
	// 			for ( int i = 1; i < vertices.size(); i++ ) {
	// 				middle_point += vertices[i].rawCoordinates();
	// 			}
	// 			middle_point /= vertices.size();
	// 			return Point<Number>( middle_point );
	// 		}
	// 	}
	// }

	std::random_device rdev;
	std::mt19937 rgen( rdev() );

	while ( true ) {
		// Do only SAT checking on the set of constrains (set and not rejectionSet)
		// here we need to check for all combinations of the rejectionSet
		// i.e. if the rejection set is the form (c1_1 n c1_2 n ... n c1_k1) u (c2_1 n c2_2 n ... n c2_k2) u ... u (cm_1 n cm_2 n ... n cm_km)
		// then the set needs to be interesected with the negation of the previous set in DNF form
		// i.e. we intersect with (!c1_1 u !c1_2 u ... u !c1_k1) n (!c2_1 u !c2_2 u ... u !c2_k2) n ... n (!cm_1 u !cm_2 u ... u !cm_km)

		// std::cout << set << std::endl;
		// std::cout << "Empty:" << set.empty() << std::endl;

		Starset<Number> setCopy( set );
		for ( HPolytope<Number> poly : rejectionSets ) {
			std::uniform_int_distribution<int> idist( 0, poly.constraints().size() - 1 );  //(inclusive, inclusive)
			int ind = idist( rgen );													   // CONSIDER: you can pick not only one constraint but a subset of constraints (with each additional constraint the solution space gets smaller)
			Halfspace<Number> hspace = poly.constraints()[ind];
			vector_t<Number> normal = Number(-1) * hspace.normal();
			Number offset = Number(-1) * hspace.offset();
			setCopy = setCopy.intersectHalfspace( Halfspace<Number>( normal, offset ) );
		}

		bool empty = setCopy.empty();
		// std::cout << setCopy << std::endl;
		std::cout << "Empty:" << empty << std::endl;
		
		if ( empty )
			continue;

		// ================= METHOD 1 =================
		// // std::cout << "set: " << setCopy << std::endl;
		// Optimizer<Number> op( setCopy.shape(), setCopy.limits() );
		// auto res = op.getInternalPoint(true);

		// if ( res.errorCode == SOLUTION::FEAS ) {
		// 	// std::cout << "res: " << res << std::endl;
		// 	Point<Number> point( res.optimumValue );
		// 	bool consistent = op.checkPoint( point );
		// 	// std::cout << "Consistent: " << consistent << std::endl;
		// 	// std::cout << "Point dimension: " << point.dimension() << std::endl;

		// 	if ( consistent ) {
		// 		// std::cout << "Sampled point (inner polytope): " << point << std::endl;
		// 		// std::cout << "Sampled point (starset): " << point.affineTransformation( setCopy.generator(), setCopy.center() ) << std::endl;
		// 		int b;
		// 		std::cout << "Found a solution!" << std::endl;
		// 		// std::cin >> b;

		// 		std::cout << "Point is contained in polytope: " << HPolytope<Number>( setCopy.shape(), setCopy.limits() ).contains( point ) << std::endl;
		// 		std::cout << "Point is contained in starset: " << setCopy.contains( point.affineTransformation( setCopy.generator(), setCopy.center() ) ) << std::endl;

		// 		return point.affineTransformation( setCopy.generator(), setCopy.center() );
		// 	}
		// }
		// int a;
		// std::cout << "Could not find a solution now!" << std::endl;
		// // std::cin >> a;
		// ============================================

		// ================= METHOD 2 =================

		HPolytope<Number> currentPoly = setCopy.constraints();
		std::uniform_int_distribution<int> idist( 0, currentPoly.size() - 1 );  //(inclusive, inclusive)
		for(int tmp = 0; tmp < 10; tmp++) {
			int ind = idist( rgen );
			Optimizer<Number> op( setCopy.shape(), setCopy.limits() );

			hypro::vector_t<Number> dir_vect = currentPoly.constraints()[ind].normal();
			auto eval_low_result = op.evaluate( -1.0 * dir_vect, true );
			auto eval_high_result = op.evaluate( dir_vect, true );
			
			Point<Number> midPoint = Point<Number>((eval_low_result.optimumValue + eval_high_result.optimumValue) / 2.0);
			Point<Number> transformedPoint = midPoint.affineTransformation(setCopy.generator(), setCopy.center());

			if(setCopy.contains(transformedPoint)) {
				std::cout << "Solution found: " << transformedPoint << std::endl;
				return transformedPoint;
			}
			else {
				std::cout << "transormation was not included in the starset" << std::endl;
				std::cout << "Midpoint contained in HPoly: " << currentPoly.contains(midPoint) << std::endl;
				std::cout << "Transformedpoint contained in StarSet: " << setCopy.contains(transformedPoint) << std::endl;
				int a;
				std::cin >> a;
			}
		}
		// ============================================

	}

	// this line means that the sampling failed (should return a pair <bool, point> instead)
	return Point<Number>( { 0, 0 } );
}

template <typename Number>
ReachabilityNode<Number>* ReachabilityTree<Number>::getFirstNonEmptyLeaf() const {
	// TODO: if a leaf is empty then it should be safe (?)
	// TODO: what if there is no leaf which is not empty, then the whole tree should be safe (?) -> return pair <bool, Starset<Number>>
	for ( auto leaf : mLeaves ) {
		if ( !leaf->representation().empty() && !leaf->isSafe() ) {
			return leaf;
		}
	}
	return mLeaves[0];
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
		std::cout << "Node does not have parent" << std::endl;
		return std::make_pair( candidate, node );  // indicates that the backpropagated counterexample originates from the very first neuron
	}

	// std::cout << "Representation: " << node->representation() << std::endl;
	// std::cout << "Vertices: " << node->representation().vertices() << std::endl;
	// std::cout << "Candidate: " << candidate << std::endl;
	// // TODO: either with the containment check is wrong or it is a floating point error
	// std::cout << "Contains: " << node->representation().contains(candidate) << std::endl;

	// here: should I check if the candidate is contained in the current set or would the backpropagated candidate be in in the parent set?
	// if ( checkForwardContainment( candidate, parentLayer, parentNeuron, parentSet ) ) {	 // TODO: do not forget to check also the exact result of the relu function
	std::cout << "Checking containment" << std::endl;
	std::cout << "Representation is: " << node->representation() << std::endl;
	std::cout << "Candidate is: " << candidate << std::endl;
	if ( node->representation().contains( candidate ) ) {
		// if the counterexample candidate is still included in the current node go back to the previous node
		ReachabilityNode<Number>* parent = node->getParent();
		Point<Number> newCandidate = propagateCandidateBack( candidate, parent->layerNumber(), parent->neuronNumber(), parent->representation() );
		std::cout << "newCandidate: " << newCandidate << std::endl;
		return identifyCounterExampleSource( newCandidate, parent );
	} else {
		// std::cout << "Candidate: " << candidate << std::endl;
		// std::cout << "Layer: " << node->layerNumber() << " Neuron: " << node->neuronNumber() << std::endl;

		// if it is not included the current neuron introduces the counterexample
		return std::make_pair( candidate, node );  // the source of the counterexample
	}
}

template <typename Number>
Point<Number> ReachabilityTree<Number>::propagateCandidateBack( const Point<Number>& candidate, int parentLayer, int parentNeuron, const Starset<Number>& parentSet ) const {
	std::cout << "Propagating candidate back..." << std::endl;
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