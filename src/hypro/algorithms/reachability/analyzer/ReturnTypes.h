#pragma once
#include <types.h>
#include <variant>
#include <datastructures/reachability/ReachTreev2.h>

namespace hypro {

template <class Success, class Failure>
struct AnalysisResult {
	std::variant<Success, Failure> variant;

	REACHABILITY_RESULT result() {
		return std::holds_alternative<Success>( variant ) ? REACHABILITY_RESULT::SAFE : REACHABILITY_RESULT::UNKNOWN;
	}

	bool isSuccess() { return std::holds_alternative<Success>( variant ); }
	bool isFailure() { return !success(); }

	Success& success() { return std::get<Success>( variant ); }
	Failure& failure() { return std::get<Failure>( variant ); }

	operator std::variant<Success, Failure> &() {
		return variant;
	}
};

/**
 * @brief Contains the results of a failed analysis
 * @tparam Representation The representation type that the analysis used
 */
template <class Representation>
struct Failure {
	ReachTreeNode<Representation>* conflictNode{};	///< The node where a conflict occured, i.e. a bad state was intersected.
};

template<class Representation>
Failure(ReachTreeNode<Representation>*) -> Failure<Representation>;

}  // namespace hypro