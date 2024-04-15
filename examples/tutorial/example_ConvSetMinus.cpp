/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * This is an example on how to set up a rudimentary reachability analysis method.
 */

// #include "hypro/representations/Polytopes/VPolytope/VPolytopeSetting.h"
// #include "hypro/representations/conversion/Converter.h"
#include <hypro/representations/GeometricObjectBase.h>

using namespace hypro;

template<typename Number, typename Converter, typename Setting>
static VPolytopeT<Number, Converter, Setting> getPolytopeP() {
    // Create a polytope
    using pointVector = std::vector<Point<Number>>;

    pointVector points;
    points.push_back(Point<Number>({Number(1), Number(1), Number(1)}));
    points.push_back(Point<Number>({Number(3), Number(1), Number(1)}));
    points.push_back(Point<Number>({Number(1), Number(3), Number(1)}));
    points.push_back(Point<Number>({Number(3), Number(3), Number(1)}));

    points.push_back(Point<Number>({Number(1), Number(3), Number(3)}));
    points.push_back(Point<Number>({Number(3), Number(3), Number(3)}));
    points.push_back(Point<Number>({Number(1), Number(1), Number(3)}));
    points.push_back(Point<Number>({Number(3), Number(1), Number(3)}));

    points.push_back(Point<Number>({Number(1.5), Number(1.5), Number(1.5)}));
    points.push_back(Point<Number>({Number(1.6), Number(1.6), Number(1.6)}));
    
    VPolytopeT<Number, Converter, Setting> vp = VPolytopeT<Number, Converter, Setting>(points);
    return vp;
}

template<typename Number, typename Converter, typename Setting>
static VPolytopeT<Number, Converter, Setting> getPolytopeG() {
    // Create a polytope
    using pointVector = std::vector<Point<Number>>;

    pointVector points;
    points.push_back(Point<Number>({Number(2), Number(2), Number(0)}));
    points.push_back(Point<Number>({Number(6), Number(2), Number(0)}));
    points.push_back(Point<Number>({Number(2), Number(5), Number(0)}));
    points.push_back(Point<Number>({Number(6), Number(5), Number(0)}));

    points.push_back(Point<Number>({Number(2), Number(5), Number(4)}));
    points.push_back(Point<Number>({Number(6), Number(5), Number(4)}));
    points.push_back(Point<Number>({Number(6), Number(2), Number(4)}));
    points.push_back(Point<Number>({Number(2), Number(2), Number(4)}));
    
    VPolytopeT<Number, Converter, Setting> vp = VPolytopeT<Number, Converter, Setting>(points);
    return vp;
}


template<typename Number, typename Converter, typename Setting>
static void calculateConvexSetMinus() {

    VPolytopeT<Number, Converter, Setting> P = getPolytopeP<Number, Converter, Setting>();
    VPolytopeT<Number, Converter, Setting> G = getPolytopeG<Number, Converter, Setting>();

    //extremePointsPrint(P);
    //convexEdgesPrint(P);
    VPolytopeT<Number, Converter, Setting> res = P.setMinusCrossing(G);
}

template<typename Number, typename Converter, typename Setting>
void convexEdgesPrint(VPolytopeT<Number, Converter, Setting> M){
    std::cout << "Convex edges of the polytope are " << std::endl;
    std::vector<std::pair<Point<Number>, Point<Number>>> edges = M.getConvexEdges();

    for (auto cur_edge : edges){
        std::cout << cur_edge.first << " , " << cur_edge.second << std::endl;
    }
}

template<typename Number, typename Converter, typename Setting>
void extremePointsPrint(VPolytopeT<Number, Converter, Setting> M){
    std::cout << "Extreme points of the polytope are " << std::endl;
    std::vector<Point<Number>> points = M.getExtremePoints();

    for (auto cur_point : points){
        std::cout << cur_point << std::endl;
    }

}

int main(int argc, char **argv) {
    std::cout << "Start of the convex set minus" << std::endl;

    using Number = double;
    using Converter = Converter<Number>;
	using Setting = VPolytopeSetting;

    calculateConvexSetMinus<Number, Converter, Setting>();

    std::cout << "End of the convex set minus" << std::endl;

    exit(0);
}
