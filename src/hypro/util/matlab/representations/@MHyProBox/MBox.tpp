#include "MBox.h"

void MBox::boxFromSingleInterval( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - new_interval: One output expected." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MBox - new_interval: One or more input arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MBox - new_interval: One or more input arguments were ignored." );

	carl::Interval<double> inter = ObjectHandle::mInterval2Hypro( prhs[2] );
	hypro::Box<double> *box = new hypro::Box<double>( inter );
	plhs[0] = convertPtr2Mat<hypro::Box<double>>( box );
}

void MBox::boxFromIntervals( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - new_intervals: One output expected." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MBox - new_intervals: One or more input arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MBox - new_intervals: One or more input arguments were ignored." );

	const mwSize *dims;
	double *in;
	int rows, cols;

	dims = mxGetDimensions( prhs[2] );
	cols = (int)dims[0];
	rows = (int)dims[1];
	std::vector<carl::Interval<double>> intervals = ObjectHandle::mIntervals2Hypro( prhs[2], rows, cols );
	hypro::Box<double> *box = new hypro::Box<double>( intervals );
	plhs[0] = convertPtr2Mat<hypro::Box<double>>( box );
}

void MBox::boxFromPoints( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - new_points: One output expected." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MBox - new_points: One or more input arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MBox - new_points: One or more input arguments were ignored." );

	std::pair<hypro::Point<double>, hypro::Point<double>> pair = ObjectHandle::mPointPair2Hypro( prhs[2] );
	hypro::Box<double> *box = new hypro::Box<double>( pair );
	plhs[0] = convertPtr2Mat<hypro::Box<double>>( box );
}

void MBox::empty( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - empty: Expecting one output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MBox - empty: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MBox - new_interval: One or more input arguments were ignored." );

	hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>( prhs[2] );
	std::size_t in = (std::size_t)mxGetScalar( prhs[3] );
	hypro::Box<double> temp = box->Empty( in );
	hypro::Box<double> *b = new hypro::Box<double>( temp );
	plhs[0] = convertPtr2Mat<hypro::Box<double>>( b );
}

void MBox::intervals( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - intervals: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MBox - intervals: One or more input arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MBox - intervals: One or more input arguments were ignored." );

	hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>( prhs[2] );
	std::vector<carl::Interval<double>> intervals = box->intervals();

	const int rows = intervals.size();
	plhs[0] = mxCreateDoubleMatrix( rows, 2, mxREAL );
	vector2Matlab( intervals, plhs[0] );
}

void MBox::insert( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MBox - insert: One argument is missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MBox - insert: One or more input arguments were ignored." );

	const mwSize *dims;
	double *in_box, *in_interval, *out;
	int cols, rows, numdims;

	hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>( prhs[2] );

	dims = mxGetDimensions( prhs[3] );
	numdims = mxGetNumberOfDimensions( prhs[3] );
	cols = (int)dims[0];
	rows = (int)dims[1];
	if ( numdims > 2 || cols != 1 || rows != 2 ) {
		mexErrMsgTxt( "MBox - insert: You have to input a 1x2-matrix!" );
	}

	carl::Interval<double> interval = ObjectHandle::mInterval2Hypro( prhs[3] );
	box->insert( interval );
}

void MBox::limits( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - limits: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MBox - limits: One argument is missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MBox - limits: One or more input arguments were ignored." );

	hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>( prhs[2] );
	std::pair<hypro::Point<double>, hypro::Point<double>> p = box->limits();
	int dim = p.first.dimension();
	plhs[0] = mxCreateDoubleMatrix( dim, 2, mxREAL );
	pair2Matlab( p, plhs[0], dim, 2 );
}

void MBox::constraints( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 2 ) mexErrMsgTxt( "MBox - constraints: Expecting two output values!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MBox - constraints: One argument is missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MBox - constraints: One or more input arguments were ignored." );

	hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>( prhs[2] );
	const std::vector<hypro::Halfspace<double>> hSpaces = box->constraints();

	const int cols = hSpaces[0].dimension();
	const int rows = hSpaces.size();

	plhs[0] = mxCreateDoubleMatrix( rows, cols, mxREAL );
	plhs[1] = mxCreateDoubleMatrix( rows, 1, mxREAL );
	vector2Matlab<hypro::Halfspace<double>>( hSpaces, plhs[0], plhs[1] );
}

void MBox::interval( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - interval: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MBox - interval: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MBox - interval: One or more input arguments were ignored." );

	// Decrease the dimension by 1 because in Matlab everything starts at 1
	size_t dim = (size_t)mxGetScalar( prhs[3] ) - 1;
	hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>( prhs[2] );
	const carl::Interval<double> inter = box->interval( dim );
	plhs[0] = mxCreateDoubleMatrix( 1, 2, mxREAL );
	ObjectHandle::convert2Matlab( inter, plhs[0], 1, 2 );
}

