/**
 * This file shows how to use the plotter.
 * @file example_plot.cpp
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since	2015-03-01
 * @version	2015-03-01
 */

#include "../src/lib/util/plot.h"
#include "../src/lib/representations/Box/Box.h"

using namespace hypro;

int main(int argc, char** argv) {
	
	Box<double> exampleBox1;
	carl::Interval<double> x(-1,3);
	carl::Interval<double> y(-1,3);
	exampleBox1.insert(0,x);
	exampleBox1.insert(1,y);
	
	std::set<Point<double>> corners = exampleBox1.corners();
	std::vector<Point<double>> tmp;
	for(auto& point : corners) {
		tmp.push_back(point);
	}
	
	plot(tmp);
	
	return 0;
}
