/* 
 * File:   rahsTwoTankTest.cpp
 * Author: jongan
 *
 * Created on Sep 15, 2014, 1:48:19 PM
 */


#include <stdlib.h>
#include <iostream>
#include "../src/lib/representations/Zonotope/ZUtility.h"
#include "../src/lib/representations/Zonotope/Zonotope.h"
#include "../src/lib/representations/Hyperplane/Hyperplane.h"
#include "../src/lib/algorithms/reachability/ZonotopeReachability.h"
#include <fstream>

#ifdef HAS_MATLAB
#include "TwoTank/Visualizer.h"
#include "mat.h"
#endif


/*
 * Google Test for Two Tank example
 */

using namespace Eigen;

hypro::Transition<double> trans1, trans2, trans3, trans4, trans5, trans6, trans7;
hypro::Location<double> loc1, loc2, loc3, loc4;

Zonotope<double> I_zonotope, U_zonotope;

std::set< hypro::Transition<double>* > transSet;
std::set< hypro::Location<double>* > locSet, initialLocSet;

struct hypro::Transition<double>::guard g15,g23,g46,g7 ;
struct hypro::Location<double>::invariant inv1, inv2, inv3, inv4;


std::set< hypro::Transition<double>* > temp_locations;

void createTwoTankHybridAutomata(hypro::HybridAutomaton<double, Zonotope<double> > * ha) {

    hypro::matrix_t<double> A,B;
    hypro::vector_t<double> b;
    A.resize(2,2);
    B.resize(2,2);
    b.resize(2, Eigen::NoChange);

    struct hypro::Transition<double>::assignment assign;

    transSet.insert(&trans1);
    transSet.insert(&trans2);
    transSet.insert(&trans3);
    transSet.insert(&trans4);
    transSet.insert(&trans5);
    transSet.insert(&trans6);
    transSet.insert(&trans7);

    locSet.insert(&loc1);
    locSet.insert(&loc2);
    locSet.insert(&loc3);
    locSet.insert(&loc4);

    initialLocSet.insert(&loc3);

    // Setup guards first

    hypro::matrix_t<double> identity;
    identity.resize(2,2);
    hypro::vector_t<double> zeroVec;
    zeroVec.resize(2,Eigen::NoChange);
    
    zeroVec.setZero();
    identity.setIdentity();
    assign.transformMat = identity;

    for (hypro::Transition<double>* trans : transSet) {
        trans->setAssignment(assign);
    }



    hypro::matrix_t<double> g;
    g.resize(2,2);
    g.setZero();
    g.block<1,2>(0,0) << 1,0;


    g15.mat = g;
    g15.vec = zeroVec;
    g15.vec(0) = -1;
    g15.op = hypro::EQ;

    g7.mat = g;
    g7.vec = zeroVec;
    g7.vec(0) = 1;
    g7.op = hypro::EQ;

    g.block<1,2>(0,0) << 0,1;   
    g23.mat = g;
    g23.vec = zeroVec;
    g23.vec(0) = 1;
    g23.op = hypro::EQ;

    g46.vec = zeroVec;
    g46.vec(0) = 0;
    g46.mat = g;
    g46.op = hypro::EQ;

    
    inv1.mat.resize(2, 2);
    inv2.mat.resize(2, 2);
    inv3.mat.resize(2, 2);
    inv4.mat.resize(0, 0);
    
    inv1.vec.resize(2, Eigen::NoChange);
    inv2.vec.resize(2, Eigen::NoChange);
    inv3.vec.resize(2, Eigen::NoChange);
    inv4.vec.resize(0, Eigen::NoChange);
    
//    inv3.mat << -1, 0,
//                 0, 0;
//    inv3.vec << -1.5, 0;
//    inv3.op = hypro::LEQ;
//    
//    inv1.mat << 0, 1,
//                0, 0;
//    inv1.vec << 0.2, 0;
//    inv1.op = hypro::LEQ;
    
    inv3.mat << -1, -1,
                 0, 0;
    inv3.vec << -1, 0;
    inv3.op = hypro::LEQ;
    
    inv1.mat << 0, 1,
                0, 0;
    inv1.vec << 0.3, 0;
    inv1.op = hypro::LEQ;
    
    inv2.mat << 0, -1,
                0, 0;
    inv2.vec << 0.12, 0;
    inv2.op = hypro::LEQ;
    
    loc4.setInvariant(inv4);
    loc3.setInvariant(inv3);
    loc2.setInvariant(inv2);
    loc1.setInvariant(inv1);
    


    // Push guards into transitiions
    trans1.setGuard(g15);
    trans1.setStartLoc(&loc1);
    trans1.setTargetLoc(&loc2);

    trans2.setGuard(g23);
    trans2.setStartLoc(&loc1);
    trans2.setTargetLoc(&loc3);

    trans3.setGuard(g23);
    trans3.setStartLoc(&loc2);
    trans3.setTargetLoc(&loc3);

    trans4.setGuard(g46);
    trans4.setStartLoc(&loc3);
    trans4.setTargetLoc(&loc1);

    trans5.setGuard(g15);
    trans5.setStartLoc(&loc3);
    trans5.setTargetLoc(&loc4);

    trans6.setGuard(g46);
    trans6.setStartLoc(&loc4);
    trans6.setTargetLoc(&loc2);

    trans7.setGuard(g7);
    trans7.setStartLoc(&loc4);
    trans7.setTargetLoc(&loc3);

    // set locations
    

    temp_locations.insert(&trans1);
    temp_locations.insert(&trans2);
    loc1.setTransitions(temp_locations);

    temp_locations.clear();

    temp_locations.insert(&trans3);
    loc2.setTransitions(temp_locations);

    temp_locations.clear();

    temp_locations.insert(&trans4);
    temp_locations.insert(&trans5);
    loc3.setTransitions(temp_locations);

    temp_locations.clear();

    temp_locations.insert(&trans6);
    temp_locations.insert(&trans7);
    loc4.setTransitions(temp_locations);

    // Set activity matrix and vectors for locations

    B.setIdentity();
    loc1.setExtInputMat(B);
    loc2.setExtInputMat(B);
    loc3.setExtInputMat(B);
    loc4.setExtInputMat(B);

    A << -1,0,
          1,0;

    loc1.setActivityMat(A);
    loc2.setActivityMat(A);

    A << -1,0,
          1,-1;
    loc3.setActivityMat(A);
    loc4.setActivityMat(A);

    b << -2,0;
    loc1.setActivityVec(b);

    b << 3,0;
    loc2.setActivityVec(b);

    b << -2,-5;
    loc3.setActivityVec(b);

    b << 3,-5;
    loc4.setActivityVec(b);

    // set initial state zonotope
    hypro::vector_t<double> center, gen;
    center.resize(2,Eigen::NoChange);
    gen.resize(2,Eigen::NoChange);
    center << 2,1;
    gen << 0.5,0;

    I_zonotope.setCenter(center);
    I_zonotope.setGenerators(gen);

    center.setZero();
    gen.setZero();
    U_zonotope.setCenter(center);
    U_zonotope.setGenerators(gen);



    // setup hybrid automaton
    ha->setValuation(I_zonotope);
    ha->setExtInputValuation(U_zonotope);
    ha->setTransitions(transSet);
    ha->setLocations(locSet);
    ha->setInitialLocations(initialLocSet);
        
}

