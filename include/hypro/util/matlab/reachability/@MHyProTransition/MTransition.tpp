#include "MTransition.h"

void MTransition::new_empty( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - new_empty: Expecting an output." );

	hypro::Transition<double>* temp = new hypro::Transition<double>();
	plhs[0] = convertPtr2Mat<hypro::Transition<double>>( temp );
}

void MTransition::copy( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - copy: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - copy: One or more arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - copy: One or more arguments were ignored." );

	hypro::Transition<double>* origin = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	plhs[0] = convertPtr2Mat<hypro::Transition<double>>( new hypro::Transition<double>( *origin ) );
}

void MTransition::new_source_target( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - new_source_target: Expecting an output." );
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition - new_source_target: One or more arguments are missing." );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - new_source_target: One or more arguments were ignored." );

	hypro::Location<double>* source = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	hypro::Location<double>* target = convertMat2Ptr<hypro::Location<double>>( prhs[3] );

	hypro::Transition<double>* tran = new hypro::Transition<double>( source, target );
	plhs[0] = convertPtr2Mat<hypro::Transition<double>>( new hypro::Transition<double>( *tran ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "new_source_target input:\n" );
	// std::string tName = target->getName();
	// std::string sName = source->getName();
	// mexPrintf( "transition %s -> %s\n", tName.c_str(), sName.c_str() );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::new_full( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - new_full: Expecting an output." );
	if ( nrhs < 6 ) mexErrMsgTxt( "MTransition - new_full: One or more arguments are missing." );
	if ( nrhs > 6 ) mexWarnMsgTxt( "MTransition - new_full: One or more arguments were ignored." );

	hypro::Location<double>* source = convertMat2Ptr<hypro::Location<double>>( prhs[2] );
	hypro::Location<double>* target = convertMat2Ptr<hypro::Location<double>>( prhs[3] );
	const hypro::Condition<double>* guard = convertMat2Ptr<hypro::Condition<double>>( prhs[4] );
	const hypro::Reset<double>* reset = convertMat2Ptr<hypro::Reset<double>>( prhs[5] );

	hypro::Transition<double>* tran = new hypro::Transition<double>( source, target, *guard, *reset );
	plhs[0] = convertPtr2Mat<hypro::Transition<double>>( new hypro::Transition<double>( *tran ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "new_full input:\n" );
	// std::string tName = target->getName();
	// std::string sName = source->getName();
	// mexPrintf( "transition %s -> %s\n", tName.c_str(), sName.c_str() );
	// hypro::matrix_t<double> gmatrix = guard->getMatrix();
	// hypro::vector_t<double> gvector = guard->getVector();
	// mexPrintf( "guard matrix:\n" );
	// for ( int i = 0; i < gmatrix.rows(); i++ ) {
	// 	for ( int j = 0; j < gmatrix.cols(); j++ ) {
	// 		mexPrintf( " %f", gmatrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "guard vector:\n" );
	// for ( int j = 0; j < gvector.rows(); j++ ) {
	// 	mexPrintf( " %f", gvector( j ) );
	// }
	// hypro::matrix_t<double> rmatrix = reset->getMatrix();
	// hypro::vector_t<double> rvector = reset->getVector();
	// mexPrintf( "reset matrix:\n" );
	// for ( int i = 0; i < rmatrix.rows(); i++ ) {
	// 	for ( int j = 0; j < rmatrix.cols(); j++ ) {
	// 		mexPrintf( " %f", rmatrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "reset vector:\n" );
	// for ( int j = 0; j < rvector.rows(); j++ ) {
	// 	mexPrintf( " %f", rvector( j ) );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::delete_tran( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - delete_tran: Expecting an output." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - delete_tran: One or more arguments were ignored." );
	destroyObject<hypro::Transition<double>>( prhs[2] );
}

void MTransition::getTarget( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - getTarget: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - getTarget: One or more arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - getTarget: One or more arguments were ignored." );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	hypro::Location<double>* target = tran->getTarget();
	plhs[0] = convertPtr2Mat<hypro::Location<double>>( new hypro::Location<double>( *target ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "getTarget:\n" );
	// std::string tName = target->getName();
	// mexPrintf( "target: %s\n", tName.c_str() );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::getSource( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - getSource: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - getSource: One or more arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - getSource: One or more arguments were ignored." );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	hypro::Location<double>* source = tran->getSource();
	plhs[0] = convertPtr2Mat<hypro::Location<double>>( new hypro::Location<double>( *source ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "getSource input:\n" );
	// std::string sName = source->getName();
	// mexPrintf( "source: %s\n", sName.c_str() );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::getGuard( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - getGuard: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - getGuard: One or more arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - getGuard: One or more arguments were ignored." );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	hypro::Condition<double> cond = tran->getGuard();
	plhs[0] = convertPtr2Mat<hypro::Condition<double>>( new hypro::Condition<double>( cond ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "getGuard input:\n" );
	// hypro::matrix_t<double> gmatrix = cond.getMatrix();
	// hypro::vector_t<double> gvector = cond.getVector();
	// mexPrintf( "guard matrix:\n" );
	// for ( int i = 0; i < gmatrix.rows(); i++ ) {
	// 	for ( int j = 0; j < gmatrix.cols(); j++ ) {
	// 		mexPrintf( " %f", gmatrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "guard vector:\n" );
	// for ( int j = 0; j < gvector.rows(); j++ ) {
	// 	mexPrintf( " %f", gvector( j ) );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::getReset( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - getReset: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - getReset: One or more arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - getReset: One or more arguments were ignored." );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	hypro::Reset<double> res = tran->getReset();
	plhs[0] = convertPtr2Mat<hypro::Reset<double>>( new hypro::Reset<double>( res ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "getReset input:\n" );
	// hypro::matrix_t<double> gmatrix = res.getMatrix();
	// hypro::vector_t<double> gvector = res.getVector();
	// mexPrintf( "reset matrix:\n" );
	// for ( int i = 0; i < gmatrix.rows(); i++ ) {
	// 	for ( int j = 0; j < gmatrix.cols(); j++ ) {
	// 		mexPrintf( " %f", gmatrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "reset vector:\n" );
	// for ( int j = 0; j < gvector.rows(); j++ ) {
	// 	mexPrintf( " %f", gvector( j ) );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::getAggregation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - getAggregation: One or more arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - getAggregation: One or more arguments were ignored." );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	hypro::Aggregation agg = tran->getAggregation();

	if ( agg == hypro::Aggregation::none ) {
		mexPrintf( "none\n" );
	} else if ( agg == hypro::Aggregation::aggregation ) {
		mexPrintf( "Agg\n" );
	}
}

void MTransition::getTriggerTime( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - getReset: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - getReset: One or more arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - getReset: One or more arguments were ignored." );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	double time = tran->getTriggerTime();
	plhs[0] = mxCreateDoubleScalar( time );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "getTriggerTime input:\n" );
	// mexPrintf( "time: %d\n", time );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::isUrgent( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - isUrgent: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - isUrgent: One argument missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - isUrgent: One or more input arguments were ignored." );

	hypro::Transition<double>* temp = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	const bool isurgent = temp->isUrgent();
	plhs[0] = mxCreateLogicalScalar( isurgent );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "isUrgent output:\n" );
	// if ( isurgent ) {
	// 	mexPrintf( "yes\n" );
	// } else {
	// 	mexPrintf( "no\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::isTimeTriggered( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - isTimeTriggered: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - isTimeTriggered: One argument missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - isTimeTriggered: One or more input arguments were ignored." );

	hypro::Transition<double>* temp = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	const bool ans = temp->isTimeTriggered();
	plhs[0] = mxCreateLogicalScalar( ans );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "isTimeTriggered output:\n" );
	// if ( ans ) {
	// 	mexPrintf( "yes\n" );
	// } else {
	// 	mexPrintf( "no\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::hasIdentityReset( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - hasIdentityReset: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - hasIdentityReset: One argument missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - hasIdentityReset: One or more input arguments were ignored." );

	hypro::Transition<double>* temp = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	const bool ans = temp->hasIdentityReset();
	plhs[0] = mxCreateLogicalScalar( ans );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "hasIdentityReset output:\n" );
	// if ( ans ) {
	// 	mexPrintf( "yes\n" );
	// } else {
	// 	mexPrintf( "no\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::getLabels( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - getLabels: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - getLabels: One argument missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - getLabels: One or more input arguments were ignored." );

	hypro::Transition<double>* temp = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	std::vector<hypro::Label> labs = temp->getLabels();
	int len = labs.size();
	const mwSize dims[2] = { 1, (mwSize)len };
	plhs[0] = mxCreateCellArray( 2, dims );
	objArray2Matlab( labs, plhs[0], len );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "getLabels output:\n" );
	// mexPrintf( "vector:\n" );
	// for ( int i = 0; i < labs.size(); i++ ) {
	// 	mexPrintf( "label %d: %s\n", i, labs[i].getName().c_str() );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::hash( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition - hash: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MTransition - hash: One or more input arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MTransition - hash: One or more input arguments were ignored!" );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	std::size_t val = tran->hash();
	plhs[0] = mxCreateDoubleScalar( val );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "hash output:\n" );
	// mexPrintf( "hash: %d\n", (double)val );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::setSource( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition - setSource: One or more input arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - setSource: One or more input arguments were ignored!" );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[3] );
	tran->setSource( loc );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "setSource input:\n" );
	// std::string sName = loc->getName();
	// mexPrintf( "source: %s\n", sName.c_str() );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::setTarget( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition - setTarget: One or more input arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - setTarget: One or more input arguments were ignored!" );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>( prhs[3] );
	tran->setTarget( loc );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "setTarget input:\n" );
	// std::string sName = loc->getName();
	// mexPrintf( "target: %s\n", sName.c_str() );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::setGuard( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition - setGuard: One or more input arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - setGuard: One or more input arguments were ignored!" );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>( prhs[3] );
	tran->setGuard( *cond );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "setGuard input:\n" );
	// hypro::matrix_t<double> gmatrix = cond->getMatrix();
	// hypro::vector_t<double> gvector = cond->getVector();
	// mexPrintf( "guard matrix:\n" );
	// for ( int i = 0; i < gmatrix.rows(); i++ ) {
	// 	for ( int j = 0; j < gmatrix.cols(); j++ ) {
	// 		mexPrintf( " %f", gmatrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "guard vector:\n" );
	// for ( int j = 0; j < gvector.rows(); j++ ) {
	// 	mexPrintf( " %f", gvector( j ) );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::setReset( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition - setReset: One or more input arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - setReset: One or more input arguments were ignored!" );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	hypro::Reset<double>* res = convertMat2Ptr<hypro::Reset<double>>( prhs[3] );
	tran->setReset( *res );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "setReset input:\n" );
	// hypro::matrix_t<double> gmatrix = res->getMatrix();
	// hypro::vector_t<double> gvector = res->getVector();
	// mexPrintf( "reset matrix:\n" );
	// for ( int i = 0; i < gmatrix.rows(); i++ ) {
	// 	for ( int j = 0; j < gmatrix.cols(); j++ ) {
	// 		mexPrintf( " %f", gmatrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "reset vector:\n" );
	// for ( int j = 0; j < gvector.rows(); j++ ) {
	// 	mexPrintf( " %f", gvector( j ) );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::setAggregation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition - setAggregation: One or more input arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - setAggregation: One or more input arguments were ignored!" );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	const int agg = (int)mxGetScalar( prhs[3] );

	if ( agg == 0 ) {
		tran->setAggregation( hypro::Aggregation::none );
	} else if ( agg == 1 ) {
		tran->setAggregation( hypro::Aggregation::aggregation );
	}

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "setAggregation input:\n" );
	// mexPrintf( "aggergation: %d\n", agg );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::setUrgent( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition - setSource: One or more input arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - setSource: One or more input arguments were ignored!" );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	const double temp = (double)mxGetScalar( prhs[3] );
	bool val = true;
	if ( temp == 0 ) val = false;
	tran->setUrgent( val );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "setUrgent input:\n" );
	// if ( val ) {
	// 	mexPrintf( "yes\n" );
	// } else {
	// 	mexPrintf( "no\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::setTriggerTime( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition - setTriggerTime: One or more input arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - setTriggerTime: One or more input arguments were ignored!" );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	const double time = (double)mxGetScalar( prhs[3] );
	tran->setTriggerTime( time );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "setTriggerTime input:\n" );
	// mexPrintf( "time: %d\n", time );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::setLabels( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition - setLabels: One or more input arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - setLabels: One or more input arguments were ignored!" );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	const mwSize* dims;
	int num;
	dims = mxGetDimensions( prhs[3] );
	num = dims[1];
	std::vector<hypro::Label> labs = ObjectHandle::objArray2Hypro<hypro::Label>( prhs[3], num );
	tran->setLabels( labs );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "setLabels input:\n" );
	// mexPrintf( "vector:\n" );
	// for ( int i = 0; i < labs.size(); i++ ) {
	// 	mexPrintf( "label %d: %s\n", i, labs[i].getName().c_str() );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::addLabel( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition - addLabel: One or more input arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - addLabel: One or more input arguments were ignored!" );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	hypro::Label* lab = convertMat2Ptr<hypro::Label>( prhs[3] );
	tran->addLabel( *lab );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "addLabel input:\n" );
	// mexPrintf( "vector:\n" );
	// mexPrintf( "label %s\n", lab->getName().c_str() );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::getDotRepresentation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition- getDotRepresentation: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition- getDotRepresentation: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - getDotRepresentation: One or more arguments were ignored." );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( plhs[2] );
	std::vector<std::string> vars = ObjectHandle::mStringVector2Hypro( prhs[3] );
	std::string str = tran->getDotRepresentation( vars );
	mxCreateString( str.c_str() );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "getDotRepresentation\n" );
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::isComposedOf( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition- isComposedOf: Expecting an output!" );
	if ( nrhs < 6 ) mexErrMsgTxt( "MTransition- isComposedOf: One or more arguments are missing!" );
	if ( nrhs > 6 ) mexWarnMsgTxt( "MTransition - isComposedOf: One or more arguments were ignored." );

	hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>( plhs[2] );
	mexErrMsgTxt( "NOT IMPLEMENTED" );
}

