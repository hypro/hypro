#include "MConstraintSet.h"

/**
 * @brief Creates an empty constraint set
 **/
void MConstraintSet::new_empty( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MConstraintSet - new_empty: One output expected." );
	if ( nrhs > 2 ) mexWarnMsgTxt( "MConstraintSet - new_empty: One or more input arguments were ignored." );

	plhs[0] = convertPtr2Mat<hypro::ConstraintSet<double>>( new hypro::ConstraintSet<double> );
}

/**
 * @brief
 **/
void MConstraintSet::isAxisAligned( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs < 1 ) mexErrMsgTxt( "MConstraintSet - isAxisAligned: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MConstraintSet - isAxisAligned: One argument missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MConstraintSet - isAxisAligned: One or more input arguments were ignored." );

	hypro::ConstraintSet<double>* temp = convertMat2Ptr<hypro::ConstraintSet<double>>( prhs[2] );
	const bool empty = temp->isAxisAligned();
	plhs[0] = mxCreateLogicalScalar( empty );
}

/**
 * @brief
 **/
void MConstraintSet::addConstraint( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 5 ) mexErrMsgTxt( "MConstraintSet - addConstraint: One or more arguments are missing!" );
	if ( nrhs > 5 ) mexWarnMsgTxt( "MConstraintSet - addConstraint: One or more input arguments were ignored." );

	const mwSize* dims;
	int  cols;

	hypro::ConstraintSet<double>* temp = convertMat2Ptr<hypro::ConstraintSet<double>>( prhs[2] );
	const double offset = (const double)mxGetScalar( prhs[4] );

	dims = mxGetDimensions( prhs[3] );
	cols = (int)dims[1];

	const hypro::vector_t<double> hy_vec = ObjectHandle::mVector2Hypro( prhs[3], cols );

	temp->addConstraint( hy_vec, offset );
}

/**
 * @brief
 **/
void MConstraintSet::type( int nlhs, mxArray* plhs[], int rhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MConstraintSet - type: Expecting one output value!" );
	std::string ans = "MHyProConstraintSet";
	plhs[0] = mxCreateString( ans.c_str() );
}

/**
 * @brief
 **/
void MConstraintSet::reduceNumberRepresentation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs < 1 ) mexErrMsgTxt( "HyProConstraintSet - reduceNumberRepresentation: Expecting an output!" );
	if ( nrhs < 4 )
		mexErrMsgTxt( "HyProConstraintSet - reduceNumberRepresentation: One or more arguments are missing!" );
	if ( nrhs > 4 )
		mexWarnMsgTxt( "MConstraintSet - reduceNumberRepresentation: One or more input arguments were ignored." );

	hypro::ConstraintSet<double>* temp = convertMat2Ptr<hypro::ConstraintSet<double>>( prhs[2] );
	const unsigned u = (const unsigned)mxGetScalar( prhs[3] );
	hypro::ConstraintSet<double> obj = temp->reduceNumberRepresentation( u );
	hypro::ConstraintSet<double>* b = new hypro::ConstraintSet<double>( obj );
	plhs[0] = convertPtr2Mat<hypro::ConstraintSet<double>>( b );
}

void MConstraintSet::linearTransformation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - linearTransformation: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - linearTransformation: One or more arguments are missing!" );
	if ( nrhs > 4 )
		mexWarnMsgTxt( "MGeometricObject - lineaTransformation: One or more input arguments were ignored." );

	const mwSize* dims;
	double* in_matrix;
	int rows, cols;

	hypro::ConstraintSet<double>* obj = convertMat2Ptr<hypro::ConstraintSet<double>>( prhs[2] );
	dims = mxGetDimensions( prhs[3] );
	cols = (int)dims[1];
	rows = (int)dims[0];

	hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro( prhs[3], rows, cols );

	std::vector<hypro::Point<double>> vertices = obj->vertices();

	mexPrintf("before:\n");
	for(int i = 0; i < vertices.size(); i++){
		for(int j = 0; j < vertices[0].dimension(); j++){
			std::size_t pos = j;
			mexPrintf("%f ", vertices[i].coordinate(j));
		}
		mexPrintf("\n");
	}

	hypro::ConstraintSet<double> temp = obj->linearTransformation( mat );

	hypro::matrix_t<double> matt = temp.matrix();

	std::vector<hypro::Point<double>> vertices1 = temp.vertices();

	mexPrintf("after:\n");
	for(int i = 0; i < vertices1.size(); i++){
		for(int j = 0; j < vertices1[0].dimension(); j++){
			std::size_t pos = j;
			mexPrintf("%f ", vertices1[i].coordinate(j));
		}
		mexPrintf("\n");
	}

	hypro::ConstraintSet<double>* b = new hypro::ConstraintSet<double>( temp );
	plhs[0] = convertPtr2Mat<hypro::ConstraintSet<double>>( b );
}





// /**
//  * @brief
//  **/
// template<typename From, typename To, typename S>
// void MConstraintSet::convert(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MConstraintSet - convert: One output is expected.");
//     if(nrhs < 6)
//         mexErrMsgTxt("MConstraintSet - convert: One or more arguments are missing.");

//     char from[64];
//     char to[64];
//     char s[64];
//     mxGetString(prhs[3], from, sizeof(from));
//     mxGetString(prhs[4], to, sizeof(to));
//     mxGetString(prhs[5], s, sizeof(s));

//     hypro::ConstraintSet<double>

//     hypro::ConstraintSet<to,s> con =

// }

/**
 * @brief The entry point to the HyPro Constraint Set class for Matalb.
 * @param nlhs Number of items in plhs
 * @param plhs Array of mxArray pointers to the output variables
 * @param nrhs Number of items in prhs
 * @param prhs Array of mxArray pointers to the input variables
 **/
void MConstraintSet::process( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	// Get the command string
	int cmd = mxGetScalar( prhs[1] );

	if ( cmd == 15 ) {
		new_empty( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 17 ) {
		new_mat_vec( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 16 ) {
		copyObj( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 1 ) {
		deleteObject( nlhs, plhs, nrhs, prhs );
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
	if ( cmd == 32 ) {
		isAxisAligned( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 33 ) {
		addConstraint( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 11 ) {
		is_empty( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 3 ) {
		vertices( nlhs, plhs, nrhs, prhs );
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
	if ( cmd == 5 ) {
		ostream( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 2 ) {
		dimension( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 12 ) {
		removeRedundancy( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 6 ) {
		size( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 13 ) {
		type( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 30 ) {
		reduceNumberRepresentation( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 18 ) {
		satisfiesHalfspace( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 19 ) {
		satisfiesHalfspaces( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 20 ) {
		project( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 21 ) {
		linearTransformation( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 22 ) {
		affineTransformation( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 23 ) {
		minkowskiSum( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 31 ) {
		intersect( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 24 ) {
		intersectHalfspace( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 25 ) {
		intersectHalfspaces( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 27 ) {
		contains_point( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 26 ) {
		contains_object( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 28 ) {
		unite_single( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 29 ) {
		unite_vec( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 4 ) {
		reduceRepresentation( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 14 ) {
		clear( nlhs, plhs, nrhs, prhs );
		return;
	}
	mexErrMsgTxt( "MConstraintSet - Command not recognized." );
}