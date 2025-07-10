/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 16.05.23.
 */

#ifndef HYPRO_GRAHAMSCAN_H
#define HYPRO_GRAHAMSCAN_H

#include <vector>
#include "../../datastructures/Point.h"

namespace hypro {
    namespace impl {
        template<typename Number>
        bool isLeftTurn(const Point<Number> &a, const Point<Number> &b, const Point<Number> &c) {
            assert(a.dimension() == 2);
            assert(b.dimension() == 2);
            assert(c.dimension() == 2);

            return (((b.rawCoordinates()(0) - a.rawCoordinates()(0)) *
                     (c.rawCoordinates()(1) - a.rawCoordinates()(1))) -
                    ((c.rawCoordinates()(0) - a.rawCoordinates()(0)) *
                     (b.rawCoordinates()(1) - a.rawCoordinates()(1))) >= 0);
        }

        template<typename Number>
        std::vector<std::size_t> grahamScan_indices(const std::vector<Point<Number>> &points) {
            if (points.size() < 3) {
                auto res = std::vector<std::size_t>(points.size());
                std::iota(res.begin(), res.end(), 0);
                return res;
            }

            // initialize -> find minimum Point
            std::size_t min = 0;
            for (std::size_t i = 1; i < points.size(); ++i) {
                assert(points[i].dimension() == 2);
                if (points[i] < points[min]) {
                    min = i;
                }
            }

            // sort Points according to polar angle -> we have to insert manually
            // (because of double imprecision)
            std::map<Number, std::size_t> sortedPoints;
            for (std::size_t i = 0; i < points.size(); ++i) {
                if (points[i] != points[min]) {
                    Number angle = points[i].polarCoordinates(points[min]).at(1);
                    if (sortedPoints.empty()) {
                        sortedPoints.insert(std::make_pair(angle, i));
                    } else {
                        for (auto pos = sortedPoints.begin(); pos != sortedPoints.end();) {
                            // if equal, take the one with bigger radial component
                            Number newAngle = points[pos->second].polarCoordinates(points[min])[1];
                            if (angle == newAngle) {
                                // if equal, compare radial coordinate (distance)
                                if (points[pos->second].polarCoordinates(points[min])[0] <
                                    points[i].polarCoordinates(points[min])[0]) {
                                    pos = sortedPoints.erase(pos);
                                    sortedPoints.insert(std::make_pair(angle, i));
                                }
                                break;
                            }
                                // we assume to be sorted, so check all angles, which are smaller or
                                // equal for equality -
                                // afterwards simply insert
                            else if (angle > newAngle) {    // not equal and smaller -> continue
                                // search (at end, simply insert)
                                ++pos;
                                if (pos == sortedPoints.end()) {
                                    sortedPoints.insert(std::make_pair(angle, i));
                                    break;
                                }
                            } else {  // larger and not equal until this point -> simply insert
                                sortedPoints.insert(std::make_pair(angle, i));
                                break;
                            }
                        }
                    }
                }
            }

            if (sortedPoints.empty()) {
                return std::vector<std::size_t>{min};
            }
            assert(sortedPoints.size() >= 1);

            std::stack<std::size_t> stack;
            // prepare stack -> initialize with 2 points
            stack.push(min);
            stack.push(sortedPoints.begin()->second);
            sortedPoints.erase(sortedPoints.begin());
            std::size_t i = 0;
            std::size_t n = sortedPoints.size();

            // main loop -> check the two topmost elements of the stack and one third,
            // new point
            while (i < n) {
                std::size_t p1 = stack.top();
                stack.pop();
                std::size_t p2 = stack.top();
                stack.pop();
                if (isLeftTurn(points[p2], points[p1], points[sortedPoints.begin()->second])) {
                    // reinsert and add new point
                    stack.push(p2);
                    stack.push(p1);
                    stack.push(sortedPoints.begin()->second);
                    sortedPoints.erase(sortedPoints.begin());
                    ++i;
                } else {
                    // only reinsert second -> equal to removing the topmost object of the
                    // stack
                    stack.push(p2);
                    if (stack.size() < 2) {
                        // in this case simply insert, as the stack has to contain at least 2
                        // points
                        stack.push(sortedPoints.begin()->second);
                        sortedPoints.erase(sortedPoints.begin());
                        ++i;
                    }
                }
            }

            // write result
            std::vector<std::size_t> res;
            while (!stack.empty()) {
                res.push_back(stack.top());
                stack.pop();
            }

            return res;
        }
    } // namespace impl

    template<typename Number>
    std::vector<Point<Number>> grahamScan(const std::vector<Point<Number>> &points) {
        auto indices = impl::grahamScan_indices(points);
        std::vector<Point<Number>> res;
        for (auto idx: indices) {
            res.emplace_back(points[idx]);
        }
        return res;
    }

}

#endif //HYPRO_GRAHAMSCAN_H
