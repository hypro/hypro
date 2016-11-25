/**
 *
 */

#include "representations/GeometricObject.h"
#include "datastructures/hybridAutomata/HybridAutomaton.h"
#include "datastructures/hybridAutomata/LocationManager.h"
#include "algorithms/reachability/Reach.h"
#include "parser/flowstar/ParserWrapper.h"
//#include <boost/program_options.hpp>
#include <sys/wait.h>
#include <signal.h>
#define PLOT_FLOWPIPE

template<typename Number, typename Representation>
static void computeReachableStates(const std::string& filename, const hypro::representation_name& type) {
	using clock = std::chrono::high_resolution_clock;
	using timeunit = std::chrono::duration<long long unsigned, std::micro>;
	//std::cout << "Filename: " << filename << std::endl;
	std::size_t numberRuns = 1;
	std::vector<std::chrono::duration<double, std::milli>> runtimes(numberRuns);
	std::chrono::duration<double, std::milli> summedTime(0.0);
	clock::time_point startParsing = clock::now();
	boost::tuple<hypro::HybridAutomaton<Number>, hypro::ReachabilitySettings<Number>> ha = hypro::parseFlowstarFile<Number>(filename);
	std::chrono::duration<double, std::milli> parseTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(clock::now() - startParsing);
	std::vector<std::pair<unsigned, hypro::reachability::flowpipe_t<Representation>>> flowpipes;
	//std::cout << "Parse time is " << parseTime.count() << std::endl;

	for(std::size_t run = 0; run < numberRuns; ++run) {
		clock::time_point start = clock::now();
		hypro::reachability::Reach<Number,Representation> reacher(boost::get<0>(ha), boost::get<1>(ha));
		flowpipes = reacher.computeForwardReachability();
		runtimes.push_back(std::chrono::duration_cast<timeunit>( clock::now() - start ));
		summedTime += std::chrono::duration_cast<std::chrono::duration<double, std::milli>>( clock::now() - start )/(numberRuns);
		//std::cout << "Summed time: " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>( summedTime ).count() << std::endl;
		std::cout << "Run finished in " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>( clock::now() - start ).count() << " ms." << std::endl;
		//std::cout << "Run finished in " << std::chrono::duration_cast<std::chrono::duration<double, std::ratio<60>>>( clock::now() - start ).count() << " minutes." << std::endl;
		PRINT_STATS()
		RESET_STATS()
	}
	std::cout << boost::get<1>(ha) << std::endl;
	std::cout << "Finished computation of reachable states: " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(summedTime).count()+std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(parseTime).count() << " ms" << std::endl;

#ifdef PLOT_FLOWPIPE
	clock::time_point startPlotting = clock::now();

	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	std::string extendedFilename = boost::get<0>(ha).reachabilitySettings().fileName;
	switch (Representation::type()) {
		case hypro::representation_name::zonotope:{
			extendedFilename += "_zonotope";
			break;
		}
		case hypro::representation_name::support_function:{
			extendedFilename += "_supportFunction";
			break;
		}
		case hypro::representation_name::polytope_v:{
			extendedFilename += "_vpoly";
			break;
		}
		case hypro::representation_name::polytope_h:{
			extendedFilename += "_hpoly";
			break;
		}
		#ifdef USE_PPL
		case hypro::representation_name::ppl_polytope:{
			extendedFilename += "_PPLpoly";
			break;
		}
		#endif
		case hypro::representation_name::box:{
			extendedFilename += "_box";
			break;
		}
		default:
			extendedFilename += "_unknownRep";
	}
	//std::cout << "filename is " << extendedFilename << std::endl;
	plotter.setFilename(extendedFilename);
	std::vector<unsigned> plottingDimensions = boost::get<0>(ha).reachabilitySettings().plotDimensions;
	plotter.rSettings().dimensions.first = plottingDimensions.front();
	plotter.rSettings().dimensions.second = plottingDimensions.back();
	plotter.rSettings().cummulative = false;


	// bad states plotting
	typename hypro::HybridAutomaton<Number>::locationStateMap badStateMapping = boost::get<0>(ha).localBadStates();
	for(const auto& state : badStateMapping) {
		unsigned bs = plotter.addObject(Representation(state.second.set.first, state.second.set.second).vertices());
		plotter.setObjectColor(bs, hypro::colors[hypro::red]);
	}

	// segments plotting
	for(const auto& flowpipePair : flowpipes){
		//std::cout << "Plot flowpipe " << flowpipePair.first << std::endl;
		unsigned cnt = 0;
		for(const auto& segment : flowpipePair.second){
			//std::cout << "Plot segment " << cnt << "/" << flowpipePair.second.size() << std::endl;
			switch (type) {
				case hypro::representation_name::support_function:{
					//unsigned tmp = plotter.addObject(segment.project(plottingDimensions).vertices(hypro::LocationManager<Number>::getInstance().location(flowpipePair.first)));
					unsigned tmp = plotter.addObject(segment.project(plottingDimensions).vertices());
					plotter.setObjectColor(tmp, hypro::colors[flowpipePair.first % (sizeof(hypro::colors)/sizeof(*hypro::colors))]);
					break;
				}
				case hypro::representation_name::zonotope:{
					unsigned tmp = plotter.addObject(segment.project(plottingDimensions).vertices());
					plotter.setObjectColor(tmp, hypro::colors[flowpipePair.first % (sizeof(hypro::colors)/sizeof(*hypro::colors))]);
					break;
				}
				case hypro::representation_name::box:{
					unsigned tmp = plotter.addObject(segment.project(plottingDimensions).vertices());
					plotter.setObjectColor(tmp, hypro::colors[flowpipePair.first % (sizeof(hypro::colors)/sizeof(*hypro::colors))]);
					break;
				}
				#ifdef USE_PPL
				case hypro::representation_name::ppl_polytope:{
					unsigned tmp = plotter.addObject(segment.project(plottingDimensions).vertices());
					plotter.setObjectColor(tmp, hypro::colors[flowpipePair.first % (sizeof(hypro::colors)/sizeof(*hypro::colors))]);
					break;
				}
				#endif
				default:
					//unsigned tmp = plotter.addObject(segment.project(plottingDimensions).vertices());
					unsigned tmp = plotter.addObject(segment.vertices());
					plotter.setObjectColor(tmp, hypro::colors[flowpipePair.first % (sizeof(hypro::colors)/sizeof(*hypro::colors))]);
			}
			++cnt;
		}
	}
	//std::cout << "Write to file." << std::endl;
	//std::cout << "Use dimensions: " << plotter.settings().dimensions.first << ", " << plotter.settings().dimensions.second << std::endl;
	plotter.plot2d();
	plotter.plotGen();
	//plotter.plotTex();

	std::cout << "Finished plotting: " << std::chrono::duration_cast<timeunit>( clock::now() - startPlotting ).count()/1000.0 << " ms" << std::endl;

#endif
}

