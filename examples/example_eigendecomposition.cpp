/**
 * Examples for constructing Eigendecomposition of Matrices
 */


#include "representations/GeometricObject.h"
#include "util/Plotter.h"
#include <eigen3/Eigen/Eigenvalues>

int main()
{
	using namespace hypro;
	using Number = double;
	using Matrix = matrix_t<Number>;
	using Vector = vector_t<Number>;

	// first matrix decomposition tests.
	int n = 3;
	Matrix A = Matrix(n,n);
/*
	A << 	0.1,0.02,
			0.2,0.02;
*/

	A << 	0, 1, 0,
			0, 0, -9.81,
			0, 0, 0;

	Matrix B = Matrix(n,n);
/*
	B << 	1, 0,
			0, 1;
*/

	B << 	1, 0, 0,
			0, 1, 0,
			0, 0, 1;

	std::cout << "A: " << std::endl << A << std::endl;
	std::cout << "B: " << std::endl << B << std::endl;

	// decompose (directly in constructor)
	//Eigen::EigenSolver<Matrix> es(A);
	Eigen::GeneralizedSelfAdjointEigenSolver<Matrix> es(A,B);
	std::cout << "The eigenvalues of the pencil (A,B) are:" << std::endl << es.eigenvalues() << std::endl;
	std::cout << "The matrix of eigenvectors, V, is:" << std::endl << es.eigenvectors() << std::endl;
	//std::cout << "Eigenvalues: " << es.eigenvalues() << std::endl;
	//std::cout << "Eigenvectors: " << es.eigenvectors() << std::endl;

	//re-create matrix
/*
	Matrix D = Matrix::Zero(2,2);
	D(0,0) = es.eigenvalues()(0);
	D(1,1) = es.eigenvalues()(1);

	std::cout << "D: " << D << std::endl;

	Matrix Q = Matrix::Zero(2,2);
	Q(0,0) = es.eigenvectors()(0,0);
	Q(0,1) = es.eigenvectors()(0,1);
	Q(1,0) = es.eigenvectors()(1,0);
	Q(1,1) = es.eigenvectors()(1,1);

	std::cout << "Q: " << Q << std::endl;
	std::cout << "Q^-1: " << Q.inverse() << std::endl;

	Matrix newA = Q*D*Q.inverse();

	std::cout << "Re-assembled A: " << newA << std::endl;
*/

	return 0;
}
