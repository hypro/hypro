/** 
 * @file   polyhedron_parser.h
 * Created on May 12, 2011
 * Last modified June 23, 2011
 * 
 * @author Sebastian Junges
 */
#ifndef POLYHEDRONPARSER_H
#define	POLYHEDRONPARSER_H


#include "polyhedron_ort.h"
#include "hpolytope.h"
#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>

namespace reachLin {

using boost::assign::map_list_of;

const boost::unordered_map<PolyhedronOrtRepresentation,std::string> PolyhedronOrtReprToString = map_list_of
    (EXTREMEVERTEX, "ExtremeVertex")
    (NEIGHBOUR, "Neighbour")
    (VERTEX, "Vertex");


/**
 * @class PolyhedronParser
 */
class PolyhedronParser {
public:
    PolyhedronParser(std::string path="./");
    PolyhedronParser(const PolyhedronParser& orig);
    virtual ~PolyhedronParser();
    
    void setPath(std::string path) {
        mPath = path;
    }
    
    std::string getPath() {
        return mPath;
    }
    
    void parseFile(std::string path, PolyhedronOrt& pol);
    
    void save(std::string name, PolyhedronOrt pol );
    
    HPolytope loadHPolytope(std::string filename);
    
private:
    
    bool openRead(std::string filename, std::fstream& fin);
    void parseLine(std::ifstream& fin, std::stringstream& iss);
    void parseHeader(std::ifstream& fin, unsigned& dim, std::string& type, std::string& subtype );
    
    std::string mPath;
    
    log4cplus::Logger mLogIn;
    log4cplus::Logger mLogOut;
};


}// end namespace.
#endif	/* POLYHEDRONPARSER_H */

