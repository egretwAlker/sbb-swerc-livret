#include <bits/stdc++.h> 

struct pairhash {
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &p) const {
    // return std::hash<T>()(x.first) ^ std::hash<U>()(x.second); // simpler alternative
    const auto h1 = hash<T>{}(p.first);
    const auto h2 = hash<U>{}(p.second);
    if (h1 == h2) return h1;
    return h1 ^ h2;
  }
};

// sanic fast
#pragma GCC optimize(" unroll-loops")
#pragma gcc optimize("Ofast")
#pragma GCC optimization("Ofast")
#pragma optimize(Ofast)

// max/min of any type
std::numeric_limits<TYPE>::max();