#include <bits/stdc++.h> 

struct pairhash {
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const {
    // return std::hash<T>()(x.first) ^ std::hash<U>()(x.second); // simpler alternative
    const auto h1 = hash<T1>{}(p.first);
    const auto h2 = hash<T2>{}(p.second);
    if (h1 == h2) return h1;
    return h1 ^ h2;
  }
};