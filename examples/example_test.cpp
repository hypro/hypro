/*
 * This is a test example file. Each example file must contain a main function and be registered in the CMakeLists.txt
 * in the example folder in order to be a valid target. The example can be generated with "make examplename", e.g. "make example_test".
 *
 * File:   example_test.cpp
 * Author: Stefan Schupp
 *
 * Created on November 19, 2013, 12:38 PM
 */

#include <cstdlib>
#include "../src/lib/config.h"

using namespace std;

/*
 *
 */
int main(int argc, char** argv) {

	mpq_class v1("0");

    mpq_class v2("13767846572620363587166795601594603052876816481/45671926166590716193865151022383844364247891968");

    hypro::vector_t<carl::FLOAT_T<mpq_class>> testVector = hypro::vector_t<carl::FLOAT_T<mpq_class>>::Zero(3);

    testVector(0) = carl::FLOAT_T<mpq_class>(v1);

    testVector(1) = carl::FLOAT_T<mpq_class>(v2);

    std::cout << "Test vector: " << testVector << std::endl;

    carl::FLOAT_T<mpq_class> norm = Eigen::norm(testVector);

    std::cout << "Norm: " << norm << std::endl;

    //ASSERT_TRUE(norm > 0);

    //hypro::vector_t<carl::FLOAT_T<mpq_class>> resultNormalized = testVector.normalized();

    //std::cout << resultNormalized << std::endl;

    return 0;
}

