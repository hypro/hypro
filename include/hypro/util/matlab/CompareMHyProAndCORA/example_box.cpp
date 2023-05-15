
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * \example example_box.cpp This example shows how to use a box representation. It covers creation of a box, an affine transformation
 * of the created box as well as the intersection with a half space and an included test for emptiness of the resulting set.
 */

#include "datastructures/Halfspace.h"
#include "representations/GeometricObjectBase.h"
#include "util/plotting/Plotter.h"

#include <sys/time.h>

int main() {
    // use rational arithmetic.
    typedef mpq_class Number;
    struct timeval t1, t2;
    double elapsedTime;

    carl::Interval <Number> *intv1 = new carl::Interval<Number>(0, 1);
    carl::Interval <Number> *intv2 = new carl::Interval<Number>(1, 12);
    carl::Interval <Number> *intv3 = new carl::Interval<Number>(-1, 10);
    carl::Interval <Number> *intv4 = new carl::Interval<Number>(-10, 5);
    carl::Interval <Number> *intv5 = new carl::Interval<Number>(20, 34);
    std::vector <carl::Interval<Number>> intervals;
    intervals.emplace_back(*intv1);
    intervals.emplace_back(*intv2);
    intervals.emplace_back(*intv3);
    intervals.emplace_back(*intv4);
    intervals.emplace_back(*intv5);

    carl::Interval <Number> *intv1_2 = new carl::Interval<Number>(-10, 1);
    carl::Interval <Number> *intv2_2 = new carl::Interval<Number>(7, 12);
    carl::Interval <Number> *intv3_2 = new carl::Interval<Number>(-5, 11);
    carl::Interval <Number> *intv4_2 = new carl::Interval<Number>(-6, 3);
    carl::Interval <Number> *intv5_2 = new carl::Interval<Number>(0, 3);
    std::vector <carl::Interval<Number>> intervals2;
    intervals2.emplace_back(*intv1_2);
    intervals2.emplace_back(*intv2_2);
    intervals2.emplace_back(*intv3_2);
    intervals2.emplace_back(*intv4_2);
    intervals2.emplace_back(*intv5_2);

    hypro::Box <Number> box1(intervals);
    hypro::Box <Number> box2(intervals2);

    // create some transformation matrix.
    hypro::matrix_t <Number> A = hypro::matrix_t<Number>::Zero(5, 5);
    A << 10, 14, 7, -9, 14, 14, 7, -6, -8, -10, 7, 9, 8,
            11, 1, -10, 9, -10, 8, -1, 12, 0, -3, -2, 9;

    // create some translation vector.
    hypro::vector_t <Number> b = hypro::vector_t<Number>::Zero(5);
    b(0) = 1;
    b(1) = 2;
    b(2) = 3;
    b(3) = 4;
    b(4) = 5;

    std::cout << "------------------------------" << std::endl;
    std::cout << "vertices" << std::endl;
    std::cout << "------------------------------" << std::endl;

    // start timer
    gettimeofday(&t1, NULL);

    // compute all vertices of the box and output them.
    std::vector <hypro::Point<Number>> tvertices = box1.vertices();

    // stop timer
    gettimeofday(&t2, NULL);

    for (const auto &vertex: tvertices)
        std::cout << vertex << std::endl;

    std::cout << box1 << std::endl;

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;  // us to ms

    std::cout << "Time spent: " << elapsedTime << "ms\n"
              << std::endl;

    std::cout << "------------------------------" << std::endl;
    std::cout << "Minkowski sum" << std::endl;
    std::cout << "------------------------------" << std::endl;

    // start timer
    gettimeofday(&t1, NULL);

    // compute all vertices of the box and output them.

    hypro::Box <Number> res = box1.minkowskiSum(box2);
    // stop timer
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;  // us to ms

    std::cout << "Time spent: " << elapsedTime << "ms\n"
              << std::endl;

    std::cout << "------------------------------" << std::endl;
    std::cout << "Affine transformation" << std::endl;
    std::cout << "------------------------------" << std::endl;

    // start timer
    gettimeofday(&t1, NULL);

    // transform the initial box with the created matrix and vector (affine transformation).
    hypro::Box <Number> res2 = box1.affineTransformation(A, b);

    std::vector <hypro::Point<Number>> tve = res2.vertices();
    for (const auto &vertex: tve)
        std::cout << vertex << std::endl;

    // stop timer
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;  // us to ms

    std::cout << "Time spent: " << elapsedTime << "ms\n"
              << std::endl;

    std::cout << "------------------------------" << std::endl;
    std::cout << "union" << std::endl;
    std::cout << "------------------------------" << std::endl;

    // start timer
    gettimeofday(&t1, NULL);

    hypro::Box <Number> res3 = box1.unite(box2);
    // stop timer
    gettimeofday(&t2, NULL);

    std::vector <hypro::Point<Number>> tve2 = res3.vertices();
    for (const auto &vertex: tve2)
        std::cout << vertex << std::endl;

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;  // us to ms

    std::cout << "Time spent: " << elapsedTime << "ms\n"
              << std::endl;

    std::cout << "------------------------------" << std::endl;
    std::cout << "intersect" << std::endl;
    std::cout << "------------------------------" << std::endl;

    // start timer
    gettimeofday(&t1, NULL);

    hypro::Box <Number> res4 = box1.intersect(box2);

    // stop timer
    gettimeofday(&t2, NULL);

    std::vector <hypro::Point<Number>> tve3 = res4.vertices();
    for (const auto &vertex: tve3)
        std::cout << vertex << std::endl;

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;  // us to ms

    std::cout << "Time spent: " << elapsedTime << "ms\n"
              << std::endl;

    std::cout << "------------------------------" << std::endl;
    std::cout << "supremum" << std::endl;
    std::cout << "------------------------------" << std::endl;

    // start timer
    gettimeofday(&t1, NULL);

    auto res5 = box1.supremum();

    // stop timer
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;  // us to ms

    std::cout << "Time spent: " << elapsedTime << "ms\n"
              << std::endl;

    std::cout << "------------------------------" << std::endl;
    std::cout << "scale" << std::endl;
    std::cout << "------------------------------" << std::endl;

    // start timer
    gettimeofday(&t1, NULL);

    auto res6 = box1 * 10;

    // stop timer
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;  // us to ms

    std::cout << "Time spent: " << elapsedTime << "ms\n"
              << std::endl;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    //	carl::Interval<Number> intv1 = new carl::Interval<Number>(0,1);
    //	carl::Interval<Number> intv2 = new carl::Interval<Number>(1,1);

    //	carl::Interval<Number> res1 = intv1 + intv2;

    return 0;
}
