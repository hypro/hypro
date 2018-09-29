#pragma once
#include <ppl.hh>

namespace benchmark {

struct Double_Interval_Policy
{
    const_bool_nodef(store_special, true);
    const_bool_nodef(store_open, true);
    const_bool_nodef(cache_empty, false);
    const_bool_nodef(cache_singleton, false);
    const_int_nodef(next_bit, 0);
    const_bool_nodef(may_be_empty, true);
    const_bool_nodef(may_contain_infinity, true);
    const_bool_nodef(check_empty_result, true);
    const_bool_nodef(check_inexact, true);
};

} // namespace
