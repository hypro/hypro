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
static VPolytopeT<Number, Converter, Setting> getPolytopeP2() {
    // Create a polytope
    using pointVector = std::vector<Point<Number>>;

    pointVector points;
    points.push_back(Point<Number>({Number(1), Number(1), Number(1)}));
    points.push_back(Point<Number>({Number(1), Number(1), Number(2)}));
    points.push_back(Point<Number>({Number(4), Number(1), Number(1)}));
    points.push_back(Point<Number>({Number(4), Number(1), Number(2)}));

    points.push_back(Point<Number>({Number(1), Number(5), Number(1)}));
    points.push_back(Point<Number>({Number(4), Number(5), Number(1)}));
    points.push_back(Point<Number>({Number(1), Number(5), Number(2)}));
    points.push_back(Point<Number>({Number(4), Number(5), Number(2)}));
    
    VPolytopeT<Number, Converter, Setting> vp = VPolytopeT<Number, Converter, Setting>(points);
    return vp;
}

template<typename Number, typename Converter, typename Setting>
static VPolytopeT<Number, Converter, Setting> getPolytopeG2() {
    // Create a polytope
    using pointVector = std::vector<Point<Number>>;

    pointVector points;

    points.push_back(Point<Number>({Number(0), Number(2), Number(0)}));
    points.push_back(Point<Number>({Number(6), Number(2), Number(0)}));
    points.push_back(Point<Number>({Number(0), Number(4), Number(0)}));
    points.push_back(Point<Number>({Number(6), Number(4), Number(0)}));

    points.push_back(Point<Number>({Number(0), Number(2), Number(3)}));
    points.push_back(Point<Number>({Number(0), Number(4), Number(3)}));
    points.push_back(Point<Number>({Number(6), Number(4), Number(3)}));
    points.push_back(Point<Number>({Number(6), Number(2), Number(3)}));
    
    VPolytopeT<Number, Converter, Setting> vp = VPolytopeT<Number, Converter, Setting>(points);
    return vp;
}

template<typename Number, typename Converter, typename Setting>
static VPolytopeT<Number, Converter, Setting> getPolytopeP3() {
    // Create a polytope
    using pointVector = std::vector<Point<Number>>;

    pointVector points;
    points.push_back(Point<Number>({Number(0), Number(0), Number(0)}));
    points.push_back(Point<Number>({Number(0), Number(7), Number(0)}));
    points.push_back(Point<Number>({Number(6), Number(7), Number(0)}));
    points.push_back(Point<Number>({Number(6), Number(0), Number(0)}));

    points.push_back(Point<Number>({Number(0), Number(0), Number(6)}));
    points.push_back(Point<Number>({Number(0), Number(7), Number(6)}));
    points.push_back(Point<Number>({Number(6), Number(7), Number(6)}));
    points.push_back(Point<Number>({Number(6), Number(0), Number(6)}));
    
    VPolytopeT<Number, Converter, Setting> vp = VPolytopeT<Number, Converter, Setting>(points);
    return vp;
}

template<typename Number, typename Converter, typename Setting>
static VPolytopeT<Number, Converter, Setting> getPolytopeG3() {
    // Create a polytope
    using pointVector = std::vector<Point<Number>>;

    pointVector points;

    points.push_back(Point<Number>({Number(3), Number(5), Number(-1)}));
    points.push_back(Point<Number>({Number(9), Number(2), Number(-1)}));
    points.push_back(Point<Number>({Number(9), Number(2), Number(4)}));
    points.push_back(Point<Number>({Number(3), Number(5), Number(4)}));

    points.push_back(Point<Number>({Number(8), Number(9), Number(4)}));
    points.push_back(Point<Number>({Number(8), Number(9), Number(-1)}));
    points.push_back(Point<Number>({Number(10), Number(8), Number(4)}));
    points.push_back(Point<Number>({Number(10), Number(8), Number(-1)}));
    
    VPolytopeT<Number, Converter, Setting> vp = VPolytopeT<Number, Converter, Setting>(points);
    return vp;
}

template<typename Number, typename Converter, typename Setting>
static VPolytopeT<Number, Converter, Setting> getPolytopeP2D() {
    // Create a polytope
    using pointVector = std::vector<Point<Number>>;

    pointVector points;

    points.push_back(Point<Number>({Number(1), Number(1)}));
    points.push_back(Point<Number>({Number(1), Number(6)}));
    points.push_back(Point<Number>({Number(6), Number(6)}));
    points.push_back(Point<Number>({Number(6), Number(1)}));
    
    VPolytopeT<Number, Converter, Setting> vp = VPolytopeT<Number, Converter, Setting>(points);
    return vp;
}

