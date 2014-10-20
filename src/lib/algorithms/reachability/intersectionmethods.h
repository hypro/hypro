/**
* This files contains the implementation of intersection related methods
*/

          /*
          * This method implements testIntersection from algoInv.m
          */
          bool testIntersection(std::vector<double>* d, mapping minus_invariants_in_L, matrix_t<double> set)
          {
               unsigned int lenghtOfSet = set.size();
               
                  // loop over all L
                  for(unsigned int i=0; i<lenghtOfSet; i++)
                  {
                       if( -set( minus_invariants_in_L[i],1 ).toDouble() > d->at(i) )    // intersection condition
                       {
                           return false;
                       }
                  }

               return true;
          }
          
          
          /*
          * Inplace operator to intersect a set with an invariant
          */
          // values(state.invariant_constraints_in_L) = min(values(state.invariant_constraints_in_L),state.d);
          void intersectWithInvariant(matrix_t<double> set, mapping constraints_in_L_A, std::vector<double>* inv_values)
          {
               int length = inv_values->size();
               
               for( int i=0; i<length; i++)
               {
                   set( constraints_in_L_A[i],1 ) = MIN(set( constraints_in_L_A[i],0 ), inv_values->at(i) ); 
               }
          }

