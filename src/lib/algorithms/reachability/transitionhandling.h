/*
* This file is included by HyReach.h and contains the implementation of functionality and data related to the determination process of the transitions possible to take
* Author: Norman Hansen
*/

#define TRANSITIONHANDLING_VERBOSE
         
         unsigned int* full =0;
         
         /*
         * Computes a list of all transitions which could be taken considering the specified flowpipe
         */
         std::vector<possibleTransition>* getPossibleTransitions(location* loc, FlowpipeSegment* flowpipe)
         {
             #ifdef TRANSITIONHANDLING_VERBOSE
                 std::string method = "getPossibleTransitions(...): ";
                 std::cout << method << "start" << BL;
             #endif
             
             std::vector<possibleTransition>* result = new std::vector<possibleTransition>(0);
             
                  if( full == 0)              // full is an array defining an identity mapping
                  {
                      full = new unsigned int[L.size()];
                      for(unsigned int i=0; i<L.size(); i++)
                      {
                            full[i] = i;
                      }
                  }
                      
                 bool transitionadded = false;       // stores wether the actually considered transition has already a detected intersection with the flowpipe   
                 convexSetOfFlowpipeSetIndexis* indices = 0;
                 
             #ifdef TRANSITIONHANDLING_VERBOSE
                 std::cout << method << "begin loop iterations" << BL;
                 unsigned int count =0;
                 std::cout << method << "number of transitions: " << loc->transitions().size()<< BL;
             #endif
             
                 for(auto iterator = loc->transitions().begin(); iterator != loc->transitions().end(); ++iterator) // iterate over outgoing transitions
                 {
                       #ifdef TRANSITIONHANDLING_VERBOSE
                           std::cout << method << "transition: " << count << BL;
                           count++;
                       #endif   
                       
                       #ifdef TRANSITIONHANDLING_VERBOSE
                              std::cout << method << "ITERATOR: " << *iterator << BL;
                       #endif 
                       
                       for(unsigned int i=0; i<flowpipe->size();i++) // iterate over sets in flowpipe
                       {
                                    #ifdef TRANSITIONHANDLING_VERBOSE
                              std::cout << method << "ITERATOR: " << *iterator << BL;
                       #endif 
                             TransitionInfo* t = transitionMap.find(*iterator)->second;
                             if(testIntersection( t->g_star_values , full , flowpipe->getSet(i), L.size()-2)) // test for intersection
                             {
                                 // set intersects a guard
                                 #ifdef TRANSITIONHANDLING_VERBOSE
                                     std::cout << method << i << " intersects the guard" << BL;
                                 #endif
                                 if(transitionadded)
                                 {
                                     #ifdef TRANSITIONHANDLING_VERBOSE
                                         std::cout << method << "transition already known" << BL;
                                     #endif
                                     // this transition has already an intersection
                                     if(indices->end+1 == i)
                                     {
                                          // consecutive sets intersect the guard
                                          indices->end = i;
                                     }
                                     else
                                     {
                                         // use new convexSetOfFlowpipeSetIndexis struct
                                         result->at(result->size()-1).sets.push_back(*indices);      // list copies values when adding the struct
                                         
                                         indices->start = i;
                                         indices->end = i;
                                     }
                                 }
                                 else
                                 {
                                     #ifdef TRANSITIONHANDLING_VERBOSE
                                         std::cout << method << "new transition" << BL;
                                     #endif
                                     // the considered set is the first intersection for this transition
                                     possibleTransition t;
                                     t.flowpipeSegment = flowpipe;
                                     t.transition_pt = (*iterator);
                                     
                                     if(indices != 0)
                                     {
                                         delete indices;
                                     }
                                     indices = new convexSetOfFlowpipeSetIndexis();
                                     indices->start = i;
                                     indices->end = i;
                                     
                                     result->push_back(t);                         // list copies values when adding the struct
                                     transitionadded = true;
                                 }
                             }
                       }
                       
                       #ifdef TRANSITIONHANDLING_VERBOSE
                              std::cout << method << "ITERATOR: " << *iterator << BL;
                       #endif        
                       
                       
                       if(transitionadded)           // there is a set of the flowpipe which intersects the considered transition and has not yet been added
                       {
                           result->at(result->size()-1).sets.push_back(*indices);             
                           transitionadded = false;   
                       } 
                 }    
                 
                 delete indices;
             
             
             #ifdef TRANSITIONHANDLING_VERBOSE
                 std::cout << method << "result: ";
                 printPossibleTransitions(result);
                 std::cout << BL;
             #endif        
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
             #ifdef TRANSITIONHANDLING_VERBOSE
                 std::string method = "clustering(...): ";
                 std::cout << method << "start" << BL;
             #endif  
             
             matrix_t<double> result(posTrans->flowpipeSegment->sets.rows(),1);
             // initialize result wit -inf (everything should initially be bigger)
             for(int i=0; i<result.size(); i++)
             {
                  result(i,0) = -INFINITY;      
             }
             
             #ifdef TRANSITIONHANDLING_VERBOSE
                 std::cout << method << "initialized result: " << result.transpose() << BL;
                 std::cout << "posTrans->sets.size(): " << posTrans->sets.size() << BL;
             #endif 
                 
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
                         #ifdef TRANSITIONHANDLING_VERBOSE
                             std::cout << method << "sets: " << posTrans->flowpipeSegment->sets << BL;
                             std::cout << method << "set index: " << posTrans->sets.at(i).start << BL;
                         #endif 
             
                         // there is only a single set
                         result = elementWiseMax(result, posTrans->flowpipeSegment->sets.col( posTrans->sets.at(i).start ) );
                     }
                 }
             
             #ifdef TRANSITIONHANDLING_VERBOSE
                 std::cout << method << "result: " << result.transpose() << BL;
             #endif     
             return result;
         }

         matrix_t<double> clustering(possibleTransition posTrans)
         {
             return clustering(&posTrans);
         }
