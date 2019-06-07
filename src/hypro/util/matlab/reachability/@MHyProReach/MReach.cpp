#include "MReach.h"

void MReach::del_reach( int lhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MReach- del_reach: Expecting an output." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MReach- del_reach: One or more arguments were ignored." );
	destroyObject<Reacher>( prhs[2] );
}

void MReach::new_reach( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MReach - new_reach: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MReach - new_reach: At least one input argument is missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MReach- new_reach: One or more arguments were ignored." );

	hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>( prhs[2] );
	Reacher* reacher = new Reacher( *autom );
	plhs[0] = convertPtr2Mat<Reacher>( reacher );
}

void MReach::computeForwardReachability( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MReach - computeForwardReachability: Expecting an output." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MReach - computeForwardReachability: At least one input argument is missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MReach- computeForwardReachability: One or more arguments were ignored." );

	Reacher* reacher = convertMat2Ptr<Reacher>( prhs[2] );
	std::vector<std::pair<unsigned, flowpipe>> flowpipes = reacher->computeForwardReachability();

	int num_flowpipes = flowpipes.size();
	mexPrintf( "\n" );
	mexPrintf( "Number of flowpipes: %d\n", num_flowpipes );
	std::vector<hypro::State_t<double>> f = flowpipes[0].second;
	mexPrintf( "Number of states in f1: %d\n", f.size() );
	mwSize dims[2] = {1, num_flowpipes};
	const char* field_names[] = {"num", "flowpipe"};
	plhs[0] = mxCreateStructArray( 2, dims, 2, field_names );
	ObjectHandle::flowpipes2Matlab( flowpipes, plhs[0], num_flowpipes );
}

void MReach::setRepresentationType( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MReach - setRepresentationType: At least one input argument is missing." );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MReach- setRepresentationType: One or more arguments were ignored." );

	Reacher* reacher = convertMat2Ptr<Reacher>( prhs[2] );
	int type = mxGetScalar( prhs[3] );
	// box=0, constraint_set = 1, support_function = 2
	if ( type == 0 )
		reacher->setRepresentationType( hypro::representation_name::box );
	else if ( type == 1 )
		reacher->setRepresentationType( hypro::representation_name::constraint_set );
	else if ( type == 2 )
		reacher->setRepresentationType( hypro::representation_name::support_function );
	else
		mexErrMsgTxt( "MReach - setRepresentationType: unknown type." );
}

void MReach::setSettings( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 4 ) mexErrMsgTxt( "MReach - setSettings: At least one input argument is missing." );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MReach- setSettings: One or more arguments were ignored." );

	Reacher* reacher = convertMat2Ptr<Reacher>( prhs[2] );
	mwIndex idx = 1;
	int ifield, nfields;
	nfields = mxGetNumberOfFields( prhs[3] );
	hypro::ReachabilitySettings settings;
	for ( ifield = 0; ifield < nfields; ifield++ ) {
		mxArray* tmp = mxGetFieldByNumber( prhs[3], 0, ifield );
		const char* fname = mxGetFieldNameByNumber( prhs[3], ifield );
		if ( !strcmp( fname, "timeBound" ) ) {
			double timeBound = mxGetScalar( tmp );
			settings.timeBound = hypro::tNumber( timeBound );
			mexPrintf( "%s: %f\n", fname, timeBound );
		} else if ( !strcmp( fname, "jumpDepth" ) ) {
			double jumpDepth = mxGetScalar( tmp );
			settings.jumpDepth = jumpDepth;
			mexPrintf( "%s: %f\n", fname, jumpDepth );
		} else if ( !strcmp( fname, "timeStep" ) ) {
			double timeStep = mxGetScalar( tmp );
			settings.timeStep = carl::convert<double, hypro::tNumber>( timeStep );
			mexPrintf( "%s: %f\n", fname, timeStep );
		} else if ( !strcmp( fname, "fileName" ) ) {
			char file[64];
			mxGetString( tmp, file, sizeof( file ) );
			std::string fileName = std::string( file );
			settings.fileName = fileName;
			mexPrintf( "%s: %s\n", fname, fileName.c_str() );
		} else if ( !strcmp( fname, "pplDenomimator" ) ) {
			double pplDenomimator = mxGetScalar( tmp );
			settings.pplDenomimator = pplDenomimator;
			mexPrintf( "%s: %f\n", fname, pplDenomimator );
		} else if ( !strcmp( fname, "plotDimensions" ) ) {
			const mwSize* dims;
			int dimx, dimy;
			dims = mxGetDimensions( tmp );
			dimx = dims[0];
			dimy = dims[1];
			std::vector<std::vector<std::size_t>> plotDimensions =
				  ObjectHandle::mVectorOfVectors2Hypro( tmp, dimx, dimy );
			settings.plotDimensions = plotDimensions;
		} else if ( !strcmp( fname, "uniformBloating" ) ) {
			double uniformBloating = mxGetScalar( tmp );
			bool uB = false;
			if ( uniformBloating == 1 ) uB = true;
			settings.uniformBloating = uB;
			mexPrintf( "%s: %f\n", fname, uniformBloating );
		} else {
			mexErrMsgTxt( "MHyProReach - setSettings: Unknown setting field." );
		}
	}
	reacher->setSettings( settings );
}

