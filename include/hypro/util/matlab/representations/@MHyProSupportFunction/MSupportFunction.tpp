#include "MSupportFunction.h"

void MSupportFunction::new_points( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MSupportFunction - new_points: One output is expected." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MSupportFunction - new_points: At least one argument is missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MSupportFunction - new_points: One or more input arguments were ignored." );

	mxArray* m_in_points;
	double* in_points;
	const mwSize* dims;
	int cols, rows;

	dims = mxGetDimensions( prhs[2] );
	cols = (const int)dims[1];
	rows = (const int)dims[0];
	m_in_points = mxDuplicateArray( prhs[2] );

	const std::vector<hypro::Point<double>> points = ObjectHandle::mPointsVector2Hypro( m_in_points, rows, cols );
	// plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>(new hypro::SupportFunction<double>(points));
	mexErrMsgTxt( "NOT IMPLEMENTED" );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "new_points input:\n" );
	// mexPrintf( "points:\n" );
	// for ( int i = 0; i < points.size(); i++ ) {
	// 	hypro::Point<double> point = points[i];
	// 	mexPrintf( "point %d:\n", i );
	// 	int len = point.dimension();
	// 	for ( int i = 0; i < len; i++ ) {
	// 		mexPrintf( " %f", point[i] );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "\n" );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MSupportFunction::new_intervals( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MSupportFunction - new_intervals: One output is expected." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MSupportFunction - new_intervals: At least one argument is missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MSupportFunction - new_intervals: At least one argument were ignored." );

	const mwSize* dims;
	int cols;
	dims = mxGetDimensions( prhs[2] );
	cols = (const int)dims[0];

	std::vector<carl::Interval<double>> intervals = ObjectHandle::mIntervals2Hypro( prhs[2], 2, cols );
	plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>( new hypro::SupportFunction<double>( intervals ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "new_intervals input:\n" );
	// mexPrintf( "intervals:\n" );
	// for ( int j = 0; j < intervals.size(); j++ ) {
	// 	carl::Interval<double> inter = intervals[j];
	// 	mexPrintf( "[%d, %d]\n", inter.lower(), inter.upper() );
	// }
	// mexPrintf( "\n" );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MSupportFunction::new_halfspaces( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MSupportFunction - new_halfspaces: One output is expected." );
	if ( nrhs < 4 ) mexErrMsgTxt( "MSupportFunction - new_halfspaces: At least one argument is missing." );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MSupportFunction - new_halfspaces: At least one argument were ignored." );

	mxArray *m_in_matrix, *m_in_vector;
	const mwSize *mat_dims, *vec_dims;
	int mat_cols, mat_rows, vec_len;

	mat_dims = mxGetDimensions( prhs[2] );
	vec_dims = mxGetDimensions( prhs[3] );
	mat_cols = (int)mat_dims[0];
	mat_rows = (int)mat_dims[1];
	vec_len = (int)vec_dims[0];
	m_in_matrix = mxDuplicateArray( prhs[2] );
	m_in_vector = mxDuplicateArray( prhs[3] );

	std::vector<hypro::Halfspace<double>> halfspaces =
		  ObjectHandle::mHalfspaces2Hypro( m_in_matrix, m_in_vector, mat_rows, mat_cols, vec_len );
	plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>( new hypro::SupportFunction<double>( halfspaces ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "new_halfSpaces input:\n" );
	// for ( int i = 0; i < halfspaces.size(); i++ ) {
	// 	hypro::vector_t<double> normal = halfspaces[i].normal();
	// 	double offset = halfspaces[i].offset();
	// 	mexPrintf( "normal %d:", i );
	// 	for ( int j = 0; j < normal.rows(); j++ ) {
	// 		mexPrintf( " %f", normal( j ) );
	// 	}
	// 	mexPrintf( "\noffset: %d\n", offset );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MSupportFunction::cleanUp( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs < 1 ) mexErrMsgTxt( "MSupportFunction - cleanUp: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MSupportFunction - cleanUp: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MSupportFunction - cleanUp: At least one argument were ignored." );

	hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[2] );
	temp->cleanUp();
}

