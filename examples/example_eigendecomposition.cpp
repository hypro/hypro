/**
 * Sandbox for the Eigendecomposition project.
 */


#include "representations/GeometricObject.h"
#include "util/Plotter.h"
#include <Eigen/Eigenvalues>

int main()
{
	using namespace hypro;
	using Number = double;
	using Matrix = matrix_t<Number>;

	// first matrix decomposition tests.

	Matrix A = Matrix(2,2);
	A << 0.1,0.02,0.2,0.02;
	std::cout << "A: " << A << std::endl;

	// decompose (directly in constructor)
	Eigen::EigenSolver<Matrix> es(A);

	std::cout << "Eigenvalues: " << es.eigenvalues() << std::endl;
	std::cout << "Eigenvectors: " << es.eigenvectors() << std::endl;

	//re-create matrix

	Matrix D = Matrix::Zero(2,2);
	D(0,0) = es.eigenvalues()(0).real();
	D(1,1) = es.eigenvalues()(1).real();

	std::cout << "D: " << D << std::endl;

	Matrix Q = Matrix::Zero(2,2);
	Q(0,0) = es.eigenvectors()(0,0).real();
	Q(0,1) = es.eigenvectors()(0,1).real();
	Q(1,0) = es.eigenvectors()(1,0).real();
	Q(1,1) = es.eigenvectors()(1,1).real();

	std::cout << "Q: " << Q << std::endl;
	std::cout << "Q^-1: " << Q.inverse() << std::endl;

	Matrix newA = Q*D*Q.inverse();

	std::cout << "Re-assembled A: " << newA << std::endl;

	return 0;
}