int main(int argc, char** argv) {

	int rep = 0;
	std::string filename = argv[1];
	if(argc > 2) {
		char* p;
		rep = strtol(argv[2], &p, 10);
	}

	using Number = mpq_class;

	switch(rep){
		#ifdef USE_PPL
		case 6: {
			using Representation = hypro::Polytope<Number>;
			std::cout << "Using a PPL-Polytope representation." << std::endl;
			computeReachableStates<Number, Representation>(filename, hypro::representation_name::ppl_polytope);
			break;
		}
		#endif
		case 5: {
			using Representation = hypro::Zonotope<Number>;
			std::cout << "Using a zonotope representation." << std::endl;
			computeReachableStates<Number, Representation>(filename, hypro::representation_name::zonotope);
			break;
		}
		case 4: {
			using Representation = hypro::SupportFunction<Number>;
			std::cout << "Using a support function representation." << std::endl;
			computeReachableStates<Number, Representation>(filename, hypro::representation_name::support_function);
			break;
		}
		case 3: {
			using Representation = hypro::VPolytope<Number>;
			std::cout << "Using a v-polytope representation." << std::endl;
			computeReachableStates<Number, Representation>(filename, hypro::representation_name::polytope_v);
			break;
		}
        case 2: {
			using Representation = hypro::HPolytope<Number>;
			std::cout << "Using a h-polytope representation." << std::endl;
			computeReachableStates<Number, Representation>(filename, hypro::representation_name::polytope_h);
			break;
		}
		case 1: {
			using Representation = hypro::Box<Number>;
			std::cout << "Using a box representation." << std::endl;
			computeReachableStates<Number, Representation>(filename, hypro::representation_name::box);
			break;
		}
		default:{
			using Representation = hypro::Box<Number>;
			std::cout << "Using a box representation." << std::endl;
			computeReachableStates<Number, Representation>(filename, hypro::representation_name::box);
		}
	}
	exit(0);
}