void MSupportFunction::depth( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs < 1 ) mexErrMsgTxt( "MSupportFunction - depth: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MSupportFunction - depth: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MSupportFunction - depth: At least one argument were ignored." );

	hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[2] );
	unsigned depth = temp->depth();
	plhs[0] = mxCreateDoubleScalar( depth );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "depth output:\n" );
	// mexPrintf( "depth: %d\n", depth );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MSupportFunction::operationCount( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MSupportFunction - operationCount: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MSupportFunction - operationCount: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MSupportFunction - operationCount: At least one argument were ignored." );

	hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[2] );
	unsigned count = temp->operationCount();
	plhs[0] = mxCreateDoubleScalar( count );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "operationCount output:\n" );
	// mexPrintf( "count: %d\n", count );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MSupportFunction::type( int nlhs, mxArray* plhs[], int rhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MSupportFunction - type: Expecting one output value!" );
	std::string ans = "MHyProSupportFunction";
	plhs[0] = mxCreateString( ans.c_str() );
}

void MSupportFunction::contains_vec( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MSupportFunction - contains_vector: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MSupportFunction - contains_vector: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MSupportFunction - contains_vector: At least one argument were ignored." );

	const mwSize* dims;
	int vec_len;
	dims = mxGetDimensions( prhs[3] );
	vec_len = (const int)dims[0];
	hypro::SupportFunction<double>* obj = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[2] );
	const hypro::vector_t<double> hy_vector = ObjectHandle::mVector2Hypro( prhs[3], vec_len );

	const bool ans = obj->contains( hy_vector );
	plhs[0] = mxCreateLogicalScalar( ans );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "contains_vec input:\n" );
	// for ( int i = 0; i < hy_vector.rows(); i++ ) {
	// 	mexPrintf( " %f", hy_vector( i ) );
	// }
	// mexPrintf( "\noutput:\n" );
	// if ( ans ) {
	// 	mexPrintf( "contains\n" );
	// } else {
	// 	mexPrintf( "not contained\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MSupportFunction::contains_dir( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs < 1 ) mexErrMsgTxt( "MSupportFunction - contains_dir: Expecting one output value!" );
	if ( nrhs < 5 ) mexErrMsgTxt( "MSupportFunction - contains_dir: One or more arguments are missing!" );
	if ( nrhs > 5 ) mexWarnMsgTxt( "MSupportFunction - contains_dir: At least one argument were ignored." );

	hypro::SupportFunction<double>* sfct_1 = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[2] );
	hypro::SupportFunction<double>* sfct_2 = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[3] );
	std::size_t directions = (std::size_t)mxGetScalar( prhs[4] );

	const bool ans = sfct_1->contains( *sfct_2, directions );
	plhs[0] = mxCreateLogicalScalar( ans );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "contains_dir input:\n" );
	// mexPrintf( "directions: %d\n", (double)directions );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MSupportFunction::scale( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs < 1 ) mexErrMsgTxt( "MSupportFunction - scale: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MSupportFunction - scale: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MSupportFunction - scale: At least one argument were ignored." );

	hypro::SupportFunction<double>* obj = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[2] );
	const double factor = (double)mxGetScalar( prhs[3] );

	hypro::SupportFunction<double> temp = obj->scale( factor );
	plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>( new hypro::SupportFunction<double>( temp ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "scalse input:\n" );
	// mexPrintf( "factor: %d\n", factor );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MSupportFunction::swap( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 5 ) mexErrMsgTxt( "MSupportFunction - swap: One or more arguments are missing!" );
	if ( nrhs > 5 ) mexWarnMsgTxt( "MSupportFunction - swap: At least one argument were ignored." );

	hypro::SupportFunction<double>* origin = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[2] );
	hypro::SupportFunction<double>* sfct_1 = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[3] );
	hypro::SupportFunction<double>* sfct_2 = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[4] );

	origin->swap( *sfct_1, *sfct_2 );
}

