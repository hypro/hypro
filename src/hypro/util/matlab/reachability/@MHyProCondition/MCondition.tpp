#include "MCondition.h"

void MCondition::new_empty( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - new_empty: Expecting an output!" );
	hypro::Condition<double>* cond = new hypro::Condition<double>();
	plhs[0] = convertPtr2Mat<hypro::Condition<double>>( cond );
}

void MCondition::new_mat_vec( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - new_mat_vec: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MCondition - new_mat_vec: One or more input arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MCondition - new_mat_vec: One or more input arguments were ignored!" );

	const mwSize *mat_dims, *vec_dims;
	int mat_rows, mat_cols, vec_len;
	mat_dims = mxGetDimensions( prhs[2] );
	vec_dims = mxGetDimensions( prhs[3] );
	mat_rows = mat_dims[0];
	mat_cols = mat_dims[1];
	vec_len = vec_dims[0];

	hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro( prhs[2], mat_rows, mat_cols );
	hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro( prhs[3], vec_len );
	hypro::Condition<double>* cond = new hypro::Condition<double>( matrix, vector );
	plhs[0] = convertPtr2Mat<hypro::Condition<double>>( cond );
}

void MCondition::new_constr_set( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - new_constr_set: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MCondition - new_constr_set: One or more input arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MCondition - new_constr_set: One or more input arguments were ignored!" );

	const hypro::ConstraintSet<double>* constraint = convertMat2Ptr<hypro::ConstraintSet<double>>( prhs[2] );
	hypro::Condition<double>* cond = new hypro::Condition<double>(*constraint);
	mexErrMsgTxt("Not implemented!");
	//plhs[0] = convertPtr2Mat<hypro::Condition<double>>(cond);
}

void MCondition::copy( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - copy: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MCondition - copy: One or more input arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MCondition - copy: One or more input arguments were ignored!" );

	hypro::Condition<double>* origin = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	hypro::Condition<double>* cond = new hypro::Condition<double>( *origin );
	plhs[0] = convertPtr2Mat<hypro::Condition<double>>( cond );
}

void MCondition::delete_condition( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MCondition - delete_condition: Expecting an output." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MCondition - delete_condition: One or more arguments were ignored." );
	destroyObject<hypro::Condition<double>>( prhs[2] );
}

void MCondition::size( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - size: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MCondition - size: One or more input arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MCondition - size: One or more input arguments were ignored!" );

	hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	std::size_t s = cond->size();
	plhs[0] = mxCreateDoubleScalar( s );
}

void MCondition::isempty( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - isempty: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MCondition - isempty: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MCondition - isempty: One or more arguments were ignored." );

	hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	const bool ans = cond->empty();
	plhs[0] = mxCreateLogicalScalar( ans );
}

void MCondition::getMatrix( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - getMatrix: One output expected!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MCondition - getMatrix: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexErrMsgTxt( "MCondition - getMatrix: One or more arguments were ignored!" );

	hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	hypro::matrix_t<double> mat = cond->getMatrix();
	plhs[0] = mxCreateDoubleMatrix( mat.rows(), mat.cols(), mxREAL );
	ObjectHandle::convert2Matlab( mat, plhs[0], mat.rows(), mat.cols() );
}

void MCondition::getVector( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - getVector: One output expected!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MCondition - getVector: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexErrMsgTxt( "MCondition - getVector: One or more arguments were ignored!" );

	hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	hypro::vector_t<double> vec = cond->getVector();
	plhs[0] = mxCreateDoubleMatrix( vec.rows(), 1, mxREAL );
	ObjectHandle::convert2Matlab( vec, plhs[0], vec.rows(), 1 );
}

void MCondition::isAxisAligned( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - isAxisAligned: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MCondition - isAxisAligned: One or more arguments are missing." );
	if ( nrhs > 3 ) mexErrMsgTxt( "MCondition - isAxisAligned: One or more arguments were ignored." );

	hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	const bool ans = cond->isAxisAligned();
	plhs[0] = mxCreateLogicalScalar( ans );
}

void MCondition::isAxisAligned_at( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - isAxisAligned_at: Expecting an output." );
	if ( nrhs < 4 ) mexErrMsgTxt( "MCondition - isAxisAligned_at: One or more arguments are missing." );
	if ( nrhs > 4 ) mexErrMsgTxt( "MCondition - isAxisAligned_at: One or more arguments were ignored." );

	hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	std::size_t s = mxGetScalar( prhs[3] );
	const bool ans = cond->isAxisAligned( s );
	plhs[0] = mxCreateLogicalScalar( ans );
}

void MCondition::setMatrix( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MCondition - setMatrix: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexErrMsgTxt( "MCondition - setMatrix: One or more arguments were ignored!" );

	const mwSize* dims;
	int rows, cols;
	dims = mxGetDimensions( prhs[3] );
	rows = dims[0];
	cols = dims[1];

	hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro( prhs[3], rows, cols );
	cond->setMatrix( mat );
}

void MCondition::setVector( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 5 ) mexErrMsgTxt( "MCondition - setVector: One or more arguments are missing!" );
	if ( nrhs > 5 ) mexErrMsgTxt( "MCondition - setVector: One or more arguments were ignored!" );

	const mwSize* dims;
	int len;
	dims = mxGetDimensions( prhs[3] );
	len = dims[0];

	hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro( prhs[3], len );
	std::size_t s = (std::size_t)mxGetScalar( prhs[4] );
	cond->setVector( vec, s );
}