void MTransition::decompose( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	mexErrMsgTxt( "NOT IMPLEMENTED" );
}

void MTransition::outstream( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	mexErrMsgTxt( "NOT IMPLEMENTED" );
}

void MTransition::equals( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition- equals: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition- equals: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - equals: One or more arguments were ignored." );

	hypro::Transition<double>* tran1 = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	hypro::Transition<double>* tran2 = convertMat2Ptr<hypro::Transition<double>>( prhs[3] );

	const bool ans = ( tran1 == tran2 );
	if ( ans )
		plhs[0] = mxCreateLogicalScalar( true );
	else
		plhs[0] = mxCreateLogicalScalar( false );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "equals input:\n" );
	// if ( ans ) {
	// 	mexPrintf( "yes\n" );
	// } else {
	// 	mexPrintf( "no\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::nequals( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MTransition- nequals: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MTransition- nequals: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MTransition - nequals: One or more arguments were ignored." );

	hypro::Transition<double>* tran1 = convertMat2Ptr<hypro::Transition<double>>( prhs[2] );
	hypro::Transition<double>* tran2 = convertMat2Ptr<hypro::Transition<double>>( prhs[3] );

	const bool ans = ( tran1 != tran2 );
	if ( ans )
		plhs[0] = mxCreateLogicalScalar( true );
	else
		plhs[0] = mxCreateLogicalScalar( false );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "unequals input:\n" );
	// if ( ans ) {
	// 	mexPrintf( "yes\n" );
	// } else {
	// 	mexPrintf( "no\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

