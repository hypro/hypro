#include <ppl.hh>

int main(int argc, char** argv) {
    
    using namespace Parma_Polyhedra_Library::IO_Operators;
    
    Parma_Polyhedra_Library::C_Polyhedron mPolyhedron = Parma_Polyhedra_Library::C_Polyhedron(2, Parma_Polyhedra_Library::UNIVERSE);
    Parma_Polyhedra_Library::Variable a(0);
    Parma_Polyhedra_Library::Variable b(1);
    
    Parma_Polyhedra_Library::Linear_Expression polynom;
    polynom.set_space_dimension(2);
    polynom.set_coefficient(a, 1);
    polynom.set_coefficient(b, 3);
    polynom.set_inhomogeneous_term(-4);
    
    std::cout << "Polynom: " << polynom << std::endl;
    
    Parma_Polyhedra_Library::Constraint constraint;
    constraint = polynom <= 0;
    
    std::cout << "Constraint: ";
    constraint.print();
    std::cout << " Dimension: " << constraint.space_dimension()  << std::endl;
    
    mPolyhedron.add_constraint(constraint);
    
    std::cout << "Polyhedron: ";
    mPolyhedron.print();
    std::cout << std::endl;
}
