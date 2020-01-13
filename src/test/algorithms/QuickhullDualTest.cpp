//
// Created by leander.behr on 10/14/19.
//

#include "gtest/gtest.h"
#include "../defines.h"
#include "algorithms/quickhull/Quickhull.h"

using namespace hypro;
using number_t  = mpq_class;

template<bool Euclidian>
using qh = Quickhull<number_t, Euclidian>;

// bool checkContainment(qh::pointVector_t& input, qh& quickhull);
// void printFacet(qh::Facet const& facet, size_t dimension);
// bool exactContains(qh::Facet const& facet, qh::point_t const& point);

template<bool Euclidian>
bool exactContains(typename qh<Euclidian>::Facet const& facet, typename qh<Euclidian>::point_t const& inpPoint) {
    hypro::vector_t<mpq_class> normal = facet.mNormal.template cast<mpq_class>();
    hypro::vector_t<mpq_class> point = inpPoint.template cast<mpq_class>();
    mpq_class offset = facet.mOffset;

    if constexpr(Euclidian) {
        return normal.dot(point) - offset <= 0;
    } else {
            if(point[point.rows() - 1] == 0) {
                return point.head(point.rows() - 1).dot(normal) - offset <= 0;
            } else {
                return point.head(point.rows() - 1).dot(normal) / point[point.rows() - 1] - offset <= 0;
            }
    }
}

template<bool Euclidian>
bool containmentCheck(qh<Euclidian> quickhull, typename qh<Euclidian>::pointVector_t input) {
    for(auto& facet : quickhull.getFacets()) {
        for(auto& point : input) {
            if(!exactContains<Euclidian>(facet, point)) {
                return false;
            }
        }
    }
    return true;
}

class QuickhullDualTest : public ::testing::Test {
protected:
    virtual void SetUp() {};
    virtual void TearDown() {};
};

TEST_F(QuickhullDualTest, Specific) {
    Quickhull<number_t, false>::pointVector_t input;

    input.emplace_back(3) << 0,1,-1;
    input.emplace_back(3) << 1,-1,-1;
    input.emplace_back(3) << 0,-1,-(1/2.0);
    input.emplace_back(3) << -1,-1, -1;

    Quickhull<number_t, false> qh{input, 2};
    qh.compute();

    Quickhull<number_t, false>::pointVector_t output;
    for(Quickhull<number_t, false>::Facet facet : qh.getFacets()) {
        output.emplace_back(2);
        output.back() = facet.mNormal;
        output.back() /= -facet.mOffset;
    }

    std::stringstream str;
    str << std::endl;
    for(auto point : output) {
        for(size_t d = 0; d < 2; ++d) {
            str << carl::convert<mpq_class, double>(point[d]) << ", ";
        }
        str << std::endl;
    }
    TRACE("quickhull", str.str());

    input = output;
    Quickhull<number_t, true> qhEuc{input, 2};
    qhEuc.compute();
}

TEST_F(QuickhullDualTest, RandomVertices) {
    size_t const N = 10;
    size_t const D = 6;

    srand(42);

    Quickhull<number_t, true>::pointVector_t input;

    for (size_t i = 0; i < N; ++i) {
        // input.emplace_back(vector_t<number_t>::Random(D));
        input.emplace_back(D);
        for(size_t d = 0; d < D; ++d) {
            input.back()[d] = rand() % 200;
        }
    }

    std::stringstream str;
    str << std::endl;
    for(auto point : input) {
        for(size_t d = 0; d < D; ++d) {
            str << carl::convert<mpq_class, double>(point[d]) << ", ";
        }
        str << std::endl;
    }
    TRACE("quickhull", str.str());

    Quickhull<number_t, true> quickhull(input, D);
    quickhull.compute();

    EXPECT_TRUE(containmentCheck(quickhull, input));

    Quickhull<number_t, true>::pointVector_t dualinput;

    for(typename qh<true>::Facet facet : quickhull.getFacets()) {
        dualinput.emplace_back(D + 1);

        dualinput.back().head(D) = facet.mNormal;
        dualinput.back()[D] = -facet.mOffset;
    }

    Quickhull<number_t, false> dualQuickhull(dualinput, D);
    dualQuickhull.compute();

    EXPECT_TRUE(containmentCheck(dualQuickhull, dualinput));

    Quickhull<number_t, false>::pointVector_t reconstructedPoints;

    if constexpr(is_exact<number_t>) {
        for(Quickhull<number_t, false>::Facet facet : dualQuickhull.getFacets()) {
            reconstructedPoints.emplace_back(D);
            //The resulting points can't be points at infinity
            EXPECT_FALSE(facet.mOffset == 0);
            facet.mNormal /= -facet.mOffset;
            reconstructedPoints.back() = facet.mNormal;
        }

        std::stringstream str2;
        str2 << std::endl;
        for(auto point : reconstructedPoints) {
            for(size_t d = 0; d < D; ++d) {
                str2 << carl::convert<mpq_class, double>(point[d]) << ", ";
            }
            str2 << std::endl;
        }
        TRACE("quickhull", str2.str());

        //Each of the reconstruced points should exist in the original points aswell.
        for(Quickhull<number_t, false>::point_t point : reconstructedPoints) {
            EXPECT_TRUE(std::find(input.begin(), input.end(), point) != input.end());
        }
    }
}

