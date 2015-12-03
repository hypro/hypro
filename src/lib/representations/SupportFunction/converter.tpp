/**
 * Specialization for a converter to a support function.
 * @file converter.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @since	2015-05-13
 * @version	2015-05-13
 */

#include "converter.h"

namespace hypro{
        // conversion from Box to support function
        template <typename Number>
        static bool convert( const hypro::Box<Number>& _source, hypro::SupportFunction<Number>& _target ) {
                unsigned dim = _source.dimension();                                                     //gets dimension of box
                assert( dim >= 1);                                                                      //only continue if dimension is at least 1

                matrix_t<Number> directions = matrix_t<Number>::Zero( 2 * dim, dim );                   //initialize normal matrix as zero matrix with 2*dim rows and dim columns
                for ( unsigned i = 0; i < dim; ++i ) {                                                  //for every dimension:
                        directions( 2 * i, i ) = -1;
                        directions( 2 * i + 1, i ) = 1;                                                 //write fixed entries (because of box) into the normal matrix (2 each column)
                }

                vector_t<Number> distances = vector_t<Number>( 2 * dim );                               //initialize distance vector with 2*dim rows

                std::vector<carl::Interval<Number>> intervals = _source.boundaries();                   //gets intervals of box
                for ( unsigned i = 0; i < dim; ++i ) {                                                  //for every dimension:
                        distances( 2 * i ) = -intervals[i].lower();
                        distances( 2 * i + 1 ) = intervals[i].upper();                                  //write inverted lower bound values and upper bound values into the distance vector
                }

                _target = SupportFunction<Number>( SF_TYPE::POLY, directions, distances); //constructs a support function with normal matrix and distance vector

                return true;
        }

        // conversion from V-Polytope to support function
        template <typename Number>
        static bool convert( const hypro::VPolytope<Number>& _source, hypro::SupportFunction<Number>& _target ) {
                HPolytope<Number> temp = HPolytope<Number>(_source);                                   //converts the source object into a h-polytope
                typename HPolytope<Number>::HyperplaneVector planes = temp.constraints();              //gets planes from the converted object
                assert( !planes.empty() );                                                             //ensures that nonempty planes got fetched before continuing

                _target = SupportFunction<Number>( SF_TYPE::POLY, planes );             //constructs a support function with the received planes

                return true;
        }



        // conversion from H-polytope to support function
        template <typename Number>
        static bool convert( const hypro::HPolytope<Number>& _source, hypro::SupportFunction<Number>& _target ) {
                typename HPolytope<Number>::HyperplaneVector planes = _source.constraints();              //gets planes from the source object
                assert( !planes.empty() );                                                                //ensures that nonempty planes got fetched before continuing

                _target = SupportFunction<Number>( SF_TYPE::POLY, planes );                //constructs a support function with the received planes

                return true;
        }
        // TODO conversion from Zonotope to support function
        template <typename Number>
        static bool convert( const hypro::Zonotope<Number>& _source, hypro::SupportFunction<Number>& _target ) {


                return true;
        }

/*                     Zonotope<Number> tmp = _source.intervalHull();
                std::vector<vector_t<Number>> vertices = tmp.computeZonotopeBoundary();
                assert( !vertices.empty() );
                vector_t<Number> minima = vertices[0];
                vector_t<Number> maxima = vertices[0];

                        for ( unsigned i = 0; i < vertices.size(); ++i ) {
                                for ( unsigned d = 0; d < _source.dimension(); ++d ) {
                                        minima( d ) = vertices[i]( d ) < minima( d ) ? vertices[i]( d ) : minima( d );
                                	maxima( d ) = vertices[i]( d ) > maxima( d ) ? vertices[i]( d ) : maxima( d );
                                        assert( minima( d ) <= maxima( d ) );
                                }
                        }

                typename Box<Number>::intervalMap intervals;
                for ( unsigned i = 0; i < _source.dimension(); ++i ) {
                        intervals.insert( std::make_pair( hypro::VariablePool::getInstance().carlVarByIndex( i ),
										  carl::Interval<Number>( minima( i ), maxima( i ) ) ) );
                }

template<typename Number>
hypro::SupportFunctionContent<Number> convert(const hypro::Polytope<Number>& _source) {
	hypro::Polytope<Number> tmp = _source;
	std::vector<Point<Number>> points = tmp.points();
	assert(!points.empty());

	vector_t<Number> minima = points[0].rawCoordinates();
	vector_t<Number> maxima = points[0].rawCoordinates();

	for(unsigned i=0; i<points.size(); ++i) {
		for(unsigned d=0; d<_source.dimension(); ++d) {
			minima(d) = points[i].rawCoordinates()(d) < minima(d) ? points[i].rawCoordinates()(d) : minima(d);
			maxima(d) = points[i].rawCoordinates()(d) > maxima(d) ? points[i].rawCoordinates()(d) : maxima(d);
			assert(minima(d) <= maxima(d));
		}
	}

	typename Box<Number>::intervalMap intervals;
	for(unsigned i=0; i<_source.dimension(); ++i) {
		intervals.insert(std::make_pair(hypro::VariablePool::getInstance().carlVarByIndex(i),
carl::Interval<Number>(minima(i), maxima(i))));
	}

	return Box<Number>(intervals);
}
*/


} //namespace