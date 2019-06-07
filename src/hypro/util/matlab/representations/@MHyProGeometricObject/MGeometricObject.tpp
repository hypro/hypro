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
}

template <typename T>
void MGeometricObject<T>::new_vector( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - new_vector: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - new_vector: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - new_vector: One or more input arguments were ignored." );

	double* in_vector;
	const mwSize* vec_dims;
	int len;
	vec_dims = mxGetDimensions(prhs[2]);
	len = (int)vec_dims[0];
	hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro( prhs[2], len );


	T* temp = new T( vector );
	plhs[0] = convertPtr2Mat<T>( temp );
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
}

template <class T>
void MGeometricObject<T>::scale( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - scale: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - scale: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - scale: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	const double factor = (double)mxGetScalar( prhs[3] );
	T temp = obj->operator*( factor );
	T* b = new T( temp );
	plhs[0] = convertPtr2Mat<T>( b );
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
}

template <class T>
void MGeometricObject<T>::is_empty( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - isEmpty: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - isEmpty: One argument missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - isEmpty: One or more input arguments were ignored." );

	mexPrintf("IS EMPTY\n");
	T* temp = convertMat2Ptr<T>( prhs[2] );
	const bool empty = temp->empty();
	plhs[0] = mxCreateLogicalScalar( empty );
}

template <class T>
void MGeometricObject<T>::vertices( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if(nlhs != 1)
	    mexErrMsgTxt("MGeometricObject - vertices: Expecting an output!");
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
}

template <class T>
void MGeometricObject<T>::equal( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - ==: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - ==: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - ==: One or more input arguments were ignored." );

	T* set_1 = convertMat2Ptr<T>( prhs[2] );
	T* set_2 = convertMat2Ptr<T>( prhs[3] );
	mxLogical ans = false;
	if ( *set_1 == *set_2 ) {
		ans = true;
	}
	plhs[0] = mxCreateLogicalScalar( ans );
}

template <class T>
void MGeometricObject<T>::unequal( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - !=: Expecting an output!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - !=: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - !=: One or more input arguments were ignored." );

	T* set_1 = convertMat2Ptr<T>( prhs[2] );
	T* set_2 = convertMat2Ptr<T>( prhs[3] );
	mxLogical ans = false;
	if ( *set_1 != *set_2 ) {
		ans = true;
	}
	plhs[0] = mxCreateLogicalScalar( ans );
}

template <class T>
void MGeometricObject<T>::supremum( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - supremum: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - supremum: One argument missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - supremum: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	double supremum = obj->supremum();
	plhs[0] = mxCreateDoubleScalar( supremum );
}

template <class T>
void MGeometricObject<T>::dimension( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - dimension: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - dimension: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - dimension: One or more input arguments were ignored." );

	T* temp = convertMat2Ptr<T>( prhs[2] );
	std::size_t dim = temp->dimension();
	plhs[0] = mxCreateDoubleScalar( dim );
}

template <class T>
void MGeometricObject<T>::removeRedundancy( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - removeRedundancy: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - removeRedundancy: One or more input arguments were ignored." );

	T* temp = convertMat2Ptr<T>( prhs[2] );
	temp->removeRedundancy();
}

template <class T>
void MGeometricObject<T>::size( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - size: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - size: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - size: One or more input arguments were ignored." );

	T* temp = convertMat2Ptr<T>( prhs[2] );
	std::size_t dim = temp->size();

	plhs[0] = mxCreateDoubleScalar( dim );
}

template <class T>
void MGeometricObject<T>::reduceNumberRepresentation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - reduceNumberRepresentation: Expecting an output!" );
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - reduceNumberRepresentation: One or more arguments are missing!" );
	if ( nrhs > 3 )
		mexWarnMsgTxt( "MGeometricObject - reduceNumberRepresentation: One or more input arguments were ignored." );

	T* temp = convertMat2Ptr<T>( prhs[2] );
	T obj = temp->reduceNumberRepresentation();
	T* b = new T( obj );
	plhs[0] = convertPtr2Mat<T>( b );
}

