#include "hypro/representations/GeometricObjectBase.h"

#include <iostream>
#include <z3++.h>

typedef mpq_class Number;

/**
   Demonstration of how Z3 can be used to prove validity of
   De Morgan's Duality Law: {e not(x and y) <-> (not x) or ( not y) }
*/
void demorgan() {
    std::cout << "de-Morgan example\n";
    
    z3::context c;

    z3::expr x = c.bool_const("x");
    z3::expr y = c.bool_const("y");
    z3::expr conjecture = (!(x && y)) == (!x || !y);
    
    z3::solver s(c);
    // adding the negation of the conjecture as a constraint.
    s.add(!conjecture);
    std::cout << s << "\n";
    std::cout << s.to_smt2() << "\n";
    switch (s.check()) {
        case z3::unsat:   std::cout << "de-Morgan is valid\n"; break;
        case z3::sat:     std::cout << "de-Morgan is not valid\n"; break;
        case z3::unknown: std::cout << "unknown\n"; break;
    }
}

/**
   \brief Find a model for <tt>x >= 1 and y < x + 3</tt>.
*/
void find_model_example1() {
    std::cout << "find_model_example1\n";
    z3::context c;
    z3::expr x = c.int_const("x");
    z3::expr y = c.int_const("y");
    z3::solver s(c);

    s.add(x >= 1);
    s.add(y < x + 3);
    std::cout << s.check() << "\n";

    z3::model m = s.get_model();
    std::cout << m << "\n";
    // traversing the model
    for (unsigned i = 0; i < m.size(); i++) {
        z3::func_decl v = m[i];
        // this problem contains only constants
        assert(v.arity() == 0); 
        std::cout << v.name() << " = " << m.get_const_interp(v) << "\n";
    }
    // we can evaluate expressions in the model.
    std::cout << "x + y + 1 = " << m.eval(x + y + 1) << "\n";
}

void H_Polytope_to_CNF(){
    std::cout << "Converting an H-Polytope into a CNF example\n";
    // Create a Z3 context
    z3::context ctx;

    // Feas example
    hypro::matrix_t<Number> A(3, 2);
    A << -1, -2, 2, 1, -1, 1;

    hypro::vector_t<Number> b(3);
    b << 4, 4, -1;

    // Infeas example
    // hypro::matrix_t<Number> A(4, 3);
    // A << 1, -1, 0, 1, 0, -1, -1, +1, +2, 0, 0, -1;

    // hypro::vector_t<Number> b(4);
    // b << 0, 0, 0, -1;

    // Feas example
    // hypro::matrix_t<Number> A(5, 2);
    // A << 1, 1, 1, -4, -1, -4, -1, 2, -3, 2;

    // hypro::vector_t<Number> b(5);
    // b << 4, 2, -3, 3, 4;

    std::vector <carl::Relation> rels;
    for (size_t i = 0; i < A.rows(); ++i) {
        rels.push_back(carl::Relation::LEQ);
    }

    std::cout << "A = \n" << A << std::endl;
    std::cout << "b = \n" << b << std::endl;
    std::cout << "Relations: " << rels << std::endl;

    hypro::EvaluationResult<Number> result = hypro::z3GetInternalPoint(A, b, rels);
    std::cout << "Optimum value:" << result.optimumValue << std::endl;
    std::cout << "Support value:" << result.supportValue << std::endl;
    std::cout << "Error code:" << result.errorCode << std::endl;
}

void point_inclusion() {
    // Given system Ax <= b, check if it is consistent
    hypro::matrix_t<Number> A(3, 2);
    A << 1, 2, 3, -1, -1, 1;

    hypro::vector_t<Number> b(3);
    b << 5, 6, -2;

    hypro::vector_t<Number> x(2);
    x << 1, -2;

    std::vector <carl::Relation> rels;
    for (size_t i = 0; i < A.rows(); ++i) {
        rels.push_back(carl::Relation::LEQ);
    }

    std::cout << "A = \n" << A << std::endl;
    std::cout << "b = \n" << b << std::endl;
    std::cout << "x = \n" << x << std::endl;
    std::cout << "Relations: " << rels << std::endl;

    // Check consistency
    bool isConsistent = hypro::z3CheckPoint(A, b, rels, hypro::Point<Number>(x));
    std::cout << "The system is: " << (isConsistent ? "consistent" : "inconsistent") << std::endl;
}

void transformed_point_inclusion() {
    hypro::matrix_t<Number> C(5, 2);
    C << 1, 1, 1, -4, -1, -4, -1, 2, -3, 2;

    hypro::vector_t<Number> d(5);
    d << 4, 2, -3, 3, 4;

    hypro::matrix_t<Number> V(3,2);
    V << 1, 1, 1, 0, 0, 1;

    hypro::vector_t<Number> c(3);
    c << 1, 2, 3;

    hypro::vector_t<Number> alpha(2);
    alpha << 2.5, 0.125;

    hypro::vector_t<Number> x = c + V * alpha;

    std::cout << "C = \n" << C << std::endl;
    std::cout << "d = \n" << d << std::endl;
    std::cout << "alpha = \n" << alpha << std::endl;\
    std::cout << "V = \n" << V << std::endl;
    std::cout << "c = \n" << c << std::endl;
    std::cout << "x = \n" << x << std::endl;

    // Check consistency
    hypro::EvaluationResult<Number> result = hypro::z3GetInternalPoint(C, d, V, c, hypro::Point<Number>(x));
    std::cout << "Optimum value:" << result.optimumValue << std::endl;
    std::cout << "Support value:" << result.supportValue << std::endl;
    std::cout << "Error code:" << result.errorCode << std::endl;
    std::cout << "The system is: " << (result.errorCode == hypro::SOLUTION::FEAS ? "consistent" : "inconsistent") << std::endl;
}


int main() {
    // More examples at: https://github.com/Z3Prover/z3/blob/master/examples/c%2B%2B/example.cpp
    // demorgan();
    // find_model_example1();

    // Own examples, useful for CEGAR
    // H_Polytope_to_CNF();
    // point_inclusion();
    transformed_point_inclusion();

    return 0;
}