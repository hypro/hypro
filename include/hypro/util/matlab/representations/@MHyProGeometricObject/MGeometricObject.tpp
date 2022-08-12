#include "MGeometricObject.h"

template <typename T>
void MGeometricObject<T>::new_empty( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - new_empty: One output is expected." );
	plhs[0] = convertPtr2Mat<T>( new T() );
}

template <typename T>
void MGeometricObject<T>::new_matrix( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - new_matrix: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - new_matrix: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - new_matrix: One or more input arguments were ignored." );

	const mwSize* mat_dims;
	int mat_rows, mat_cols;

	mat_dims = mxGetDimensions( prhs[2] );
	mat_cols = (int)mat_dims[1];
	mat_rows = (int)mat_dims[0];

	hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro( prhs[2], mat_rows, mat_cols );
	plhs[0] = convertPtr2Mat<T>( new T( matrix ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "new_matrix input:\n" );
	// mexPrintf( "matrix:\n" );
	// for ( int i = 0; i < matrix.rows(); i++ ) {
	// 	for ( int j = 0; j < matrix.cols(); j++ ) {
	// 		mexPrintf( " %f", matrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "\n" );
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <typename T>
void MGeometricObject<T>::new_vector( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - new_vector: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - new_vector: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - new_vector: One or more input arguments were ignored." );

	double* in_vector;
	const mwSize* vec_dims;
	int len;
	vec_dims = mxGetDimensions( prhs[2] );
	len = (int)vec_dims[0];
	hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro( prhs[2], len );
	plhs[0] = convertPtr2Mat<T>( new T( vector ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "new_vector input:\n" );
	// mexPrintf( "vector:\n" );
	// for ( int j = 0; j < vector.rows(); j++ ) {
	// 	mexPrintf( " %f", vector( j ) );
	// }
	// mexPrintf( "\noutput:\n" );

	// T* test = new T( vector );
	// hypro::matrix_t<double> mat = test->matrix();
	// hypro::vector_t<double> vec = test->vector();
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

template <typename T>
void MGeometricObject<T>::copyObj( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - copyObj: One output expected." );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - copyObj: One argument is missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - copyObj: One or more input arguments were ignored." );

	T* origin = convertMat2Ptr<T>( prhs[2] );
	plhs[0] = convertPtr2Mat<T>( new T( *origin ) );
}

template <typename T>
void MGeometricObject<T>::new_mat_vec( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - new_mat_vec: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - new_mat_vec: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - new_mat_vec: One or more input arguments were ignored." );

	const mwSize *mat_dims, *vec_dims;
	int mat_rows, mat_cols, len;

	mat_dims = mxGetDimensions( prhs[2] );
	mat_cols = (int)mat_dims[1];
	mat_rows = (int)mat_dims[0];
	vec_dims = mxGetDimensions( prhs[3] );
	len = (int)vec_dims[0];
	hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro( prhs[2], mat_rows, mat_cols );
	hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro( prhs[3], len );
	plhs[0] = convertPtr2Mat<T>( new T( matrix, vector ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "new_mat_vec input:\n" );
	// mexPrintf( "matrix:\n" );
	// for ( int i = 0; i < matrix.rows(); i++ ) {
	// 	for ( int j = 0; j < matrix.cols(); j++ ) {
	// 		mexPrintf( " %f", matrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "vector:\n" );
	// for ( int j = 0; j < vector.rows(); j++ ) {
	// 	mexPrintf( " %f", vector( j ) );
	// }
	// mexPrintf( "\noutput:\n" );

	// T* test = new T( matrix, vector );
	// hypro::matrix_t<double> mat = test->matrix();
	// hypro::vector_t<double> vec = test->vector();
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

template <class T>
void MGeometricObject<T>::deleteObject( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - deleteObject: One or more arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - deleteObject: One or more arguments were ignored." );

	destroyObject<T>( prhs[2] );
}

template <class T>
void MGeometricObject<T>::matrix( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - matrix: One output expected!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - matrix: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - matrix: One or more input arguments were ignored." );

	T* temp = convertMat2Ptr<T>( prhs[2] );
	hypro::matrix_t<double> mat = temp->matrix();

	int rows = mat.rows();
	int cols = mat.cols();

	plhs[0] = mxCreateDoubleMatrix( rows, cols, mxREAL );
	ObjectHandle::convert2Matlab( mat, plhs[0], rows, cols );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "matrix input:\n" );
	// mexPrintf( "matrix:\n" );
	// for ( int i = 0; i < mat.rows(); i++ ) {
	// 	for ( int j = 0; j < mat.cols(); j++ ) {
	// 		mexPrintf( " %f", mat( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "\n" );
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::scale( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - scale: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - scale: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - scale: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	const double factor = (double)mxGetScalar( prhs[3] );
	T temp = obj->operator*( factor );
	plhs[0] = convertPtr2Mat<T>( new T( temp ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "scale input:\n" );
	// hypro::matrix_t<double> matrix = obj->matrix();
	// hypro::vector_t<double> vector = obj->vector();
	// mexPrintf( "matrix:\n" );
	// for ( int i = 0; i < matrix.rows(); i++ ) {
	// 	for ( int j = 0; j < matrix.cols(); j++ ) {
	// 		mexPrintf( " %f", matrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "vector:\n" );
	// for ( int j = 0; j < vector.rows(); j++ ) {
	// 	mexPrintf( " %f", vector( j ) );
	// }
	// mexPrintf( "\noutput:\n" );

	// T* test = new T( matrix, vector );
	// hypro::matrix_t<double> mat = test->matrix();
	// hypro::vector_t<double> vec = test->vector();
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

template <class T>
void MGeometricObject<T>::vector( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - vector: One output expected!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - vector: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - vector: One or more input arguments were ignored." );

	T* temp = convertMat2Ptr<T>( prhs[2] );
	hypro::vector_t<double> vec = temp->vector();
	plhs[0] = mxCreateDoubleMatrix( vec.size(), 1, mxREAL );
	ObjectHandle::convert2Matlab( vec, plhs[0], vec.size(), 1 );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "vector input:\n" );
	// mexPrintf( "vector:\n" );
	// for ( int j = 0; j < vec.cols(); j++ ) {
	// 	mexPrintf( " %f", vec( j ) );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::is_empty( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - isEmpty: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - isEmpty: One argument missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - isEmpty: One or more input arguments were ignored." );

	T* temp = convertMat2Ptr<T>( prhs[2] );
	const bool empty = temp->empty();
	plhs[0] = mxCreateLogicalScalar( empty );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "is_empty input:\n" );
	// if ( empty ) {
	// 	mexPrintf( "empty\n" );
	// } else {
	// 	mexPrintf( "not empty\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::vertices( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - vertices: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - vertices: One argument is missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - vertices: One or more input arguments were ignored." );

	T* temp = convertMat2Ptr<T>( prhs[2] );
	std::vector<hypro::Point<double>> vertices = temp->vertices();
	int cols = vertices.size();
	if ( cols != 0 ) {
		int rows = vertices[0].dimension();
		plhs[0] = mxCreateDoubleMatrix( rows, cols, mxREAL );
		ObjectHandle::convert2Matlab( vertices, plhs[0] );
	} else {
		mexWarnMsgTxt( "MGeometricObject - vertices: The object has no vertices." );
		plhs[0] = mxCreateDoubleMatrix( 1, 1, mxREAL );
	}

	//+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "vertices output:\n" );
	// if ( cols != 0 ) {
	// 	int rows = vertices[0].dimension();
	// 	for ( int j = 0; j < cols; j++ ) {
	// 		hypro::Point<double> p = vertices[j];
	// 		for ( int i = 0; i < rows; i++ ) {
	// 			mexPrintf( " %f", p[i] );
	// 		}
	// 		mexPrintf( "\n" );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	//+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::equal( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - ==: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - ==: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - ==: One or more input arguments were ignored." );

	T* obj_1 = convertMat2Ptr<T>( prhs[2] );
	T* obj_2 = convertMat2Ptr<T>( prhs[3] );
	mxLogical ans = false;
	if ( *obj_1 == *obj_2 ) {
		ans = true;
	}
	plhs[0] = mxCreateLogicalScalar( ans );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "equal output:\n" );
	// if ( ans ) {
	// 	mexPrintf( "equal\n" );
	// } else {
	// 	mexPrintf( "not equal\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::unequal( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - !=: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - !=: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - !=: One or more input arguments were ignored." );

	T* obj_1 = convertMat2Ptr<T>( prhs[2] );
	T* obj_2 = convertMat2Ptr<T>( prhs[3] );
	mxLogical ans = false;
	if ( *obj_1 != *obj_2 ) {
		ans = true;
	}
	plhs[0] = mxCreateLogicalScalar( ans );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "unequal output:\n" );
	// if ( ans ) {
	// 	mexPrintf( "unequal\n" );
	// } else {
	// 	mexPrintf( "not unequal\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::supremum( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - supremum: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - supremum: One argument missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - supremum: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	double supremum = obj->supremum();
	plhs[0] = mxCreateDoubleScalar( supremum );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "supremum output: %f\n", supremum );
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::dimension( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - dimension: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - dimension: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - dimension: One or more input arguments were ignored." );

	T* temp = convertMat2Ptr<T>( prhs[2] );
	std::size_t dim = temp->dimension();
	plhs[0] = mxCreateDoubleScalar( dim );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "dimension output: %f\n", (double)dim );
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::removeRedundancy( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - removeRedundancy: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - removeRedundancy: One or more input arguments were ignored." );

	T* temp = convertMat2Ptr<T>( prhs[2] );
	temp->removeRedundancy();

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "removeRedundancy output:\n" );
	// hypro::matrix_t<double> mat = temp->matrix();
	// hypro::vector_t<double> vec = temp->vector();
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

template <class T>
void MGeometricObject<T>::size( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - size: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - size: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - size: One or more input arguments were ignored." );

	T* temp = convertMat2Ptr<T>( prhs[2] );
	std::size_t dim = temp->size();
	plhs[0] = mxCreateDoubleScalar( dim );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "size output: %f\n", (double)dim );
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::reduceNumberRepresentation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - reduceNumberRepresentation: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - reduceNumberRepresentation: One or more arguments are missing!" );
	if ( nrhs > 3 )
		mexWarnMsgTxt( "MGeometricObject - reduceNumberRepresentation: One or more input arguments were ignored." );

	T* temp = convertMat2Ptr<T>( prhs[2] );
	T obj = temp->reduceNumberRepresentation();
	plhs[0] = convertPtr2Mat<T>( new T( obj ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "reduceNumberRepresentation output:\n" );
	// hypro::matrix_t<double> mat = temp->matrix();
	// hypro::vector_t<double> vec = temp->vector();
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

template <class T>
void MGeometricObject<T>::satisfiesHalfspace( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs < 2 ) mexErrMsgTxt( "MGeometricObject - satisfiesHalfspace: Expecting two output values!" );
	if ( nrhs < 5 ) mexErrMsgTxt( "MGeometricObject - satisfiesHalfspace: One or more arguments are missing!" );
	if ( nrhs > 5 ) mexWarnMsgTxt( "MGeometricObject - satisfiesHalfspace: One or more input arguments were ignored." );

	const mwSize* dims;
	dims = mxGetDimensions( prhs[3] );
	const int rows = (int)dims[0];

	T* temp = convertMat2Ptr<T>( prhs[2] );
	const int offset = (const int)mxGetScalar( prhs[4] );
	const hypro::vector_t<double> hy_normal = ObjectHandle::mVector2Hypro( prhs[3], rows );
	const hypro::Halfspace<double> hSpace = hypro::Halfspace<double>( hy_normal, offset );

	std::pair<hypro::CONTAINMENT, T> p = temp->satisfiesHalfspace( hSpace );
	std::string ans = "";
	ObjectHandle::convert2Matlab( p.first, ans );
	plhs[0] = mxCreateString( ans.c_str() );
	plhs[1] = convertPtr2Mat<T>( new T( p.second ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "satisfiesHalfspace input:\n" );
	// mexPrintf( "vector:\n" );
	// for ( int j = 0; j < hy_normal.rows(); j++ ) {
	// 	mexPrintf( " %f", hy_normal( j ) );
	// }
	// mexPrintf( "offset: %f\n", offset );
	// mexPrintf( "\noutput:\n" );
	// mexPrintf( "containment: %s\n", ans.c_str() );
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::satisfiesHalfspaces( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs < 2 ) mexErrMsgTxt( "MGeometricObject - satisfiesHalfspaces: Expecting two output values!" );
	if ( nrhs < 5 ) mexErrMsgTxt( "MGeometricObject - satisfiesHalfspaces: One or more arguments are missing!" );
	if ( nrhs > 5 )
		mexWarnMsgTxt( "MGeometricObject - satisfiesHalfspaces: One or more input arguments were ignored." );

	mxArray *out_box, *out_cont;
	const mwSize *mat_dims, *vec_dims;
	int mat_rows, mat_cols, vec_len;

	T* temp = convertMat2Ptr<T>( prhs[2] );
	mat_dims = mxGetDimensions( prhs[3] );
	vec_dims = mxGetDimensions( prhs[4] );
	mat_cols = (int)mat_dims[1];
	mat_rows = (int)mat_dims[0];
	vec_len = (int)vec_dims[0];

	const hypro::matrix_t<double> hy_matrix = ObjectHandle::mMatrix2Hypro( prhs[3], mat_rows, mat_cols );
	const hypro::vector_t<double> hy_vector = ObjectHandle::mVector2Hypro( prhs[4], vec_len );
	std::pair<hypro::CONTAINMENT, T> p = temp->satisfiesHalfspaces( hy_matrix, hy_vector );

	std::string ans = "";
	ObjectHandle::convert2Matlab( p.first, ans );
	out_cont = plhs[0] = mxCreateString( ans.c_str() );
	T* b = new T( p.second );
	plhs[1] = convertPtr2Mat<T>( b );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "satisfiesHalfspaces input:\n" );
	// mexPrintf( "matrix:\n" );
	// for ( int i = 0; i < hy_matrix.rows(); i++ ) {
	// 	for ( int j = 0; j < hy_matrix.cols(); j++ ) {
	// 		mexPrintf( " %f", hy_matrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "\nvector: " );
	// for ( int i = 0; i < hy_vector.rows(); i++ ) {
	// 	mexPrintf( " %f", hy_vector( i ) );
	// }

	// mexPrintf( "\noutput:\n" );
	// mexPrintf( "containment: %s\n", ans.c_str() );
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::projectOn( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - project: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - project: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - project: One or more input arguments were ignored." );

	const mwSize* vec_dims;
	double* in_dimensions;
	int len;

	T* obj = convertMat2Ptr<T>( prhs[2] );
	vec_dims = mxGetDimensions( prhs[3] );
	len = (int)vec_dims[0];
	std::vector<std::size_t> hy_dimensions = ObjectHandle::mSizeVector2Hypro( prhs[3], len );
	T temp = obj->projectOn( hy_dimensions );
	plhs[0] = convertPtr2Mat<T>( new T( temp ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "project input:\n" );
	// mexPrintf( "dims: " );
	// for ( int i = 0; i < hy_dimensions.size(); i++ ) {
	// 	mexPrintf( " %d", hy_dimensions[i] );
	// }
	// mexPrintf( "\n" );
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::linearTransformation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - linearTransformation: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - linearTransformation: One or more arguments are missing!" );
	if ( nrhs > 4 )
		mexWarnMsgTxt( "MGeometricObject - lineaTransformation: One or more input arguments were ignored." );
	const mwSize* dims;
	int rows, cols;
	dims = mxGetDimensions( prhs[3] );
	cols = (int)dims[1];
	rows = (int)dims[0];

	T* obj = convertMat2Ptr<T>( prhs[2] );
	hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro( prhs[3], rows, cols );
	T temp = obj->linearTransformation( mat );
	plhs[0] = convertPtr2Mat<T>( new T( temp ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "linearTransformation input:\n" );
	// mexPrintf( "matrix:\n" );
	// for ( int i = 0; i < mat.rows(); i++ ) {
	// 	for ( int j = 0; j < mat.cols(); j++ ) {
	// 		mexPrintf( " %f", mat( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf("output matrix:\n");
	// hypro::matrix_t<double> m = temp.matrix();
	// for ( int i = 0; i < m.rows(); i++ ) {
	// 	for ( int j = 0; j < m.cols(); j++ ) {
	// 		mexPrintf( " %f", m( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::affineTransformation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - affineTransformation: Expecting one output value!" );
	if ( nrhs < 5 ) mexErrMsgTxt( "MGeometricObject - affineTransformation: One or more arguments are missing!" );
	if ( nrhs > 5 )
		mexWarnMsgTxt( "MGeometricObject - affineTransformation: One or more input arguments were ignored." );

	const mwSize *mat_dims, *vec_dims;
	double *in_matrix, *in_vector;
	int mat_rows, mat_cols, vec_len;

	T* obj = convertMat2Ptr<T>( prhs[2] );
	mat_dims = mxGetDimensions( prhs[3] );
	vec_dims = mxGetDimensions( prhs[4] );
	mat_cols = (int)mat_dims[1];
	mat_rows = (int)mat_dims[0];
	vec_len = (int)vec_dims[0];

	hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro( prhs[3], mat_rows, mat_cols );
	hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro( prhs[4], vec_len );

	T temp = obj->affineTransformation( matrix, vector );
	plhs[0] = convertPtr2Mat<T>( new T( temp ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "affineTransformation input:\n" );
	// mexPrintf( "matrix:\n" );
	// for ( int i = 0; i < matrix.rows(); i++ ) {
	// 	for ( int j = 0; j < matrix.cols(); j++ ) {
	// 		mexPrintf( " %f", matrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "\nvector: " );
	// for ( int i = 0; i < vector.rows(); i++ ) {
	// 	mexPrintf( " %f", vector( i ) );
	// }
	// mexPrintf("output matrix:\n");
	// hypro::matrix_t<double> m = temp.matrix();
	// for ( int i = 0; i < m.rows(); i++ ) {
	// 	for ( int j = 0; j < m.cols(); j++ ) {
	// 		mexPrintf( " %f", m( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::minkowskiSum( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - minkowskiSum: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - minkowskiSum: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - minkowskiSum: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	T* obj_rhs = convertMat2Ptr<T>( prhs[3] );
	T sum = obj->minkowskiSum( *obj_rhs );
	plhs[0] = convertPtr2Mat<T>( new T( sum ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "minkowskiSum\n" );
	// mexPrintf("output matrix:\n");
	// hypro::matrix_t<double> m = sum.matrix();
	// for ( int i = 0; i < m.rows(); i++ ) {
	// 	for ( int j = 0; j < m.cols(); j++ ) {
	// 		mexPrintf( " %f", m( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::intersect( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - intersect: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - intersect: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - intersect: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	T* obj_rhs = convertMat2Ptr<T>( prhs[3] );
	T intersected = obj->intersect( *obj_rhs );
	plhs[0] = convertPtr2Mat<T>( new T( intersected ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "intersect\n" );
	// mexPrintf("output matrix:\n");
	// hypro::matrix_t<double> m = intersected.matrix();
	// for ( int i = 0; i < m.rows(); i++ ) {
	// 	for ( int j = 0; j < m.cols(); j++ ) {
	// 		mexPrintf( " %f", m( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::intersectHalfspace( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - intersectHalfspace: Expecting two output values!" );
	if ( nrhs < 5 ) mexErrMsgTxt( "MGeometricObject - intersectHalfspace: One or more arguments are missing!" );
	if ( nrhs > 5 ) mexWarnMsgTxt( "MGeometricObject - intersectHalfspace: One or more input arguments were ignored." );

	const mwSize* dims;
	dims = mxGetDimensions( prhs[3] );
	const int rows = (int)dims[0];

	T* obj = convertMat2Ptr<T>( prhs[2] );
	const hypro::vector_t<double> hy_normal = ObjectHandle::mVector2Hypro( prhs[3], rows );
	const int offset = (const int)mxGetScalar( prhs[4] );

	const hypro::Halfspace<double> hSpace = hypro::Halfspace<double>( hy_normal, offset );
	T temp = obj->intersectHalfspace( hSpace );
	plhs[0] = convertPtr2Mat<T>( new T( temp ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "intersectHalfspace input:\n" );
	// mexPrintf( "\nvector: " );
	// for ( int i = 0; i < hy_normal.rows(); i++ ) {
	// 	mexPrintf( " %f", hy_normal( i ) );
	// }
	// mexPrintf( "\noffset: %d", offset );
	// mexPrintf("output matrix:\n");
	// hypro::matrix_t<double> m = temp.matrix();
	// for ( int i = 0; i < m.rows(); i++ ) {
	// 	for ( int j = 0; j < m.cols(); j++ ) {
	// 		mexPrintf( " %f", m( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::intersectHalfspaces( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - intersectHalfspaces: Expecting one output value!" );
	if ( nrhs < 5 ) mexErrMsgTxt( "MGeometricObject - intersectHalfspaces: One or more arguments are missing!" );
	if ( nrhs > 5 )
		mexWarnMsgTxt( "MGeometricObject - intersectHalfspaces: One or more input arguments were ignored." );

	const mwSize *mat_dims, *vec_dims;
	int mat_rows, mat_cols, vec_len;

	T* obj = convertMat2Ptr<T>( prhs[2] );
	mat_dims = mxGetDimensions( prhs[3] );
	vec_dims = mxGetDimensions( prhs[4] );
	mat_cols = (int)mat_dims[1];
	mat_rows = (int)mat_dims[0];
	vec_len = (int)vec_dims[0];

	hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro( prhs[3], mat_rows, mat_cols );
	hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro( prhs[4], vec_len );

	T temp = obj->intersectHalfspaces( matrix, vector );
	plhs[0] = convertPtr2Mat<T>( new T( temp ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "intersectHalfspaces input:\n" );
	// mexPrintf( "matrix:\n" );
	// for ( int i = 0; i < matrix.rows(); i++ ) {
	// 	for ( int j = 0; j < matrix.cols(); j++ ) {
	// 		mexPrintf( " %f", matrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "\nvector: " );
	// for ( int i = 0; i < vector.rows(); i++ ) {
	// 	mexPrintf( " %f", vector( i ) );
	// }
	// mexPrintf("output matrix:\n");
	// hypro::matrix_t<double> m = temp.matrix();
	// for ( int i = 0; i < m.rows(); i++ ) {
	// 	for ( int j = 0; j < m.cols(); j++ ) {
	// 		mexPrintf( " %f", m( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::contains_point( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - contains_point: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - contains_point: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - contains_point: One or more input arguments were ignored." );

	const mwSize* dims;
	int point_len;
	T* obj = convertMat2Ptr<T>( prhs[2] );
	dims = mxGetDimensions( prhs[3] );
	point_len = (int)dims[0];
	hypro::Point<double> hy_point = ObjectHandle::mPoint2Hypro( prhs[3], point_len );
	const bool ans = obj->contains( hy_point );
	plhs[0] = mxCreateLogicalScalar( ans );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "contains_point output:\n" );
	// if ( ans ) {
	// 	mexPrintf( "yes\n" );
	// } else {
	// 	mexPrintf( "no\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::contains_object( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - contains_object: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - contains_object: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - contains_object: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	T* obj_arg = convertMat2Ptr<T>( prhs[3] );

	const bool ans = obj->contains( *obj_arg );
	plhs[0] = mxCreateLogicalScalar( ans );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "contains_object output:\n" );
	// if ( ans ) {
	// 	mexPrintf( "yes\n" );
	// } else {
	// 	mexPrintf( "no\n" );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::unite_single( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - unite_single: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - unite_single: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - unite_single: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	T* obj_rhs = convertMat2Ptr<T>( prhs[3] );

	T temp = obj->unite( *obj_rhs );
	plhs[0] = convertPtr2Mat<T>( new T( temp ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "unite_single output:\n" );
	// hypro::matrix_t<double> matrix = temp.matrix();
	// hypro::vector_t<double> vector = temp.vector();

	// mexPrintf( "matrix:\n" );
	// for ( int i = 0; i < matrix.rows(); i++ ) {
	// 	for ( int j = 0; j < matrix.cols(); j++ ) {
	// 		mexPrintf( " %f", matrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "\nvector: " );
	// for ( int i = 0; i < vector.rows(); i++ ) {
	// 	mexPrintf( " %f", vector( i ) );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::unite_vec( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - unite_vec: Expecting one output value!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - unite_vec: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - unite_vec: One or more input arguments were ignored." );

	const mwSize* dims;
	dims = mxGetDimensions( prhs[2] );
	const int len = dims[1];
	const std::vector<T> objects = ObjectHandle::objArray2Hypro<T>( prhs[2], len );
	T united = T::unite( objects );
	plhs[0] = convertPtr2Mat<T>( new T( united ) );

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "unite_vec output:\n" );
	// hypro::matrix_t<double> matrix = united.matrix();
	// hypro::vector_t<double> vector = united.vector();

	// mexPrintf( "matrix:\n" );
	// for ( int i = 0; i < matrix.rows(); i++ ) {
	// 	for ( int j = 0; j < matrix.cols(); j++ ) {
	// 		mexPrintf( " %f", matrix( i, j ) );
	// 	}
	// 	mexPrintf( "\n" );
	// }
	// mexPrintf( "\nvector: " );
	// for ( int i = 0; i < vector.rows(); i++ ) {
	// 	mexPrintf( " %f", vector( i ) );
	// }
	// //+++++++++++++TESTING++++++++++++++++++++
}

template <class T>
void MGeometricObject<T>::reduceRepresentation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - reduceRepresentation: One or more arguments are missing!" );
	if ( nrhs > 3 )
		mexWarnMsgTxt( "MGeometricObject - reduceRepresentation: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	obj->reduceRepresentation();

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "reduceRepresentation output:\n" );
	// hypro::matrix_t<double> mat = obj->matrix();
	// hypro::vector_t<double> vec = obj->vector();
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

template <class T>
void MGeometricObject<T>::clear( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - clear: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - clear: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	obj->clear();

	// //+++++++++++++TESTING++++++++++++++++++++
	// mexPrintf( "clear output:\n" );
	// hypro::matrix_t<double> mat = obj->matrix();
	// hypro::vector_t<double> vec = obj->vector();
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

template <class T>
void MGeometricObject<T>::ostream( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "HyProGeometricObject - ostream: One or more input arguments are missing." );
	if ( nrhs > 3 ) mexWarnMsgTxt( "HyProGeometricObject - ostream: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	hypro::matrix_t<double> mat = obj->matrix();
	hypro::vector_t<double> vec = obj->vector();

	int rows = mat.rows();
	int cols = mat.cols();

	int len = vec.size();

	mexPrintf( "Matrix: [" );
	for ( int i = 0; i < rows; i++ ) {
		for ( int j = 0; j < cols; j++ ) {
			mexPrintf( "%f ", mat( i, j ) );
		}
		mexPrintf( "\n" );
	}
	mexPrintf( "]\n" );

	mexPrintf( "Vector: [" );
	for ( int i = 0; i < len; i++ ) {
		mexPrintf( "%f ", vec( i ) );
	}
	mexPrintf( "]\n\n" );
}