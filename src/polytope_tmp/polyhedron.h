/** 
 * @file   polyhedron.h
 * Created on May 12, 2011
 * Last modified May 12, 2011
 * 
 * @author Sebastian Junges
 * 
 */

#ifndef POLYHEDRON_H
#define	POLYHEDRON_H

namespace reachLin {
    
    class Polyhedron {
    public:
        Polyhedron(unsigned dim);
        virtual ~Polyhedron();
        unsigned getDimension() const {return mDimension;}
        
    protected:
        unsigned mDimension;
    private:

    };


}
#endif	/* POLYHEDRON_H */

