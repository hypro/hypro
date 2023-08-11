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
#include <hypro/datastructures/Point.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <random>

template<typename Number>
class VPolytopeUtilTest : public ::testing::Test {
protected:
    virtual void SetUp() {}

    virtual void TearDown() {}
};

TYPED_TEST(VPolytopeUtilTest, RemoveRedundantPoints) {
    using namespace hypro;
    std::vector<Point<TypeParam >> vertexCandidates;

    std::mt19937 engine(0);
    std::uniform_real_distribution<> dist(0, 10);

    for (int k = 0; k < 10; ++k) {
        std::vector<TypeParam> coordinates;
        for (int l = 0; l < 3; ++l) {
            coordinates.emplace_back(dist(engine));
        }
        vertexCandidates.emplace_back(coordinates);
    }

    auto result1 = removeRedundantPoints<TypeParam, true>(vertexCandidates);
    auto result2 = removeRedundantPoints<TypeParam, false>(vertexCandidates);

    EXPECT_TRUE(std::equal(std::begin(result1), std::end(result1), std::begin(result2)));
}
