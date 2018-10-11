#pragma once
#include "../datastructures/HybridAutomaton/State.h"
#include "../representations/types.h"

namespace hypro {

template<typename Number>
struct PlotData {
	std::vector<typename State_t<Number>::rep_variant> segments;
	std::size_t threadId;
	std::size_t refinementLevel;

	PlotData(const typename State_t<Number>::rep_variant& s, std::size_t l) :
		threadId(),
		refinementLevel(l)
	{
		segments.push_back(s);
	}

	PlotData(const std::vector<typename State_t<Number>::rep_variant>& s, std::size_t l) :
		segments(s),
		threadId(),
		refinementLevel(l)
	{}
};

} // hypro
