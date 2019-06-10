#include "MLocation.h"

void MLocation::new_empty( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - new_empty: Expecting an output." );

	hypro::Location<double>* loc = new hypro::Location<double>();
	mexPrintf( "New location Addresss %p\n", loc );
	plhs[0] = convertPtr2Mat<hypro::Location<double>>( loc );
}

void MLocation::new_matrix( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - new_matrix: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - new_matrix: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MLocation - new_matrix: One or more arguments were ignored." );

	double* in_matrix;
	const mwSize* dims;
	int rows, cols;

	dims = mxGetDimensions( prhs[2] );
	cols = dims[1];
	rows = dims[0];

	hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro( prhs[2], rows, cols );
	hypro::Location<double>* loc = new hypro::Location<double>( mat );
	plhs[0] = convertPtr2Mat<hypro::Location<double>>( loc );
}

void MLocation::new_mat_tran_inv( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MHyProLocation - new_mat_tran_inv: Expecting an output!" );
	if ( nrhs < 5 ) mexErrMsgTxt( "MHyProLocation - new_mat_tran_inv: One or more arguments are missing!" );
	if ( nrhs > 5 ) mexWarnMsgTxt( "MHyProLocation - new_mat_tran_inv: One or more input arguments were ignored." );

	const mwSize *mat_dims, *vec_dims;
	int mat_rows, mat_cols, vec_len;

	mat_dims = mxGetDimensions( prhs[2] );
	mat_cols = (int)mat_dims[1];
	mat_rows = (int)mat_dims[0];
	vec_dims = mxGetDimensions( prhs[3] );
	vec_len = (int)vec_dims[0];

	hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro( prhs[2], mat_rows, mat_cols );
	const std::vector<hypro::Transition<double>> temp =
		  ObjectHandle::objArray2Hypro<hypro::Transition<double>>( prhs[3], vec_len );
	hypro::Condition<double>* inv = convertMat2Ptr<hypro::Condition<double>>( prhs[4] );
	std::vector<std::unique_ptr<hypro::Transition<double>>> transitions;

	for ( const auto& elem : temp ) {
		hypro::Transition<double>* t = new hypro::Transition<double>( elem );
		std::unique_ptr<hypro::Transition<double>> tran = std::make_unique<hypro::Transition<double>>( *t );
		transitions.emplace_back( std::move( tran ) );
	}
	hypro::Location<double>* loc = new hypro::Location<double>( matrix, std::move( transitions ), *inv );

	plhs[0] = convertPtr2Mat<hypro::Location<double>>( loc );
}

void MLocation::copy( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - copy: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - copy: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MLocation - copy: One or more arguments were ignored." );

	hypro::Location<double>* origin = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	plhs[0] = convertPtr2Mat<hypro::Location<double>>( new hypro::Location<double>( *origin ) );
}

void MLocation::delete_loc( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - delete_loc: Expecting an output." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MLocation - delete_loc: One or more arguments were ignored." );
	destroyObject<hypro::Location<double>>( prhs[2] );
}

void MLocation::getNumberFlow( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - getNumberFlow: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - getNumberFlow: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MLocation - getNumberFlow: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	std::size_t num = loc->getNumberFlow();
	plhs[0] = mxCreateDoubleScalar( num );
}

void MLocation::getLinearFlow( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - getLinearFlow: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - getLinearFlow: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MLocation - getLinearFlow: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	hypro::linearFlow<double> flow = loc->getLinearFlow();
	plhs[0] = convertPtr2Mat<hypro::linearFlow<double>>( new hypro::linearFlow<double>( flow ) );
}

void MLocation::getLinearFlows( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - getLinearFlows: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - getLinearFlows: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MLocation - getLinearFlows: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	std::vector<hypro::linearFlow<double>> flows = loc->getLinearFlows();
	int len = flows.size();
	const mwSize dims[2] = {1, (mwSize)len};
	plhs[0] = mxCreateCellArray( 2, dims );
	objArray2Matlab( flows, plhs[0], len );
}

void MLocation::getInvariant( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - getInvariant: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - getInvariant: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MLocation - getInvariant: One or more arguments were ignored." );

	mexPrintf( "GETINVARIANT\n" );
	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	hypro::Condition<double> cond = loc->getInvariant();
	mexPrintf( "get invariant location Addresss %p\n", cond );
	hypro::Condition<double>* address = &cond;
	mexPrintf( "get invariant condition Addresss %p\n", address );
	plhs[0] = convertPtr2Mat<hypro::Condition<double>>( new hypro::Condition<double>( cond ) );
	// plhs[0] = convertPtr2Mat<hypro::Condition<double>>(address);
}

void MLocation::getTransitions( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - getTransitions: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - getTransitions: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MLocation - getTransitions: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	std::vector<hypro::Transition<double>*> temp = loc->getTransitions();
	std::vector<hypro::Transition<double>> transitions;

	for ( const auto& elem : temp ) {
		transitions.emplace_back( *elem );
	}

	mxArray* m_array_out;
	int len = temp.size();
	const mwSize dims[2] = {1, (mwSize)len};
	plhs[0] = mxCreateCellArray( 2, dims );
	objArray2Matlab( transitions, plhs[0], len );
}

