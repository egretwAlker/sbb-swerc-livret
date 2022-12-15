#include<cstdio>
#include<vector>
#include<complex>
using namespace std;
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i=a;i<(b);++i)
#define all(x) begin(x), end(x)
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

typedef complex<double> C;
typedef vector<double> vc;

void fft(vector<C>& a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1);
  static vector<C> rt(2, 1);
  for(int k=2;k<n;k*=2) {
    R.resize(n); rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L)/k);
    rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2]*x : R[i/2];
  }
  vi rev(n);
  rep(i, 0, n) rev[i] = (rev[i/2] | (i&1)<<L) / 2;
  rep(i, 0, n) if(i < rev[i]) swap(a[i], a[rev[i]]);
  for(int k=1;k<n;k*=2)
    for(int i=0;i<n;i+=2*k) rep(j, 0, k) {
      C z = rt[j+k]*a[i+j+k];
      a[i+j+k] = a[i+j] - z;
      
    }
}

int main(void) {
  return 0;
}