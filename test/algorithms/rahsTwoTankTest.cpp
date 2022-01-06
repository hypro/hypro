/*
 * File:   rahsTwoTankTest.cpp
 * Author: jongan
 *
 * Created on Sep 15, 2014, 1:48:19 PM
 */

#include "../../hypro/algorithms/reachability/RAHS.h"
#include "../../hypro/representations/Zonotope/ZUtility.h"
#include "../../hypro/representations/Zonotope/Zonotope.h"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

/*
 * Google Test for Two Tank example
 */

using namespace Eigen;

class TwoTankTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		std::set<hypro::Transition<double>*> transSet;
		std::set<hypro::Location<double>*> locSet, initialLocSet;

		transSet.insert( &trans1 );
		transSet.insert( &trans2 );
		transSet.insert( &trans3 );
		transSet.insert( &trans4 );
		transSet.insert( &trans5 );
		transSet.insert( &trans6 );
		transSet.insert( &trans7 );

		locSet.insert( &loc1 );
		locSet.insert( &loc2 );
		locSet.insert( &loc3 );
		locSet.insert( &loc4 );

		initialLocSet.insert( &loc3 );

		// Setup guards first
		struct hypro::Transition<double>::guard g15, g23, g46, g7;
		struct hypro::Transition<double>::assignment assign;

		Matrix2d identity;
		Vector2d zeroVec;
		zeroVec.setZero();
		identity.setIdentity();
		assign.transformMat = identity;

		for ( hypro::Transition<double>* trans : transSet ) {
			trans->setAssignment( assign );
		}

		Matrix2d g;
		g.setZero();
		g.block<1, 2>( 0, 0 ) << 1, 0;

		g15.mat = g;
		g15.vec = zeroVec;
		g15.vec( 0 ) = -1;
		g15.op = hypro::EQ;

		g7.mat = g;
		g7.vec = zeroVec;
		g7.vec( 0 ) = 1;
		g7.op = hypro::EQ;

		g.block<1, 2>( 0, 0 ) << 0, 1;
		g23.mat = g;
		g23.vec = zeroVec;
		g23.vec( 0 ) = 1;
		g23.op = hypro::EQ;

		g46.vec = zeroVec;
		g46.vec( 0 ) = 0;
		g46.mat = g;
		g46.op = hypro::EQ;

		// Push guards into transitiions
		trans1.setGuard( g15 );
		trans1.setStartLoc( &loc1 );
		trans1.setTargetLoc( &loc2 );

		trans2.setGuard( g23 );
		trans2.setStartLoc( &loc1 );
		trans2.setTargetLoc( &loc3 );

		trans3.setGuard( g23 );
		trans3.setStartLoc( &loc2 );
		trans3.setTargetLoc( &loc3 );

		trans4.setGuard( g46 );
		trans4.setStartLoc( &loc3 );
		trans4.setTargetLoc( &loc1 );

		trans5.setGuard( g15 );
		trans5.setStartLoc( &loc3 );
		trans5.setTargetLoc( &loc4 );

		trans6.setGuard( g46 );
		trans6.setStartLoc( &loc4 );
		trans6.setTargetLoc( &loc2 );

		trans7.setGuard( g7 );
		trans7.setStartLoc( &loc4 );
		trans7.setTargetLoc( &loc3 );

		// set locations
		std::set<hypro::Transition<double>*> temp_locations;

		temp_locations.insert( &trans1 );
		temp_locations.insert( &trans2 );
		loc1.setTransitions( temp_locations );

		temp_locations.clear();

		temp_locations.insert( &trans3 );
		loc2.setTransitions( temp_locations );

		temp_locations.clear();

		temp_locations.insert( &trans4 );
		temp_locations.insert( &trans5 );
		loc3.setTransitions( temp_locations );

		temp_locations.clear();

		temp_locations.insert( &trans6 );
		temp_locations.insert( &trans7 );
		loc4.setTransitions( temp_locations );

		// Set activity matrix and vectors for locations

		B.setIdentity();
		loc1.setActivityInputMat( B );
		loc2.setActivityInputMat( B );
		loc3.setActivityInputMat( B );
		loc4.setActivityInputMat( B );

		A << -1, 0, 1, 0;

		loc1.setActivityMat( A );
		loc2.setActivityMat( A );

		A << -1, 0, 1, -1;
		loc3.setActivityMat( A );
		loc4.setActivityMat( A );

		b << -2, 0;
		loc1.setActivityVec( b );

		b << 3, 0;
		loc2.setActivityVec( b );

		b << -2, -5;
		loc3.setActivityVec( b );

		b << 3, -5;
		loc4.setActivityVec( b );

		// set initial state zonotope
		Vector2d center, gen;
		center << 2, 1;
		gen << 0.5, 0;

		I_zonotope.setCenter( center );
		I_zonotope.setGenerators( gen );

		center.setZero();
		gen.setZero();
		U_zonotope.setCenter( center );
		U_zonotope.setGenerators( gen );

		// setup hybrid automaton
		ha1->setValuation( I_zonotope );
		ha1->setInputValuation( U_zonotope );
		ha1->setTransitions( transSet );
		ha1->setLocations( locSet );
		ha1->setInitialLocations( initialLocSet );
	}
	virtual void TearDown() { delete ha1; }

	//        Visualizer vis;

	hypro::Transition<double> trans1, trans2, trans3, trans4, trans5, trans6, trans7;
	hypro::Location<double> loc1, loc2, loc3, loc4;
	Matrix2d A, B;
	Vector2d b;

	Zonotope<double> I_zonotope, U_zonotope;

	hypro::HybridAutomaton<double>* ha1 = new hypro::HybridAutomaton<double>;
};

