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

// fast CIN
ios_base::sync_with_stdio(false);
cin.tie(NULL);

// sanic fast
#pragma GCC optimize(" unroll-loops")
#pragma gcc optimize("Ofast")
#pragma GCC optimization("Ofast")
#pragma optimize(Ofast)
#pragma GCC optimize ("Ofast") // will make GCC auto-vectorize loops and optimizes floating points better.
#pragma GCC target ("avx2") // can double performance of vectorized code, but causes crashes on old machines.
#pragma GCC optimize ("trapv") // kills the program on integer overflows (but is really slow).

x&(-x) // the least bit in x
for(int x=m; x; ) { --x &= m;...} // loops over all subset masks of m (except m itself)
c = x&(-x), r=x+c; (((r^x)>>2)/c) | r // next number after x with the same number of bits set
rep(b,0,K) rep(i,0,(1<<K)) if(i&1<<b) D[i]+=D[i^(1<<b)]; // computes all sums of subsets

/**
 * Description:
 * Find the smallest i in $[a,b]$ that maximizes $f(i)$, assuming that $f(a) < \dots < f(i) \ge \dots \ge f(b)$.
 * To reverse which of the sides allows non-strict inequalities, change the < marked with (A) to <=, and reverse the loop at (B).
 * To minimize $f$, change it to >, also at (B).
 * Usage:
	int ind = ternSearch(0,n-1,[\&](int i){return a[i];});
 * Time: O(\log(b-a))
 */
#pragma once

template<class F>
int ternSearch(int a, int b, F f) {
	assert(a <= b);
	while (b - a >= 5) {
		int mid = (a + b) / 2;
		if (f(mid) < f(mid+1)) a = mid; // (A)
		else b = mid+1;
	}
	rep(i,a+1,b+1) if (f(a) < f(i)) a = i; // (B)
	return a;
}



/**
 * Description: Compute indices for the longest increasing subsequence.
 * Time: $O(N \log N)$
 */
#pragma once

template<class I> vi lis(const vector<I>& S) {
	if (S.empty()) return {};
	vi prev(sz(S));
	typedef pair<I, int> p;
	vector<p> res;
	rep(i,0,sz(S)) {
		// change 0 -> i for longest non-decreasing subsequence
		auto it = lower_bound(all(res), p{S[i], 0});
		if (it == res.end()) res.emplace_back(), it = res.end()-1;
		*it = {S[i], i};
		prev[i] = it == res.begin() ? 0 : (it-1)->second;
	}
	int L = sz(res), cur = res.back().second;
	vi ans(L);
	while (L--) ans[L] = cur, cur = prev[cur];
	return ans;
}
// ConstantIntervals.h
/** * Description: Split a monotone function on [from, to) into a minimal set of half-open intervals on which it has the same value.
 *  Runs a callback g for each such interval.
 * Usage: constantIntervals(0, sz(v), [\&](int x){return v[x];}, [\&](int lo, int hi, T val){...});
 * Time: O(k\log\frac{n}{k}) */
#pragma once

template<class F, class G, class T>
void rec(int from, int to, F& f, G& g, int& i, T& p, T q) {
	if (p == q) return;
	if (from == to) {
		g(i, to, p);
		i = to; p = q;
	} else {
		int mid = (from + to) >> 1;
		rec(from, mid, f, g, i, p, f(mid));
		rec(mid+1, to, f, g, i, p, q);
	}
}
template<class F, class G>
void constantIntervals(int from, int to, F f, G g) {
	if (to <= from) return;
	int i = from; auto p = f(i), q = f(to-1);
	rec(from, to-1, f, g, i, p, q);
	g(i, to, q);
}

// max/min of any type
std::numeric_limits<TYPE>::max();