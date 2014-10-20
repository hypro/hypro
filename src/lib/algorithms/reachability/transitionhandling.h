/*
* This file is included by HyReach.h and contains the implementation of functionality and data related to the determination process of the transitions possible to take
*/

         /*
         * This structure describes a set of consecutive sets in the flowpipe by the start and end indexis relatively to a specific flowpipeSegment
         * The main purpose of this structure is to be used as elements of a list inside the possibleTransition structure
         */
         struct convexSetOfFlowpipeSetIndexis
         {
                unsigned int start;
                unsigned int end;
         };
          
         /*
         * Structure describing a possible transition and a list of all associated sets of the currently considered flowpipe
         */
         struct possibleTransition
         {
                transition* transition_pt;      // transition
                FlowpipeSegment* flowpipeSegment;  // flowpipe the set indexis relate to
                std::vector<convexSetOfFlowpipeSetIndexis> sets; // list of successive sets having an intersection with the guard (and I* etc.) of the transition 
         };
         
         /*
         * Computes a list of all transitions which could be taken considering the specified flowpipe
         */
         std::vector<possibleTransition>* getPossibleTransitions(location* loc, FlowpipeSegment* flowpipe)
         {
             std::vector<possibleTransition>* result = new std::vector<possibleTransition>(0);
             // TODO:
                     
                     
                     
             return result;        
         }

         /*
         * Applies element-wise on two nx1 matrices the maximum operator
         */
         matrix_t<double> elementWiseMax(matrix_t<double> a, matrix_t<double> b)
         {
             matrix_t<double> result(a.rows(), a.cols());
             for(int i=0; i<a.rows(); i++)
             {
                 result(i,0) = MAX(a(i,0),b(i,0));
             }
             return result;
         }

         /*
         * Clusters all sets which have an intersection with the given guard (and precomputed invariant values)
         */
         matrix_t<double> clustering(possibleTransition* posTrans)
         {
             matrix_t<double> result(posTrans->flowpipeSegment->sets.rows(),1);
             // initialize result wit -inf (everything should initially be bigger)
             for(int i=0; i<result.size(); i++)
             {
                  result(i,0) = -INFINITY;      
             }
                 
                 // start computing the maximum values         
                 for(unsigned int i=0; i< posTrans->sets.size(); i++)
                 {
                     if(posTrans->sets.at(i).end > posTrans->sets.at(i).start)
                     {
                        // there are multiple successive sets -> compute maximum over them
                        for(unsigned int j=posTrans->sets.at(i).start; j <= posTrans->sets.at(i).end; j++)
                        {
                            result = elementWiseMax(result, posTrans->flowpipeSegment->sets.col( j ) );
                        }
                     }
                     else
                     {
                         // there is only a single set
                         result = elementWiseMax(result, posTrans->flowpipeSegment->sets.col( posTrans->sets.at(i).start ) );
                     }
                 }
                 
             return result;
         }

         matrix_t<double> clustering(possibleTransition posTrans)
         {
             return clustering(&posTrans);
         }
