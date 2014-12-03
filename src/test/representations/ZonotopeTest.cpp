/* 
 * File:   ZonotopeTest.cpp
 * Author: jongan
 *
 * Created on Sep 1, 2014, 11:56:26 AM
 */

#include <stdlib.h>
#include <iostream>
#include "gtest/gtest.h"
#include "../../lib/representations/Zonotope/Zonotope.h"
#include "../../lib/representations/Hyperplane/Hyperplane.h"

/*
 * Google Test for Zonotope Implementation
 */

TEST(ZonotopeTest, PlainConstructor) {
    Zonotope<double> z1;
    EXPECT_EQ(z1.dimension(), 0);
    EXPECT_EQ(z1.center().rows(), 0);
    EXPECT_EQ(z1.center().cols(), 1);
    EXPECT_EQ(z1.generators().rows(), 0);
    EXPECT_EQ(z1.generators().cols(), 0);
}

TEST(ZonotopeTest, DimConstructor) {
    unsigned int dim = 4;
    Zonotope<double> z1(dim);
    EXPECT_EQ(z1.dimension(), 4);
}

TEST(ZonotopeTest, FullConstructor) {
    Eigen::Matrix<double, 2,3> gen;
    Eigen::Matrix<double, 2,1> center;

    gen << 2,3,6,
           4,1,5;
    center << 1,
              2;

    Zonotope<double> z2(center, gen);
    EXPECT_EQ(z2.dimension(),2);
    EXPECT_EQ(z2.center(), center);
    EXPECT_EQ(z2.generators(), gen);
}

TEST(ZonotopeTest, CopyConstructor) {
    Eigen::Matrix<double, 3,2> gen;
    Eigen::Matrix<double, 3,1> center;
    center << 1,5,2;
    gen << 1,2,
            2,8,
            9,1;
    Zonotope<double> z1(center, gen);
    Zonotope<double> z_copy(z1);
    
    EXPECT_EQ(z_copy.dimension(),z1.dimension());
    EXPECT_EQ(z_copy.center(),z1.center());
    EXPECT_EQ(z_copy.generators(),z1.generators());
}

TEST(ZonotopeAlgorithmTest, ComputeZonotopeBoundary) {
    Zonotope<double> z1(2);
    Eigen::Matrix<double,2,1> center = {1.1941, 0.1068};
    Eigen::Matrix<double, 2,6> generators;
    generators << 0.3993,   0.0160,    0.0020,    0.0035,         0,   -0.0017,
                    0.0898,    0.0196,   -0.0015,    0.0008,    0.0035,   -0.0045;
    
    z1.setCenter(center);
    z1.setGenerators(generators);
    
    std::vector< Eigen::Matrix<double, Eigen::Dynamic, 1> > results = z1.computeZonotopeBoundary();
}

TEST(ZonotopeAlgorithmTest, ZonogoneHPIntersect) {
    Eigen::Matrix<double, 2,1> dVec = {0,1},  center = {1.1941, 0.1068};
    Eigen::Matrix<double, 2,6> generators;
    generators << 0.3993,   0.0160,    0.0020,    0.0035,         0,   -0.0017,
                    0.0898,    0.0196,   -0.0015,    0.0008,    0.0035,   -0.0045;
    
    Hyperplane<double> hp(dVec, 0);
    Zonotope<double> z(center, generators), res;
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> dummy;
    intersectZonogoneHyperplane(z, hp, res, dummy);
}

TEST(ZonotopeAlgorithmTest, MinkowskiSum) {
    Zonotope<double> z1(2), z2(2), z3(2);

    Eigen::Matrix<double,2,1> cen1, cen2, cen_res, gen_sum;
    Eigen::Matrix<double,2,2> gen1, gen2;

    cen1 << 1,
            2;
    cen2 << 4,
            7;

    gen1 << 3,4,
            6,1;
    gen2 << 2,1,
            7,8;


    z1.setCenter(cen1);
    z1.setGenerators(gen1);
    z2.setCenter(cen2);
    z2.setGenerators(gen2);

    z1.minkowskiSum(z1, z2);

    cen_res << 5,
               9;

    gen_sum << 10,
               22;
    
    

    EXPECT_EQ(z1.center(), cen_res);
    EXPECT_EQ(z1.numGenerators(), 4);
    EXPECT_EQ(z1.generators().rowwise().sum(), gen_sum); 
    
    z2.minkowskiSum(z1,z3);
    EXPECT_EQ(z1.numGenerators(), 2);
    EXPECT_EQ(z1.generators(), gen2);

    // z1.minkowskiSum(*this, z2);
    // EXPECT_NE(z1.center(), cen1);

}

