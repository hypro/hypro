/*
 *  This file contains the definition of the flowpipe structure
 *  Author: Norman Hansen
 */

#include "hyreach_utils.h"

namespace hypro {
/*
 *    This class represents a flowpipe consisting of multiple support function evaluations
 */
class Flowpipe {
  private:
	Location* location;				  // the location which "generated" this flowpipe
	unsigned int starttime, endtime;  // absolute time reference
	vector<double>* evaluations[];	// array of lists to store the evaluation values

  public:
	/*
	 *   add a list of values
	 */
	void addEvaluations( unsigned int position, vector<double>* values ) { evaluations[position] = values; }

	Flowpipe( unsigned int numberOfDirections ) {
		// create array
		vector<double>* temp[numberOfDirections];
		evaluations = temp;
	}
}
}