TEST_F( TwoTankTest, Correctness ) {
	RAHS<double> rahs( 2 );
	rahs.loadHybridAutomaton( ha1 );
	ZUtility::Options opt = { ZUtility::NDPROJECTION, 3 };
	rahs.startReachabilityAnalysis( 100, 1, 0.01, 20, opt );
	std::cout << "Size of flowpipe: " << rahs.flowpipe().size() << std::endl;
	//    const unsigned long dims[2] = {1,rahs.flowpipe().size()};
	//
	//    unsigned i=0;
	//    mxArray * res;
	//    mxArray * cell_array = vis.createCellArray(2, dims);
	//    for (Zonotope<double> zp : rahs.flowpipe()) {
	//        Zonotope<double> z2(zp,0,1);
	//        std::vector<Eigen::Matrix<double, Eigen::Dynamic, 1> > boundaries = z2.computeZonotopeBoundary();
	//
	//        MatrixXd temp_matrix = zonotope2Matrix(zp);
	//
	//        res = vis.createMatrix(temp_matrix.rows(), temp_matrix.cols());
	//        vis.matrix2mxArray<double>(temp_matrix, res);
	//        vis.setCellArray(cell_array, i, res);
	//        i++;
	//
	//
	//        if (i==3) {
	//            std::ofstream fs;
	//            fs.open("zonotopetest.txt");
	//            std::cout << "Num of points: " << boundaries.size() << std::endl;
	//            std::cout << "x: ";
	//
	//            fs << "x :";
	//            for (unsigned i=0; i<boundaries.size(); i++) {
	//                std::cout << boundaries[i](0) << ",";
	//                fs << boundaries[i](0) << ", ";
	//            }
	//            std::cout << std::endl << "y:";
	//            fs << std::endl << "y: ";
	//            for (unsigned i=0; i<boundaries.size(); i++) {
	//                std::cout << boundaries[i](1) << ",";
	//                fs << boundaries[i](1) << ", ";
	//            }
	//            fs << "Generators: \n" << z2.generators() << std::endl;
	//            fs << "Center: \n" << z2.center() << std::endl;
	//
	//            fs.close();
	//
	////            std::cout << "Boundaries mat:\n" << boundariesMat << std::endl;
	//        }
	//    }
	//    vis.sendVariable2Matlab("Q", cell_array);
	//
	//    mxDestroyArray(res);
	//
	//    unsigned int count = 0;
	//    for (auto key: rahs.intersections()) {
	//        for (Zonotope<double> z : key.second) {
	//            count++;
	//        }
	//    }
	//
	//    mxArray * res2;
	//    MATFile * matfile = matOpen("convexhull.mat", "w");
	//    MATFile * matfile2 = matOpen("intersect.mat", "w");
	//    if (matfile == NULL || matfile2 == NULL) {
	//        std::cout << "Open failed..." << std::endl;
	//    }
	//
	//    const unsigned long dims3[2] = {1,count-1};
	//    count = 0;
	//    mxArray * intersect_array = vis.createCellArray(2,dims3);
	//    for (auto key: rahs.intersections()) {
	//        for (Zonotope<double> z : key.second) {
	//            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> temp_matrix = zonotope2Matrix(z);
	//            res2 = vis.createMatrix(temp_matrix.rows(), temp_matrix.cols());
	//            vis.matrix2mxArray<double>(temp_matrix, res2);
	//            vis.setCellArray(intersect_array, count, res2);
	//            count++;
	//        }
	//    }
	//
	//    mxArray * res3;
	//    const unsigned long dims4[2] = {1,rahs.pivotalZonotopes().size()};
	//    mxArray * pivotal_array = vis.createCellArray(2,dims4);
	//    count = 0;
	//    // plot pivotal zonotopes
	//    for (auto zt: rahs.pivotalZonotopes()) {
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
	//
	//
	//
	//    vis.sendVariable2Matlab("intersect2", intersect_array);
	//    vis.sendVariable2Matlab("pivotal", pivotal_array);
	//
	//    matPutVariable(matfile, "convexhull", pivotal_array);
	//    matPutVariable(matfile2, "intersect", intersect_array);
	//    matClose(matfile);
	//    matClose(matfile2);
	//    vis.executeMatlabScript("plotReachableSets");
	//    std::cout << vis.buffer << std::endl;
	//    mxDestroyArray(res2);
	//    mxDestroyArray(intersect_array);
}