// TEST_F(QuickhullDualTest, RandomVerticesModified) {
//     size_t const N = 50;
//     size_t const D = 6;

//     srand(42);

//     Quickhull<number_t, true>::pointVector_t input;

//     for (size_t i = 0; i < N; ++i) {
//         input.emplace_back(vector_t<number_t>::Random(D));
//         // for(size_t d = 0; d < D; ++d) {
//         //     input.back()[d] = rand() % 200;
//         // }
//     }

//     input.push_back(vector_t<number_t>::Zero(D));

//     // input.emplace_back(D) << -1, -1, -1;
//     // input.emplace_back(D) << -1, -1, 1;
//     // input.emplace_back(D) << -1, 1, -1;
//     // input.emplace_back(D) << -1, 1, 1;
//     // input.emplace_back(D) << 1, -1, -1;
//     // input.emplace_back(D) << 1, -1, 1;
//     // input.emplace_back(D) << 1, 1, -1;
//     // input.emplace_back(D) << 1, 1, 1;
//     // input.emplace_back(D) << 0,0,0;

//     std::stringstream str;
//     str << std::endl;
//     for(auto point : input) {
//         for(size_t d = 0; d < D; ++d) {
//             str << carl::convert<mpq_class, double>(point[d]) << ", ";
//         }
//         str << std::endl;
//     }
//     TRACE("quickhull", str.str());

//     Quickhull<number_t, true> quickhull(input, D);
//     quickhull.compute();

//     EXPECT_TRUE(containmentCheck(quickhull, input));

//     Quickhull<number_t, true>::pointVector_t dualinput;

//     for(typename qh<true>::Facet facet : quickhull.getFacets()) {
//         dualinput.emplace_back(D);

//         dualinput.back() = facet.mNormal;
//         dualinput.back() /= facet.mOffset;
//     }

//     Quickhull<number_t, true> dualQuickhull(dualinput, D);
//     dualQuickhull.compute();

//     EXPECT_TRUE(containmentCheck(dualQuickhull, dualinput));

//     Quickhull<number_t, true>::pointVector_t reconstructedPoints;

//     if constexpr(is_exact<number_t>) {
//         for(Quickhull<number_t, true>::Facet facet : dualQuickhull.getFacets()) {
//             reconstructedPoints.emplace_back(D);
//             //The resulting points can't be points at infinity
//             EXPECT_FALSE(facet.mOffset == 0);
//             facet.mNormal /= -facet.mOffset;
//             reconstructedPoints.back() = facet.mNormal;
//         }

//         std::stringstream str2;
//         str2 << std::endl;
//         for(auto point : reconstructedPoints) {
//             for(size_t d = 0; d < D; ++d) {
//                 str2 << carl::convert<mpq_class, double>(point[d]) << ", ";
//             }
//             str2 << std::endl;
//         }
//         TRACE("quickhull", str2.str());

//         //Each of the original points should exist in the reconstructed points aswell.
//         for(Quickhull<number_t, true>::point_t point : reconstructedPoints) {
//             EXPECT_TRUE(std::find(input.begin(), input.end(), point) != input.end());
//         }
//     }
// }