template <class T>
void MGeometricObject<T>::satisfiesHalfspace( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs < 2 ) mexErrMsgTxt( "MGeometricObject - satisfiesHalfspace: Expecting two output values!" );
	if ( nrhs < 5 ) mexErrMsgTxt( "MGeometricObject - satisfiesHalfspace: One or more arguments are missing!" );
	if ( nrhs > 5 ) mexWarnMsgTxt( "MGeometricObject - satisfiesHalfspace: One or more input arguments were ignored." );

	mxArray **out_box, *out_cont;
	const mwSize* dims;
	double *in_normal, *cont;
	int rows;

	T* temp = convertMat2Ptr<T>( prhs[2] );

	const int offset = (const int)mxGetScalar( prhs[4] );
	dims = mxGetDimensions( prhs[3] );
	rows = (int) dims[0];
	const hypro::vector_t<double> hy_normal = ObjectHandle::mVector2Hypro( prhs[3], rows );
	const hypro::Halfspace<double> hSpace = hypro::Halfspace<double>( hy_normal, offset );

	std::pair<hypro::CONTAINMENT, T> p = temp->satisfiesHalfspace( hSpace );
	std::string ans = "";
	ObjectHandle::convert2Matlab( p.first, ans );
	out_cont = plhs[0] = mxCreateString( ans.c_str() );
	T* b = new T( p.second );
	plhs[1] = convertPtr2Mat<T>( b );
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
}

template <class T>
void MGeometricObject<T>::project( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - project: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - project: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - project: One or more input arguments were ignored." );

	const mwSize* vec_dims;
	double* in_dimensions;
	int len;

	T* obj = convertMat2Ptr<T>( prhs[2] );
	vec_dims = mxGetDimensions( prhs[3] );
	len = (int)vec_dims[0];

	std::vector<hypro::Point<double>> vertices = obj->vertices();
	std::vector<std::size_t> hy_dimensions = ObjectHandle::mSizeVector2Hypro( prhs[3], len );

	T temp = obj->project( hy_dimensions );
	std::vector<hypro::Point<double>> verticest = obj->vertices();
	T* b = new T( temp );
	plhs[0] = convertPtr2Mat<T>( b );
}

template <class T>
void MGeometricObject<T>::linearTransformation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - linearTransformation: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - linearTransformation: One or more arguments are missing!" );
	if ( nrhs > 4 )
		mexWarnMsgTxt( "MGeometricObject - lineaTransformation: One or more input arguments were ignored." );

	const mwSize* dims;
	double* in_matrix;
	int rows, cols;

	T* obj = convertMat2Ptr<T>( prhs[2] );
	dims = mxGetDimensions( prhs[3] );
	cols = (int)dims[1];
	rows = (int)dims[0];

	hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro( prhs[3], rows, cols );
	T temp = obj->linearTransformation( mat );
	T* b = new T( temp );
	plhs[0] = convertPtr2Mat<T>( b );
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

	hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro( prhs[3], mat_rows, mat_cols );
	hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro( prhs[4], vec_len );

	T temp = obj->affineTransformation( mat, vec );
	T* b = new T( temp );
	plhs[0] = convertPtr2Mat<T>( b );
}

template <class T>
void MGeometricObject<T>::minkowskiSum( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - minkowskiSum: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - minkowskiSum: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - minkowskiSum: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	T* obj_rhs = convertMat2Ptr<T>( prhs[3] );

	T sum = obj->minkowskiSum( *obj_rhs );
	T* b = new T( sum );
	plhs[0] = convertPtr2Mat<T>( b );
}

template <class T>
void MGeometricObject<T>::intersect( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - intersect: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - intersect: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - intersect: One or more input arguments were ignored." );

	T* box = convertMat2Ptr<T>( prhs[2] );
	T* box_rhs = convertMat2Ptr<T>( prhs[3] );
	T sum = box->intersect( *box_rhs );
	T* b = new T( sum );
	plhs[0] = convertPtr2Mat<T>( b );
}

