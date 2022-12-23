#include<bits/stdc++.h>
using namespace std;
#define sz(x) ((int)(x).size())
#define err(...) fprintf(stderr, __VA_ARGS__)
typedef vector<int> poly;
const int N=4e5+10, P=998244353;
int inv[N];
int qmi(int x, int y = P-2) {
  int ans = 1;
  for(;y;y>>=1, x=1ll*x*x%P) if(y&1)
      ans = 1ll*ans*x%P;
  return ans;
}
namespace core {
  int a[N], b[N], w[N], rev[N];
  void ntt(int *a, int len) {
    for(int i=1;i<len;++i) if(i>rev[i])
      swap(a[i], a[rev[i]]);
    for(int d=1;d<len;d<<=1)
      for(int m=d<<1,i=0;i<len;i+=m)
        for(int j=0;j<d;++j) {
          int x = a[i+j], y = 1ll*a[i+j+d]*w[len/m*j]%P;
          a[i+j] = (x+y>=P ? x+y-P : x+y);
          a[i+j+d] = (x-y<0 ? x-y+P : x-y);
        }
  }
}

poly operator*(const poly &va, const poly &vb) {
  using namespace core;
  int len = 1;
  while(len < sz(va) + sz(vb) - 1) len <<= 1;
  for(int i=0;i<len;++i) a[i] = (i<sz(va)? va[i] : 0);
  for(int i=0;i<len;++i) b[i] = (i<sz(vb)? vb[i] : 0);
  for(int i=1;i<len;++i) rev[i] = rev[i>>1] >> 1 | (i&1?len>>1:0);
  w[0] = 1;
  w[1] = qmi(3, (P-1)/len);
  for(int i=2;i<len;++i) w[i] = 1ll*w[i-1]*w[1]%P;
  ntt(a, len); ntt(b, len);
  for(int i=0;i<len;++i) a[i] = 1ll*a[i]*b[i]%P;
  reverse(a+1, a+len); ntt(a, len);
  poly c(sz(va)+sz(vb)-1);
  for(int i=0, invlen=qmi(len);i<sz(c);++i)
    c[i] = 1ll*a[i]*invlen%P;
  return c;
}

poly fix(poly a, int n) {
  a.resize(n);
  return a;
}

poly invp(poly f, int n) {
  poly g(1, qmi(f[0]));
  while(sz(g)<n) {
    int nlen = min<int>(sz(g)<<1, n);
    poly tmp(fix(fix(f, nlen)*g, nlen));
    for(int i=0;i<nlen;++i) tmp[i] = (P-tmp[i]+(i==0?2:0)%P);
    g = fix(g*tmp, nlen);
  }
  return g;
}

poly deri(poly f) {
  for(int i=1;i<sz(f);++i) f[i] = 1ll*f[i]*i%P;
  f.erase(f.begin());
  return f;
}

poly inte(poly f) {
  f.insert(f.begin(), 0);
  for(int i=1;i<sz(f);++i) f[i] = 1ll*f[i]*inv[i]%P;
  return f;
}

poly logn(poly f, int n) {
  return inte(fix(deri(f)*invp(f, n-1), n-1));
}

poly exp(poly f, int n) {
  f.resize(n);
  poly g(1, 1);
  while(sz(g) < n) {
    int nlen = min<int>(sz(g)<<1, n);
    poly tmp = logn(g, nlen);
    for(int i=0;i<nlen;++i) tmp[i] = (f[i] - tmp[i] + !i + P) % P;
    g = fix(g*tmp, nlen);
  }
  return g;
}
int n;
int main() {
  inv[0] = inv[1] = 1;
  for(int i=2;i<N;++i)inv[i] = 1ll*inv[P%i]*(P-P/i)%P;
  scanf("%d", &n);
  poly a(n);
  for(int i=0;i<n;++i) scanf("%d", &a[i]);
  a = exp(a, n);
  for(int i=0;i<sz(a);++i) printf("%d ", a[i]);
  printf("\n%d\n", inv[2]*3ll%P);
  printf("%d\n", inv[6]);
  printf("%d\n", inv[24]);
}