//TEST(ZonotopeOperationTest, Intersection1) {
//    Eigen::Matrix<double, 3,3> gen, exp_gen, delta_gen;
//    Eigen::Matrix<double, 3,1> cen, d_vector, exp_center, delta_center;
//    gen << 2,0,0,
//            0,1,0,
//            0,0,3;
//
//    exp_gen << 1.6926, -0.2049, -0.6916,
//                -0.1025, 0.9317, -0.2305,
//                -1.0374, -0.6916, 0.660;
//
//    delta_gen << 0.001, 0.001, 0.001,
//                 0.001, 0.001, 0.001,
//                 0.001, 0.001, 0.001;
//
//
//    cen << 1,
//            1,
//            1;
//
//    exp_center << 1.1793,
//                  1.0598,
//                  1.6051;
//
//    d_vector << 6,
//                8,
//                9;
//
//    delta_center << 0.001,
//                    0.001,
//                    0.001;
//
//    Zonotope<double> z1(3), res(3);
//    z1.setCenter(cen);
//    z1.setGenerators(gen);
//
//    Hyperplane<double> hp(3);
//    hp.setVector(d_vector);
//    hp.setScalar(30);
//
//    z1.intersect(res, hp, NDPROJECTION);
//
//    EXPECT_LT((res.center()-exp_center).array().abs().matrix().sum(), delta_center.sum());
//    EXPECT_LT((res.generators()-exp_gen).array().abs().matrix().rowwise().sum().sum(), delta_gen.array().abs().matrix().rowwise().sum().sum());
//}

TEST(ZonotopeAlgorithmTest, IntersectionHalfspace) {
    Variable x(0), y(1);
    Constraint hspace(y<=x-1);
    Eigen::Matrix<double, 2,1> z_center(3,-10);
    Eigen::Matrix<double, 2,2> z_gen;
    z_gen << 0,1,
             1,0;
    Zonotope<double> z1(z_center, z_gen), result(2);
     
    // Case 1: Zonotope is wholly inside the halfspace
    bool foundIntersect = z1.intersect(result, hspace);
    // Expect: result zonotope is the original zonotope, nothing is changed 
    // Intersection trivially present
    EXPECT_TRUE(foundIntersect);
    EXPECT_EQ(result.center(), z_center);
    EXPECT_EQ(result.generators(), z_gen);
    
    // Case 2: Zonotope is wholly outside of the halfspace
    z_center << -3,3;
    z_gen << 0,1,
             1,0;
    z1.setCenter(z_center);
    z1.setGenerators(z_gen);
    foundIntersect = z1.intersect(result, hspace);
    // Expect: No intersect was found
    EXPECT_FALSE(foundIntersect);
    
    // Case 3: Zonotope intersects partially with halfspace
    z_center << 0,0;
    z_gen << 0,2,
             2,0;
    
    z1.setCenter(z_center);
    z1.setGenerators(z_gen);
    
    foundIntersect = z1.intersect(result, hspace);
    // Expect: Intersect to be found, resulting zonotope is a different zonotope
    // TODO: verify that the resulting zonotope is correct
    EXPECT_TRUE(foundIntersect);
    EXPECT_TRUE(result.center()!= z_center);
//    EXPECT_TRUE(result.generators()!=z_gen);
    
    
}

TEST(ZonotopeAlgorithmTest, IntersectionPolytope) {
    
    Eigen::Matrix<double, 2,1> z_center;
    Eigen::Matrix<double, 2,2> z_gen;
    z_center << 0,-1;
    z_gen << 0,1,
             1,0;
    Zonotope<double> z1(z_center, z_gen), result_zonotope(2);
    
    C_Polyhedron poly1(2, UNIVERSE);
    Variable x(0),y(1);
    Constraint_System cs;
    cs.insert(y<=3);
    cs.insert(y>=1);
    cs.insert(y>=x-2);
    cs.insert(y<=2*x-1);
    poly1.add_constraints(cs);
    
    bool res = z1.intersect(result_zonotope, poly1);
    
    EXPECT_EQ(res, false);
    
    
}

