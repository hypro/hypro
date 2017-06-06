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

	Matrix A = Matrix(3,3);
	A << 0.1,0,-56,0,0,1,0,0,0;
	std::cout << "A: " << A << std::endl;

	// decompose (directly in constructor)
	Eigen::EigenSolver<Matrix> es(A);

	std::cout << "Eigenvalues: " << es.eigenvalues() << std::endl;
	std::cout << "Eigenvectors: " << es.eigenvectors() << std::endl;

	//re-create matrix

	Matrix D = Matrix::Zero(3,3);
	D(0,0) = es.eigenvalues()(0).real();
	D(1,1) = es.eigenvalues()(1).real();
	D(2,2) = es.eigenvalues()(2).real();

	std::cout << "D: " << D << std::endl;

	Matrix Q = Matrix::Zero(3,3);
	Q(0,0) = es.eigenvectors()(0,0).real();
	Q(0,1) = es.eigenvectors()(0,1).real();
	Q(0,2) = es.eigenvectors()(0,2).real();
	Q(1,0) = es.eigenvectors()(1,0).real();
	Q(1,1) = es.eigenvectors()(1,1).real();
	Q(1,2) = es.eigenvectors()(1,2).real();
	Q(2,0) = es.eigenvectors()(2,0).real();
	Q(2,1) = es.eigenvectors()(2,1).real();
	Q(2,2) = es.eigenvectors()(2,2).real();

	std::cout << "Q: " << Q << std::endl;
	std::cout << "Q^-1: " << Q.inverse() << std::endl;

	Matrix newA = Q*D*Q.inverse();

	std::cout << "Re-assembled A: " << newA << std::endl;

	return 0;
}