void MReach::settings( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MReach - setSettings: At least one input argument is missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MReach- setSettings: One or more arguments were ignored." );

	Reacher* reacher = convertMat2Ptr<Reacher>( prhs[2] );
	const hypro::ReachabilitySettings currSettings = reacher->settings();

	double tB = carl::convert<hypro::tNumber, double>( currSettings.timeBound );
	int jD = currSettings.jumpDepth;
	double tS = carl::convert<hypro::tNumber, double>( currSettings.timeStep );
	std::string fN = currSettings.fileName;
	unsigned long pplD = currSettings.pplDenomimator;
	std::vector<std::vector<std::size_t>> dim = currSettings.plotDimensions;
	bool uB = currSettings.uniformBloating;
	int cl = currSettings.clustering;
	bool uITI = currSettings.useInvariantTimingInformation;
	bool uGTI = currSettings.useGuardTimingInformation;
	bool uBSTI = currSettings.useBadStateTimingInformation;

	mexPrintf( "Settings:\n" );
	mexPrintf( "timeBound: %f\n", tB );
	mexPrintf( "jumpDepth: %d\n", jD );
	mexPrintf( "timeStep: %f\n", tS );
	mexPrintf( "fileName: %s\n", fN.c_str() );
	mexPrintf( "pplDenomimator: %d\n", pplD );
	mexPrintf( "dims:\n" );
	for ( int i = 0; i < dim.size(); i++ ) {
		std::vector<std::size_t> current = dim[i];
		mexPrintf( "[" );
		for ( int j = 0; j < dim[0].size(); j++ ) {
			mexPrintf( "%d ", current[j] );
		}
		mexPrintf( "]\n" );
	}
	if ( uB ) {
		mexPrintf( "uniformBloating: true\n" );
	} else {
		mexPrintf( "uniformBloating: false\n" );
	}
	mexPrintf( "clustering: %d\n", cl );
	if ( uITI ) {
		mexPrintf( "useInvariantTimingInformation: true\n" );
	} else {
		mexPrintf( "useInvariantTimingInformation: false\n" );
	}
	if ( uGTI ) {
		mexPrintf( "useGuardTimingInformation: true\n" );
	} else {
		mexPrintf( "useGuardTimingInformation: false\n" );
	}
	if ( uBSTI ) {
		mexPrintf( "useBadStateTimingInformation: true\n" );
	} else {
		mexPrintf( "useBadStateTimingInformation: false\n" );
	}
}

void MReach::process( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	int cmd = mxGetScalar( prhs[1] );

	if ( cmd == 3 ) {
		computeForwardReachability( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 2 ) {
		new_reach( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 1 ) {
		del_reach( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 4 ) {
		setSettings( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 5 ) {
		setRepresentationType( nlhs, plhs, nrhs, prhs );
		return;
	}
	if ( cmd == 6 ) {
		settings( nlhs, plhs, nrhs, prhs );
		return;
	}

	mexErrMsgTxt( "MReach - Command not recognized." );
}