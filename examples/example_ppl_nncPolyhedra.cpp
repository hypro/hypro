/**
 * Example which shows how to use PPL NNC polyhedra
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @file example_ppl_nncPolyhedra.cpp
 * 
 * @since       2014-03-25
 * @version     2014-03-25
 */

#include <ppl.hh>

using namespace Parma_Polyhedra_Library;
using namespace std;
using namespace Parma_Polyhedra_Library::IO_Operators;

int main(int argc, char** argv) {
    Variable x(0);
    Variable a(1);
    Variable b(2);
    Variable c(3);
    Variable y(1);
    
    cout << "*** vars ***" << endl << x << ", " << y << ", " << b << ", " << c << endl;
    
    C_Polyhedron polytope1;
    
    C_Polyhedron ph(2, EMPTY);
    ph.add_generator(point());
    ph.add_generator(ray(x));
    ph.add_generator(ray(y));

    std::cout << "*** ph ***" << std::endl;
    std::cout << ph.generators() << std::endl;
    
    Generator_System gs = ph.generators();
    gs.insert(point(x));
    gs.insert(point(y));

    cout << "*** gs ***" << endl;
    cout << gs << endl;

    C_Polyhedron known_result(2);
    known_result.add_constraint(x >= 0);
    known_result.add_constraint(y >= 0);

    //return C_Polyhedron(gs) == known_result;
    
    Generator_System nncGs;
    nncGs.insert(point());
    nncGs.insert(point(3*x));
    nncGs.insert(point(3*x+3*y));
    nncGs.insert(point(3*y));
    
    cout << "Generator: " << nncGs << endl;
    
    nncGs.add_corresponding_points();
    
    cout << "Generator (with points): " << nncGs << endl;
    
    NNC_Polyhedron nncPoly(nncGs);
    
    cout << nncPoly << endl;
}