int main() {
    hypro::HybridAutomaton<double, Zonotope<double> > * ha1 = new hypro::HybridAutomaton<double, Zonotope<double> > ;
    createTwoTankHybridAutomata(ha1);
    ZonotopeReachability<double> zreach(2);
    zreach.loadHybridAutomaton(ha1);
    std::cout << "loaded hybrid automaton..." << std::endl;
    ZUtility::Options opt = {ZUtility::NDPROJECTION, 3};
    zreach.startReachabilityAnalysis(100,1,0.01,20, opt);
    

#ifdef HAS_MATLAB
    Visualizer vis;
    const unsigned long dims[2] = {1,zreach.flowpipe().size()};
    
    unsigned i=0;
    mxArray * res;
    mxArray * cell_array = vis.createCellArray(2, dims);
    for (Zonotope<double> zp : zreach.flowpipe()) {
        Zonotope<double> z2(zp,0,1);
        std::vector<hypro::vector_t<double> > boundaries = z2.computeZonotopeBoundary();
        
        MatrixXd temp_matrix = zonotope2Matrix(zp);
        
        res = vis.createMatrix(temp_matrix.rows(), temp_matrix.cols());        
        vis.matrix2mxArray<double>(temp_matrix, res);        
        vis.setCellArray(cell_array, i, res);
        i++;
    }
    vis.sendVariable2Matlab("Q", cell_array);
    std::cout << zreach.flowpipe().size() << " number of zonotopes sent to matlab..." << std::endl;
    mxDestroyArray(res);
    
    unsigned int count = 0;
    for (auto key: zreach.intersections()) {
        for (Zonotope<double> z : key.second) {
            count++;
        }
    }
    
    mxArray * res2;
//    MATFile * matfile = matOpen("convexhull.mat", "w");
//    MATFile * matfile2 = matOpen("intersect.mat", "w");
//    if (matfile == NULL || matfile2 == NULL) {
//        std::cout << "Open failed..." << std::endl;
//    }
    
    
    mxArray * intersect_array;
    if (count > 0) {
        const unsigned long dims3[2] = {1,count-1};
        count = 0;
        intersect_array = vis.createCellArray(2,dims3);
        for (auto key: zreach.intersections()) {
            for (Zonotope<double> z : key.second) {
                Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> temp_matrix = zonotope2Matrix(z);
                res2 = vis.createMatrix(temp_matrix.rows(), temp_matrix.cols());  
                vis.matrix2mxArray<double>(temp_matrix, res2);        
                vis.setCellArray(intersect_array, count, res2);
                count++;
            }
        }
    }
    else {
        const unsigned long dims3[2] = {0,0};
        intersect_array = vis.createCellArray(2, dims3);
    }
    
    vis.sendVariable2Matlab("intersect", intersect_array);
    std::cout << count << " number of intersects sent to matlab..." << std::endl;
    
    if (count > 0) 
        mxDestroyArray(res2);
//    mxDestroyArray(intersect_array);
//    mxArray * res3;
//    const unsigned long dims4[2] = {1,zreach.pivotalZonotopes().size()};
//    mxArray * pivotal_array = vis.createCellArray(2,dims4);
//    count = 0;
//    // plot pivotal zonotopes
//    for (auto zt: zreach.pivotalZonotopes()) {
////        for (Zonotope<double> z : key.second) {
////            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> temp_matrix = zonotope2Matrix(z);
////            res3 = vis.createMatrix(temp_matrix.rows(), temp_matrix.cols());  
////            vis.matrix2mxArray<double>(temp_matrix, res3);        
////            vis.setCellArray(intersect_array, count, res3);
////            count++;
////        }
//        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> temp_matrix = zonotope2Matrix(zt.second);
//        res3 = vis.createMatrix(temp_matrix.rows(), temp_matrix.cols());
//        vis.matrix2mxArray<double>(temp_matrix, res3);
//        vis.setCellArray(pivotal_array, count, res3);
//        count++;
//    }
    
    
    
    
//    vis.sendVariable2Matlab("pivotal", pivotal_array);
//    matPutVariable(matfile, "convexhull", pivotal_array);
//    matPutVariable(matfile2, "intersect", intersect_array);
//    matClose(matfile);
//    matClose(matfile2);
    vis.executeMatlabScript("plotReachableSets"); 
    std::cout << vis.buffer << std::endl;
//    mxDestroyArray(res2);
    mxDestroyArray(intersect_array);
#endif
    delete ha1;
}

