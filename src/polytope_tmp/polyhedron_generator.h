/** 
 * @file   polyhedron_generator.h
 * Created on May 12, 2011
 * Last modified May 12, 2011
 * 
 * @author Sebastian Junges
 * 
 */

#ifndef POLYHEDRONGENERATOR_H
#define	POLYHEDRONGENERATOR_H

#include "polyhedron_ort.h"
#include "vertex.h"

namespace reachLin {
class PolyhedronGenerator {
public:
    PolyhedronGenerator();
    PolyhedronGenerator(const PolyhedronGenerator& orig);
    
    virtual ~PolyhedronGenerator();

    static std::vector<Vertex> selectPrimitive(unsigned dim, unsigned bound);
    static PolyhedronOrt generateHigherDimensionPolyhedron(unsigned dim, unsigned bound);
    static PolyhedronOrt generateFullRandomPolyhedron(unsigned dim,  Point& bounds, float rate, unsigned& blackpoints);
    static PolyhedronOrt generateSnakedRandomPolyhedron(unsigned dim,  Point& bounds, const Point& start, unsigned steps, unsigned& blackpoints);
    static PolyhedronOrt generateLocationDependentPolyhedron(unsigned dim, Point& bounds, const Point& mean, float rate, unsigned& blackpoints);

    static PolyhedronOrt generateRandomPolyhedronAroundMean();
private:

    
    static log4cplus::Logger mLogger;
};
}
#endif	/* POLYHEDRONGENERATOR_H */

