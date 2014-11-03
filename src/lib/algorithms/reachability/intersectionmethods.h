/**
* This files contains the implementation of intersection related methods
*/

#define INTERSECTION_VERBOSE

          /*
          * This method implements testIntersection from algoInv.m (ignores the two last entries)
          */
          bool testIntersection(std::vector<double>* d, mapping minus_invariants_in_L, matrix_t<double> set)
          {
               #ifdef INTERSECTION_VERBOSE
                   std::cout << "testIntersection(...): " << "d:" << *d << BL;
                   print(*d);
                   std::cout << BL;
                   std::cout << "mapping minus_invariants_in_L: d->size() = " << d->size() << BL;
                   printArray<unsigned int>(minus_invariants_in_L, d->size());
                   std::cout << BL << "set: " << BL << set << BL;
               #endif
                              
                  // loop over all L
                  for(unsigned int i=0; i<d->size(); i++)   // -2 because the 2 last directions are artificial
                  {
                       if( -set( minus_invariants_in_L[i],0 ).toDouble() > d->at(i) )    // intersection condition
                       {
                           #ifdef INTERSECTION_VERBOSE
                                  std::cout << "testIntersection(...): " << "returns false" << BL;
                           #endif
                           return false;
                       }
                  }

               #ifdef INTERSECTION_VERBOSE
                   std::cout << "testIntersection(...): " << "returns true" << BL;
               #endif
               return true;
          }
          
          
          /*
          * operator to intersect a set with an invariant
          */
          // values(state.invariant_constraints_in_L) = min(values(state.invariant_constraints_in_L),state.d);
          matrix_t<double> intersectWithInvariant(matrix_t<double> set, mapping constraints_in_L_A, std::vector<double>* inv_values)
          {
               int length = inv_values->size();
               matrix_t<double>result = set;
               
               for( int i=0; i<length; i++)
               {
                   result( constraints_in_L_A[i],0 ) = MIN(result( constraints_in_L_A[i],0 ).toDouble(), inv_values->at(i) ); 
               }
               
               return result;
          }
          
          /*
          * Computes the intersection of two convex sets
          */
          matrix_t<double> intersect(matrix_t<double> set1, matrix_t<double> set2)
          {
              matrix_t<double> result(set1.size(),1);
              for(int i=0; i<set1.size(); i++)
              {
                  result(i,0) = MIN(set1(i,0), set2(i,0));
              }
              return result;
          }