template<typename Number, typename Converter, typename Setting>
static VPolytopeT<Number, Converter, Setting> getPolytopeG2D() {
    // Create a polytope
    using pointVector = std::vector<Point<Number>>;

    pointVector points;

    points.push_back(Point<Number>({Number(4), Number(4)}));
    points.push_back(Point<Number>({Number(4), Number(8)}));
    points.push_back(Point<Number>({Number(8), Number(8)}));
    points.push_back(Point<Number>({Number(8), Number(4)}));
    
    VPolytopeT<Number, Converter, Setting> vp = VPolytopeT<Number, Converter, Setting>(points);
    return vp;
}

template<typename Number, typename Converter, typename Setting>
static void printPolytopeV(VPolytopeT<Number, Converter, Setting> P, std::string name) {
    std::cout << "Polytope " << name << " is:" << std::endl;
    // for (auto it_point = P.begin(); it_point != P.end(); it_point++){
    //     std::cout << *it_point << std::endl;
    // }
    std::cout << P << std::endl;
}

template<typename Number, typename Converter, typename Setting>
static void printPolytopeH(HPolytopeT<Number, Converter, Setting> P, std::string name) {
    std::cout << "Polytope " << name << " is:" << std::endl;
    std::cout << P << std::endl;
}


template<typename Number, typename Converter, typename Setting>
static void calculateConvexSetMinus(int rep) {
    
    VPolytopeT<Number, Converter, Setting> P;
    VPolytopeT<Number, Converter, Setting> G;
    VPolytopeT<Number, Converter, Setting> res;


    switch (rep)
    {
        case 1:
            P = getPolytopeP<Number, Converter, Setting>();
            G = getPolytopeG<Number, Converter, Setting>();
            res = P.setMinusCrossingV(G);

            printPolytopeV(P, "P");
            printPolytopeV(G, "G");
            printPolytopeV(res, "P - G");
            break;

        case 2:
            P = getPolytopeP2<Number, Converter, Setting>();
            G = getPolytopeG2<Number, Converter, Setting>();
            res = P.setMinusCrossingV(G);

            printPolytopeV(P, "P");
            printPolytopeV(G, "G");
            printPolytopeV(res, "P - G");
            break;
        
        case 3:
            P = getPolytopeP3<Number, Converter, Setting>();
            G = getPolytopeG3<Number, Converter, Setting>();
            res = P.setMinusCrossingV(G);

            printPolytopeV(P, "P");
            printPolytopeV(G, "G");
            printPolytopeV(res, "P - G");
            break;

        case 4:
            P = getPolytopeP2D<Number, Converter, Setting>();
            G = getPolytopeG2D<Number, Converter, Setting>();
            res = P.setMinusCrossingV(G);

            printPolytopeV(P, "P");
            printPolytopeV(G, "G");
            printPolytopeV(res, "P - G");
            break;

        case 5:
            P = getPolytopeP3<Number, Converter, Setting>();
            G = getPolytopeG3<Number, Converter, Setting>();

            using HSetting = HPolytopeSetting;
            HPolytopeT<Number, Converter, HSetting> G_H = hypro::Converter<Number>::toHPolytope(G, CONV_MODE::OVER);

            VPolytopeT<Number, Converter, Setting> res = P.setMinusCrossingH(G_H);

            printPolytopeV(P, "P");
            printPolytopeV(G, "G");
            printPolytopeH(G_H, "G_H");

            printPolytopeV(res, "P - G_H");
            break;

    }
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

    int rep = 0;
    if (argc == 2) {
        char *p;
        rep = strtol(argv[1], &p, 10);
    }else{
        std::cout << "Please provide a number for example to run:" << std::endl;
        std::cout << "Options: Numbers 1,2,3 V-Polytope P and V-Polytope G in 3D" << std::endl;
        std::cout << "Options: Number 4 V-Polytope P and V-Polytope G in 2D" << std::endl;
        std::cout << "Options: Number 5 V-Polytope P and H-Polytope G in 3D" << std::endl;
        return 0;
    }

    using Number = mpq_class; //slower
    using Converter = Converter<Number>;
	using Setting = VPolytopeSetting;


    std::cout << "Running example " << rep << std::endl;
    calculateConvexSetMinus<Number, Converter, Setting>(rep);


    exit(0);
}
