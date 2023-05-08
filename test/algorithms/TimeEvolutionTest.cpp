/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <hypro/algorithms/reachability/handlers/timeEvolutionHandlers/singularTimeEvolutionHandler.h>
#include <hypro/representations/GeometricObjectBase.h>

TEST(TimeEvolutionTest, SingularEvolution) {
    using Number = mpq_class;
    using VPoly = hypro::VPolytope<Number>;
    using Vector = hypro::vector_t<Number>;
    using Point = hypro::Point<Number>;

    Vector origin = Vector::Zero(2);

    VPoly init{Point{origin}};

    Vector dynamics1 = Vector::Zero(2);
    dynamics1 << Number(1), Number(1);
    VPoly dynamicsPoly1{Point{dynamics1}};

    auto unbndTimeEvolution = hypro::singularApplyTimeEvolution(init, dynamicsPoly1.vertices());

    EXPECT_TRUE(unbndTimeEvolution.vertices().size() == 1);
    EXPECT_TRUE(unbndTimeEvolution.rays().size() == 1);
    EXPECT_EQ(origin, unbndTimeEvolution.vertices().front().rawCoordinates());

    Vector v1 = Vector::Zero(2);
    v1 << Number(0), Number(1);

    VPoly init2{{origin, v1}};

    auto bndTimeEvolution =
            hypro::singularApplyBoundedTimeEvolution(init2, dynamicsPoly1.vertices(), hypro::tNumber(10));
    EXPECT_TRUE(bndTimeEvolution.vertices().size() == 4);
    EXPECT_TRUE(bndTimeEvolution.rays().size() == 0);

    SUCCEED();
}

TEST(TimeEvolutionTest, SingularEvolutionPreciseVPoly) {
    using Number = mpq_class;
    using VPoly = hypro::VPolytope<Number>;
    using Vector = hypro::vector_t<Number>;
    using Point = hypro::Point<Number>;

    Vector origin = Vector::Zero(2);
    Vector v0 = Vector(2);
    v0 << 1, 0;
    Vector v1 = Vector(2);
    v1 << 1, 1;
    Vector v2 = Vector(2);
    v2 << 0, 1;

    VPoly init{{Point{origin}, Point{v0}, Point{v1}, Point{v2}}};

    Vector dynamics1 = Vector::Zero(2);
    dynamics1 << Number(1), Number(1);
    VPoly dynamicsPoly1{Point{dynamics1}};

    auto bndTimeEvolution =
            hypro::singularApplyBoundedTimeEvolution(init, dynamicsPoly1.vertices(), hypro::tNumber(10));
    EXPECT_EQ(bndTimeEvolution.vertices().size(), 6);

    EXPECT_TRUE(bndTimeEvolution.rays().size() == 0);
    // vertices
    EXPECT_TRUE(bndTimeEvolution.contains(Point{0, 0}));
    EXPECT_TRUE(bndTimeEvolution.contains(Point{1, 0}));
    EXPECT_TRUE(bndTimeEvolution.contains(Point{0, 1}));
    EXPECT_TRUE(bndTimeEvolution.contains(Point{11, 10}));
    EXPECT_TRUE(bndTimeEvolution.contains(Point{11, 11}));
    EXPECT_TRUE(bndTimeEvolution.contains(Point{10, 11}));
    // some external points
    Number eps = Number(0.0001);
    EXPECT_FALSE(bndTimeEvolution.contains(Point{0, -eps}));
    EXPECT_FALSE(bndTimeEvolution.contains(Point{-eps, 0}));
    EXPECT_FALSE(bndTimeEvolution.contains(Point{1 + eps, 0}));
    EXPECT_FALSE(bndTimeEvolution.contains(Point{3, 0}));
    EXPECT_FALSE(bndTimeEvolution.contains(Point{11 + eps, 10}));
    EXPECT_FALSE(bndTimeEvolution.contains(Point{11 + eps, 10}));
    SUCCEED();
}
