/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Examples for constructing Eigendecomposition of Matrices
 */

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>
#include <eigen3/Eigen/Eigenvalues>

int main() {
    using namespace hypro;
    using Number = double;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    // first matrix decomposition tests.
    int n = 3;
    Matrix A = Matrix(n, n);
    /*
            A << 	0.1,0.02,
                            0.2,0.02;
    */

    A << 0, 1, 0, 0, 0, -9.81, 0, 0, 0;

    Matrix B = Matrix(n, n);
    /*
            B << 	1, 0,
                            0, 1;
    */

    B << 1, 0, 0, 0, 1, 0, 0, 0, 1;

    std::cout << "A: " << std::endl << A << std::endl;
    std::cout << "B: " << std::endl << B << std::endl;

    // decompose (directly in constructor)
    // Eigen::EigenSolver<Matrix> es(A);
    Eigen::GeneralizedSelfAdjointEigenSolver<Matrix> es(A, B);
    std::cout << "The eigenvalues of the pencil (A,B) are:" << std::endl
              << es.eigenvalues() << std::endl;
    std::cout << "The matrix of eigenvectors, V, is:" << std::endl
              << es.eigenvectors() << std::endl;
    // std::cout << "Eigenvalues: " << es.eigenvalues() << std::endl;
    // std::cout << "Eigenvectors: " << es.eigenvectors() << std::endl;

    // re-create matrix
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
