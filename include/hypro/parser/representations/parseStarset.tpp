#include "../../representations/GeometricObjectBase.h"
#include "../../util/logging/Logger.h"

#include <iostream>
#include <cstdio>

namespace hypro
{

template <typename Number>
static Starset<Number> readStarFromFile( const char* filename ) {
    // Load file and check if it exists
    FILE* fstream = fopen( filename, "r" );
    assert( fstream != NULL );

    if ( fstream == NULL ) {
        FATAL( "hypro.parser.starset", "Could not open the input file" );
    }

    int n, m, p;  // star dimension; number of variables; number of constraints
    if ( fscanf( fstream, "%d %d %d", &n, &m, &p ) != 3 ) {
        FATAL( "hypro.parser.starset", "Error during reading the input file" )
    }
    vector_t<Number> center = vector_t<Number>( n );
    matrix_t<Number> basis = matrix_t<Number>( n, m );
    matrix_t<Number> shape = matrix_t<Number>( p, m );
    vector_t<Number> limits = vector_t<Number>( p );

    double tmp;
    for ( int i = 0; i < n; i++ ) {
        if ( fscanf( fstream, "%le", &tmp ) != 1 ) {
            FATAL( "hypro.parser.starset", "Error during reading the input file" )
        }
        center[i] = carl::convert<double, Number>( tmp );
    }

    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < m; j++ ) {
            if ( fscanf( fstream, "%le", &tmp ) != 1 ) {
                FATAL( "hypro.parser.starset", "Error during reading the input file" )
            }
            basis( i, j ) = carl::convert<double, Number>( tmp );
        }
    }

    for ( int i = 0; i < p; i++ ) {
        for ( int j = 0; j < m; j++ ) {
            if ( fscanf( fstream, "%le", &tmp ) != 1 ) {
                FATAL( "hypro.parser.starset", "Error during reading the input file" )
            }
            shape( i, j ) = carl::convert<double, Number>( tmp );
        }
    }

    for ( int i = 0; i < p; i++ ) {
        if ( fscanf( fstream, "%le", &tmp ) != 1 ) {
            FATAL( "hypro.parser.starset", "Error during reading the input file" )
        }
        limits[i] = carl::convert<double, Number>( tmp );
    }

    return Starset<Number>( center, shape, limits, basis );
}

template <typename Number>
static std::vector<Starset<Number>> readKStarsFromFile( const char* filename ) {
    // Load file and check if it exists
    FILE* fstream = fopen( filename, "r" );
    assert( fstream != NULL );

    if ( fstream == NULL ) {
        FATAL( "hypro.parser.starset", "Could not open the input file" );
    }

    int k;
    fscanf( fstream, "%d", &k );
    std::vector<Starset<Number>> inputStars;
    for(int l = 0; l < k; l++) {
        int n, m, p;  // star dimension; number of variables; number of constraints
        if ( fscanf( fstream, "%d %d %d", &n, &m, &p ) != 3 ) {
            FATAL( "hypro.parser.starset", "Error during reading the input file" )
        }
        vector_t<Number> center = vector_t<Number>( n );
        matrix_t<Number> basis = matrix_t<Number>( n, m );
        matrix_t<Number> shape = matrix_t<Number>( p, m );
        vector_t<Number> limits = vector_t<Number>( p );

        double tmp;
        for ( int i = 0; i < n; i++ ) {
            if ( fscanf( fstream, "%le", &tmp ) != 1 ) {
                FATAL( "hypro.parser.starset", "Error during reading the input file" )
            }
            center[i] = carl::convert<double, Number>( tmp );
        }

        for ( int i = 0; i < n; i++ ) {
            for ( int j = 0; j < m; j++ ) {
                if ( fscanf( fstream, "%le", &tmp ) != 1 ) {
                    FATAL( "hypro.parser.starset", "Error during reading the input file" )
                }
                basis( i, j ) = carl::convert<double, Number>( tmp );
            }
        }

        for ( int i = 0; i < p; i++ ) {
            for ( int j = 0; j < m; j++ ) {
                if ( fscanf( fstream, "%le", &tmp ) != 1 ) {
                    FATAL( "hypro.parser.starset", "Error during reading the input file" )
                }
                shape( i, j ) = carl::convert<double, Number>( tmp );
            }
        }

        for ( int i = 0; i < p; i++ ) {
            if ( fscanf( fstream, "%le", &tmp ) != 1 ) {
                FATAL( "hypro.parser.starset", "Error during reading the input file" )
            }
            limits[i] = carl::convert<double, Number>( tmp );
        }

        inputStars.push_back(Starset<Number>( center, shape, limits, basis ));
    }
    return inputStars;
}

} // namespace hypro