void MTransition::process( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	int cmd = mxGetScalar( prhs[1] );

	if ( cmd == 2 ) {
		new_empty( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 3 ) {
		copy( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 1 ) {
		delete_tran( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 4 ) {
		new_source_target( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 5 ) {
		new_full( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 6 ) {
		getTarget( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 7 ) {
		getSource( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 8 ) {
		getGuard( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 9 ) {
		getReset( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 10 ) {
		getAggregation( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 11 ) {
		getTriggerTime( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 12 ) {
		isUrgent( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 13 ) {
		isTimeTriggered( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 14 ) {
		hasIdentityReset( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 15 ) {
		getLabels( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 16 ) {
		hash( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 17 ) {
		setSource( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 18 ) {
		setTarget( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 19 ) {
		setGuard( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 20 ) {
		setReset( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 21 ) {
		setAggregation( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 22 ) {
		setUrgent( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 23 ) {
		setTriggerTime( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 24 ) {
		setLabels( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 25 ) {
		addLabel( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 26 ) {
		getDotRepresentation( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 27 ) {
		isComposedOf( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 28 ) {
		decompose( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 29 ) {
		equals( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 30 ) {
		nequals( nlhs, plhs, nrhs, prhs );
		return;
	}

	mexErrMsgTxt( "MTransition - Command not recognized." );
}