#include "ReachabilityNode.h"

namespace hypro {
namespace reachability {

template <typename Number>
ReachabilityNode<Number>::ReachabilityNode()
	: mPlotter( hypro::Plotter<Number>::getInstance() ) {}

template <typename Number>
ReachabilityNode<Number>::ReachabilityNode( Starset<Number> representation, NN_REACH_METHOD method, int layerNumber, int neuronNumber )
	: mRepresentation( representation )
	, mMethod( method )
	, mLayerNumber( layerNumber )
	, mNeuronNumber( neuronNumber )
	, mIsLeaf( false )
	, mIsSafe( false )
	, mIsComputed( false )
	, mHasParent( false )
	, mChildren(std::vector<ReachabilityNode<Number>*>())
	, mPlotter( hypro::Plotter<Number>::getInstance() )
	, mCounterExample(Point<Number>()) {}

// template <typename Number>
// ReachabilityNode<Number>::~ReachabilityNode() {
// 	if ( !mIsLeaf ) {
// 		if ( mHasPosChild ) {
// 			mHasPosChild = false;
// 			delete mPosChild;
// 		}
// 		if ( mHasNegChild ) {
// 			mHasNegChild = false;
// 			delete mNegChild;
// 		}
// 	}
// }

template <typename Number>
bool ReachabilityNode<Number>::isLeaf() const {
	return mIsLeaf;
}

template <typename Number>
void ReachabilityNode<Number>::setLeaf( bool isLeaf ) {
	mIsLeaf = isLeaf;
}

template <typename Number>
bool ReachabilityNode<Number>::isSafe() const {
	return mIsSafe;
}

template <typename Number>
void ReachabilityNode<Number>::setSafe( bool isSafe ) {
	mIsSafe = isSafe;
}

template <typename Number>
bool ReachabilityNode<Number>::isComputed() const {
	return mIsComputed;
}

template <typename Number>
void ReachabilityNode<Number>::setComputed( bool isComputed ) {
	mIsComputed = isComputed;
}

template <typename Number>
bool ReachabilityNode<Number>::hasParent() const {
	return mHasParent;
}

template <typename Number>
void ReachabilityNode<Number>::setHasParent( bool hasParent ) {
	mHasParent = hasParent;
}

template <typename Number>
bool ReachabilityNode<Number>::hasChild(int index) const{
	return 0 <= index && index < mChildren.size();
}

template <typename Number>
int ReachabilityNode<Number>::getNumberOfChildren() const{
	return mChildren.size();
}

template <typename Number>
ReachabilityNode<Number>* ReachabilityNode<Number>::getParent() const {
	return mParent;
}

template <typename Number>
void ReachabilityNode<Number>::setParent( ReachabilityNode<Number>* parent ) {
	mHasParent = true;
	mParent = parent;
}

template <typename Number>
ReachabilityNode<Number>* ReachabilityNode<Number>::getChild(int index) const {
	assert(0 <= index && index < mChildren.size());
	return mChildren[index];
}

template <typename Number>
void ReachabilityNode<Number>::setChild( int index, ReachabilityNode<Number>* child ){
	assert(0 <= index && index < mChildren.size());
	mChildren[index] = child;
}

template <typename Number>
void ReachabilityNode<Number>::addChild(ReachabilityNode<Number>* child ){
	mChildren.push_back(child);
}

template <typename Number>
void ReachabilityNode<Number>::removeAllChildren(){
	mChildren.clear();
}

template <typename Number>
int ReachabilityNode<Number>::layerNumber() const {
	return mLayerNumber;
}

template <typename Number>
int ReachabilityNode<Number>::neuronNumber() const {
	return mNeuronNumber;
}

template <typename Number>
NN_REACH_METHOD ReachabilityNode<Number>::method() const {
	return mMethod;
}

template <typename Number>
void ReachabilityNode<Number>::setMethod( NN_REACH_METHOD method ) {
	mMethod = method;
}

template <typename Number>
Starset<Number> ReachabilityNode<Number>::representation() const {
	return mRepresentation;
}

template <typename Number>
void ReachabilityNode<Number>::setRepresentation( const Starset<Number>& representation ) {
	mRepresentation = representation;
}

template <typename Number>
bool ReachabilityNode<Number>::hasCounterExample() const{
	return mCounterExample.dimension() > 0;
} 
template <typename Number>
Point<Number> ReachabilityNode<Number>::getCounterExample() const{
	return mCounterExample;
}

template <typename Number>
Point<Number> ReachabilityNode<Number>::_checkSafetyRandom(Starset<Number> set, const std::vector<matrix_t<Number>> safeSetMatrices, const std::vector<vector_t<Number>> safeSetVectors, int iterations) const {
	//Try to generate a counterexample
    std::random_device rdev;
	std::mt19937 rgen( rdev() );
	std::cout << "Trying to produce a counterexample for " << iterations << " iterations..." << std::endl;
	while ( 0 < iterations) {
        iterations--;
        //Create a starset of containing potential counterexamples
        Starset<Number> setCopy( set ); 
		// for ( HPolytope<Number> poly : rejectionSets ) {
		// 	std::uniform_int_distribution<int> idist( 0, poly.constraints().size() - 1 );
		// 	int ind = idist( rgen );				
		// 	Halfspace<Number> hspace = poly.constraints()[ind];
        //     //Note:
        //     // The border of the Halfspace and the starset is possibly contained in the rejectionSets!
        //     // This is not often a problem, because we try to take a center point as a counterexample
		// 	vector_t<Number> normal = Number(-1) * hspace.normal();
		// 	Number offset = Number(-1) * hspace.offset();
		// 	setCopy = setCopy.intersectHalfspace( Halfspace<Number>( normal, offset ) );
		// }

		for (unsigned i = 0; i < safeSetMatrices.size(); i++) {
			std::uniform_int_distribution<int> idist( 0, safeSetMatrices[i].rows() - 1 );
			int ind = idist( rgen );				
            //Note:
            // The border of the Halfspace and the starset is possibly contained in the rejectionSets!
            // This is not often a problem, because we try to take a center point as a counterexample
			vector_t<Number> normal = Number(-1) * safeSetMatrices[i].row( ind );
			Number offset = Number(-1) * safeSetVectors[i][ind];
			setCopy = setCopy.intersectHalfspace( Halfspace<Number>( normal, offset ) );
		}

        if ( setCopy.empty() ){
            continue;
        }

        //Find a potential counterexample in the generated starset
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

            //Ensure point is contained in the starset and not contained in any rejectionSet
            bool isCounterexample = true;
            // for (int i = 0; i < rejectionSets.size() && isCounterexample; i++){
            //     vector_t<Number> v = (rejectionSets[i].matrix() * transformedPoint.rawCoordinates());
            //     isCounterexample = isCounterexample && !( v <= rejectionSets[i].vector());                    
            // }
			for (int i = 0; i < safeSetMatrices.size() && isCounterexample; i++){
                vector_t<Number> v = (safeSetMatrices[i] * transformedPoint.rawCoordinates());
                isCounterexample = isCounterexample && !( v <= safeSetVectors[i]);                    
            }
			if(isCounterexample && setCopy.contains(transformedPoint)) {	
                std::cout << "Found counterexample in iteration " << iterations << std::endl;
				return transformedPoint;
			}
		}
    }
	return _checkSafetyZ3(set, safeSetMatrices, safeSetVectors);
}
 
template <typename Number>
Point<Number> ReachabilityNode<Number>::_checkSafetyZ3(Starset<Number> set, const std::vector<matrix_t<Number>> safeSetMatrices, const std::vector<vector_t<Number>> safeSetVectors ) const { 
	std::cout << "Producing a counterexample with z3..." << std::endl;
	
	// if a counterexample exists, result contains an element in the predicate of set
	// this predicate corresponds to a point in set that is not element of any HPolytope in rejectionSets
	EvaluationResult<Number> result = z3GetCounterexample( set.shape(), set.limits(), set.generator(), set.center(), safeSetMatrices, safeSetVectors);

    if (result.errorCode == SOLUTION::FEAS){
        // A counterexample exists
        return Point<Number>(set.generator() * result.optimumValue + set.center());
    }
    
	return Point<Number>(); 
}

template <typename Number>
Point<Number> ReachabilityNode<Number>::_checkSafetyZ3SmallRepresentation(Starset<Number> set,  const std::vector<matrix_t<Number>> safeSetMatrices, const std::vector<vector_t<Number>> safeSetVectors ) const { 
	std::cout << "Producing a counterexample with z3..." << std::endl;
	
	// if a counterexample exists, result contains an element in the predicate of set
	// this predicate corresponds to a point in set that is not element of any HPolytope in rejectionSets
	EvaluationResult<Number> result = z3GetCounterexampleSmall( set.shape(), set.limits(), set.generator(), set.center(), safeSetMatrices, safeSetVectors);
	
	switch(result.errorCode){
		case SOLUTION::FEAS:	
			return Point<Number>(set.generator() * result.optimumValue + set.center());
		case SOLUTION::INFEAS:
			return Point<Number>();
		default: //z3GetCounterexampleSmall uses an incomlete method for a mixed integer and rational problem and can thus return UNKOWN
			return _checkSafetyZ3(set, safeSetMatrices, safeSetVectors);		
	}
}

template <typename Number>
bool ReachabilityNode<Number>::checkSafeRecursive( Starset<Number> currentSet, const std::vector<matrix_t<Number>> safeSetMatrices, const std::vector<vector_t<Number>> safeSetVectors, COUNTEREXAMPLE_STRATEGY strategy ) {
	
	Point<Number> counterexample;
	switch(strategy){
		case COUNTEREXAMPLE_STRATEGY::Z3_BASIC: 
			counterexample = _checkSafetyZ3(currentSet, safeSetMatrices, safeSetVectors);
			break;
		case COUNTEREXAMPLE_STRATEGY::RANDOM:
			counterexample = _checkSafetyRandom(currentSet, safeSetMatrices, safeSetVectors, 10);			
			break;
		case COUNTEREXAMPLE_STRATEGY::Z3_SMALL_REPRESENTATION:
			counterexample = _checkSafetyZ3SmallRepresentation(currentSet, safeSetMatrices, safeSetVectors);
			break;
		default:
			assert(false && "Not a known strategy to find counterexamples");
			break;
	}
	
	if(counterexample.dimension() > 0){
		mCounterExample = counterexample;
		return false;
	}

	return true;
}

template <typename Number>
bool ReachabilityNode<Number>::checkSafe( const std::vector<matrix_t<Number>> safeSetMatrices, const std::vector<vector_t<Number>> safeSetVectors, COUNTEREXAMPLE_STRATEGY strategy) {
	// if the node is a leaf, we should check if the representation is only in the safe region (which is a non-convex set, DNF)
	if ( mIsLeaf) {
		return hasCounterExample() ? false : checkSafeRecursive( mRepresentation, safeSetMatrices, safeSetVectors, strategy);
	} 

	// if the node is not a leaf, then it safetiness depends on the children
	for (ReachabilityNode<Number>* child : mChildren){
		if(!(child->checkSafe(safeSetMatrices, safeSetVectors, strategy))){
			return false;
		}
	}

	return true;
}

template <typename Number>
void ReachabilityNode<Number>::plot( bool holdOn, size_t color ) const {
	// std::cout << mRepresentation << std::endl;
	std::vector<hypro::Point<Number>> vertices = mRepresentation.vertices();
	mPlotter.addObject( vertices, color );
	if ( !holdOn ) {
		mPlotter.plot2d( PLOTTYPE::png );
	}
}

}  // namespace reachability
}  // namespace hypro