void MBox::at( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - at: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MBox - at: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MBox - at: One or more input arguments were ignored." );

	size_t dim = (size_t)mxGetScalar( prhs[3] ) - 1;
	hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>( prhs[2] );
	const carl::Interval<double> inter = box->at( dim );

	plhs[0] = mxCreateDoubleMatrix( 1, 2, mxREAL );
	ObjectHandle::convert2Matlab( inter, plhs[0], 1, 2 );
}

void MBox::is_symmetric( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - isSymmetric: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MBox - isSymmetric: One argument missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MBox - isSymmetric: One or more input arguments were ignored." );

	hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>( prhs[2] );
	const bool empty = box->isSymmetric();
	mxLogical a = empty;
	plhs[0] = mxCreateLogicalScalar( empty );
}

void MBox::max( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - max: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MBox - max: One argument missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MBox - max: One or more input arguments were ignored." );

	hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>( prhs[2] );
	hypro::Point<double> m = box->max();
	int dim = m.dimension();
	plhs[0] = mxCreateDoubleMatrix( dim, 1, mxREAL );
	ObjectHandle::convert2Matlab( m, plhs[0], dim, 1 );
}

void MBox::min( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - min: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MBox - min: One argument missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MBox - min: One or more input arguments were ignored." );

	hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>( prhs[2] );
	hypro::Point<double> m = box->min();
	int dim = m.dimension();
	plhs[0] = mxCreateDoubleMatrix( dim, 1, mxREAL );
	ObjectHandle::convert2Matlab( m, plhs[0], dim, 1 );
}

void MBox::type( int nlhs, mxArray *plhs[], int rhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - type: Expecting one output value!" );
	std::string ans = "MHyProBox";
	plhs[0] = mxCreateString( ans.c_str() );
}

void MBox::makeSymmetric( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - makeSymmetric: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MBox - makeSymmetric: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MBox - makeSymmetric: One or more input arguments were ignored." );

	hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>( prhs[2] );
	hypro::Box<double> symmBox = box->makeSymmetric();
	plhs[0] = plhs[0] = convertPtr2Mat<hypro::Box<double>>( new hypro::Box<double>( symmBox ) );
}

void MBox::minkowskiDecomposition( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MBox - minkowskiDecomposition: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MBox - minkowskiDecomposition: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MBox - minkowskiDecomposition: One or more input arguments were ignored." );

	hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>( prhs[2] );
	hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn> *box_rhs =
		  convertMat2Ptr<hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>>( prhs[3] );

	hypro::Box<double> sum = box->minkowskiDecomposition( *box_rhs );
	hypro::Box<double> *b = new hypro::Box<double>( sum );
	plhs[0] = convertPtr2Mat<hypro::Box<double>>( b );
}

/**
 * @brief The entry point to the HyPro Box class for Matalb.
 * @param nlhs Number of items in plhs
 * @param plhs Array of mxArray pointers to the output variables
 * @param nrhs Number of items in prhs
 * @param prhs Array of mxArray pointers to the input variables
 **/
void MBox::process( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
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
	if ( cmd == 8 ) {
		unequal( nlhs, plhs, nrhs, prhs );
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
		project( nlhs, plhs, nrhs, prhs );
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
	if ( cmd == 27 ) {
		unite_vec(nlhs, plhs, nrhs, prhs);
		return;
	}

	if ( cmd == 100 ) {
		new_empty( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 101 ) {
		copyObj( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 102 ) {
		boxFromPoints( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 103 ) {
		boxFromSingleInterval( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 104 ) {
		boxFromIntervals( nlhs, plhs, nrhs, prhs );
		return;
	}
	
	if ( cmd == 105 ) {
		new_mat_vec( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 106 ) {
		empty( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 107 ) {
		intervals( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 108 ) {
		limits( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 109 ) {
		constraints( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 110 ) {
		insert( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 111 ) {
		interval( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 112 ) {
		at( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 113 ) {
		is_symmetric( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 114 ) {
		max( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 115 ) {
		min( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 116 ) {
		supremum( nlhs, plhs, nrhs, prhs );
		return;
	}	
	if ( cmd == 117 ) {
		scale( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 118 ) {
		makeSymmetric( nlhs, plhs, nrhs, prhs );
		return;
	}
	
	if ( cmd == 119 ) {
		minkowskiDecomposition( nlhs, plhs, nrhs, prhs );
		return;
	}	
	if ( cmd == 120 ) {
		clear( nlhs, plhs, nrhs, prhs );
		return;
	}

	mexErrMsgTxt( "MBox - Command not recognized." );
}
