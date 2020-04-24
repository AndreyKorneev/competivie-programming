#ifndef DATA_STRUCTURES_ORDERED_SET_H_
#define DATA_STRUCTURES_ORDERED_SET_H_

#include "algs/common.h"
//~ BEGIN ordered_set
// required: GCC_COMPILER
#ifdef GCC_COMPILER
using namespace __gnu_pbds;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#endif
//~ END ordered_set

#endif
