#include "../src/hypro/types.h"

int main(int argc, char** argv) {
    using namespace hypro;

    using Number = mpq_class;
    matrix_t<Number> A = matrix_t<Number>(1,2);

    std::cout << "Rows at compile time: " << A.RowsAtCompileTime << std::endl;

    A << 1,1;

    std::cout << "Solution: " << convert<Number,double>(A.fullPivLu().kernel()) << std::endl;

}



