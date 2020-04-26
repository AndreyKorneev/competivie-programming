#ifndef COMMON_H_
#define COMMON_H_

//~ BEGIN ALWAYS_INCLUDE
#include <bits/stdc++.h>
using namespace std;
//~ END ALWAYS_INCLUDE

//~ BEGIN `all`
#define all(x) (x).begin(), (x).end()
//~ END `all`

//~ BEGIN `lli`
using lli = long long int;
//~ END `lli`

//~ BEGIN `pii`
using pii = pair<int, int>;
//~ END `pii`

//~ BEGIN `vi`
using vi = vector<int>;
//~ END `vi`

//~ BEGIN `vpii`
// required: pii
using vpii = vector<pii>;
//~ END `vpii`

//~ BEGIN `GCC_COMPILER`
#if defined(__GNUC__) && !defined(__clang__)
#define GCC_COMPILER
#endif
//~ END `GCC_COMPILER`

//~ BEGIN `llf`
// required: GCC_COMPILER
#ifdef GCC_COMPILER
using llf = __float128;
#else
using llf = long double;
#endif
//~ END `llf`

#endif