void MSupportFunction::forceLinTransReduction( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MSupportFunction - forcedLinTransReduction: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MSupportFunction - forcedLinTransReduction: At least one argument were ignored." );

	hypro::SupportFunction<double>* sfct = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[2] );
	sfct->forceLinTransReduction();

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "forceLinTransReduction output:\n" );
	// hypro::matrix_t<double> mat = sfct->matrix();
	// hypro::vector_t<double> vec = sfct->vector();
	// mexPrintf( "matrix:\n" );
	// for ( int i = 0; i < mat.rows(); i++ ) {
	// 	for ( int j = 0; j < mat.cols(); j++ ) {
	// 		mexPrintf( " %f", mat( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "\nvector: " );
	// for ( int i = 0; i < vec.rows(); i++ ) {
	// 	mexPrintf( " %f", vec( i ) );
	// }
	// mexPrintf( "\n" );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MSupportFunction::collectProjections( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MSupportFunction - collectProjections: Expecting one output value!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MSupportFunction - collectProjections: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MSupportFunction - collectProjections: At least one argument were ignored." );

	mxArray* m_out;
	double* out;

	hypro::SupportFunction<double>* sfct = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[2] );
	std::vector<std::size_t> vec = sfct->collectProjections();

	m_out = plhs[0] = mxCreateDoubleMatrix( vec.size(), 1, mxREAL );
	out = mxGetPr( m_out );
	for ( int i = 0; i < vec.size(); i++ ) {
		out[i] = vec[i];
	}
	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "collectProjections output:\n" );
	// mexPrintf( "\nvector: " );
	// for ( int i = 0; i < vec.size(); i++ ) {
	// 	mexPrintf( " %f", vec[i] );
	// }
	// mexPrintf( "\n" );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MSupportFunction::reduceNumberRepresentation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MSupportFunction - reduceNumberRepresentation: One or more arguments are missing!" );
	if ( nrhs > 3 )
		mexWarnMsgTxt( "MSupportFunction - reduceNumberRepresentation: At least one argument were ignored." );

	hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[2] );
	temp->reduceNumberRepresentation();
}

/*
 * @brief The entry point to the HyPro Support Function class for Matalb.
 * @param nlhs Number of items in plhs
 * @param plhs Array of mxArray pointers to the output variables
 * @param nrhs Number of items in prhs
 * @param prhs Array of mxArray pointers to the input variables
 */
void MSupportFunction::process( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	int cmd = mxGetScalar( prhs[1] );

	if ( cmd == 1 ) {
		deleteObject( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 2 ) {
		dimension( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 3 ) {
		vertices( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 4 ) {
		reduceRepresentation( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 5 ) {
		ostream( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 6 ) {
		size( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 7 ) {
		equal( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 9 ) {
		matrix( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 10 ) {
		vector( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 11 ) {
		is_empty( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 12 ) {
		removeRedundancy( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 13 ) {
		type( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 14 ) {
		satisfiesHalfspace( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 15 ) {
		satisfiesHalfspaces( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 16 ) {
		projectOn( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 17 ) {
		linearTransformation( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 18 ) {
		affineTransformation( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 19 ) {
		minkowskiSum( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 20 ) {
		intersectHalfspace( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 21 ) {
		intersectHalfspaces( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 22 ) {
		contains_point( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 23 ) {
		contains_object( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 24 ) {
		reduceNumberRepresentation( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 25 ) {
		intersect( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 26 ) {
		unite_single( nlhs, plhs, nrhs, prhs );
		return;
	}
	// if ( cmd == 27 ) {
	// 	unite_vec(nlhs, plhs, nrhs, prhs); !!!!!!!!!??????
	// 	return;
	// }
	if ( cmd == 100 ) {
		new_empty( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 101 ) {
		new_matrix( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 102 ) {
		copyObj( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 103 ) {
		new_points( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 104 ) {
		new_intervals( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 105 ) {
		new_mat_vec( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 106 ) {
		new_halfspaces( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 107 ) {
		contains_point( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 108 ) {
		supremum( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 109 ) {
		cleanUp( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 110 ) {
		depth( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 111 ) {
		operationCount( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 112 ) {
		contains_dir( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 113 ) {
		swap( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 114 ) {
		forceLinTransReduction( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 115 ) {
		collectProjections( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 116 ) {
		scale( nlhs, plhs, nrhs, prhs );
		return;
	}

	mexErrMsgTxt( "MSupportFunction - Command not recognized." );
}