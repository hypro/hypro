#include "ltiUrgencyHandler.h"

namespace hypro {

template <typename Representation>
std::vector<Representation> ltiUrgencyHandler<Representation>::urgentSetDifference(
        const std::vector<Representation>& segment, Transition<Number>* trans ) {
    std::vector<Representation> splitSegment;
    for ( const Representation& s : segment ) {
        std::vector<Representation> sDiff = setDifference( s, trans->getJumpEnablingSet() );
        splitSegment.insert( splitSegment.end(), sDiff.begin(), sDiff.end() );
    }
    return splitSegment;
}

template <class Representation>
Representation ltiUrgencyHandler<Representation>::cutoff( Representation const& set, Condition<Number> const& condition ) {

    if ( condition.isTrue() || set.empty() ) {
        return Representation::Empty();
    } else if ( condition.isFalse() || set.empty() ) {
        return set;
    } else if ( intersect( set, condition ).first == CONTAINMENT::FULL ) {
        return Representation::Empty();
    }
    std::size_t dimension = set.dimension();

    Optimizer<Number> conditionOptimizer( condition.getMatrix(), condition.getVector() );
    Optimizer<Number> vertexOptimizer;

    matrix_t<Number> mat( condition.getMatrix().rows() + 2 * dimension + 4, dimension + 2 );
    vector_t<Number> vec( mat.rows() );
    mat.bottomLeftCorner( condition.getMatrix().rows(), condition.getMatrix().cols() ) = condition.getMatrix();
    mat.bottomRightCorner( condition.getMatrix().rows(), 2 ) = matrix_t<Number>::Zero( condition.getMatrix().rows(), 2 );
    mat.topRows( 2 * dimension + 4 ) = matrix_t<Number>::Zero( 2 * dimension + 4, dimension + 2 );
    for ( std::size_t i = 0; i < dimension; ++i ) {
        mat( 2*i, i ) = -1;
        mat( 2*i + 1, i ) = 1;
    }
    // equations for lambda and 1 - lambda (sum equals 1, both >= 0)
    mat( 2 * dimension, dimension ) = 1;
    mat( 2 * dimension, dimension + 1 ) = 1;
    mat( 2 * dimension + 1, dimension ) = -1;
    mat( 2 * dimension + 1, dimension + 1 ) = -1;
    mat( 2 * dimension + 2, dimension ) = -1;
    mat( 2 * dimension + 3, dimension + 1 ) = -1;

    vec.tail( condition.getVector().rows() ) = condition.getVector();
    vec.head( 2 * dimension ) = vector_t<Number>::Zero( 2 * dimension );
    vec( 2 * dimension ) = 1;
    vec( 2 * dimension + 1 ) = -1;
    vec( 2 * dimension + 2 ) = 0;
    vec( 2 * dimension + 3 ) = 0;

    vertexOptimizer.setVector( vec );

    vector_t<Number> lambda = vector_t<Number>::Zero( dimension + 2 );
    lambda ( dimension + 1 ) = 1;

    std::vector<Point<Number>> oldVertices = set.vertices();
    std::vector<Point<Number>> newVertices;
    for ( const auto& vertex : oldVertices ) {
        if ( !conditionOptimizer.checkPoint( vertex ) ) {
            newVertices.push_back( vertex );
            continue;
        }
        std::vector<Point<Number>> replacement;
        for ( const auto& otherVertex : oldVertices ) {
            if ( conditionOptimizer.checkPoint( otherVertex ) ) continue;
            for ( std::size_t i = 0; i < dimension; ++i ) {
                mat( 2*i, dimension ) = vertex.at( i );
                mat( 2*i + 1, dimension ) = -vertex.at( i );
                mat( 2*i, dimension + 1 ) = otherVertex.at( i );
                mat( 2*i + 1, dimension + 1 ) = -otherVertex.at( i );
            }
            vertexOptimizer.setMatrix( mat );
            const auto res = vertexOptimizer.evaluate( lambda, false );
            std::cout << "Evaluation result: " << res.supportValue << "\n";
            assert( res.errorCode == SOLUTION::FEAS );
            assert( res.supportValue >= 0 && res.supportValue <= 1 );
            if ( res.supportValue == 0 ) {
                replacement = { vertex };
                break;
            }
            assert( res.supportValue < 1 );
            replacement.push_back( Point<Number>( res.optimumValue.head( dimension ) ) );
        }
        newVertices.insert( newVertices.end(), replacement.begin(), replacement.end() );
    }
    VPolytope<Number> newPol( newVertices );
    Representation res;
    convert( newPol, res );
    return res;
}

} // namespace hypro