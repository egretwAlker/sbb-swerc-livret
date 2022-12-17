#include<bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i=a;i<(b);++i)
#define all(x) begin(x), end(x)
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) { // a[pos] += dif
    for(;pos<sz(s);pos |= pos+1) s[pos] += dif;
  }
  ll query(int pos) { // sum of values in [0, pos[
    ll res = 0;
    for(;pos>0;pos &= pos-1) res += s[pos-1];
    return res;
  }
  int lower_bound(ll sum) { // min pos s.t. sum of [0, pos] >= sum
    // returns n if no sum is >= sum, or -1 if empty sum is
    if(sum <= 0) return -1;
    int pos = 0;
    for(int pw = 1<<25;pw;pw>>=1) {
      if(pos + pw <= sz(s) && s[pos+pw-1] < sum) {
        pos += pw;
        sum -= s[pos-1];
      }
    }
    return pos;
  }
};

// computes sum a[i, j] for all i<I, j<J
struct FT2 {
  vector<vi> ys; vector<FT> ft;
  FT2(int limx) : ys(limx) {}
  void fakeUpdate(int x, int y) {
    for(; x<sz(ys); x |= x+1) ys[x].push_back(y);
  }
  void init() {
    for(vi& v:ys) {
      sort(all(v));
      ft.emplace_back(sz(v));
    }
  }
  int ind(int x, int y) {
    return (int)(lower_bound(all(ys[x]), y)-ys[x].begin());
  }
  void update(int x, int y, ll dif) {
    for(; x<sz(ys); x|=x+1)
      ft[x].update(ind(x, y), dif);
  }
  ll query(int x, int y) {
    ll sum = 0;
    for(; x; x&=x-1)
      sum += ft[x-1].query(ind(x-1, y));
    return sum;
  }
};

int main(void) {
  FT st(10);
  st.update(0, 1);
  st.update(2, 1);
  cout<<st.query(3);
  return 0;
}