TEST(ZonotopeOperationTest, RemoveEmptyGen) {
    Eigen::Matrix<double, 3, 1> center;
    center << 2,
              3,
              6;
    
    Eigen::Matrix<double, 3, 4> gen;
    Eigen::Matrix<double, 3, 3> gen2;
    
    gen << 2,3,0,2,
           3,6,0,3,
           1,5,0,7;
    
    gen2 << 2,3,2,
            3,6,3,
            1,5,7;
    
    Zonotope<double> z1;
    z1.setCenter(center);
    z1.setGenerators(gen);
    z1.removeEmptyGenerators();
   
    EXPECT_EQ(z1.generators(), gen2);
    
}

TEST(ZonotopeOperationTest, AddGenerators) {
    Zonotope<double> z(2);
    Eigen::Matrix<double,2,3> generators, generators2;
    Eigen::Matrix<double, 2, 6> concat_gens;
    generators << 1,2,5,
                  3,1,6;
    
    generators2 << 2,1,6,
                   2,6,8;
    
    z.addGenerators(generators);
    EXPECT_EQ(z.generators(), generators);
    
    z.addGenerators(generators2);
    concat_gens << generators, generators2;
    EXPECT_EQ(z.generators(), concat_gens);
    
}

TEST(ZonotopeAlgorithmTest, Intersection2) {
    Zonotope<double> z1(3);
    Eigen::Matrix<double, 3,1> z_center, d, exp_center, delta;
    Eigen::Matrix<double, 3,7> generators;
    z_center << -0.0407,
                -6.3274,
                1;
    d << 1,
         0,
         0;
    
    exp_center << 0,
                  -6.254369393209305,
                  0.994400337321514;
    
    delta << 0.01,
             0.01,
             0.01;
    
    generators <<0.01, 0.00645, 0.03163725, -5e-05, 0.0111647739218983, 0.00714545531001491,-0.0224310133091988,
                0,0.0100000000000000,0.0490500000000000,0,0,0.0111647739218983,-0.0700969165912463,
                0,0,0,0,0,0,0.0111647739218983;
    
    z1.setCenter(z_center);
    z1.setGenerators(generators);
    
    Hyperplane<double> h1(3);
    h1.setVector(d);
    h1.setScalar(0);
    
    Zonotope<double> result;
    z1.intersect(result, h1, ZUtility::ALAMO);
    
   EXPECT_LT((result.center()-exp_center).array().abs().matrix().sum(), delta.sum());
}

TEST(ZonotopeAlgorithmTest, ConvexHull) {
    Zonotope<double> z1(2), z2(2), result;
    Eigen::Matrix<double, 2, 1> c1, c2, expected_center;
    Eigen::Matrix<double, 2, 2> g1;
    Eigen::Matrix<double, 2, 3> g2;
    Eigen::Matrix<double, 2, 4> expected_generators;
    
    c1 << 2,1;
    c2 << 1,1;
    
    g1 << 1,1,
          0,1;
    
    g2 << 1,1,-0.5,
          0,1,0.2;
    
    expected_center << 1.5, 1;
    expected_generators << 1, 1, -0.5, -0.5,
                            0, 1, 0, 0.2;
    
    z1.setCenter(c1);
    z1.setGenerators(g1);
    z2.setCenter(c2);
    z2.setGenerators(g2);
    
    z1.convexHull(result, z2);
   
    EXPECT_EQ(result.center(), expected_center);
    EXPECT_EQ(result.generators(), expected_generators);
}


TEST(ZonotopeAlgorithmTest, IntervalHull) {
    Eigen::Matrix<double, 2, 1> center = {2.0,1.0};
    Eigen::Matrix<double, 2, 3> generators;
    Eigen::Matrix<double, 2, 2> expected_generators;
    generators << 1, 4, 3,
                  6, 2, 1;
    expected_generators << 8, 0,
                           0, 9;
    Zonotope<double> result, zIH(center, generators);
    
    zIH.intervalHull(result);
        
    EXPECT_EQ(result.generators(), expected_generators);
    EXPECT_EQ(result.center(), center);
}