void MLocation::getExternalInput( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - getExternalInput: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - getExternalInput: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MLocation - getExternalInput: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	std::vector<carl::Interval<double>> input = loc->getExternalInput();
	plhs[0] = mxCreateDoubleMatrix( input.size(), 2, mxREAL );
	vector2Matlab<carl::Interval<double>>( input, plhs[0] );
}

void MLocation::hasExternalInput( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - hasExternalInput: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - hasExternalInput: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MLocation - hasExternalInput: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	const bool ans = loc->hasExternalInput();
	plhs[0] = mxCreateLogicalScalar( ans );
}

void MLocation::hash( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - hash: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - hash: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MLocation - hash: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	std::size_t h = loc->hash();
	plhs[0] = mxCreateDoubleScalar( h );
}

void MLocation::getName( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - getName: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - getName: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MLocation - getName: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	std::string name = loc->getName();
	plhs[0] = mxCreateString( name.c_str() );
}

void MLocation::dimension( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - dimension: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MLocation - dimension: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MLocation - dimension: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	std::size_t h = loc->dimension();
	plhs[0] = mxCreateDoubleScalar( h );
}

void MLocation::dimension_at( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - dimension_at: Expecting an output." );
	if ( nrhs < 4 ) mexErrMsgTxt( "MLocation - dimension_at: One or more arguments are missing." );
	if ( nrhs > 4 ) mexErrMsgTxt( "MLocation - dimension_at: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	std::size_t pos = (std::size_t)mxGetScalar( prhs[3] );
	std::size_t h = loc->dimension( pos );
	plhs[0] = mxCreateDoubleScalar( h );
}

void MLocation::setName( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MLocation - setName: One or more arguments are missing." );
	if ( nrhs > 4 ) mexErrMsgTxt( "MLocation - setName: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	mexPrintf( "setName loc Addresss %p\n", loc );
	char* name = mxArrayToString( prhs[3] );
	loc->setName( std::string( name ) );
}

void MLocation::setFlow( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MLocation - setFlow: One or more arguments are missing." );
	if ( nrhs > 4 ) mexErrMsgTxt( "MLocation - setFlow: One or more arguments were ignored." );

	double* in_matrix;
	const mwSize* dims;
	int rows, cols;

	dims = mxGetDimensions( prhs[3] );
	cols = dims[1];
	rows = dims[0];

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro( prhs[3], rows, cols );

	loc->setFlow( mat );
}

void MLocation::setLinearFlow( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 5 ) mexErrMsgTxt( "MLocation - setLinearFlow: One or more arguments are missing." );
	if ( nrhs > 5 ) mexErrMsgTxt( "MLocation - setLinearFlow: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	const hypro::linearFlow<double>* flow = convertMat2Ptr<hypro::linearFlow<double>>( prhs[3] );
	std::size_t i = (std::size_t)mxGetScalar( prhs[4] );
	loc->setLinearFlow( *flow, i );
}

void MLocation::setLinearFlow_vec( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MLocation - setFlow_vec: One or more arguments are missing." );
	if ( nrhs > 4 ) mexErrMsgTxt( "MLocation - setFlow_vec: One or more arguments were ignored." );

	const mwSize* dims;
	int len;
	dims = mxGetDimensions( prhs[3] );
	len = dims[0];

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	const std::vector<hypro::linearFlow<double>> flows =
		  ObjectHandle::objArray2Hypro<hypro::linearFlow<double>>( prhs[3], len );
	loc->setLinearFlow( flows );
}

void MLocation::setInvariant( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MLocation - setInvariant: One or more arguments are missing." );
	if ( nrhs > 4 ) mexErrMsgTxt( "MLocation - setInvariant: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>( prhs[3] );
	mexPrintf( "Set invariant Condition Addresss %p\n", cond );
	loc->setInvariant( *cond );
}

// void MLocation::setTransition(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
//     if(nrhs < 4)
//          mexErrMsgTxt("MLocation - setTransition: One or more arguments are missing.");
//     if(nrhs > 4)
//          mexErrMsgTxt("MLocation - setTransition: One or more arguments were ignored.");

//     hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
//     hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[3]);
//     loc->setTransition(*tran);
// }

void MLocation::addTransition( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MLocation - addTransition: One or more arguments are missing." );
	if ( nrhs > 4 ) mexErrMsgTxt( "MLocation - addTransition: One or more arguments were ignored." );

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	hypro::Transition<double>* temp = convertMat2Ptr<hypro::Transition<double>>( prhs[3] );
	std::unique_ptr<hypro::Transition<double>> tran( new hypro::Transition<double>( *temp ) );
	loc->addTransition( std::move( tran ) );
}

void MLocation::setExtInput( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MLocation - setExtInput: One or more arguments are missing." );
	if ( nrhs > 4 ) mexErrMsgTxt( "MLocation - setExtInput: One or more arguments were ignored." );

	const mwSize* dims;
	int rows, cols;

	dims = mxGetDimensions( prhs[3] );
	cols = dims[1];
	rows = dims[0];
	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	std::vector<carl::Interval<double>> ints = ObjectHandle::mIntervals2Hypro( prhs[3], rows, cols );

	loc->setExtInput( ints );
}

void MLocation::isComposedOf( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - isComposedOf: Expecting an output!" );
	if ( nrhs < 6 ) mexErrMsgTxt( "MLocation - isComposedOf: One or more arguments are missing!" );
	if ( nrhs > 6 ) mexWarnMsgTxt( "MLocation - isComposedOf: One or more arguments were ignored." );

	const mwSize *rhsvar_dim, *thisvar_dim;
	rhsvar_dim = mxGetDimensions( prhs[4] );
	thisvar_dim = mxGetDimensions( prhs[5] );
	int rhsvar_len = rhsvar_dim[1];
	int thisvar_len = thisvar_dim[1];

	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	hypro::Location<double>* rhs = convertMat2Ptr<hypro::Location<double>>( prhs[3] );
	std::vector<std::string> rhsVars = ObjectHandle::mStringVector2Hypro( prhs[4], rhsvar_len );
	std::vector<std::string> thisVars = ObjectHandle::mStringVector2Hypro( prhs[5], thisvar_len );

	// bool ans = loc->isComposedOf(*rhs, rhsVars, thisVars);
	// plhs[0] = mxCreateLogicalScalar(ans); ---> ?
}

// void MLocation::getDotRepresentation(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MLocation - getDotRepresentation: Expecting an output!");
//     if(nrhs < 4)
//         mexErrMsgTxt("MLocation - getDotRepresentation: One or more arguments are missing!");
//     if(nrhs > 4)
//         mexWarnMsgTxt("MLocation - getDotRepresentation: One or more arguments were ignored.");

//     const mwSize* dims;
//     int len;
//     dims = mxGetDimensions(prhs[3]);
//     len = dims[0];

//     hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
//     std::vector<std::string> vars = ObjectHandle::mStringVector2Hypro(prhs[3], len);
//     std::string rep = loc->getDotRepresentation(vars);
//     plhs[0] = mxCreateString(rep.c_str());
// }

void MLocation::decompose( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	// TODO
}

void MLocation::less( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - less: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MLocation - less: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MLocation - less: One or more arguments were ignored." );

	hypro::Location<double>* loc_1 = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	hypro::Location<double>* loc_2 = convertMat2Ptr<hypro::Location<double>>( prhs[3] );

	mxLogical ans = false;
	if ( *loc_1 < *loc_2 ) ans = true;
	plhs[0] = mxCreateLogicalScalar( ans );
}

void MLocation::equals( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - equals: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MLocation - equals: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MLocation - equals: One or more arguments were ignored." );

	hypro::Location<double>* loc_1 = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	hypro::Location<double>* loc_2 = convertMat2Ptr<hypro::Location<double>>( prhs[3] );

	mxLogical ans = false;
	if ( *loc_1 == *loc_2 ) ans = true;
	plhs[0] = mxCreateLogicalScalar( ans );
}

void MLocation::unequals( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MLocation - unequals: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MLocation - unequals: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MLocation - unequals: One or more arguments were ignored." );

	hypro::Location<double>* loc_1 = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	hypro::Location<double>* loc_2 = convertMat2Ptr<hypro::Location<double>>( prhs[3] );

	mxLogical ans = false;
	if ( *loc_1 != *loc_2 ) ans = true;
	plhs[0] = mxCreateLogicalScalar( ans );
}

void MLocation::outstream( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	// TODO
}

void MLocation::process( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	int cmd = mxGetScalar( prhs[1] );

	if ( cmd == 2 ) {
		new_empty( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 4 ) {
		new_matrix( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 5 ) {
		new_mat_tran_inv( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 3 ) {
		copy( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 1 ) {
		delete_loc( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 6 ) {
		getNumberFlow( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 7 ) {
		getLinearFlow( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 8 ) {
		getLinearFlows( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 9 ) {
		getInvariant( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 10 ) {
		getTransitions( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 11 ) {
		getExternalInput( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 12 ) {
		hasExternalInput( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 13 ) {
		hash( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 14 ) {
		getName( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 15 ) {
		dimension( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 16 ) {
		dimension_at( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 17 ) {
		setName( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 18 ) {
		setFlow( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 19 ) {
		setLinearFlow( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 20 ) {
		setLinearFlow_vec( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 21 ) {
		setInvariant( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 23 ) {
		addTransition( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 22 ) {
		setExtInput( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 24 ) {
		isComposedOf( nlhs, plhs, nrhs, prhs );
		return;
	}
	// if (cmd == 25){
	//     getDotRepresentation(nlhs, plhs, nrhs, prhs);
	//     return;
	// }
	if ( cmd == 26 ) {
		decompose( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 27 ) {
		less( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 28 ) {
		equals( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 29 ) {
		unequals( nlhs, plhs, nrhs, prhs );
		return;
	}
	mexErrMsgTxt( "MLocation - Command not recognized." );
}