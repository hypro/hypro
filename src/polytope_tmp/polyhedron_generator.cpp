/** 
 * @file   polyhedron.cpp
 * Created on May 12, 2011
 * Last modified May 12, 2011
 * 
 * @author Sebastian Junges
 */

#include "polyhedron_generator.h"
#include "polyhedron_parser.h"
#include <vector>
#include <cmath>

using namespace log4cplus;

namespace reachLin {
    
PolyhedronGenerator::PolyhedronGenerator() {
}

PolyhedronGenerator::~PolyhedronGenerator() {
}

    log4cplus::Logger PolyhedronGenerator::mLogger = Logger::getInstance("reachLin.Generator.Orthogonal");
/**
 * 
 * @param dim number of dimensions the primitive should have. Currently only 2 is supported.
 * @param bound value giving the bound in all dimensions
 * @return A list of vertices of a 2d polyhedron.
 */
std::vector<Vertex> PolyhedronGenerator::selectPrimitive(unsigned dim, unsigned bound=reachLin_NR_PRIMITIVES) {
   //throw an error if not two.
    if (dim != 2) LOG4CPLUS_FATAL(mLogger, "Only two dimensional is supported for selectPrimitive");
    std::cout << "Select primitive\n";
   
    if (bound-1 > reachLin_NR_PRIMITIVES) bound = reachLin_NR_PRIMITIVES;   
   std::vector<Vertex> v;
   PolyhedronOrt pol; //= PolyhedronOrt(v,dim);
   PolyhedronOrt operatingPol; // = PolyhedronOrt(v,dim);
   PolyhedronParser parser = PolyhedronParser(reachLin_PRIMITIVES_LOCATION);
   
   unsigned rnd = rand()%bound +1;
   //rnd is also the size.
   parser.parseFile("primitive"+(boost::lexical_cast<std::string >(rnd)),pol);
   //move it randomly around.
   pol.move(Point::Random(Point(dim,bound-rnd)));
   LOG4CPLUS_DEBUG(mLogger, "Moving with " << operatingPol);
   
   unsigned runs = 6;
   unsigned bnd =bound*0.8;
       
   for (unsigned j=0;j<runs; j++) {
        rnd = rand()%bnd +1;
        //rnd is also the size.
        
        LOG4CPLUS_TRACE(mLogger, "Random: " << rnd);
        parser.parseFile("primitive"+(boost::lexical_cast<std::string >(rnd)),operatingPol);
        //move it randomly around.
        operatingPol.move(Point::Random(Point(dim,bound-rnd)));
        LOG4CPLUS_DEBUG(mLogger, "Moving with " << operatingPol);
        if (1.5*rnd < bnd) {pol = pol.calculateUnion(operatingPol);}
        else {pol = pol.calculateIntersection(operatingPol);}
   }
   
   return pol.getVertices();

}


/**
 * 
 * @param dim
 * @param bounds
 * @param rate
 * @param blackpoints
 * @return 
 */
PolyhedronOrt PolyhedronGenerator::generateFullRandomPolyhedron(unsigned dim, Point& bounds, float rate, unsigned& blackpoints) {
    int threshold = (int)(rate * RAND_MAX);
    std::map<Point, bool> grid;
    Point p = Point(dim);
    bool colour;
    blackpoints = 0;
    do {
        // std::cout<< "bounds " << bounds << std::endl;
        colour = rand()<threshold;
        if (colour) blackpoints++;
        grid.insert(std::pair<Point, bool>(p,colour));
        p.nextPointOnGrid(bounds);
        //std::cout << p << "[" << colour <<"]"<< std::endl;
    } while (p != bounds);
    bounds.IncrementInAllDim();
    LOG4CPLUS_INFO(mLogger, "Generated grid");
    return PolyhedronOrt(grid, bounds, dim);
}

PolyhedronOrt PolyhedronGenerator::generateLocationDependentPolyhedron(unsigned dim, Point& bounds,const Point& mean, float rate, unsigned& blackpoints) {
    std::map<Point, bool> grid;
    Point p = Point(dim);
    bool colour;
    blackpoints = 0;
    std::cout << bounds;
    do {
        std::cout << p;
        double prob = p.getDistanceDependentProbabiltity(mean,bounds[0], rate);
        std::cout << " " << prob << std::endl;
        if (prob >= 1) colour = true; 
        else  colour = rand()<prob*RAND_MAX;
        if (colour) blackpoints++;
        grid.insert(std::pair<Point, bool>(p,colour));
        p.nextPointOnGrid(bounds);
        //std::cout << p << "[" << colour <<"]"<< std::endl;
    } while (p != bounds);
    bounds.IncrementInAllDim();
    LOG4CPLUS_INFO(mLogger, "Generated grid");
    return PolyhedronOrt(grid, bounds, dim);
}

/**
 * 
 * @param dim
 * @param bounds
 * @param start
 * @param steps
 * @param blackpoints
 * @return 
 */
PolyhedronOrt PolyhedronGenerator::generateSnakedRandomPolyhedron(unsigned dim, Point& bounds,const Point& start, unsigned steps, unsigned& blackpoints) {
        std::map<Point, bool> grid;
        Point p = Point(dim);
        bool colour;
        blackpoints = 0;
        do {
            // std::cout<< "bounds " << bounds << std::endl;
            grid.insert(std::pair<Point, bool>(p,colour));
            p.nextPointOnGrid(bounds);
            //std::cout << p << "[" << colour <<"]"<< std::endl;
        } while (p != bounds);
        
        LOG4CPLUS_INFO(mLogger, "Filled grid");
        p = start;
        grid[p] = true;
        unsigned restarts = steps/bounds.sum() ;
        for (unsigned d=0; d<restarts; d++) {
            //std::cout << d<<"/"<<restarts<<std::endl;
            p=start;
            unsigned innerloops =  steps/restarts/5;
            for (unsigned i = 0; i<innerloops; i++) {
                p = p.moveRandomInBoundary(bounds);
                grid[p] = true;
                //std::cout << p << std::endl;
            }
            Point q = p;
            for (unsigned k = 0; k < 4; k++) {
                for (unsigned i = 0; i<innerloops; i++) {
                    p = p.moveRandomInBoundary(bounds);
                    grid[p] = true;
                    //std::cout << p << std::endl;
                }
                p = q;
            }
            
        }
        
        for (std::map<Point,bool>::iterator it = grid.begin(); it != grid.end(); it++) {
            if (it->second) blackpoints++;
        }
        bounds.IncrementInAllDim();
        
        LOG4CPLUS_INFO(mLogger, "Generated grid");
        
    //   std::cout << "Number of memberpoints " << blackpoints << " out of  " << pow(bounds[0]+1, dim) <<" (" << (double)blackpoints/(double)pow(bounds[0]+1, dim) << ")" <<  std::endl;

        return PolyhedronOrt(grid, bounds, dim);

    }

/**
 * Builds a higher dimensional polyhedron by 
 * @param dim the dimension
 * @param bound value giving the bound in all dimensions
 * @return 
 */
PolyhedronOrt PolyhedronGenerator::generateHigherDimensionPolyhedron(unsigned dim, unsigned bound) {
    unsigned dimension = 0;
    unsigned nrVertices = 1;
    std::vector< std::vector<Vertex> > primitives;
    std::vector<Vertex> vertices;
    primitives.reserve(dim);
    unsigned primDim = 2;
    while (dimension < dim)  {
        unsigned size;
        do {
            vertices = selectPrimitive(primDim, bound);
            size = vertices.size();
        } while(size == 0);
        
        primitives.push_back(vertices);
        dimension += primDim;
        nrVertices *= size;
    }
    vertices.clear();
    vertices.reserve(nrVertices);
    vertices.resize(nrVertices,Vertex(2, true));

    unsigned remainingVertices = nrVertices;
    for (unsigned k=0; k<primitives.size(); k++) {
        unsigned repeat = remainingVertices/primitives[k].size();
        remainingVertices /= primitives[k].size();
        unsigned again = nrVertices/(repeat*primitives[k].size());
      /*  std::cout << "repeat: " << repeat << endl;
        cout << "again: " << again << endl;
        cout << "---------" << endl;*/
        for (unsigned r=0; r<again; r++) {
            unsigned agOffset = r*repeat*primitives[k].size();
            for (unsigned j=0; j<primitives[k].size(); j++) {
                unsigned repOffset = repeat*j;
                for (unsigned i= 0; i<repeat; i++) {
                    vertices[agOffset+repOffset+i].insertCoordinates(primitives[k][j].getCoordinates(), primDim*k);
                    if (!primitives[k][j].getColor()) vertices[agOffset+repOffset+i].setColor(false);
                }
            }
        }
        
    }
    for (unsigned i=0; i<nrVertices; i++) {
        vertices[i].setDimension(dim);
        LOG4CPLUS_INFO(mLogger,  i <<": " <<vertices[i]);
    }

    return reachLin::PolyhedronOrt(vertices, dim);
    
}

}