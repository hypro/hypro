#pragma once

#ifdef HYPRO_USE_PPL
#include <ppl.hh>

namespace benchmark {
namespace box {

struct Double_Interval_Policy {
	const_bool_nodef( store_special, true );
	const_bool_nodef( store_open, true );
	const_bool_nodef( cache_empty, true );
	const_bool_nodef( cache_singleton, true );
	const_int_nodef( next_bit, 0 );
	const_bool_nodef( may_be_empty, true );
	const_bool_nodef( may_contain_infinity, false );
	const_bool_nodef( check_empty_result, true );
	const_bool_nodef( check_inexact, true );
};
}  // namespace box
}  // namespace benchmark

#endif