// // TEST_F(QuickhullDualTest, SpecificEnumeration) {
// //     qh::pointVector_t vertices{};
// //     vertices.emplace_back(3) << number_t(-9)/number_t(100), 15 , number_t(14)/number_t(10);
// //     vertices.emplace_back(3) << number_t(-9)/number_t(100), 16 , number_t(14)/number_t(10);
// //     vertices.emplace_back(3) << number_t(-9)/number_t(100), 15 , number_t(13)/number_t(10);
// //     vertices.emplace_back(3) << number_t(-9)/number_t(100), 16 , number_t(13)/number_t(10);
// //     vertices.emplace_back(3) << number_t(-9)/number_t(100), 15 , number_t(6)/number_t(5);
// //     vertices.emplace_back(3) << number_t(-9)/number_t(100), 16 , number_t(6)/number_t(5);
// //     vertices.emplace_back(3) << number_t(-9)/number_t(100), 15 , number_t(9)/number_t(100);
// //     vertices.emplace_back(3) << number_t(-9)/number_t(100), 16 , number_t(9)/number_t(100);
// //     vertices.emplace_back(3) << number_t(-9)/number_t(10), 15 , 0;
// //     vertices.emplace_back(3) << number_t(-9)/number_t(10), 16 , 0;
// //     vertices.emplace_back(3) << number_t(-1)/number_t(2) , 15 , number_t(5)/number_t(2);
// //     vertices.emplace_back(3) << number_t(-1)/number_t(2) , 16 , number_t(5)/number_t(2);
// //     vertices.emplace_back(3) << number_t(-47)/number_t(100) , 15 , number_t(5)/number_t(2);
// //     vertices.emplace_back(3) << number_t(-47)/number_t(100) , 16 , number_t(5)/number_t(2);
// //     vertices.emplace_back(3) << 0 , 15 , 0;
// //     vertices.emplace_back(3) << 0 , 15 , number_t(7)/number_t(5);
// //     vertices.emplace_back(3) << 0 , 15 , number_t(5)/number_t(2);
// //     vertices.emplace_back(3) << 0 , 16 , 0;
// //     vertices.emplace_back(3) << 0 , 16 , number_t(7)/number_t(5);
// //     vertices.emplace_back(3) << 0 , 16 , number_t(5)/number_t(2);

// //     qh quickhull{vertices, 3};
// //     quickhull.compute();

// //     for(auto const& facet : quickhull.getFacets()) {
// //         printFacet(facet, 3);
// //     }
// //     std::cout << "SpecificEnumeration END" << std::endl;
// //     EXPECT_TRUE(nonFancyCheckContainment(vertices, quickhull));
// // }

// // TEST_F(QuickhullDualTest, Degenerate) {
// //     qh::pointVector_t vertices{};
// //     vertices.emplace_back(3) << 5, 0 , 0;
// //     vertices.emplace_back(3) << 3, -2 , 4;
// //     vertices.emplace_back(3) << number_t(1)/number_t(2), 3 , number_t(3)/number_t(2);
// //     vertices.emplace_back(3) << -12, 14 , 3;
// //     vertices.emplace_back(3) << number_t(9)/number_t(100), 16 , number_t(-1109)/number_t(100);


// //     qh quickhull{vertices, 3};
// //     quickhull.compute();

// //     for(auto const& facet : quickhull.getFacets()) {
// //         printFacet(facet, 3);
// //     }
// //     std::cout << "Degenerate END" << std::endl;
// //     EXPECT_TRUE(nonFancyCheckContainment(vertices, quickhull));
// // }

// // TEST_F(QuickhullDualTest, Degenerate3dLine) {
// //     qh::pointVector_t vertices{};
// //     vertices.emplace_back(3) << 5, 0 , 0;
// //     vertices.emplace_back(3) << 3, -2 , 4;

// //     qh quickhull{vertices, 3};
// //     quickhull.compute();

// //     for(auto const& facet : quickhull.getFacets()) {
// //         printFacet(facet, 3);
// //     }
// //     std::cout << "Degenerate3dLine END" << std::endl;
// //     EXPECT_TRUE(nonFancyCheckContainment(vertices, quickhull));
// // }