void MCondition::constraints( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - constraints: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MCondition - constraints: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexErrMsgTxt( "MCondition - constraints: One or more arguments were ignored!" );

	hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	std::vector<hypro::ConstraintSet<double>> constrs = cond->constraints();

	mxArray* m_out_constrs;
	int len = constrs.size();
	const mwSize dims[2] = {1, (mwSize)len};
	plhs[0] = m_out_constrs = mxCreateCellArray( 2, dims );
	objArray2Matlab( constrs, m_out_constrs, len );
}

void MCondition::hash( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - hash: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MCondition - hash: One or more input arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MCondition - hash: One or more input arguments were ignored!" );

	hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	std::size_t s = cond->hash();
	plhs[0] = mxCreateDoubleScalar( s );
}

// void MCondition::getDotRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MCondition - getDotRepresentation: Expecting an output!");
//     if(nrhs < 4)
//         mexErrMsgTxt("MCondition - getDotRepresentation: One or more input arguments are missing!");
//     if(nrhs > 4)
//         mexWarnMsgTxt("MCondition - getDotRepresentation: One or more input arguments were ignored!");

//     const mwSize* dims;
//     int len;
//     dims = mxGetDimensions(prhs[3]);
//     len = dims[0];

//     hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
//     std::vector<std::string> strs = ObjectHandle::mStringVector2Hypro(prhs[3], len);

//     std::string ans = cond->getDotRepresentation(strs);
//     plhs[0] = mxCreateString(ans.c_str());
// }

void MCondition::decompose( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	// TODO:
}

void MCondition::equals( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs < 1 ) mexErrMsgTxt( "MCondition - ==: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MCondition - ==: One or more arguments are missing!" );

	hypro::Condition<double>* cond_1 = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	hypro::Condition<double>* cond_2 = convertMat2Ptr<hypro::Condition<double>>( prhs[3] );
	mxLogical ans = false;
	if ( *cond_1 == *cond_2 ) {
		ans = true;
	}
	plhs[0] = mxCreateLogicalScalar( ans );
}

void MCondition::unequals( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs < 1 ) mexErrMsgTxt( "MCondition - !=: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MCondition - !=: One or more arguments are missing!" );

	hypro::Condition<double>* cond_1 = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	hypro::Condition<double>* cond_2 = convertMat2Ptr<hypro::Condition<double>>( prhs[3] );
	mxLogical ans = false;
	if ( *cond_1 != *cond_2 ) {
		ans = true;
	}
	plhs[0] = mxCreateLogicalScalar( ans );
}

void MCondition::outstream( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	// TODO:
}

void MCondition::combine( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MCondition - getDotRepresentation: Expecting an output!" );
	if ( nrhs < 7 ) mexErrMsgTxt( "MCondition - getDotRepresentation: One or more input arguments are missing!" );
	if ( nrhs > 7 ) mexWarnMsgTxt( "MCondition - getDotRepresentation: One or more input arguments were ignored!" );

	const mwSize *dims_haVar, *dims_lhsVar, *dims_rhsVar;
	int len_haVar, len_lhsVar, len_rhsVar;
	dims_haVar = mxGetDimensions( prhs[4] );
	dims_lhsVar = mxGetDimensions( prhs[5] );
	dims_rhsVar = mxGetDimensions( prhs[6] );
	len_haVar = dims_haVar[0];
	len_lhsVar = dims_lhsVar[0];
	len_rhsVar = dims_rhsVar[0];

	hypro::Condition<double>* lhs = convertMat2Ptr<hypro::Condition<double>>( prhs[2] );
	hypro::Condition<double>* rhs = convertMat2Ptr<hypro::Condition<double>>( prhs[3] );
	std::vector<std::string> haVar = ObjectHandle::mStringVector2Hypro( prhs[4], len_haVar );
	std::vector<std::string> lhsVar = ObjectHandle::mStringVector2Hypro( prhs[5], len_lhsVar );
	std::vector<std::string> rhsVar = ObjectHandle::mStringVector2Hypro( prhs[6], len_rhsVar );
}

void MCondition::process( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	int cmd = mxGetScalar( prhs[1] );

	if ( cmd == 2 ) {
		new_empty( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 4 ) {
		new_constr_set( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 5 ) {
		new_mat_vec( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 3 ) {
		copy( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 1 ) {
		delete_condition( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 6 ) {
		size( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 7 ) {
		isempty( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 8 ) {
		getMatrix( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 9 ) {
		getVector( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 10 ) {
		isAxisAligned( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 11 ) {
		isAxisAligned_at( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 12 ) {
		setMatrix( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 13 ) {
		setVector( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 14 ) {
		constraints( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 15 ) {
		hash( nlhs, plhs, nrhs, prhs );
		return;
	}
	// if (cmd == 16){
	//     getDotRepresentation(nlhs, plhs, nrhs, prhs);
	//     return;
	// }
	if ( cmd == 17 ) {
		decompose( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 18 ) {
		equals( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 19 ) {
		unequals( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 20 ) {
		combine( nlhs, plhs, nrhs, prhs );
		return;
	}
	mexErrMsgTxt( "MCondition - Command not recognized." );
}
