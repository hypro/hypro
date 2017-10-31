/**
 * \example example_differenceBounds.cpp This example shows how to use a representation by difference Bounds.
 */


#include "representations/GeometricObject.h"
#include "datastructures/Halfspace.h"
#include "datastructures/Point.h"
#include "util/Plotter.h"

typedef double Number;
hypro::DifferenceBounds <Number> testDBM;
hypro::DifferenceBounds <Number> testDBM2;
void createTestDBM();
void createTestDBM2();
void testComparison();
void testPlus();
void testVertices();
void testElapse();
void testRewind();
void testFree();
void testReset();
void testCopy();
void testShift();
void testEmpty();
void testContains();
void testIntersectConstraint();
void testPrint();

int main() {
    createTestDBM();
    createTestDBM2();
    //testComparison();
    //testPlus();
    //testVertices();
    //testElapse();
    //testRewind();
    //testFree();
    //testReset();
    //testCopy();
    //testShift();
    //testEmpty();
    //testContains();
    testIntersectConstraint();
    //testPrint();
    return 0;
}

void createTestDBM(){
    hypro::matrix_t<hypro::DifferenceBounds<Number>::DBMEntry> mat = hypro::matrix_t<hypro::DifferenceBounds<Number>::DBMEntry>(3,3);
    mat << hypro::DifferenceBounds<Number>::DBMEntry(0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(-4.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(-4.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(10.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(0.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(0.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(11.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(2.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(0.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ);
    testDBM = hypro::DifferenceBounds<Number>();
    testDBM.setDBM(mat);
    testDBM.setTimeHorizon(20.0);
}

void createTestDBM2(){
    hypro::matrix_t<hypro::DifferenceBounds<Number>::DBMEntry> mat = hypro::matrix_t<hypro::DifferenceBounds<Number>::DBMEntry>(3,3);
    mat << hypro::DifferenceBounds<Number>::DBMEntry(0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(-4.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(-4.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(9.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(0.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(0.0, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(10.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(1.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ),
            hypro::DifferenceBounds<Number>::DBMEntry(0.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ);
    testDBM2 = hypro::DifferenceBounds<Number>();
    testDBM2.setDBM(mat);
    testDBM2.setTimeHorizon(20.0);
}


void testComparison(){
    hypro::DifferenceBounds<Number>::DBMEntry infty = hypro::DifferenceBounds<Number>::DBMEntry(0,hypro::DifferenceBounds<Number>::BOUND_TYPE::INFTY);

    hypro::DifferenceBounds<Number>::DBMEntry smaller1 = hypro::DifferenceBounds<Number>::DBMEntry(1.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER);
    hypro::DifferenceBounds<Number>::DBMEntry smaller2 = hypro::DifferenceBounds<Number>::DBMEntry(2.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER);

    hypro::DifferenceBounds<Number>::DBMEntry smallerEq1 = hypro::DifferenceBounds<Number>::DBMEntry(1.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ);
    hypro::DifferenceBounds<Number>::DBMEntry smallerEq2 = hypro::DifferenceBounds<Number>::DBMEntry(2.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ);

    std::cout << infty << " < " << infty <<" :" << (infty < infty) << "\n";
    std::cout << smaller1 << " < " << infty <<" :" << (smaller1 < infty) << "\n";
    std::cout << infty << " < " << smaller1 <<" :" << (infty < smaller1) << "\n";
    std::cout << smallerEq1 << " < " << infty <<" :" << (smallerEq1 < infty) << "\n";
    std::cout << infty << " < " << smallerEq1 <<" :" << (infty < smallerEq1) << "\n";

    std::cout << smaller1 << " < " << smaller2 <<" :" << (smaller1 < smaller2) << "\n";
    std::cout << smaller2 << " < " << smaller1 <<" :" << (smaller2 < smaller1) << "\n";


    std::cout << smaller1 << " < " << smallerEq1 <<" :" << (smaller1 < smallerEq1) << "\n";
    std::cout << smallerEq1 << " < " << smaller1 <<" :" << (smallerEq1 < smaller1) << "\n";
    std::cout << smaller1 << " < " << smallerEq2 <<" :" << (smaller1 < smallerEq2) << "\n";
    std::cout << smallerEq2 << " < " << smaller1 <<" :" << (smallerEq2 < smaller1) << "\n";

    std::cout << smallerEq2 << " < " << smallerEq1 <<" :" << (smallerEq2 < smallerEq1) << "\n";
    std::cout << smallerEq1 << " < " << smallerEq2 <<" :" << (smallerEq1 < smallerEq2) << "\n";
}

void testPlus(){
    hypro::DifferenceBounds<Number>::DBMEntry infty = hypro::DifferenceBounds<Number>::DBMEntry(0,hypro::DifferenceBounds<Number>::BOUND_TYPE::INFTY);

    hypro::DifferenceBounds<Number>::DBMEntry smaller1 = hypro::DifferenceBounds<Number>::DBMEntry(1.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER);
    hypro::DifferenceBounds<Number>::DBMEntry smaller2 = hypro::DifferenceBounds<Number>::DBMEntry(2.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER);

    hypro::DifferenceBounds<Number>::DBMEntry smallerEq1 = hypro::DifferenceBounds<Number>::DBMEntry(1.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ);
    hypro::DifferenceBounds<Number>::DBMEntry smallerEq2 = hypro::DifferenceBounds<Number>::DBMEntry(2.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ);

    std::cout << infty << " + " << infty <<" :" << (infty + infty) << "\n";
    std::cout << smaller1 << " + " << infty <<" :" << (smaller1 + infty) << "\n";
    std::cout << infty << " + " << smaller1 <<" :" << (infty + smaller1) << "\n";
    std::cout << smallerEq1 << " + " << infty <<" :" << (smallerEq1 + infty) << "\n";
    std::cout << infty << " + " << smallerEq1 <<" :" << (infty + smallerEq1) << "\n";

    std::cout << smaller1 << " + " << smaller2 <<" :" << (smaller1 + smaller2) << "\n";
    std::cout << smaller2 << " + " << smaller1 <<" :" << (smaller2 + smaller1) << "\n";


    std::cout << smaller1 << " + " << smallerEq1 <<" :" << (smaller1 + smallerEq1) << "\n";
    std::cout << smallerEq1 << " + " << smaller1 <<" :" << (smallerEq1 + smaller1) << "\n";
    std::cout << smaller1 << " + " << smallerEq2 <<" :" << (smaller1 + smallerEq2) << "\n";
    std::cout << smallerEq2 << " + " << smaller1 <<" :" << (smallerEq2 + smaller1) << "\n";

    std::cout << smallerEq2 << " + " << smallerEq1 <<" :" << (smallerEq2 + smallerEq1) << "\n";
    std::cout << smallerEq1 << " + " << smallerEq2 <<" :" << (smallerEq1 + smallerEq2) << "\n";
}

void testVertices(){
    // compute vertices
    std::cout<< "Test instance vertices for DBM1: \n";
    std::vector<hypro::Point<Number>> verts1 = testDBM.vertices();
    std::cout<< verts1;

    std::cout<< "Test instance vertices for DBM2: \n";
    std::vector<hypro::Point<Number>> verts2 = testDBM2.vertices();
    std::cout<< verts2;

    //plot to pdf
    hypro::Plotter<Number>::getInstance().clear();
    unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject(verts1);
    unsigned obj3 = hypro::Plotter<Number>::getInstance().addObject(verts2);
    hypro::Plotter<Number>::getInstance().setObjectColor(obj2, hypro::plotting::colors[hypro::plotting::green]);
    hypro::Plotter<Number>::getInstance().setObjectColor(obj3, hypro::plotting::colors[hypro::plotting::red]);

    // create a *.plt file (gnuplot).
    hypro::Plotter<Number>::getInstance().setFilename("verticesTest");
    hypro::Plotter<Number>::getInstance().plot2d();
}

void testElapse(){
    std::cout<< "Test elapse: \n";

    hypro::DifferenceBounds <Number> elapsed = testDBM.elapse();
    std::cout<< elapsed;
    std::vector<hypro::Point<Number>> verts = elapsed.vertices();
    std::cout<< verts;

    //plot to pdf
    hypro::Plotter<Number>::getInstance().clear();
    unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject(verts);
    hypro::Plotter<Number>::getInstance().setObjectColor(obj2, hypro::plotting::colors[hypro::plotting::green]);

    // create a *.plt file (gnuplot).
    hypro::Plotter<Number>::getInstance().setFilename("elapseTest");
    hypro::Plotter<Number>::getInstance().plot2d();
}

void testRewind(){
    std::cout<< "Test rewind: \n";

    hypro::DifferenceBounds <Number> rewind = testDBM.rewind();
    std::cout<< rewind;
    std::vector<hypro::Point<Number>> verts = rewind.vertices();
    std::cout<< verts;

    //plot to pdf
    hypro::Plotter<Number>::getInstance().clear();
    unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject(verts);
    hypro::Plotter<Number>::getInstance().setObjectColor(obj2, hypro::plotting::colors[hypro::plotting::green]);

    // create a *.plt file (gnuplot).
    hypro::Plotter<Number>::getInstance().setFilename("rewindTest");
    hypro::Plotter<Number>::getInstance().plot2d();
}

void testFree(){
    std::cout<< "Test free: \n";

    hypro::DifferenceBounds <Number> freed = testDBM.free(2);//free y
    std::cout<< freed;
    std::vector<hypro::Point<Number>> verts = freed.vertices();
    std::cout<< verts;

    //plot to pdf
    hypro::Plotter<Number>::getInstance().clear();
    unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject(verts);
    hypro::Plotter<Number>::getInstance().setObjectColor(obj2, hypro::plotting::colors[hypro::plotting::green]);

    // create a *.plt file (gnuplot).
    hypro::Plotter<Number>::getInstance().setFilename("freeTest");
    hypro::Plotter<Number>::getInstance().plot2d();
}

void testReset(){
    std::cout<< "Test reset: \n";

    hypro::DifferenceBounds <Number> reset = testDBM.reset(1,0.0);//reset x
    std::cout<< reset;
    std::vector<hypro::Point<Number>> verts = reset.vertices();
    std::cout<< verts;

    //plot to pdf
    hypro::Plotter<Number>::getInstance().clear();
    unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject(verts);
    hypro::Plotter<Number>::getInstance().setObjectColor(obj2, hypro::plotting::colors[hypro::plotting::green]);

    // create a *.plt file (gnuplot).
    hypro::Plotter<Number>::getInstance().setFilename("resetTest");
    hypro::Plotter<Number>::getInstance().plot2d();
}

void testCopy(){
    std::cout<< "Test copy: \n";

    hypro::DifferenceBounds <Number> copy = testDBM.copy(1,2);//copy x to y
    std::cout<< copy;
    std::vector<hypro::Point<Number>> verts = copy.vertices();
    std::cout<< verts;

    //plot to pdf
    hypro::Plotter<Number>::getInstance().clear();
    unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject(verts);
    hypro::Plotter<Number>::getInstance().setObjectColor(obj2, hypro::plotting::colors[hypro::plotting::green]);

    // create a *.plt file (gnuplot).
    hypro::Plotter<Number>::getInstance().setFilename("copyTest");
    hypro::Plotter<Number>::getInstance().plot2d();
}

void testShift(){
    std::cout<< "Test shift: \n";

    hypro::DifferenceBounds <Number> shift = testDBM.shift(1,5.0);//shift x 5 to the right
    std::cout<< shift;
    std::vector<hypro::Point<Number>> verts = shift.vertices();
    std::cout<< verts;

    //plot to pdf
    hypro::Plotter<Number>::getInstance().clear();
    unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject(verts);
    hypro::Plotter<Number>::getInstance().setObjectColor(obj2, hypro::plotting::colors[hypro::plotting::green]);

    // create a *.plt file (gnuplot).
    hypro::Plotter<Number>::getInstance().setFilename("shiftTest");
    hypro::Plotter<Number>::getInstance().plot2d();
}

void testEmpty(){
    bool isEmpty = testDBM.empty();
    std::cout << "DBM is empty: " << isEmpty << "\n";
}

void testContains(){
    bool contains = testDBM.contains(testDBM2);
    std::cout << "DBM1 contains DBM2: " << contains << "\n";
}

void testIntersectConstraint(){
    std::cout<< "Test intersection with constraint: \n";

    // intersect with x-0 <= 8.0
    hypro::DifferenceBounds <Number> intersection = testDBM.intersectConstraint(1,0,hypro::DifferenceBounds<Number>::DBMEntry(8.0,hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ));
    std::cout<< intersection;
    std::vector<hypro::Point<Number>> verts = intersection.vertices();
    std::cout<< verts;

    //plot to pdf
    hypro::Plotter<Number>::getInstance().clear();
    unsigned obj2 = hypro::Plotter<Number>::getInstance().addObject(verts);
    hypro::Plotter<Number>::getInstance().setObjectColor(obj2, hypro::plotting::colors[hypro::plotting::green]);

    // create a *.plt file (gnuplot).
    hypro::Plotter<Number>::getInstance().setFilename("intersectionTest");
    hypro::Plotter<Number>::getInstance().plot2d();
}

void testPrint(){
    std::cout<< "Test instance DBM: \n";
    std::cout<<testDBM;
}
