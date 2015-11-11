/**
 *
 */

#include "../config.h"

namespace hypro {

	template<typename Number, typename Representation>
	static double approximateVolume(Representation _in, std::size_t sublevels = 0) {
		double pointCount = 0;
		std::vector<Point<Number>> vertices = _in.vertices();

		//for(Point<Number> vertex: vertices) {
		//	std::cout << "Vertex of new poyltope:\n" << vertex.coordinate(0) << ", " << vertex.coordinate(1) << ", " << vertex.coordinate(2) << std::endl;
		//}

		unsigned dimension = vertices[0].dimension();
		std::vector<std::pair<Number,Number>> bounderies;
		std::vector<bool> count_help;
		std::vector<Number> count_point;
		std::vector<double> resolution;
		bool running=true;
		double volumeUnit=1;

		// TODO, also figure out, if we need Number as a template parameter (I guess not)
		// TODO: where do we set the initial resolution? As a parameter with a default value specified as a constant in config.h maybe.

		// Determine the min max in each dimension std::vector<std::pair<int, int>>  and init
		for(unsigned i = 0; i<dimension; i++){
			bounderies.push_back(std::pair<Number,Number>(0,0));
			count_help.push_back(false);
			count_point.push_back(0);
			resolution.push_back(0);
		}

		// Compute bounderies
		for(Point<Number> vertex: vertices) {
			for(unsigned i = 0; i<dimension; i++){
				if(bounderies[i].first>vertex.coordinate(i)) {
					bounderies[i].first = vertex.coordinate(i);
				} else if(bounderies[i].second<vertex.coordinate(i)) {
					bounderies[i].second = vertex.coordinate(i);
				}
			}
		}

		// Post-init with bounderies-info: compute resolution, volumeUnit and init count_point
		for(unsigned i = 0; i<dimension; i++ ) {
		  //std::cout << "bound." << i << " : " << bounderies[i].first << " till " << bounderies[i].second << std::endl;
			resolution[i]= (bounderies[i].second-bounderies[i].first)/50; // 100 is guessed approximated resolution depending on bounderies TODO in config.h?
			volumeUnit*=resolution[i];
			count_point[i]=bounderies[i].first;
	}

		// Create a grid from bounderies and decide (count) for each point if _in contains it - recursive?
		while(running){
			for(unsigned i=0; i<dimension; i++){
				if(i==0 || count_help[i]){
						count_point[i]+=resolution[i];
						count_help[i]=false;
						if(count_point[i]>bounderies[i].second && i<dimension-1){
							count_point[i]=bounderies[i].first;
							count_help[i+1]=true;
						} else if(count_point[i]>bounderies[i].second && i==dimension-1){
							running=false;
						}
				}
			}
			// Point computed
			//std::cout << "count_point (";
			//for(unsigned i = 0; i<dimension; i++ ) {
			//	std::cout << count_point[i] << " r"<<resolution[i] << " ";
			//}
			//std::cout << ") is ";
			if(_in.contains(count_point)){
				pointCount+=volumeUnit;
				//std::cout << " inside!" << std::endl;
			} else {
				//std::cout << " NOT inside!" << std::endl;
			}
		}

		return pointCount;
	}

}
