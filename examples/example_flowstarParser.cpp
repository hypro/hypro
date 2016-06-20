/**
 *
 */

#include "datastructures/hybridAutomata/HybridAutomaton.h"
#include "algorithms/reachability/Reach.h"
#include "representations/GeometricObject.h"
#include "parser/flowstar/ParserWrapper.h"
#include "util/Plotter.h"
#include <chrono>
#include <string>
//#include <boost/program_options.hpp>


template<typename Number, typename Representation>
static void computeReachableStates(const std::string& filename, const hypro::representation_name& type) {
	using clock = std::chrono::high_resolution_clock;
	using timeunit = std::chrono::microseconds;
	clock::time_point start = clock::now();

	std::cout << "Filename: " << filename << std::endl;
	boost::tuple<hypro::HybridAutomaton<Number>, hypro::ReachabilitySettings<Number>> ha = hypro::parseFlowstarFile<Number>(filename);
	hypro::reachability::Reach<Number,Representation> reacher(boost::get<0>(ha), boost::get<1>(ha));
	std::cout << boost::get<1>(ha) << std::endl;
	std::vector<std::pair<unsigned, hypro::reachability::flowpipe_t<Representation>>> flowpipes = reacher.computeForwardReachability();
	std::cout << "Finished computation of reachable states: " << std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000.0 << " ms" << std::endl;

	clock::time_point startPlotting = clock::now();

	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	std::string extendedFilename = boost::get<0>(ha).reachabilitySettings().fileName;
	switch (type) {
		case hypro::representation_name::support_function:{
			extendedFilename += "_supportFunction";
			break;
		}
		case hypro::representation_name::polytope_h:{
			extendedFilename += "_hpoly";
			break;
		}
		case hypro::representation_name::box:{
			extendedFilename += "_box";
			break;
		}
		default:
			extendedFilename += "_unknownRep";
	}
	std::cout << "filename is " << extendedFilename << std::endl;
	plotter.setFilename(extendedFilename);
	std::vector<unsigned> plottingDimensions = boost::get<0>(ha).reachabilitySettings().plotDimensions;
	plotter.rSettings().dimensions.first = plottingDimensions.front();
	plotter.rSettings().dimensions.second = plottingDimensions.back();
	plotter.rSettings().cummulative = false;

	// bad states plotting
	typename hypro::HybridAutomaton<Number>::locationStateMap badStateMapping = boost::get<0>(ha).localBadStates();
	for(const auto& state : badStateMapping) {
		unsigned bs = plotter.addObject(Representation(boost::get<hypro::cPair<Number>>(state.second.set).first, boost::get<hypro::cPair<Number>>(state.second.set).second).vertices());
		plotter.setObjectColor(bs, hypro::colors[hypro::red]);
	}

	// segments plotting
	for(const auto& flowpipePair : flowpipes){
		for(const auto& segment : flowpipePair.second){
			unsigned tmp = plotter.addObject(segment.vertices());
			plotter.setObjectColor(tmp, hypro::colors[flowpipePair.first % (sizeof(hypro::colors)/sizeof(*hypro::colors))]);
		}
	}

	plotter.plot2d();
	plotter.plotGen();
	plotter.plotTex();

	std::cout << "Finished plotting: " << std::chrono::duration_cast<timeunit>( clock::now() - startPlotting ).count()/1000.0 << " ms" << std::endl;
}

int main(int argc, char** argv) {
	/*
	namespace po = boost::program_options;
	po::options_description desc("Allowed options");
	desc.add_options()
			("help", "produce help message")
			("representation", po::value<int>(), "set representation (1=box, 2=hpoly, 3=supportFunction)")
			("in", po::value<std::string>(), "specify input file path" )
			;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}

	int rep = 0;
	std::string filename;
	if (vm.count("representation")) {
		rep = vm["representation"].as<int>();
	}

	if( vm.count("in")) {
		filename = vm["in"].as<std::string>();
	} else {
		std::cout << "No input file given, exiting. Try --help to obtain full list of options." << std::endl;
		exit(0);
	}
	*/

	int rep = 0;
	std::string filename = argv[1];
	if(argc > 2) {
		char* p;
		rep = strtol(argv[2], &p, 10);
	}

#ifdef USE_CLN_NUMBERS
	using Number = cln::cl_RA;
#else
	using Number = mpq_class;
#endif

	switch(rep){
		case 3: {
			using Representation = hypro::SupportFunction<Number>;
			std::cout << "Using a support function representation." << std::endl;
			computeReachableStates<Number, Representation>(filename, hypro::representation_name::support_function);
			break;
		}
		case 2: {
			using Representation = hypro::HPolytope <Number>;
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
