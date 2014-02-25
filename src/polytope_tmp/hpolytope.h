/** 
 * @file   hpolytope.h
 * Created on June 29, 2011
 * Last modified July 5, 2011
 * 
 * @author Sebastian Junges
 * 
 */

#ifndef HPOLYTOPE_H
#define	HPOLYTOPE_H

#include <gmpxx.h>
#include "gmpqsupport.h"
#include "linearConstraint.h"
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include "polyhedron.h"
using namespace Eigen;

namespace reachLin {

/**
 * @class HPolytope
 * A class for convex polytopes in their H-representation.
 * 
 */
class HPolytope : public Polyhedron {
public:
    HPolytope(unsigned dim);
    virtual ~HPolytope();
    
    /**
     * Get the actual number of constraints.
     * @return 
     */
    inline unsigned getNrConstraints() { return nrConstraints; }
    
    /**
     * 
     * @param a The new row in A.
     * @param b The value in b.
     * @return 
     * TODO implement returnvalue
     */
    bool addConstraint(Eigen::VectorXr a, rational b) {
        assert(a.cols() == mDimension-1);
        mb(nrConstraints) = b;
        mA.row(nrConstraints) = a;
        nrConstraints++;
        return true;
    }
    
    /**
     * 
     * @param con
     * @return
     * Might be slow!
     * TODO implement returnvalue 
     */
    bool addConstraint(LinearConstraint& con) {
        assert(con.getDimension() == mDimension);
        mb(nrConstraints) = con(mDimension);
        for(unsigned i=0; i<mDimension; i++) {
            mA(nrConstraints,i) = con(i);
        }
        nrConstraints++;
        return true;
    }
    
    /**
     * Swap the row with the row to be deleted, zero the row and decrease the number of constraints.
     * @param index The indexnr of the constraint we want to remove.
     */
    void removeConstraint(unsigned index) {
        assert(index <= nrConstraints);
        Transpositions<2> tr;
        tr(index) = nrConstraints;
        mA = tr * mA;
        mb = tr * mb;
        mb(nrConstraints) = 0;
        for(unsigned i = 0; i<mDimension; i++) {
            mA(nrConstraints,i) = 0;
        }
        nrConstraints--;
    }
    
    /**
     * Find a given constraint.
     * @param a The row to be found
     * @param b with the value to be found
     * @return The index where it was found.
     */
    int findConstraint(Eigen::VectorXr a, rational b);
    bool clean();
    
    HPolytope calculateIntersection(); 
protected:
    
    unsigned nrConstraints;
    Eigen::MatrixXr mA;
    Eigen::VectorXr mb;
};

}

#endif	/* HPOLYTOPE_H */