// // TEST_F(QuickhullDualTest, Degenerate6dSurface) {
// //     size_t const N = 500;
// //     size_t const D = 6;

// //     srand(42);

// //     qh::pointVector_t input;

// //     for (size_t i = 0; i < N; ++i) {
// //         input.emplace_back(qh::point_t::Random(D));
// //     }

// //     std::cout << std::setprecision(23);


// //     qh::pointVector_t vertices{};
// //     vertices.emplace_back(qh::point_t::Random(6));
// //     vertices.emplace_back(qh::point_t::Random(6));
// //     vertices.emplace_back(qh::point_t::Random(6));

// //     qh quickhull{vertices, 6};
// //     quickhull.compute();

// //     for(auto const& facet : quickhull.getFacets()) {
// //         printFacet(facet, 6);
// //     }
// //     std::cout << "Degenerate6dSurface END" << std::endl;
// //     EXPECT_TRUE(nonFancyCheckContainment(vertices, quickhull));
// // }

// // TEST_F(QuickhullDualTest, SinglePoint) {
// //     qh::pointVector_t vertices{};

// //     vertices.emplace_back(3) << number_t(9)/number_t(100), 16 , number_t(-1109)/number_t(100);

// //     qh quickhull{vertices, 3};
// //     quickhull.compute();

// //     for(auto const& facet : quickhull.getFacets()) {
// //         printFacet(facet, 3);
// //     }
// //     std::cout << "SinglePoint END" << std::endl;
// //     EXPECT_TRUE(nonFancyCheckContainment(vertices, quickhull));
// // }

// // TEST_F(QuickhullDualTest, RodReactor) {
// //     qh::pointVector_t vertices{};
// //     vertices.emplace_back(3) << 524.991, 29.16, 29.16;
// //     vertices.emplace_back(3) << 524.994, 29.16, 29.16;
// //     vertices.emplace_back(3) << 524.991, 29.16, 29.16;
// //     vertices.emplace_back(3) << 524.994, 29.16, 29.16;
// //     vertices.emplace_back(3) << 524.991, 29.16, 29.16;
// //     vertices.emplace_back(3) << 524.994, 29.16, 29.16;
// //     vertices.emplace_back(3) << 524.991, 29.16, 29.16;
// //     vertices.emplace_back(3) << 524.994, 29.16, 29.16;

// //     vertices.emplace_back(3) << 525.016, 29.17, 29.17;
// //     vertices.emplace_back(3) << 525.019, 29.17, 29.17;
// //     vertices.emplace_back(3) << 525.016, 29.17, 29.17;
// //     vertices.emplace_back(3) << 525.019, 29.17, 29.17;
// //     vertices.emplace_back(3) << 525.016, 29.17, 29.17;
// //     vertices.emplace_back(3) << 525.019, 29.17, 29.17;
// //     vertices.emplace_back(3) << 525.016, 29.17, 29.17;
// //     vertices.emplace_back(3) << 525.019, 29.17, 29.17;

// //     vertices.emplace_back(3) << 5, 29.17, 29.17;






// //     qh quickhull{vertices, 3};
// //     quickhull.compute();

// //     for(auto const& facet : quickhull.getFacets()) {
// //         printFacet(facet, 3);
// //     }
// //     std::cout << "Degenerate END" << std::endl;
// //     EXPECT_TRUE(nonFancyCheckContainment(vertices, quickhull));
// // }

// bool checkContainment(qh::pointVector_t& input, qh& quickhull) {
//     return std::all_of(input.begin(), input.end(), [&quickhull](qh::point_t& v){

//         return std::all_of(quickhull.getFacets().begin(), quickhull.getFacets().end(), [&v](qh::Facet const& facet){
//             return !facet.visible(v);
//         });
//     });
// }

// void printFacet(qh::Facet const& facet, size_t dimension) {
//         char var = 'b';

//         std::cout << "(" << facet.mNormal[0] << ")a";
//         for(size_t i = 1; i < dimension; ++i) {
//             std::cout << " + (" << facet.mNormal[i] << ")" << var;
//             var += 1;
//         }

//         std::cout << " = " << facet.mOffset << std::endl;
// }