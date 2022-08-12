#pragma once
#include <iosfwd>

namespace hypro {

struct TreeStatistic {
	double avgBranching = 0.0;
	double avgLevel = 0.0;
	std::size_t nodeCnt = 0;
	std::size_t depth = 0;
	std::vector<std::size_t> levelCnt;
};

}  // namespace hypro

namespace std {

inline std::ostream& operator<<( std::ostream& out, const hypro::TreeStatistic& in ) {
	out << "Average branching: \t\t" << in.avgBranching << std::endl;
	out << "Average refinement level: \t" << in.avgLevel << std::endl;
	out << "Maximal refinement level: \t" << in.levelCnt.size() - 1 << std::endl;
	out << "Number nodes: \t\t\t" << in.nodeCnt << std::endl;
	out << "Depth: \t\t\t\t" << in.depth << std::endl;
	std::size_t i = 0;
	while ( i < in.levelCnt.size() ) {
		out << "Nodes at level " << i << ": " << in.levelCnt[i] << std::endl;
		++i;
	}
	return out;
}

}  // namespace std
