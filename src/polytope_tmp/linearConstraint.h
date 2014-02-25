/** 
 * @file   linearConstraint.h
 * Created on July 5, 2011
 * Last modified July 5, 2011
 * 
 * @author Sebastian Junges
 *
 * 
 */

#ifndef LINEARCONSTRAINT_H
#define	LINEARCONSTRAINT_H

#include "settings.h"
#include <iostream>

namespace reachLin {
    
    class LinearConstraint {
    public:
        LinearConstraint(Eigen::VectorXr a, rational b);
     
        LinearConstraint(unsigned dim);
        
        unsigned getDimension() {
            return dimension;
        }
        
        
        rational& operator()(unsigned index) {
            assert(index < dimension+1);
            return a(index);
        }

        friend std::ostream& operator<<(std::ostream& ostr, const LinearConstraint& lincon) {
            for(unsigned i=0; i<lincon.dimension; i++) {
                ostr << lincon.a(i) << " ";
            }
            ostr << "| " << lincon.a(lincon.dimension) << std::endl;
        }
        
        friend std::istream& operator>>(std::istream& istr, LinearConstraint& lincon) {
            Eigen::VectorXr a;
            unsigned i = 0;
            while(istr.good()) {
                istr >> a(i++);
                istr.ignore(10, '|');
                if (istr.peek() == '|') {
                    istr.ignore(2);
                    break;
                }
            }
            unsigned dimension = i+1;
            istr >> a(dimension);
            
        }
        
    protected:
        Eigen::VectorXr a;
        
        unsigned dimension;
    };
    

}

#endif	/* LINEARCONSTRAINT_H */

