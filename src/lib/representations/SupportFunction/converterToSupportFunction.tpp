/**
 * Specialization for a converter to a support function.
 * @file converterToSupportFunction.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @since	2015-05-13
 * @version	2016-01-28
 */

#include "converterToSupportFunction.h"

namespace hypro{
        // conversion from support function to support function
        template <typename Number>
        static bool convert( const hypro::SupportFunction<Number>& _source, hypro::SupportFunction<Number>& _target, const CONV_MODE mode){
            _target = _source;
            return true;
        }

        // conversion from box to support function
        template <typename Number>
        static bool convert( const hypro::Box<Number>& _source, hypro::SupportFunction<Number>& _target, const CONV_MODE mode) {
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

                _target = SupportFunction<Number>( SF_TYPE::POLY, directions, distances);               //constructs a support function with normal matrix and distance vector

                return true;
        }

        // conversion from V-Polytope to support function
        template <typename Number>
        static bool convert( const hypro::VPolytope<Number>& _source, hypro::SupportFunction<Number>& _target, const CONV_MODE mode) {
                HPolytope<Number> temp;
                convert(_source, temp);                                                                //converts the source object into a h-polytope
                typename HPolytope<Number>::HyperplaneVector planes = temp.constraints();              //gets planes from the converted object
                assert( !planes.empty() );                                                             //ensures that nonempty planes got fetched before continuing

                _target = SupportFunction<Number>( SF_TYPE::POLY, planes );                            //constructs a support function with the received planes

                return true;
        }



        // conversion from H-polytope to support function
        template <typename Number>
        static bool convert( const hypro::HPolytope<Number>& _source, hypro::SupportFunction<Number>& _target, const CONV_MODE mode) {
                typename HPolytope<Number>::HyperplaneVector planes = _source.constraints();            //gets planes from the source object
                assert( !planes.empty() );                                                              //ensures that nonempty planes got fetched before continuing

                _target = SupportFunction<Number>( SF_TYPE::POLY, planes );                             //constructs a support function with the received planes

                return true;
        }

        // TODO more efficient conversion (if possible ; detour via V-Polytope seems inefficient)
        // conversion from Zonotope to support function
        template <typename Number>
        static bool convert( const hypro::Zonotope<Number>& _source, hypro::SupportFunction<Number>& _target, const CONV_MODE mode) {
                typename std::vector<hypro::vector_t<Number>> vertices = _source.vertices();           //computes the vertices from the source zonotope
                assert (!vertices.empty() );                                                           //checks if any vertices were received

                VPolytope<Number> temp = VPolytope<Number>(vertices);                                  //builds a V-Polytope with the received vertices
                HPolytope<Number> temp2;
           		convert(temp, temp2);                                                                  //converts the V-Polytope into its H-representation
                typename HPolytope<Number>::HyperplaneVector planes = temp2.constraints();             //gets planes from the converted object
                assert( !planes.empty() );                                                             //ensures that nonempty planes got fetched before continuing

                _target = SupportFunction<Number>( SF_TYPE::POLY, planes );                            //constructs a support function with the received planes

                return true;
        }

} //namespace