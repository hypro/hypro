/** 
 * @file   polyhedron_parser.cpp
 * Created on May 12, 2011
 * Last modified June 23, 2011
 * 
 * @author Sebastian Junges
 */
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include "polyhedron_parser.h"
#include "polyhedron_ort.h"
#include "point.h"
#include "hpolytope.h"


using namespace log4cplus;
using std::string;

namespace reachLin {

    PolyhedronParser::PolyhedronParser(std::string path) : 
    mPath(path)
    {
        mLogIn = Logger::getInstance("reachLin.Parser.Input");
        mLogOut = Logger::getInstance("reachLin.Parser.Output");
    }

    PolyhedronParser::~PolyhedronParser() {
    }
    
    
    /**
     * Saves the polyhedron. Saves only the data that is useful for the representation the polyhedron is in.
     * @param name the name of the polyhedron, combined with the parsers' mPath.
     * @param pol The polyhedron to be saved.
     */
    void PolyhedronParser::save(std::string name, PolyhedronOrt pol ) {
        std::ofstream outfile;
        
        
        outfile << pol.mDimension << std::endl;
        outfile << "ORTHOGONAL" << std::endl; //type
        outfile << PolyhedronOrtReprToString.at(pol.getRepresentation()) << std::endl; //subtype
        outfile << pol.mNrVertices << std::endl;
        
        VertexContainerIt it;
        for (it = pol.mVertices.begin(); it != pol.mVertices.end(); it++ ) {
            outfile << it->toString(false);
            //outfile.flush();
            if (pol.getRepresentation() == EXTREMEVERTEX) {
                outfile << " " <<(pol.mExtremeVertices.isVertex(*it).first); 
            } else {
                outfile << " " << 0;
            }
            outfile << std::endl;    
        }
        if (pol.getRepresentation() == NEIGHBOUR) {
            for (it = pol.mVertices.begin(); it != pol.mVertices.end(); ++it) {
                outfile << it->toString(false) << std::endl;
                
                for (vSetIt nit = pol.mNeighbourhood.getNeighbourhoodBegin(*it); nit != pol.mNeighbourhood.getNeighbourhoodEnd(*it); ++nit) {
                    outfile << nit->toString(false) << std::endl;
                }            
                
            }
        }
        
        outfile.close();
    
    }

    /**
     * @brief Helperfunction for the load-method.
     * Skips lines preceding with a '#'
     */
    void PolyhedronParser::parseLine(std::ifstream& fin, std::stringstream& iss) {
        string line;
        //TODO There should be a better way to handle comments
        bool comment;
        do {
            comment = (fin.peek() == '#');
            getline(fin, line);
        } while(comment);
        iss.ignore(1024, '\n');
        iss.clear();
        iss << line;
    }
    
    /**
     * 
     * @param filename Filename to be read at mPath.
     * @param fin filestream.
     * @return true, if success
     */
    bool PolyhedronParser::openRead(string filename, std::ifstream& fstr) {
        string path = mPath = filename;
        fstr.open(path.c_str());
        if(!fstr) {
            LOG4CPLUS_FATAL(mLogIn, path<< " could not be opened");
            return false;
        }
        
        LOG4CPLUS_INFO(mLogIn, path << "  opened");
        return true;
    }
    
    bool PolyhedronParser::openWrite(string filename, std::ofstream& fstr) {
        string path = mPath = filename;
        fstr.open(path.c_str());
        if(!fstr) {
            LOG4CPLUS_FATAL(mLogOut, path<< " could not be opened");
            return false;
        }
        
        LOG4CPLUS_INFO(mLogOut, path << "  opened");
        return true;
    }
    
    
    /**
     * 
     * @param fin
     * @param dim   
     * @param type
     * @param subtype
     */
    void PolyhedronParser::parseHeader(std::ifstream& fin, unsigned& dim, string& type, string& subtype ) {
        string line;
        std::stringstream iss(line);
        parseLine(fin, iss);
        iss >> dim;
        LOG4CPLUS_INFO(mLogIn, "dimension " << dim);
        
        parseLine(fin, iss);
        iss >> type;
        parseLine(fin,iss);
        iss >> subtype;
        LOG4CPLUS_INFO(mLogIn, "type " << type <<  ", subtype " << subtype);
    }
    