template <class T>
void MGeometricObject<T>::intersectHalfspace( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - intersectHalfspace: Expecting two output values!" );
	if ( nrhs < 5 ) mexErrMsgTxt( "MGeometricObject - intersectHalfspace: One or more arguments are missing!" );
	if ( nrhs > 5 ) mexWarnMsgTxt( "MGeometricObject - intersectHalfspace: One or more input arguments were ignored." );

	mxArray *out_box, *out_cont;
	const mwSize* dims;
	double *in_normal, *cont;
	int  cols;

	T* obj = convertMat2Ptr<T>( prhs[2] );
	const int offset = (const int)mxGetScalar( prhs[4] );
	dims = mxGetDimensions( prhs[3] );
	cols = (int)dims[1];

	const hypro::vector_t<double> hy_normal = ObjectHandle::mVector2Hypro( prhs[3], cols );
	const hypro::Halfspace<double> hSpace = hypro::Halfspace<double>( hy_normal, offset );

	T temp = obj->intersectHalfspace( hSpace );
	T* inter = new T( temp );
	plhs[0] = convertPtr2Mat<T>( inter );
}

template <class T>
void MGeometricObject<T>::intersectHalfspaces( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - intersectHalfspaces: Expecting one output value!" );
	if ( nrhs < 5 ) mexErrMsgTxt( "MGeometricObject - intersectHalfspaces: One or more arguments are missing!" );
	if ( nrhs > 5 )
		mexWarnMsgTxt( "MGeometricObject - intersectHalfspaces: One or more input arguments were ignored." );

	const mwSize *mat_dims, *vec_dims;
	double *in_matrix, *in_vector;
	int mat_rows, mat_cols, vec_len;

	T* obj = convertMat2Ptr<T>( prhs[2] );
	mat_dims = mxGetDimensions( prhs[3] );
	vec_dims = mxGetDimensions( prhs[4] );
	mat_cols = (int)mat_dims[1];
	mat_rows = (int)mat_dims[0];
	vec_len = (int)vec_dims[0];

	hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro( prhs[3], mat_rows, mat_cols );
	hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro( prhs[4], vec_len );

	T temp = obj->intersectHalfspaces( mat, vec );
	T* b = new T( temp );
	plhs[0] = convertPtr2Mat<T>( b );
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
}

template <class T>
void MGeometricObject<T>::contains_object( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - contains_box: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - contains_box: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - contains_box: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	T* obj_arg = convertMat2Ptr<T>( prhs[3] );

	const bool ans = obj->contains( *obj_arg );
	plhs[0] = mxCreateLogicalScalar( ans );
}

template <class T>
void MGeometricObject<T>::unite_single( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nlhs != 1 ) mexErrMsgTxt( "MGeometricObject - unite_single: Expecting one output value!" );
	if ( nrhs < 4 ) mexErrMsgTxt( "MGeometricObject - unite_single: One or more arguments are missing!" );
	if ( nrhs > 4 ) mexWarnMsgTxt( "MGeometricObject - unite_single: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	T* obj_rhs = convertMat2Ptr<T>( prhs[3] );

	T temp = obj->unite( *obj_rhs );
	T* b = new T( temp );
	plhs[0] = convertPtr2Mat<T>( b );
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
	T united = T::unite(objects);
	T* b = new T( united );
	plhs[0] = convertPtr2Mat<T>( b );
}

template <class T>
void MGeometricObject<T>::reduceRepresentation( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - reduceRepresentation: One or more arguments are missing!" );
	if ( nrhs > 3 )
		mexWarnMsgTxt( "MGeometricObject - reduceRepresentation: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	obj->reduceRepresentation();
}

template <class T>
void MGeometricObject<T>::clear( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
	if ( nrhs < 3 ) mexErrMsgTxt( "MGeometricObject - clear: One or more arguments are missing!" );
	if ( nrhs > 3 ) mexWarnMsgTxt( "MGeometricObject - clear: One or more input arguments were ignored." );

	T* obj = convertMat2Ptr<T>( prhs[2] );
	obj->clear();
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