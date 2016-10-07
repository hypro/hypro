/*
 *  Author: Norman Hansen
 */

/*
* This class will free some globally used ressources when the Hyreach class is deleted
*/
class CleanupOnExit {
  public:
	~CleanupOnExit() {
		glp_free_env();  // tear down glpk environment
	}

	/**
	* Removes all FlowpipeSegements in the list specified using a parameter explicitely
	*/
	static void removeFlowpipeSegments( std::list<FlowpipeSegment*>* flowpipeSegmentList ) {
		for ( auto iterator = flowpipeSegmentList->begin(); iterator != flowpipeSegmentList->end(); ++iterator ) {
			FlowpipeSegment* fs = *iterator;
			delete fs;
		}
	}
};