    /**
     * 
     * @param filename
     * @return 
     */
    HPolytope PolyhedronParser::loadHPolytope(std::string filename) {
        std::ifstream fin;
        string line;
        std::stringstream iss(line);
        
        openRead(filename, fin);
        
        unsigned dimension;
        string type;
        string subtype;
        
        parseHeader(fin, dimension, type, subtype);
        
        if(type != "HPOLYTOPE") {
            fin.close();
            LOG4CPLUS_ERROR(mLogIn, "Not a H-polytope");
            return 0;
        }
        
        unsigned nrConstraints;
        parseLine(fin, iss);
        iss >> nrConstraints;
        
        HPolytope polytope(dimension);
        LinearConstraint lincon;
        for(unsigned i = 0; i<nrConstraints; i++) {
            parseLine(fin, iss);
            iss >> lincon;
            polytope.addConstraint(lincon);
        }
        
        
        
    }

    /**
     * Reads a polyhedron. Supports the three Orthogonal representations.
     * TODO better errorhandling.
     * TODO change naming and type
     * @param name The file to be opened, located at mPath.
     * @param pol The Polyhedron that is saved.
     */
    void PolyhedronParser::parseFile(std::string name, PolyhedronOrt& pol) {
        std::ifstream fin;
        string line;
        std::stringstream iss(line);

        //Polyhedron information.
        unsigned dimension;
        string type;
        string subtype;

        openRead(name, fin);
        parseHeader(fin, dimension, type, subtype);
        
        if (type == "ORTHOGONAL") {
            unsigned nrVertices;

            parseLine(fin, iss);
            iss >> nrVertices;
            
            // read vertices.
            bool colour, extreme;
            std::vector<Vertex> vertices;
            std::vector<Vertex> extremeVertices;
            vertices.reserve(nrVertices);
            LOG4CPLUS_DEBUG(mLogIn, "Start reading " << nrVertices << " vertices with dim=" << dimension);
            
            Vertex v(dimension,false);
            for (unsigned  i = 0; i < nrVertices; i++) {
                parseLine(fin, iss);
                iss >> v >> extreme;
                
                vertices.push_back(v);
                if (extreme){
                    extremeVertices.push_back(v);
                }
            }
            LOG4CPLUS_INFO(mLogIn, "Finished reading vertices");
            
            NeighbourhoodContainer neighbourhoods;
            if (subtype == "Neighborhood") {
                Vertex vertex(dimension, false);
                std::vector<Vertex> neighbours;
                for (unsigned i = 0; i<nrVertices; ++i) {
                    parseLine(fin, iss);
                    iss >> vertex;
                    for (unsigned j=0; j+1<pow(2,dimension); ++j) {
                        parseLine(fin, iss);
                        iss >> v;
                        neighbours.push_back(v);
                    }
                    neighbourhoods.insertVertexAndNeighbours(vertex,neighbours.begin(), neighbours.end());
                    
                }
                LOG4CPLUS_INFO(mLogIn, "Finished reading neighbourhoods");
            }
            //TODO check iss flags.

            //TODO read more info.  

            
            fin.close();

            if (subtype == "Vertex") {
                pol = PolyhedronOrt(vertices,dimension);
                return;
            }
            if (subtype == "Neighborhood") {
                pol = PolyhedronOrt(vertices,dimension, neighbourhoods);
                return;
            }
            if (subtype == "Extreme") {
                pol = PolyhedronOrt(vertices, dimension, extremeVertices);
                return;
            }
            LOG4CPLUS_WARN(mLogIn, "Not a supported subtype");
        }
        fin.close();
        LOG4CPLUS_ERROR(mLogIn, "Not a orthogonal polyhedron");
        
    }
} // end namespace