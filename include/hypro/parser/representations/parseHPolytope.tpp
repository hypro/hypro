#include "../../representations/GeometricObjectBase.h"
#include "../../util/logging/Logger.h"

#include <iostream>
#include <cstdio>

namespace hypro
{

template <typename Number>
static HPolytope<Number> readHpolytopeFromFile( const char* filename ) {
    // Load file and check if it exists
    FILE* fstream = fopen( filename, "r" );
    assert( fstream != NULL );

    if ( fstream == NULL ) {
        FATAL( "hypro.parser.hpolytope", "Could not open the input file" );
    }

    int n, m;  // number of constraints, hpolytope dimension;
    if ( fscanf( fstream, "%d %d", &n, &m ) != 2 ) {
        FATAL( "hypro.parser.hpolytope", "Error during reading the input file" )
    }

    matrix_t<Number> shape = matrix_t<Number>( n, m );
    vector_t<Number> limits = vector_t<Number>( n );

    double tmp;
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < m; j++ ) {
            if ( fscanf( fstream, "%le", &tmp ) != 1 ) {
                FATAL( "hypro.parser.hpolytope", "Error during reading the input file" )
            }
            shape( i, j ) = carl::convert<double, Number>( tmp );
        }
    }

    for ( int i = 0; i < n; i++ ) {
        if ( fscanf( fstream, "%le", &tmp ) != 1 ) {
            FATAL( "hypro.parser.hpolytope", "Error during reading the input file" )
        }
        limits[i] = carl::convert<double, Number>( tmp );
    }

    return HPolytope<Number>( shape, limits );
}

template <typename Number>
static std::vector<HPolytope<Number>> readKHpolytopesFromFile( const char* filename ) {
    // Load file and check if it exists
    FILE* fstream = fopen( filename, "r" );
    assert( fstream != NULL );

    if ( fstream == NULL ) {
        FATAL( "hypro.parser.hpolytope", "Could not open the input file" );
    }

    int k;
    fscanf( fstream, "%d", &k );
    std::vector<HPolytope<Number>> inputHPolytopes;
    for(int l = 0; l < k; l++) {
        int n, m;  // number of constraints, hpolytope dimension;
        if ( fscanf( fstream, "%d %d", &n, &m ) != 2 ) {
            FATAL( "hypro.parser.hpolytope", "Error during reading the input file" )
        }

        matrix_t<Number> shape = matrix_t<Number>( n, m );
        vector_t<Number> limits = vector_t<Number>( n );

        double tmp;
        for ( int i = 0; i < n; i++ ) {
            for ( int j = 0; j < m; j++ ) {
                if ( fscanf( fstream, "%le", &tmp ) != 1 ) {
                    FATAL( "hypro.parser.hpolytope", "Error during reading the input file" )
                }
                shape( i, j ) = carl::convert<double, Number>( tmp );
            }
        }

        for ( int i = 0; i < n; i++ ) {
            if ( fscanf( fstream, "%le", &tmp ) != 1 ) {
                FATAL( "hypro.parser.hpolytope", "Error during reading the input file" )
            }
            limits[i] = carl::convert<double, Number>( tmp );
        }

        inputHPolytopes.push_back(HPolytope<Number>( shape, limits ));
    }
    return inputHPolytopes;
}

} // namespace hypro
