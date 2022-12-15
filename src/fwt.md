Isomorphisms of rings

or operation

$$
\tilde f(x) = \sum_{y\subset x} f(y)
$$

xor operation

$$
\tilde f(x) = \sum_{y} (-1)^{|x\& y|}f(y)
$$

https://codeforces.com/contest/662/problem/C

```cpp
#include<stdio.h>

#define M 1000001
#define N 20
#define Q (1<<N)
#define lb(x) ((x)&(-x))
#define err(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

int n, m, B;
int x[M];
char s[M];
ll f[Q], g[Q];

void fwt(ll *f) {
  for(int i=1;i<=B;i<<=1) {
    for(int j=0;j<=B;++j) {
      if(j&i) {
        f[j] += f[j^i];
        f[j^i] = 2*f[j^i] - f[j];
      }
    }
  }
}

void dfwt(ll *f) {
  for(int i=1;i<=B;i<<=1) {
    for(int j=0;j<=B;++j) {
      if(j&i) {
        f[j] = (f[j]-f[j^i])>>1;
        f[j^i] += f[j];
      }
    }
  }
}

int main(void) {
  scanf("%d%d", &n, &m);
  for(int i=0;i<n;++i) {
    scanf("%s", s);
    for(int j=0;j<m;++j) {
      x[j] = (x[j]<<1)^(s[j]-'0');
    }
  }
  for(int i=0;i<m;++i) {
    ++f[x[i]];
  }
  B = (1<<n)-1;
  for(int i=1;i<=B;++i) {
    g[i] = g[i^lb(i)]+1;
  }
  for(int i=0;i<=B;++i) {
    if(n-g[i] < g[i])
      g[i] = n-g[i];
  }

  fwt(f);
  fwt(g);
  for(int i=0;i<=B;++i)
    f[i] *= g[i];
  dfwt(f);
  ll mn=f[0];
  for(int i=0;i<=B;++i)
    if(mn>f[i])
      mn = f[i];
  printf("%lld", mn);
  return 0;
}
```